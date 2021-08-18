#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <vector>

using namespace std;

enum class status : uint8_t {
    occupied,
    empty,
    deleted
};

template<typename V, typename K, typename hasher = std::hash<K>>
class hashtable {
    struct bucket {
        status s;
        V val;
        K key;
    };
    public:
    
    virtual bool insert(const K& key, const V& val);

    virtual void erase(const K& key, const V& val);

    virtual void operator[](const V& val);
};

template<typename V, typename K, typename hasher = std::hash<K>>
class sepchain : public hashtable<V, K, hasher> {
    vector<vector<V>> items;
    hasher h;
    public:

    bool insert(const K& key, const V& val) {
        size_t index = h(key);
        for (size_t i = 0; i < items[index].size(); i++)
        {
            if (val == items[index][i])
            {
                return false;
            }
        }
        items[index].push_back(val);
        return true;
    }

    void erase(const K& key, const V& val) {
        hasher h;
        size_t index = h(key);
        for (size_t i = 0; i < items[index].size(); i++)
        {
            if (val == items[index][i])
            {
                swap(items[index][i],items[index].back());
                items[index].pop_back();
            }
        }
    }
    
    V& operator[](const K& key) {
        hasher h;
        size_t index = h(key);
        if (!this->insert(key, nullptr))
        {
            for (size_t i = 0; i < items[index].size(); i++)
            {
                if (items[index][i] == nullptr)
                {
                    return &items[index][i];
                }
            }
        }
        return &items[index].back();
    }
};

template<typename V, typename K, typename hasher = std::hash<K>>
class quadprobe : public hashtable<V, K, hasher> {
    // vector<bucket> items;
};

template<typename V, typename K, typename hasher = std::hash<K>>
class dblhash : public hashtable<V, K, hasher> {
    // vector<bucket> items;
};

#endif