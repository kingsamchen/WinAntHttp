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

TEST(Posts, Post)
{
    constexpr char kRequestAddr[] = "http://127.0.0.1:5000";
    auto response = Post(Url(kRequestAddr));
    EXPECT_EQ(200, response.status_code());
    EXPECT_TRUE(!response.text().empty());
    std::cout << response.text() << std::endl;
}

TEST(Posts, UrlEncodedContent)
{
    constexpr char kRequestAddr[] = "http://127.0.0.1:5000/url-encoded-content";
    Payload content {
        {"type", "urlencoded"}, {"category", "test"}, {"data", ""}
    };
    auto response = Post(Url(kRequestAddr), content);
    EXPECT_EQ(200, response.status_code());
    EXPECT_EQ(kPassed, response.text());
}

TEST(Posts, EscapedUrlEncodedContent)
{
    constexpr char kRequestAddr[] = "http://127.0.0.1:5000/escape-test";
    auto response = Post(Url(kRequestAddr), Payload{{"data", "!@#$%^&*()_-=+~`,.<>/?;:[]{}|\\ "}});
    EXPECT_EQ(200, response.status_code());
    EXPECT_EQ(kPassed, response.text());
}

TEST(Posts, PostAsJSON)
{
    constexpr char kRequestAddr[] = "http://127.0.0.1:5000/json-test";
    JSONContent data(R"({
        "zoomLevel": 0,
        "trimOnSave": true,
        "colorTheme": "Visual Studio Dark"
    })");
    auto response = Post(Url(kRequestAddr), std::move(data));
    EXPECT_EQ(200, response.status_code());
    EXPECT_EQ(kPassed, response.text());
}

TEST(Posts, PostAsMultipart)
{
    constexpr char kRequestAddr[] = "http://127.0.0.1:5000/multipart-test";
    Multipart upload;
    Multipart::File file {"file", "test.txt", Multipart::File::kDefaultMimeType, "hello, world!"};
    upload.AddPart(std::move(file)).AddPart(Multipart::Value {"file_size", "unknown"});

    auto response = Post(Url(kRequestAddr), std::move(upload));
    EXPECT_EQ(200, response.status_code());
}

}   // namespace wat
