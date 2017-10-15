/*
 @ 0xCCCCCCCC
*/

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef WINANT_HTTP_WINANT_REQUEST_BUILDER_H_
#define WINANT_HTTP_WINANT_REQUEST_BUILDER_H_

#include "winant_http/winant_request.h"

namespace wat {

class HttpRequestBuilder {
public:
    explicit HttpRequestBuilder(HttpRequest::Method method) {}

    ~HttpRequestBuilder() = default;

    // TODO: Complete these.

    void SetOption(...) {}

    HttpRequest Build()
    {
        return {};
    }

private:
    HttpRequest::Method method_;
};

}   // namespace wat

#endif  // WINANT_HTTP_WINANT_REQUEST_BUILDER_H_
