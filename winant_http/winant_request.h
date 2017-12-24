/*
 @ 0xCCCCCCCC
*/

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef WINANT_HTTP_WINANT_REQUEST_H_
#define WINANT_HTTP_WINANT_REQUEST_H_

#include "kbase/basic_macros.h"
#include "kbase/basic_types.h"

#include "winant_http/internal/scoped_internet_handle.h"
#include "winant_http/winant_common_types.h"
#include "winant_http/winant_response.h"

namespace wat {

class HttpRequest {
public:
    enum class Method : size_t {
        Get = 0,
        Post,
        Head
    };

    HttpRequest(Method method, const Url& url);

    ~HttpRequest() = default;

    DISALLOW_COPY(HttpRequest);

    DEFAULT_MOVE(HttpRequest);

    void SetLoadFlags(LoadFlags flags);

    void SetHeaders(const Headers& headers);

    void SetPayload(const Payload& payload);

    void SetJSON(const JSONContent& json);

    void SetMultipart(const Multipart& multipart);

    void SetReadResponseHandler(ReadResponseHandler handler);

    HttpResponse Start();

private:
    void SetContent(RequestContent&& content);

private:
    Method method_;
    Url canonicalized_url_;
    LoadFlags load_flags_;
    std::string body_;
    ReadResponseHandler read_response_handler_;
    internal::ScopedInternetHandle inet_env_;
    internal::ScopedInternetHandle conn_session_;
    internal::ScopedInternetHandle request_;
};

inline std::ostream& operator<<(std::ostream& out, HttpRequest::Method method)
{
    out << kbase::enum_cast(method);
    return out;
}

}   // namespace wat

#endif  // WINANT_HTTP_WINANT_REQUEST_H_
