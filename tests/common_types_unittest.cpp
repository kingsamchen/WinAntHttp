/*
 @ 0xCCCCCCCC
*/

#include "gtest/gtest.h"

#include "winant_http/winant_common_types.h"

#include "kbase/string_util.h"

namespace wat {

TEST(TypeUrl, GeneralUsage)
{
    Url empty_url;
    EXPECT_TRUE(empty_url.empty());

    Url url("http://foobar.com");
    EXPECT_FALSE(url.empty());

    const std::string test_url = "http://foo.bar.com";
    url = Url(test_url);
    EXPECT_EQ(test_url, url.spec());
}

TEST(TypeHeaders, GeneralUsage)
{
    Headers empty_headers;
    EXPECT_TRUE(empty_headers.empty());

    Headers headers {
        {"key1", "value1"},
        {"key2", "value2"}
    };
    EXPECT_FALSE(headers.empty());

    headers = Headers {
        {"cookie", "blah"},
        {"range", "12345"}
    };
    EXPECT_FALSE(headers.HasHeader("key1"));
    EXPECT_FALSE(headers.HasHeader("key2"));

    headers.SetHeader("etag", "0xdeadbeef");
    EXPECT_TRUE(headers.HasHeader("etag"));

    std::string header_value;
    EXPECT_TRUE(headers.GetHeader("cookie", header_value));
    EXPECT_EQ(header_value, "blah");
    EXPECT_TRUE(headers.GetHeader("range", header_value));
    EXPECT_EQ(header_value, "12345");
    EXPECT_TRUE(headers.GetHeader("etag", header_value));
    EXPECT_EQ(header_value, "0xdeadbeef");
    EXPECT_FALSE(headers.GetHeader("non-exist", header_value));

    // Won't cause any trouble
    headers.RemoveHeader("non-exist");

    headers.RemoveHeader("cookie");
    EXPECT_FALSE(headers.HasHeader("cookie"));

    headers.clear();
    EXPECT_TRUE(headers.empty());
}

TEST(TypeHeaders, Iteration)
{
    Headers headers {
        {"key1", "value1"},
        {"key2", "value2"},
        {"key3", "value3"}
    };

    for (const auto& header : headers) {
        EXPECT_TRUE(!header.first.empty() && !header.second.empty());
        // Watch out if you changed literal content in headers above.
        EXPECT_EQ(header.first.back(), header.second.back());
    }
}

TEST(TypeHeaders, ToString)
{
    Headers headers {
        {"key1", "value1"},
        {"key2", ""},
        {"key3", "value3"}
    };

    const char kExpectedHeaderStr[] = "key1: value1\r\nkey2:\r\nkey3: value3\r\n\r\n";

    auto header_string = headers.ToString();
    ASSERT_TRUE(!header_string.empty());
    EXPECT_TRUE(kbase::EndsWith(header_string, "\r\n\r\n"));
    EXPECT_EQ(kExpectedHeaderStr, header_string);
}

TEST(TypeParameters, GeneralUsage)
{
    Parameters empty_params;
    EXPECT_TRUE(empty_params.empty());

    Parameters params { {"access_key", "token123"} };
    EXPECT_FALSE(params.empty());

    params.Add({"uid", "789"}).Add({"appkey", "winant http"});

    // Test multiple pairs with the same key.
    params.Add({"appkey", "backup&winant"});

    const char query_string[] =
        "access_key=token123&uid=789&appkey=winant%20http&appkey=backup%26winant";
    EXPECT_EQ(query_string, params.ToString());
}

TEST(TypeParameters, Empty)
{
    Parameters empty_params;
    EXPECT_TRUE(empty_params.empty());

    // Bypass internal empty detection.
    Parameters empty_content {{"", ""}};
    EXPECT_FALSE(empty_content.empty());
    EXPECT_TRUE(empty_content.ToString().empty());
}

TEST(TypePayload, GeneralUsage)
{
    Payload empty_payload;
    EXPECT_TRUE(empty_payload.empty());

    Payload payload {{"token", "token123"}};
    EXPECT_FALSE(payload.empty());
    payload.Add({"uid", "kcno.1"}).Add({"app", "winant http"});

    const wchar_t type[] = L"Content-Type: application/x-www-form-urlencoded\r\n";
    const char data[] = "token=token123&uid=kcno.1&app=winant%20http";
    auto content = payload.ToString();
    EXPECT_EQ(type, content.first);
    EXPECT_EQ(data, content.second);
}

}   // namespace wat
