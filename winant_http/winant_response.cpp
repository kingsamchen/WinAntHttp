/*
 @ 0xCCCCCCCC
*/

#include "winant_http/winant_response.h"

namespace wat {

HttpResponse::HttpResponse(int status_code, std::string body)
    : status_code_(status_code), body_(std::move(body))
{}

int HttpResponse::status_code() const noexcept
{
    return status_code_;
}

const std::string& HttpResponse::text() const noexcept
{
    return body_;
}

}   // namespace wat
