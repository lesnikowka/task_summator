#include <iostream>

typedef size_t T;

struct node {
    T val = 0;
    node* next = nullptr;
};

node* write_number(T number) {
    node* first = new node;
    node* tmp = first;

    while (number) {
        tmp->val = number % 10;
        number /= 10;
        if (number) {
            tmp->next = new node;
            tmp = tmp->next;
        }
    }


    return first;
}

void summ(node* first, node* second) {
    bool add_digit = false;
    node* prev = first;

    while (first || second || add_digit) {
        if (first && second) {
            prev = first;
            if (first->val + second->val + (size_t)add_digit > 9) {
                first->val = (first->val + second->val + (size_t)add_digit) % 10;
                add_digit = true;
            }
            else {
                first->val = first->val + second->val + (size_t)add_digit;
                add_digit = false;
            }
            first = first->next;
            second = second->next;
        }
        else if (first) {
            prev = first;
            if (first->val + (size_t)add_digit > 9) {
                first->val = 0;
                add_digit = true;
            }
            else {
                first->val += (size_t)add_digit;
                add_digit = false;
            }
            first = first->next;
        }
        else if(second){
            prev->next = new node;
            prev = prev->next;
            if(second->val + (size_t)add_digit > 9){
                prev->val = 0;
                add_digit = true;
            }
            else {
                prev->val = second->val + (size_t)add_digit;
                add_digit = false;
            }
            second = second->next;
        }
        else if (add_digit) {
            prev->next = new node;
            prev = prev->next;
            prev->val = 1;
            add_digit = false;
        }
    }
}

size_t to_number(node* first){
    size_t digit = 1;
    size_t number = 0;
    while (first) {
        number += first->val * digit;
        first = first->next;
        digit*=10;
    }
    return number;
}

void destruct(node* first) {
    if (first) {
        node* tmp = first;
        node* tmp2;
        while (tmp->next) {
            tmp2 = tmp->next;
            delete tmp;
            tmp = tmp2;
        }
    }
}

void test() {
    node* first;
    node* second;

    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            first = write_number(i);
            second = write_number(j);
            summ(first, second);
            if (to_number(first) != i + j) {
                std::cout << "TEST FAILED" << std::endl;
                std::cout << "i = " << i << " j = " << j << std::endl;
            }
            destruct(first);
            destruct(second);
        }
    }
}

int main()
{
    test();

    //while (true) {
    //    int val1, val2;
    //    std::cin >> val1;
    //    std::cin >> val2;
    //    node* first = write_number(val1);
    //    node* second = write_number(val2);
    //    summ(first, second);
    //    to_number(first);
    //    std::cout << to_number(first) << " ";
    //}
}
