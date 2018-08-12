#ifndef __SKIPLIST_H__
#define __SKIPLIST_H__

#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <functional>

using namespace std;

#define MAX_LEVEL 100 

template <class T>
class SkipNode 
{
    public:

        SkipNode(int level, const T &value)
        {
            forward = new SkipNode<T> * [level + 1];
            memset(forward, 0, sizeof(SkipNode<T>*) * (level + 1));
            this->value = value;
        }

        ~SkipNode()
        {
            delete[] forward;
        }

    public:

        T value;
        SkipNode<T> **forward;
};

template <class T>
class SkipList 
{
    public:

        SkipList() 
        {
            header = new SkipNode<T>(MAX_LEVEL, T());
            level = 0;
        }

        ~SkipList()
        {
            delete header;
        }

        void Print() const;
        bool Contains(const T &) const;
        void Insert(const T &);
        void Erase(const T &);

    private:
        SkipNode<T> *header;
        int level;

        int random_level();
};

template<class T>
class Comparator : public std::binary_function<T, T, bool> 
{
    public:
        bool operator() (T t1, T t2) 
        {
            return (t1 < t2);
        }
};

template <class T>
int SkipList<T>::random_level() 
{
    int lvl = rand() / RAND_MAX;
    return lvl < MAX_LEVEL ? lvl : MAX_LEVEL;
}

template <class T>
void SkipList<T>::Print() const 
{
    const SkipNode<T> *x = header->forward[0];
    cout << "{";

    while (x != NULL) 
    {
        cout << x->value;
        x = x->forward[0];
        if (x != NULL)
            cout << ",";
    }

    cout << "}" << endl;
}

template <class T>
bool SkipList<T>::Contains(const T& Search_val) const 
{
    Comparator<T> compareTo;
    const SkipNode<T> *x = header;
    for (int i = level; i >= 0; --i) 
    {
        while (x->forward[i] != NULL && compareTo(x->forward[i]->value, Search_val)) 
        {
            x = x->forward[i];
        }
    }

    x = x->forward[0];
    return x != NULL && x->value == Search_val;
}

template <class T>
void SkipList<T>::Insert(const T &value) 
{
    SkipNode<T> *x = header;
    SkipNode<T> *update[MAX_LEVEL + 1];
    memset(update, 0, sizeof(SkipNode<T>*) * (MAX_LEVEL + 1));
    Comparator<T> compareTo;

    for (int i = level; i >= 0; --i) 
    {
        while (x->forward[i] != NULL && compareTo(x->forward[i]->value, value)) 
        {
            x = x->forward[i];
        }
        update[i] = x;
    }

    x = x->forward[0];

    if (x == NULL || x->value != value) 
    {
        int lvl = random_level();
        if (lvl > level) 
        {
            for (int i = level + 1; i <= lvl; ++i) 
            {
                update[i] = header;
            }
        }
        level = lvl;

        x = new SkipNode<T>(lvl, value);
        
        for (int i = 0; i <= lvl; ++i) 
        {
            x->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = x;
        }
    }
}

template <class T>
void SkipList<T>::Erase(const T &value) 
{
    SkipNode<T> *x = header;
    SkipNode<T> *update[MAX_LEVEL + 1];
    memset(update, 0, sizeof(SkipNode<T>*) * (MAX_LEVEL + 1));
    Comparator<T> compareTo;

    for (int i = level; i >= 0; --i) 
    {
        while (x->forward[i] != NULL && compareTo(x->forward[i]->value, value)) 
        {
            x = x->forward[i];
        }
        update[i] = x;
    }

    x = x->forward[0];

    if (x->value == value) 
    {
        for (int i = 0; i <= level; i++) 
        {
            if (update[i]->forward[i] != x) 
                break;
            update[i]->forward[i] = x->forward[i];
        }

        delete x;

        while (level > 0 && header->forward[level] == NULL)
            level --;
    }
}

#endif // __SKIPLIST_H__
