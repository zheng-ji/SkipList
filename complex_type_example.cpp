#include "SkipList.h"
#include <iostream>
using namespace std;

clasl Score {
    public:
        int num; 

        Score() {
            num = 0;
        }

        Score(int n) {
            num = n;
        }

        Score(const Score & other) {
            num = other.num;
        }

        Score& operator= (const Score& other) {
            this->num = other.num;
            return *this;
        }

        friend bool operator< (const Score & lhs, const Score & rhs) {
            return lhs.num < rhs.num;
        }

        friend bool operator== (const Score & lhs, const Score & rhs) {
            return lhs.num == rhs.num;
        }

        friend bool operator!= (const Score &lhs, const Score & rhs) {
            return lhs.num != rhs.num;
        }

        friend ostream & operator << (ostream & os, const Score &s) {
            os << s.num ;
            return os;
        }
};


int main() {
    SkipList<Score> sl;
    sl.Print();

    Score score1(3);
    Score score2(5);
    Score score3(2);
    sl.Insert(score1);
    sl.Insert(score2);
    sl.Insert(score3);

    if (sl.Contains(score2)) {
        cout << "score2 in list" << endl;
    }

    sl.Print();

    sl.Erase(score2);
    sl.Print();

    if (!sl.Contains(score2))
        cout << "score2 has been deleted" << endl;

    return 0;
}
