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
class sepchain{
    vector<vector<V>> items;
    hasher h;
    size_t numItems;

    void rehash_grow() {
        vector<vector<V>> oldItems = items;
        items.clear();
        items.resize();

        hasher h;

        for (size_t i = 0; i < oldItems.size(); i++)
        {
            for (size_t j = 0; j < oldItems[i].size(); j++)
            {
                items.insert(oldItems[i][j]);
            }
            
        }
        
    }

    public:

    sepchain() {
        items.resize(16);
        numItems = 0;
    }

    size_t size() {
        return numItems;
    }

    bool insert(const K& key, const V& val) {
        size_t index = h(key) % this->size();
        for (size_t i = 0; i < items[index].size(); i++)
        {
            if (val == items[index][i])
            {
                return false;
            }
        }
        items[index].push_back(val);
        numItems++;
        if (items.size() / numItems == 2)
        {
            rehash_grow();
        }
        
        return true;
    }

    void erase(const K& key, const V& val) {
        hasher h;
        size_t index = h(key) % this->size();
        for (size_t i = 0; i < items[index].size(); i++)
        {
            if (val == items[index][i])
            {
                swap(items[index][i],items[index].back());
                items[index].pop_back();
                numItems--;
            }
        }
    }
    
    V& operator[](const K& key) {
        hasher h;
        size_t index = h(key) % this->size();
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
class quadprobe {
    struct bucket {
        status s;
        V val;
        K key;
    };
    vector<bucket> items;
};

template<typename V, typename K, typename hasher = std::hash<K>>
class dblhash {
    struct bucket {
        status s;
        V val;
        K key;
    };
    vector<bucket> items;
};

#endif