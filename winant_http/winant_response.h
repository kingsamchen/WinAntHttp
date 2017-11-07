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

namespace wat {

class HttpResponse {
public:
    HttpResponse(int status_code, std::string body);

    ~HttpResponse() = default;

    DEFAULT_COPY(HttpResponse);

    DEFAULT_MOVE(HttpResponse);

    int status_code() const noexcept;

    const std::string& text() const noexcept;

private:
    int status_code_;
    std::string body_;
};

}   // namespace wat

#endif  // WINANT_HTTP_WINANT_RESPONSE_H_
