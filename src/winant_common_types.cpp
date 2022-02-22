/*
 @ 0xCCCCCCCC
*/

#include "winant_http/winant_common_types.h"

#include <numeric>
#include <random>

#include "kbase/error_exception_util.h"
#include "kbase/string_format.h"

#include "winant_http/winant_utils.h"

namespace {

const wchar_t kContentTypeURLEncoded[] = L"Content-Type: application/x-www-form-urlencoded\r\n";
const wchar_t kContentTypeJSON[] = L"Content-Type: application/json\r\n";
const wchar_t kContentMultipart[] = L"Content-Type: multipart/form-data; boundary=";

std::string GenerateMultipartBoundary()
{
    const char* kBoundaryPrefix = "---------------------------";

    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<> dist;

    int r0 = dist(engine);
    int r1 = dist(engine);

    return kbase::StringPrintf("%s%08X%08X", kBoundaryPrefix, r0, r1);
}

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

// -*- JSONContent -*-

RequestContent JSONContent::ToString() const
{
    return {kContentTypeJSON, data};
}

// -*- Multipart -*-

Multipart& Multipart::AddPart(Value value)
{
    values.push_back(std::move(value));

    return *this;
}

Multipart& Multipart::AddPart(const File& file)
{
    files.push_back(file);

    return *this;
}

Multipart& Multipart::AddPart(File&& file)
{
    files.push_back(std::move(file));

    return *this;
}

RequestContent Multipart::ToString() const
{
    auto boundary = GenerateMultipartBoundary();

    std::wstring content_type(kContentMultipart);
    content_type.append(kbase::ASCIIToWide(boundary)).append(L"\r\n");

    size_t reserved_size = 128U * files.size();
    for (const auto& file : files) {
        reserved_size += file.data.size();
    }

    std::string data;
    data.reserve(reserved_size);

    for (const auto& value : values) {
        data.append("--").append(boundary).append("\r\n");
        data.append("Content-Disposition: form-data; ")
            .append("name=\"").append(value.first).append("\"\r\n\r\n")
            .append(value.second).append("\r\n");
    }

    for (const auto& file : files) {
        data.append("--").append(boundary).append("\r\n");
        data.append("Content-Disposition: form-data; ")
            .append("name=\"").append(file.name).append("\"; ")
            .append("filename=\"").append(file.filename).append("\"\r\n");
        data.append("Content-Type: ").append(file.mime_type).append("\r\n\r\n");
        data.append(file.data).append("\r\n");
    }

    data.append("--").append(boundary).append("--\r\n");

    return {content_type, std::move(data)};
}

}   // namespace wat
