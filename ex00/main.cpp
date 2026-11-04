
#include <iostream>
#include <vector>
#include <list>
#include <exception>
#include "easyfind.hpp"

int main()
{
    std::vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(20);

    try
    {
        std::vector<int>::iterator it = easyfind(v, 20);
        std::cout << *it << std::endl;
        it = easyfind(v, 999);
        std::cout << *it << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::list<int> l;

    l.push_back(5);
    l.push_back(15);
    l.push_back(25);

    std::list<int>::iterator it = easyfind(l, 15);
    std::cout << *it << std::endl;

    return 0;
}
