/*
 @ 0xCCCCCCCC
*/

#include "gtest/gtest.h"

#include "winant_http/winant_utils.h"

#include "kbase/string_format.h"

namespace {

struct EscapeCase {
    const char* input;
    const char* output;
};

}   // namespace

namespace wat {

TEST(WinAntUtils, EscapeUrl)
{
    const EscapeCase escape_cases[] = {
        { "foo", "foo" },
        { "foo bar", "foo%20bar" },
        { "foo++", "foo%2B%2B" }
    };

    for (const auto& item : escape_cases) {
        EXPECT_EQ(item.output, EscapeUrl(item.input));
    }

    constexpr kbase::StringView kNoEscape("ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                          "abcdefghijklmnopqrstuvwxyz"
                                          "0123456789"
                                          "-_.~");
    for (int i = 0; i < 256; ++i) {
        std::string in;
        in.push_back(i);
        std::string out = EscapeUrl(in);
        if (0 == i) {
            EXPECT_EQ(out, std::string("%00"));
        } else if (kNoEscape.find(in) == std::string::npos) {
            // Check %hex escaping
            std::string expected = kbase::StringPrintf("%%%02X", i);
            EXPECT_EQ(expected, out);
        } else {
            // No change for things in the no_escape list.
            EXPECT_EQ(out, in);
        }
    }
}

}   // namespace wat
