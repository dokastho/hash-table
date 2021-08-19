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
    int passedTests = 0;
    sepchain<string, int> hash1;
    cout << "Test 1\n";
    hash1["foo"] = 0;
    if (hash1["foo"] == 0)
    {
        passedTests++;
        cout << "Passed\n";
    }
    else {
        cout << "Failed\n";
        cout << "Actual: " << hash1["foo"] << endl;
        cout << "Expected: 0\n";
    }
    
    hash1["foo"] = 1;
    if (hash1["foo"] == 1)
    {
        passedTests++;
        cout << "Passed\n";
    }
    else {
        cout << "Failed\n";
        cout << "Actual: " << hash1["foo"] << endl;
        cout << "Expected: 1\n";
    }
    
    if (hash1.size() == 1)
    {
        passedTests++;
        cout << "Passed\n";
    }
    else {
        cout << "Failed Size Test\n";
        cout << "Actual: " << hash1.size() << endl;
        cout << "Expected: 1\n";
    }
    hash1.erase("foo",1);
    assert(hash1.size() == 0);

    quadprobe<string, int> hash2;
    assert(hash2["foo"] == 0);
    hash2["foo"] = 1;
    assert(hash2["foo"] == 1);
    assert(hash2.size() == 1);
    hash2.erase("foo");
    assert(hash2.size() == 0);

    dblhash<string, int> hash3;
    assert(hash3["foo"] == 0);
    hash3["foo"] = 1;
    assert(hash3["foo"] == 1);
    assert(hash3.size() == 1);
    hash3.erase("foo");
    assert(hash3.size() == 0);

    return 0;
}