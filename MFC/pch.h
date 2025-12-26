#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"

// GDI+ 支持
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

// STL 容器
#include <vector>
#include <stack>
#include <memory>

#endif //PCH_H
