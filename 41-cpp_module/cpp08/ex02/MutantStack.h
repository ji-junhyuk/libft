#ifndef CPP08_MUTANTSTACK_H
#define CPP08_MUTANTSTACK_H

#include <stack>
#include <list>

template <typename T>
class MutantStack : public std::stack<T>
{

public:
    typedef typename std::stack<T>::container_type::iterator iterator;
    typedef typename std::stack<T>::container_type::const_iterator const_iterator;

    MutantStack();
    MutantStack(const MutantStack<T>& other);
    MutantStack<T>& operator=(const MutantStack<T>& other);
    ~MutantStack();

    const_iterator begin(void) const;
    iterator begin(void);
    const_iterator end(void) const;
    iterator end(void);
};

#include "MutantStack.tpp"

#endif //CPP08_MUTANTSTACK_H
