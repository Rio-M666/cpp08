#include "Span.hpp"
#include <cassert>
#include <climits>

static void checkNoSpan(Span &sp)
{
    bool shortestThrown = false;
    bool longestThrown = false;

    try
    {
        sp.shortestSpan();
    }
    catch (const Span::NoSpanException &)
    {
        shortestThrown = true;
    }
    try
    {
        sp.longestSpan();
    }
    catch (const Span::NoSpanException &)
    {
        longestThrown = true;
    }
    assert(shortestThrown && longestThrown);
}

static void testExceptions()
{
    Span empty(0);
    checkNoSpan(empty);
    bool fullThrown = false;
    try
    {
        empty.addNumber(1);
    }
    catch (const Span::FullException &)
    {
        fullThrown = true;
    }
    assert(fullThrown);

    Span sp(2);
    sp.addNumber(-5);
    checkNoSpan(sp);
    sp.addNumber(-5);
    assert(sp.shortestSpan() == 0 && sp.longestSpan() == 0);
    fullThrown = false;
    try
    {
        sp.addNumber(10);
    }
    catch (const Span::FullException &)
    {
        fullThrown = true;
    }
    assert(fullThrown);
}

static void testRange()
{
    std::vector<int> numbers;
    numbers.push_back(-10);
    numbers.push_back(10);
    numbers.push_back(9);

    Span sp(4);
    sp.addNumber(numbers.begin(), numbers.end());
    assert(sp.shortestSpan() == 1 && sp.longestSpan() == 20);
    sp.addNumber(numbers.begin(), numbers.begin());

    bool fullThrown = false;
    try
    {
        sp.addNumber(numbers.begin(), numbers.end());
    }
    catch (const Span::FullException &)
    {
        fullThrown = true;
    }
    assert(fullThrown);
    sp.addNumber(9);
    assert(sp.shortestSpan() == 0 && sp.longestSpan() == 20);

    numbers.clear();
    for (int i = 0; i < 10000; ++i)
        numbers.push_back(i * 2);
    Span large(10000);
    large.addNumber(numbers.begin(), numbers.end());
    assert(large.shortestSpan() == 2);
    assert(large.longestSpan() == 19998);
}

static void testCopy()
{
    Span original(3);
    original.addNumber(3);
    original.addNumber(17);
    Span copied(original);
    Span assigned(1);
    assigned.addNumber(99);
    assigned = original;
    Span &alias = assigned;
    assigned = alias;

    original.addNumber(4);
    assert(original.shortestSpan() == 1);
    assert(copied.shortestSpan() == 14 && copied.longestSpan() == 14);
    assert(assigned.shortestSpan() == 14 && assigned.longestSpan() == 14);
    copied.addNumber(10);
    assigned.addNumber(16);
    assert(copied.shortestSpan() == 7);
    assert(assigned.shortestSpan() == 1);
}

static bool testLimits()
{
    Span sp(2);
    sp.addNumber(INT_MIN);
    sp.addNumber(INT_MAX);
    const unsigned int expected = static_cast<unsigned int>(INT_MAX) - static_cast<unsigned int>(INT_MIN);

    if (sp.shortestSpan() < 1 || sp.longestSpan() < 1 || static_cast<unsigned int>(sp.shortestSpan()) != expected || static_cast<unsigned int>(sp.longestSpan()) != expected)
    {
        std::cerr << "INT_MIN/INT_MAX span test failed: expected "
                  << expected << std::endl;
        return false;
    }
    return true;
}

int main()
{
    Span sp = Span(5);

    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);

    std::cout << sp.shortestSpan() << std::endl;
    std::cout << sp.longestSpan() << std::endl;

    assert(sp.shortestSpan() == 2 && sp.longestSpan() == 14);
    testExceptions();
    testRange();
    testCopy();
    if (!testLimits())
        return 1;

    return 0;
}
