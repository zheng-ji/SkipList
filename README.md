![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg) ![Build status](https://travis-ci.org/zheng-ji/skiplist.svg?branch=master)
# dpool 

使用模板化实现调表，主要特性：
- 使用简单。 
- 支撑增删改查
- 支持各种类型，包括内建或者自定义的[数据结构](https://github.com/zheng-ji/skiplist/blob/master/complex_type_example.cpp)。

## 快速上手
```C++
#include "skiplist.h"
#include <iostream>
using namespace std;

int main() {
    SkipList<int> sl;
    sl.Print();

    sl.Insert(3);
    sl.Insert(1);
    sl.Insert(0);

    if (sl.Contains(s1)) 
    {
        cout << "3 in list" << endl;
    }
    sl.Print();

    sl.Erase(s1);
    sl.Print();

    if (!sl.Contains(s1))
        cout << "3 has been deleted" << endl;
    return 0;
}
```
