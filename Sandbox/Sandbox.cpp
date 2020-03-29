// Sandbox.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#define KRAKEN_DEBUG
#include <Kraken.h>

int main()
{
    auto test1 = Kraken::LinkedList<int>();
    test1.prepend(1);
    test1.prepend(2);
    test1.prepend(3);

    test1.display_debug();

    auto test2 = Kraken::LinkedList<char>();
    test2.append('a');
    test2.append('b');
    test2.append('c');

    test2.display_debug();
    test2.remove('b');
    test2.display_debug();

    auto test3 = Kraken::LinkedList<std::string>();
    test3.append("Olivia");
    test3.append("James");
    test3.display_debug();
    test3.insert_after("Olivia", "Nat");
    test3.display_debug();
    test3.insert_before("Olivia", "Flynn");
    test3.display_debug();

    std::cout << "Test3 contains Bill? " << test3.contains("Bill") << std::endl;
    std::cout << "Test3 contains Nat? " << test3.contains("Nat") << std::endl;


}
