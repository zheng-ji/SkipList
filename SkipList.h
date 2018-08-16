#ifndef __SKIPLIST_H__
#define __SKIPLIST_H__

#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <functional>

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

        SkipList(int max_level) 
        {
            header = new SkipNode<T>(max_level, T());
            level = 0;
            m_max_level = max_level;
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
        int m_max_level;

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
    return lvl < m_max_level ? lvl : m_max_level;
}

template <class T>
void SkipList<T>::Print() const 
{
    const SkipNode<T> *node = header->forward[0];
    std::cout << "{";

    while (node != NULL) 
    {
        std::cout << node->value;
        node = node->forward[0];
        if (node != NULL)
            std::cout << ",";
    }

    std::cout << "}" << std::endl;
}

template <class T>
bool SkipList<T>::Contains(const T& Search_val) const 
{
    Comparator<T> compareTo;
    const SkipNode<T> *node = header;
    for (int i = level; i >= 0; --i) 
    {
        while (node->forward[i] != NULL && compareTo(node->forward[i]->value, Search_val)) 
        {
            node = node->forward[i];
        }
    }

    node = node->forward[0];
    return node != NULL && node->value == Search_val;
}

template <class T>
void SkipList<T>::Insert(const T &value) 
{
    SkipNode<T> *node = header;
    SkipNode<T> *update[m_max_level + 1];
    memset(update, 0, sizeof(SkipNode<T>*) * (m_max_level + 1));
    Comparator<T> compareTo;

    for (int i = level; i >= 0; --i) 
    {
        while (node->forward[i] != NULL && compareTo(node->forward[i]->value, value)) 
        {
            node = node->forward[i];
        }
        update[i] = node;
    }

    node = node->forward[0];

    if (node == NULL || node->value != value) 
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

        node = new SkipNode<T>(lvl, value);
        
        for (int i = 0; i <= lvl; ++i) 
        {
            node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = node;
        }
    }
}

template <class T>
void SkipList<T>::Erase(const T &value) 
{
    SkipNode<T> *node = header;
    SkipNode<T> *update[m_max_level + 1];
    memset(update, 0, sizeof(SkipNode<T>*) * (m_max_level + 1));
    Comparator<T> compareTo;

    for (int i = level; i >= 0; --i) 
    {
        while (node->forward[i] != NULL && compareTo(node->forward[i]->value, value)) 
        {
            node = node->forward[i];
        }
        update[i] = node;
    }

    node = node->forward[0];

    if (node->value == value) 
    {
        for (int i = 0; i <= level; i++) 
        {
            if (update[i]->forward[i] != node) 
                break;
            update[i]->forward[i] = node->forward[i];
        }

        delete node;

        while (level > 0 && header->forward[level] == NULL)
            level --;
    }
}

#endif // __SKIPLIST_H__
