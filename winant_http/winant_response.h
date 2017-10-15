/*
 @ 0xCCCCCCCC
*/

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef WINANT_HTTP_WINANT_RESPONSE_H_
#define WINANT_HTTP_WINANT_RESPONSE_H_

#include <string>

namespace wat {

class HttpResponse {
public:
    HttpResponse() = default;

    ~HttpResponse() = default;

private:
    int status_code_;
    std::string text_;
};

}   // namespace wat

#endif  // WINANT_HTTP_WINANT_RESPONSE_H_
