#include "hashtable.h"
#include <cassert>

/*                      HASH TABLE SNAPSHOT
*   The purpose of this file is to demonstrate my understanding
*   of the c++ STL unordered_map. This will include the following 
*   collision resolution methods: seperate chaining, quadratic 
*   probing and double hashing. These three methods are 
*   fundementally different in concept, and are therefore included
*   in this snapshot. Not included is linear probing due to it’s 
*   similarity and inferiority to quadratic probing
*/

int main() {
    sepchain<string, int> hash1;
    assert(hash1["foo"] == 0);
    hash1["foo"] = 1;
    assert(hash1["foo"] == 1);
    assert(hash1.size() == 1);

    quadprobe<string, int> hash2;
    assert(hash2["foo"] == 0);
    hash2["foo"] = 1;
    assert(hash2["foo"] == 1);
    assert(hash2.size() == 1);

    dblhash<string, int> hash3;
    assert(hash3["foo"] == 0);
    hash3["foo"] = 1;
    assert(hash3["foo"] == 1);
    assert(hash3.size() == 1);

    return 0;
}