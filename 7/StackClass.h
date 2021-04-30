#pragma once
#include <cstddef>
template <class T>
class Stack{
    private:
        struct list {
            T data;
            struct list * next;
        };
        typedef struct stack {struct list *top;} stck;
        stck *S;

    public:
        Stack();
        ~Stack();
        void makenull();
        T top();
        T NextToTop();
        T pop();
        void push(T a);
        bool empty();
};