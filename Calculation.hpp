#ifndef CALCULATION_HPP_INCLUDED
#define CALCULATION_HPP_INCLUDED

#include <stack>
#include <string>
#include <exception>
#include "Complex.hpp"
#include "Operation.hpp"
#include "common.hpp"
#include "Dictionary.hpp"
#include "config.hpp"

template<class T> // To be used in bracket stack. The unsigned int marks the position of the bracket
struct linkedStackElement{
    T elem;
    unsigned pos;
};

Complex * grabArgs(std::stack<Complex *> &, unsigned); // fetch numbers from number stack according to the number of arguments required
Complex * convertAndSet(std::string &); // set a number from a string, receiving from grabNum
void calcStacks(std::stack<Complex *> &, std::stack<Operation *> &); // handle stacks
bool calcOrPush(std::stack<Operation *> &, std::stack<linkedStackElement<Operation *>> &, Operation *);

Complex * calcString(std::string &); // the overall calculation process

#endif // CALCULATION_HPP_INCLUDED
