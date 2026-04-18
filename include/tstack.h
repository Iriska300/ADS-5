// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
private:
    T arr[size];
    int top_idx = -1;

public:
    TStack() = default;

    void push(const T& value) {
        if (top_idx < size - 1) {
            arr[++top_idx] = value;
        }
    }

    T pop() {
        if (top_idx >= 0) {
            return arr[top_idx--];
        }
        return T();
    }

    T top() const {
        if (top_idx >= 0) {
            return arr[top_idx];
        }
        return T();
    }

    bool is_empty() const {
        return top_idx == -1;
    }

    bool is_full() const {
        return top_idx == size - 1;
    }
  
};

#endif 
