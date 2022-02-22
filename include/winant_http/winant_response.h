/*
 @ 0xCCCCCCCC
*/

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef WINANT_HTTP_WINANT_RESPONSE_H_
#define WINANT_HTTP_WINANT_RESPONSE_H_

#include <string>

#include "kbase/basic_macros.h"

#include "winant_http/winant_common_types.h"

namespace wat {

class HttpResponse {
public:
    HttpResponse(int status_code, Headers headers, std::string body);

    ~HttpResponse() = default;

    HttpResponse(const HttpResponse&) = default;
	HttpResponse &operator=(const HttpResponse&) = default;

	HttpResponse(HttpResponse&&) = default;
	HttpResponse &operator=(HttpResponse &&) = default;

    int status_code() const noexcept;

    const Headers& headers() const noexcept;

    const std::string& text() const noexcept;

private:
    int status_code_;
    Headers headers_;
    std::string body_;
};

}   // namespace wat

#endif  // WINANT_HTTP_WINANT_RESPONSE_H_
