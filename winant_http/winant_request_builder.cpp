/*
 @ 0xCCCCCCCC
*/

#include "winant_http/winant_request_builder.h"

#include "kbase/error_exception_util.h"

namespace {

using wat::Parameters;
using wat::Url;

Url CanonicalizeUrl(const Url& original, const Parameters& params)
{
    std::string canonilized = original.spec();
    if (!params.empty()) {
        canonilized.append(1, '?').append(params.ToString());
    }

    return Url(canonilized);
}

}   // namespace

namespace wat {

HttpRequestBuilder::HttpRequestBuilder(HttpRequest::Method method)
    : method_(method), content_type_(ContentType::None)
{}

void HttpRequestBuilder::SetOption(Url url)
{
    ENSURE(CHECK, !url.empty()).Require();
    url_ = std::move(url);
}

void HttpRequestBuilder::SetOption(Headers headers)
{
    ENSURE(CHECK, !headers.empty()).Require();
    headers_ = std::move(headers);
}

void HttpRequestBuilder::SetOption(Parameters params)
{
    ENSURE(CHECK, !params.empty()).Require();
    parameters_ = std::move(params);
}

void HttpRequestBuilder::SetOption(Payload payload)
{
    ENSURE(CHECK, method_ == HttpRequest::Method::Post).Require();
    ENSURE(CHECK, content_type_ == ContentType::None).Require();
    ENSURE(CHECK, !payload.empty()).Require();

    payload_ = std::move(payload);
    content_type_ = ContentType::Payload;
}

void HttpRequestBuilder::SetOption(JSONContent json)
{
    ENSURE(CHECK, method_ == HttpRequest::Method::Post).Require();
    ENSURE(CHECK, content_type_ == ContentType::None).Require();
    ENSURE(CHECK, !json.empty()).Require();

    json_ = std::move(json);
    content_type_ = ContentType::JSON;
}

void HttpRequestBuilder::SetOption(Multipart multipart)
{
    ENSURE(CHECK, method_ == HttpRequest::Method::Post).Require();
    ENSURE(CHECK, content_type_ == ContentType::None).Require();
    ENSURE(CHECK, !multipart.empty()).Require();

    multipart_ = std::move(multipart);
    content_type_ = ContentType::Multipart;
}

void HttpRequestBuilder::SetRequestContent(HttpRequest& request) const
{
    switch (content_type_) {
        case ContentType::Payload:
            request.SetPayload(payload_);
            break;

        case ContentType::JSON:
            request.SetJSON(json_);
            break;

        case ContentType::Multipart:
            request.SetMultipart(multipart_);
            break;

        default:
            ENSURE(CHECK, kbase::NotReached())(kbase::enum_cast(content_type_)).Require();
    }
}

HttpRequest HttpRequestBuilder::Build() const
{
    HttpRequest request(method_, CanonicalizeUrl(url_, parameters_));

    if (!headers_.empty()) {
        request.SetHeaders(headers_);
    }

    if (content_type_ != ContentType::None) {
        SetRequestContent(request);
    }

    return request;
}

}   // namespace wat
