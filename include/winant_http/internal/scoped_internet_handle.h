/*
 @ 0xCCCCCCCC
*/

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef WINANT_HTTP_INTERNAL_SCOPED_INTERNET_HANDLE_H_
#define WINANT_HTTP_INTERNAL_SCOPED_INTERNET_HANDLE_H_

#include <Windows.h>
#include <WinInet.h>

#include "kbase/scoped_handle.h"

namespace wat {
namespace internal {

struct InternetHandleTraits {
    using Handle = HINTERNET;

    InternetHandleTraits() = delete;

    ~InternetHandleTraits() = delete;

    static Handle NullHandle() noexcept
    {
        return nullptr;
    }

    static bool IsValid(Handle handle) noexcept
    {
        return handle != nullptr;
    }

    static void Close(Handle handle) noexcept
    {
        InternetCloseHandle(handle);
    }
};

using ScopedInternetHandle = kbase::GenericScopedHandle<InternetHandleTraits>;

}   // namespace internal
}   // namespace wat

#endif  // WINANT_HTTP_INTERNAL_SCOPED_INTERNET_HANDLE_H_
