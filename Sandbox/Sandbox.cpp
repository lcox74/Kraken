// Sandbox.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include <Kraken.h>

int main()
{
    auto test1 = Kraken::LinkedList<int>();
    test1.insert(1);
    test1.insert(2);
    test1.insert(3);

    auto test2 = Kraken::LinkedList<char>();
    test2.append('a');
    test2.append('b');
    test2.append('c');

    test2.remove('b');
    
    auto test3 = Kraken::LinkedList<std::string>();
    test3.insert("Olivia");
    test3.insert("James");
    test3.insert("Nat");
}
