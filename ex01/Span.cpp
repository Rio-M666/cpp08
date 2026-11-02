#include "Span.hpp"

Span::Span() : _N(0)
{
}
Span::Span(unsigned int N) : _N(N)
{
}
Span::Span(const Span &other) : _N(other._N)
{
}
void Span::addNumber(int n)
{
    if (_numbers.size() >= _N)
        throw FullExeption();
    _numbers.push_back(n);
}
void Span::addNumber(std::vector<int>::iterator first, std::vector<int>::iterator last)
{
    if (_numbers.size() + std::distance(first, last) > _N)
        throw FullExeption();
    _numbers.insert(_numbers.end(), first, last);
}
int Span::shortestSpan()
{
    if (_numbers.size() < 2)
        throw NoSpanExeption();
    std::vector<int> it = _numbers;
    std::sort(it.begin(), it.end());

    int min = it[1] - it[0];
    for (unsigned int i = 2; i < it.size(); i++)
    {
        if (it[i] - it[i - 1] < min)
            min = it[i] - it[i - 1];
    }
    return min;
}
int Span::longestSpan()
{
    if (_numbers.size() < 2)
        throw NoSpanExeption();
    int min = *std::min_element(_numbers.begin(), _numbers.end());
    int max = *std::max_element(_numbers.begin(), _numbers.end());
    int result = max - min;
    return (result);
}