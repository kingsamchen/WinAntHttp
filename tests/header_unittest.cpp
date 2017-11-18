/*
 @ 0xCCCCCCCC
*/

#include "gtest/gtest.h"

#include "winant_http/winant_http.h"

namespace {

const char kPassed[] = "passed";

}   // namespace

namespace wat {

TEST(RequestHeader, GeneralUsage)
{
    constexpr char kRequestAddr[] = "http://127.0.0.1:5000/basic-headers";
    Headers headers {
        {"category", "test"},
        {"buvid", "0xDEADBEEF"},
        {"expires", "2020-01-01"}
    };

    auto response = Get(Url(kRequestAddr), headers);
    EXPECT_EQ(200, response.status_code());
    EXPECT_EQ(kPassed, response.text());
}

}   // namespace wat
