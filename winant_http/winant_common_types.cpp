/*
 @ 0xCCCCCCCC
*/

#include "winant_http/winant_common_types.h"

#include "kbase/error_exception_util.h"

#include "winant_http/winant_utils.h"

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

// -*- Parameters -*-

Parameters& Parameters::Add(const Parameter& param)
{
    ENSURE(CHECK, !param.first.empty()).Require();
    params.push_back(param);
    return *this;
}

std::string Parameters::ToContent() const
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

}   // namespace wat
