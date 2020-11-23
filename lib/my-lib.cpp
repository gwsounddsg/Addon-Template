#include <iostream>

int foo() {
    return 8;
}

int bar(int x) {
    return x + 42;
}


class ClassA {

public:
    ClassA();
    ~ClassA();
    int Add(int a, int b);
};

ClassA::ClassA() {}
ClassA::~ClassA() {}

int ClassA::Add(int a, int b) {
    return a + b;
}