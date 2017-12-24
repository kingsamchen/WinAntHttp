/*
 @ 0xCCCCCCCC
*/

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef WINANT_HTTP_WINANT_REQUEST_BUILDER_H_
#define WINANT_HTTP_WINANT_REQUEST_BUILDER_H_

#include "winant_http/winant_common_types.h"
#include "winant_http/winant_request.h"

namespace wat {

class HttpRequestBuilder {
private:
    enum class ContentType {
        None,
        Payload,
        JSON,
        Multipart
    };

public:
    explicit HttpRequestBuilder(HttpRequest::Method method);

    ~HttpRequestBuilder() = default;

    void SetOption(Url url);

    void SetOption(Headers headers);

    void SetOption(LoadFlags flags);

    void SetOption(Parameters params);

    void SetOption(Payload payload);

    void SetOption(JSONContent json);

    void SetOption(Multipart multipart);

    HttpRequest Build() const;

private:
    void SetRequestContent(HttpRequest& request) const;

private:
    HttpRequest::Method method_;
    Url url_;
    Headers headers_;
    LoadFlags load_flags_;
    Parameters parameters_;
    ContentType content_type_;
    Payload payload_;
    JSONContent json_;
    Multipart multipart_;
};

}   // namespace wat

#endif  // WINANT_HTTP_WINANT_REQUEST_BUILDER_H_
