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

template<typename K, typename V, typename hasher = std::hash<K>>
class sepchain{
    vector<vector<pair<K,V>>> items;
    hasher h;
    size_t numItems,index;

    void rehash_grow() {
        vector<vector<pair<K,V>>> oldItems = items;
        items.clear();
        items.resize(2 * oldItems.size());

        for (size_t i = 0; i < oldItems.size(); i++)
        {
            for (size_t j = 0; j < oldItems[i].size(); j++)
            {
                insert(oldItems[i][j].first,oldItems[i][j].second);
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
        index = h(key) % items.size();
        for (size_t i = 0; i < items[index].size(); i++)
        {
            if (key == items[index][i].first)
            {
                return false;
            }
        }
        items[index].push_back({key,val});
        numItems++;
        if (items.size() / numItems == 2)
        {
            rehash_grow();
        }
        
        return true;
    }

    void erase(const K& key, const V& val) {
        index = h(key) % items.size();
        for (size_t i = 0; i < items[index].size(); i++)
        {
            if (val == items[index][i].second)
            {
                swap(items[index][i],items[index].back());
                items[index].pop_back();
                numItems--;
            }
        }
    }
    
    V& operator[](const K& key) {
        index = h(key) % items.size();
        V def;
        this->insert(key,def);
        for (size_t i = 0; i < items[index].size(); i++)
        {
            if (items[index][i].first == key)
            {
                return items[index][i].second;
            }
            
        }
        return items[index].back().second;
    }
};

template<typename K, typename V, typename hasher = std::hash<K>>
class quadprobe {
    struct bucket {
        status s = status::occupied;
        V val;
        K key;
    };
    vector<bucket> items;
    size_t numItems,index;
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
        index = h(key) % items.size();
        while (items[index].s == status::occupied)
        {
            if (items[index].key == key)
            {
                return false;
            }
            
            index += h(key) * h(key) % items.size();
        }
        bucket b;
        b.val = val;
        b.key = key;
        b.s = status::occupied;

        items[index] = b;
        numItems++;

        if (items.size() / numItems == 2)
        {
            rehash_grow();
        }
        
        return true;
    }

    void erase(const K& key) {
        index = h(key) % items.size();
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
        index = h(key) % items.size();
        V def;
        this->insert(key,def);
        return items[index].val;
    }

};

template<typename K, typename V, typename hasher = std::hash<K>>
class dblhash {
    struct bucket {
        status s = status::occupied;
        V val;
        K key;
    };
    vector<bucket> items;
    size_t numItems,index;
    hasher h,h2;
    
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

    dblhash() {
        items.resize(16);
        numItems = 0;
    }

    size_t size() {
        return numItems;
    }

    bool insert(const K& key, const V& val) {
        index = h(key) % items.size();
        size_t c = 1;
        while (items[index].s == status::occupied)
        {
            if (items[index].key == key)
            {
                return false;
            }
            
            index += h2(key) * c % items.size();
            c++;
        }
        bucket b;
        b.val = val;
        b.key = key;
        b.s = status::occupied;

        items[index] = b;
        numItems++;

        if (items.size() / numItems == 2)
        {
            rehash_grow();//
        }
        
        return true;
    }

    void erase(const K& key) {
        index = h(key) % items.size();
        size_t c = 1;
        while (items[index].s == status::occupied)
        {
            if (items[index].key == key)
            {
                items[index].s = status::deleted;
                numItems--;
            }
            
            index += h2(key) * c % items.size();
            c++;
        }
    }

    V& operator[](const K& key) {
        index = h(key) % items.size();
        V def;
        this->insert(key,def);
        return items[index].val;
    }

};
#endif