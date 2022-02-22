/*
 @ 0xCCCCCCCC
*/

#include "winant_http/winant_utils.h"

#include "kbase/string_format.h"

namespace wat {

std::string EscapeUrl(kbase::StringView str)
{
    constexpr kbase::StringView kUnreserved("ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                            "abcdefghijklmnopqrstuvwxyz"
                                            "0123456789"
                                            "-_.~");

    std::string escaped;
    for (auto ch : str) {
        if (kUnreserved.find_first_of(ch) != kbase::StringView::npos) {
            escaped.push_back(ch);
        } else {
            escaped.append(1, '%')
                   .append(kbase::StringPrintf("%.2X", static_cast<unsigned char>(ch)));
        }
    }

    return escaped;
}

}   // namespace wat
