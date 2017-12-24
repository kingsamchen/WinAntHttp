WinAntHttp
===

WinAntHttp is an ant-weight http client based on Windows WinINet APIs, and its interfaces are inspired by [Python Requests](https://github.com/kennethreitz/requests).

A quick view of GET request:

```c++
#include "winant_http/winant_http.h"

auto response = wat::Get(Url("https://httpbin.org/get"),
                         Parameters{{"key", "value"}, {"type", "test"}});
assert(response.status_code() == 200);
assert(response.headers().HasHeader("Content-Type"));   // response header
assert(!response.text().empty());   // response body
```

More details of the usage can be found under folder `test`.

Build Instructions
===

**Requirements**

- Windows 7, or later
- Visual Studio 2017 (Visual Studio 2015 or other compilers that support C++ 14 should also work)

**Build Steps**

Clone the repository using `git clone https://github.com/kingsamchen/WinAntHttp.git --recursive`

Open the solution and build the solution.
