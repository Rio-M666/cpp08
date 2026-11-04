#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <iterator>
#include <exception>
#include <vector>
class Span
{
private:
    unsigned int _N;
    std::vector<int> _numbers;

public:
    Span();
    Span(unsigned int N);
    Span(const Span &other);
    Span &operator=(const Span &other);
    ~Span();
    void addNumber(int n);
    unsigned int shortestSpan();
    unsigned int longestSpan();
    void addNumber(std::vector<int>::iterator first, std::vector<int>::iterator last);

    class FullException : public std::exception
    {
    public:
        virtual const char *what() const throw();
    };

    class NoSpanException : public std::exception
    {
    public:
        virtual const char *what() const throw();
    };
};

#endif
