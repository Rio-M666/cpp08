#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <stdexcept>
#include <algorithm>

template <typename T>
typename T::iterator easyfind(T &container, int value)
{
    typename T::iterator it;
    it = std::find(container.begin(), container.end(), value);
    if (it == container.end())
        throw std::out_of_range("Number not found");
    return it;
}

#endif
