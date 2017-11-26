/*
 @ 0xCCCCCCCC
*/

#include "winant_http/winant_common_types.h"

#include "kbase/error_exception_util.h"
#include "kbase/string_format.h"

#include "winant_http/winant_utils.h"

namespace {

const wchar_t kContentTypeURLEncoded[] = L"Content-Type: application/x-www-form-urlencoded\r\n";

}   // namespace

namespace wat {

// -*- Headers -*-

bool Headers::HasHeader(const std::string& key) const
{
    return headers_.count(key) != 0;
}

bool Headers::GetHeader(const std::string& key, std::string& value) const
{
    auto it = headers_.find(key);
    if (it == headers_.cend()) {
        return false;
    }

    value = it->second;

    return true;
}

void Headers::SetHeader(const std::string& key, const std::string& value)
{
    headers_[key] = value;
}

void Headers::RemoveHeader(const std::string& key)
{
    headers_.erase(key);
}

std::string Headers::ToString() const
{
    std::string content;
    for (const auto& header : headers_) {
        if (header.second.empty()) {
            kbase::StringAppendPrintf(content, "%s:\r\n", header.first.c_str());
        } else {
            kbase::StringAppendPrintf(content, "%s: %s\r\n", header.first.c_str(),
                                      header.second.c_str());
        }
    }

    content.append("\r\n");

    return content;
}

// -*- Parameters -*-

Parameters& Parameters::Add(Parameter param)
{
    ENSURE(CHECK, !param.first.empty()).Require();
    params.push_back(std::move(param));
    return *this;
}

std::string Parameters::ToString() const
{
    if (params.empty()) {
        return std::string();
    }

    constexpr size_t kReservedSize = 32U;
    std::string content;
    content.reserve(kReservedSize);
    for (const auto& param : params) {
        if (!content.empty()) {
            content.append(1, '&');
        }

        content.append(EscapeUrl(param.first));
        if (!param.second.empty()) {
            content.append(1, '=').append(EscapeUrl(param.second));
        }
    }

    return content;
}

// -*- Payload -*-

Payload& Payload::Add(Argument arg)
{
    ENSURE(CHECK, !arg.first.empty()).Require();
    data.push_back(std::move(arg));
    return *this;
}

RequestContent Payload::ToString() const
{
    if (data.empty()) {
        return {};
    }

    constexpr size_t kReservedSize = 32U;
    std::string content;
    content.reserve(kReservedSize);
    for (const auto& argument : data) {
        if (!content.empty()) {
            content.append(1, '&');
        }

        content.append(EscapeUrl(argument.first));
        if (!argument.second.empty()) {
            content.append(1, '=').append(EscapeUrl(argument.second));
        }
    }

    return {kContentTypeURLEncoded, std::move(content)};
}

}   // namespace wat
