#include "Span.hpp"

#include <algorithm>
Span::Span() : _N(0)
{
}
Span::Span(unsigned int N) : _N(N)
{
}
Span::Span(const Span &other) : _N(other._N), _numbers(other._numbers)
{
}
Span &Span::operator=(const Span &other)
{
    if (this != &other)
    {
        _N = other._N;
        _numbers = other._numbers;
    }
    return *this;
}
Span::~Span()
{
}
void Span::addNumber(int n)
{
    if (_numbers.size() >= _N)
        throw FullException();
    _numbers.push_back(n);
}
void Span::addNumber(std::vector<int>::iterator first, std::vector<int>::iterator last)
{
    if (_numbers.size() + std::distance(first, last) > _N)
        throw FullException();
    _numbers.insert(_numbers.end(), first, last);
}
unsigned int Span::shortestSpan()
{
    if (_numbers.size() < 2)
        throw NoSpanException();
    std::vector<int> it = _numbers;
    std::sort(it.begin(), it.end());

    unsigned int min = static_cast<unsigned int>(it[1]) - static_cast<unsigned int>(it[0]);
    for (unsigned int i = 2; i < it.size(); i++)
    {
        unsigned int diff = static_cast<unsigned int>(it[i]) - static_cast<unsigned int>(it[i - 1]);
        if (diff < min)
            min = diff;
    }
    return min;
}
unsigned int Span::longestSpan()
{
    if (_numbers.size() < 2)
        throw NoSpanException();
    int min = *std::min_element(_numbers.begin(), _numbers.end());
    int max = *std::max_element(_numbers.begin(), _numbers.end());
    unsigned int result = static_cast<unsigned int>(max) - static_cast<unsigned int>(min);
    return (result);
}
const char *Span::FullException::what() const throw()
{
    return ("Container is full");
}

const char *Span::NoSpanException::what() const throw()
{
    return ("Not enough numbers in container");
}
