#include<iostream>

template < typename E >
class Stack {
private:
    E * stack;
    int t = -1;;
    int capacity = 1000;
public:
    Stack() {
        this -> stack = new E[this -> capacity];
    }
    Stack(int c) {
        this -> capacity = c;
        this -> stack = new E[this -> capacity];

    }

    int Size() {
        return (this -> t + 1);
    }

    bool isEmpty() {
        return (this -> t == -1);
    }

    E top() {
        return stack[t];
    }

    void push(E data) {
        if (Size() == this -> capacity) return;

        stack[++t] = data;

    }

    E pop() {
        if (isEmpty()) return NULL;

        E answer = stack[t];
        stack[t] = NULL;

        t--;

        return answer;
    }

};
