#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <exception>
#include <algorithm>

class notfoundExeption : public std::exception
{
public:
    virtual const char *what() const throw()
    {
        return ("Number not found");
    }
};

template <typename T>
typename T::iterator easyfind(T &container, int value)
{
    typename T::iterator it;
    it = std::find(container.begin(), container.end(), value);
    if (it == container.end())
        throw notfoundExeption();
    return it;
}

#endif
