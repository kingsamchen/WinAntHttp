/*
 @ 0xCCCCCCCC
*/

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef WINANT_HTTP_WINANT_REQUEST_H_
#define WINANT_HTTP_WINANT_REQUEST_H_

namespace wat {

class HttpRequest {
public:
    enum class Method : size_t {
        Get = 0,
        Post,
        Header
    };
};

}   // namespace wat

#endif  // WINANT_HTTP_WINANT_REQUEST_H_
