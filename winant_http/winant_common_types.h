/*
 @ 0xCCCCCCCC
*/

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef WINANT_HTTP_WINANT_COMMON_TYPES_H_
#define WINANT_HTTP_WINANT_COMMON_TYPES_H_

#include <map>
#include <string>
#include <vector>

#include "kbase/basic_macros.h"

namespace wat {

class Url {
public:
    Url() = default;

    explicit Url(std::string url)
        : spec_(std::move(url))
    {}

    ~Url() = default;

    DEFAULT_COPY(Url);

    DEFAULT_MOVE(Url);

    bool empty() const noexcept
    {
        return spec_.empty();
    }

    const std::string& spec() const noexcept
    {
        return spec_;
    }

private:
    std::string spec_;
};

class Headers {
public:
    using data_type = std::map<std::string, std::string>;
    using value_type = data_type::value_type;
    using iterator = data_type::iterator;
    using const_iterator = data_type::const_iterator;

    Headers() = default;

    Headers(std::initializer_list<value_type> init)
        : headers_(init)
    {}

    ~Headers() = default;

    DEFAULT_COPY(Headers);

    DEFAULT_MOVE(Headers);

    bool empty() const noexcept
    {
        return headers_.empty();
    }

    void clear()
    {
        headers_.clear();
    }

    bool HasHeader(const std::string& key) const;

    bool GetHeader(const std::string& key, std::string& value) const;

    void SetHeader(const std::string& key, const std::string& value);

    // This function does nothing if the header to be removed does not exist.
    void RemoveHeader(const std::string& key);

    iterator begin()
    {
        return headers_.begin();
    }

    const_iterator begin() const
    {
        return headers_.begin();
    }

    const_iterator cbegin() const
    {
        return headers_.cbegin();
    }

    iterator end()
    {
        return headers_.end();
    }

    const_iterator end() const
    {
        return headers_.end();
    }

    const_iterator cend() const
    {
        return headers_.cend();
    }

private:
    data_type headers_;
};

struct Parameters {
    using Parameter = std::pair<std::string, std::string>;
    using data_type = std::vector<Parameter>;

    data_type params;

    Parameters() = default;

    Parameters(std::initializer_list<data_type::value_type> init)
        : params(init)
    {}

    bool empty() const noexcept
    {
        return params.empty();
    }

    Parameters& Add(const Parameter& param);

    std::string ToContent() const;
};

}   // namespace wat

#endif  // WINANT_HTTP_WINANT_COMMON_TYPES_H_
