#include "SkipList.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    SkipList<string> sl;
    sl.Print();

    sl.Insert("hello");
    sl.Insert("world");
    sl.Insert("ok");
    sl.Insert("good");

    if (sl.Contains("world")) {
        cout << "world in list" << endl;
    }

    sl.Print();

    sl.Erase("world");
    sl.Print();

    if (!sl.Contains("world"))
        cout << "world has been deleted" << endl;

    return 0;
}
