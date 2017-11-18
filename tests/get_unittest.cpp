/*
 @ 0xCCCCCCCC
*/

#include <iostream>

#include "gtest/gtest.h"

#include "winant_http/winant_http.h"

namespace {

constexpr char kPassed[] = "passed";

}   // namespace

namespace wat {

TEST(Gets, Get)
{
    constexpr char kRequestAddr[] = "http://127.0.0.1:5000";
    auto response = Get(Url(kRequestAddr));
    EXPECT_EQ(200, response.status_code());
    EXPECT_TRUE(!response.text().empty());
    std::cout << "-> " << response.text() << std::endl;
}

TEST(Gets, NormalQueryString)
{
    constexpr char kRequestAddr[] = "http://127.0.0.1:5000/query-string";
    auto response = Get(Url(kRequestAddr), Parameters{{"key", "value"}, {"solekey", ""}});
    EXPECT_EQ(200, response.status_code());
    EXPECT_EQ(kPassed, response.text());
}

TEST(Gets, EscapedQueryString)
{
    constexpr char kRequestAddr[] = "http://127.0.0.1:5000/escape-test";
    auto response = Get(Url(kRequestAddr),
                        Parameters{{"data", "!@#$%^&*()_-=+~`,.<>/?;:[]{}|\\ "}});
    EXPECT_EQ(200, response.status_code());
    EXPECT_EQ(kPassed, response.text());
}

TEST(Gets, EmptyQueryString)
{
    constexpr char kRequestAddr[] = "http://127.0.0.1:5000/empty-query-string";
    auto response = Get(Url(kRequestAddr), Parameters{{"", ""}});
    EXPECT_EQ(200, response.status_code());
    EXPECT_EQ(kPassed, response.text());
}

}   // namespace wat
