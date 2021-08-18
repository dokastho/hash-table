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
    struct bucket {
        K key;
        vector<V> values;
    }
    vector<bucket> items;
    hasher h;
    size_t numItems;

    void rehash_grow() {
        vector<bucket> oldItems = items;
        items.clear();
        items.resize();

        for (size_t i = 0; i < oldItems.size(); i++)
        {
            for (size_t j = 0; j < oldItems[i].values.size(); j++)
            {
                insert(oldItems[i].key,oldItems[i].values[j]);
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
            if (val == items[index].values[i])
            {
                return false;
            }
        }
        items[index].values.push_back(val);
        numItems++;
        if (items.size() / numItems == 2)
        {
            rehash_grow();
        }
        
        return true;
    }

    void erase(const K& key, const V& val) {
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
        status s = status::occupied;
        V val;
        K key;
    };
    vector<bucket> items;
    size_t numItems;
    hasher h;
    
    void rehash_grow() {
        vector<bucket> oldItems = items;
        items.clear();
        items.resize(2 * oldItems.size());;

        for (size_t i = 0; i < oldItems.size(); i++)
        {
            this->insert(oldItems[i].key,oldItems[i].val);
        }
    }
    public:

    quadprobe() {
        items.resize(16);
        numItems = 0;
    }

    size_t size() {
        return numItems;
    }

    bool insert(const K& key, const V& val) {
        size_t index = h(key) % items.size();
        while (items[index].s == status::occupied)
        {
            if (items[index].key == key)
            {
                return false;
            }
            
            index += h(key) * h(hey) % items.size();
        }
        bucket b;
        b.val = val;
        b.key = key;
        b.status = status::occupied;

        items[index] = b;
        numItems++;

        if (items.size() / numItems == 2)
        {
            rehash_grow();
        }
        
        return true;
    }

    void erase(const K& key, const V& val) {
        size_t index = h(key) % items.size();
        while (items[index].s == status::occupied)
        {
            if (items[index].key == key)
            {
                items[index].s = status::deleted;
                numItems--;
            }
            
            index += h(key) * h(key) % items.size();
        }
    }

    V& operator[](const K& key) {
        size_t index = h(key) % items.size();
        if (insert(key,nullptr))
        {
            while (items[index].key != key)
            {
                index += h(key) * h(key);
            }
        }
        
        while (items[index].s == status::occupied)
        {
            if (items[index].key == key)
            {
                break;
            }
            
            index += h(key) * h(hey) % items.size();
        }
        items[index].s = status::occupied;
        numItems++;
        return &items[index].val;
    }

};

template<typename V, typename K, typename hasher = std::hash<K>>
class dblhash {
    struct bucket {
        status s;
        V val;
        K key;
    };
    vector<bucket> items;
    size_t numItems;
    hasher h;
    
    void rehash_grow() {

    }
    public:

    dblhash() {
        items.resize(16);
        numItems = 0;
    }

    size_t size() {
        return numItems;
    }

    bool insert(const K& key, const V& val) {}

    void erase(const K& key, const V& val) {}

    V& operator[](const K& key) {}
};

#endif