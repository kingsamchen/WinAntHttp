/*
 @ 0xCCCCCCCC
*/

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef WINANT_HTTP_WINANT_UTILS_H_
#define WINANT_HTTP_WINANT_UTILS_H_

#include <string>

#include "kbase/string_view.h"

namespace wat {

std::string EscapeUrl(kbase::StringView str);

}   // namespace wat

#endif  // WINANT_HTTP_WINANT_UTILS_H_
