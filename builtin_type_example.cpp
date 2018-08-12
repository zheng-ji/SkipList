#include "SkipList.h"
#include <iostream>
#include <string>

using namespace std;

int main() 
{
    int max_level = 10;
    SkipList<string> sl(max_level);

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
