![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
# SkipList

使用模板实现的跳表：
- 使用简单，只需要引入头文件 `SkipList.h`
- 支撑增删改查
- 支持各种类型: 包括内建类型, 自定义[数据结构](https://github.com/zheng-ji/skiplist/blob/master/complex_type_example.cpp)。

## Quick Start
```C++
#include "SkipList.h"
#include <iostream>
#include <string>
using namespace std;

int main() 
{
    SkipList<string> sl;

    sl.Insert("hello");
    sl.Insert("world");
    sl.Insert("ok");
    sl.Insert("good");

    if (sl.Contains("world")) 
    {
        cout << "world in list" << endl;
    }

    sl.Print();
    sl.Erase("world");
    sl.Print();
    if (!sl.Contains("world"))
        cout << "world has been deleted" << endl;

    return 0;
}
```
