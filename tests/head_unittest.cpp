/*
 @ 0xCCCCCCCC
*/

#include <iostream>

#include "gtest/gtest.h"

#include "winant_http/winant_http.h"

namespace wat {

TEST(Heads, Welcome)
{
    constexpr char kRequestAddr[] = "http://127.0.0.1:5000";
    auto response = Head(Url(kRequestAddr));
    EXPECT_EQ(200, response.status_code());
    EXPECT_TRUE(response.text().empty());
}

}   // namespace wat
