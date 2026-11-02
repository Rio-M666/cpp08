#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <iterator>
class Span
{
private:
    unsigned int _N;
    std::vector<int> _numbers;

public:
    Span();
    Span(unsigned int N);
    Span(const Span &other);
    void addNumber(int n);
    int shortestSpan();
    int longestSpan();
    void addNumber(std::vector<int>::iterator first, std::vector<int>::iterator last);

    class FullExeption : public std::exception
    {
    public:
        virtual const char *what() const throw();
    };

    class NoSpanExeption : public std::exception
    {
    public:
        virtual const char *what() const throw();
    };
};

#endif
