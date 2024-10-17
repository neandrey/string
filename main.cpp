#include <iostream>
#include <set>
#include "string.h"

using namespace std;

int main()
{

    multiset<String> str_set;
    for (String temp; cin >> temp;)
    {
        str_set.insert(temp);
    }

    for (auto s : str_set)
    {
        cout << s << " ";
    }
    cout << endl;

    return 0;
}
