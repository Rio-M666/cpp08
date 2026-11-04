#include "MutantStack.hpp"
#include <algorithm>
#include <cassert>
#include <list>
#include <string>

static void testAdditional()
{
    MutantStack<int> empty;
    assert(empty.empty() && empty.size() == 0);
    assert(empty.begin() == empty.end());

    MutantStack<int> original;
    std::list<int> reference;
    const int values[] = {5, 3, 5, 737, 0};
    for (unsigned int i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
    {
        original.push(values[i]);
        reference.push_back(values[i]);
    }
    assert(original.size() == reference.size());
    assert(std::equal(original.begin(), original.end(), reference.begin()));
    MutantStack<int>::iterator it = original.end();
    --it;
    assert(*it == 0);
    --it;
    assert(*it == 737);

    MutantStack<int> copied(original);
    MutantStack<int> assigned;
    assigned.push(99);
    assigned = original;
    MutantStack<int> &alias = assigned;
    assigned = alias;
    assert(copied.size() == original.size());
    assert(assigned.size() == original.size());
    assert(std::equal(copied.begin(), copied.end(), reference.begin()));
    assert(std::equal(assigned.begin(), assigned.end(), reference.begin()));

    *original.begin() = 42;
    original.top() = 100;
    assert(*original.begin() == 42 && original.top() == 100);
    assert(*copied.begin() == 5 && copied.top() == 0);
    assert(*assigned.begin() == 5 && assigned.top() == 0);
    std::stack<int> base(original);
    assert(base.size() == original.size() && base.top() == 100);

    original.pop();
    assert(original.size() == 4 && original.top() == 737);
    while (!original.empty())
        original.pop();
    assert(original.begin() == original.end());

    MutantStack<std::string> words;
    words.push("hello");
    words.push("world");
    assert(*words.begin() == "hello" && words.top() == "world");
}

int main()
{
    MutantStack<int> mstack;

    mstack.push(5);
    mstack.push(17);

    std::cout << mstack.top() << std::endl;

    mstack.pop();

    std::cout << mstack.size() << std::endl;

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    //[...]
    mstack.push(0);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

    ++it;
    --it;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }
    std::stack<int> s(mstack);
    testAdditional();
    return 0;
}
