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
    : method_(method)
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

HttpRequest HttpRequestBuilder::Build() const
{
    HttpRequest request(method_, CanonicalizeUrl(url_, parameters_));

    if (!headers_.empty()) {
        request.SetHeaders(headers_);
    }

    return request;
}

}   // namespace wat
