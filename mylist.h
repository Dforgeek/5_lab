#ifndef INC_5_LAB_MYLIST_H
#define INC_5_LAB_MYLIST_H

//template<class T>
class Stack {
public:
    struct Node {
//        T data;
        Node *next{nullptr};
    };

    Node *head = nullptr;
public:
    Stack() = default;


    Node *pop() {
        Node *top = head;
        head = head->next;
        return top;
    }

    void push(Node *newNode) {

        newNode->next = head;
        head = newNode;
        //head->next = nullptr;
    }

    Stack &operator=(const Stack &copy) = default;
};


#endif //INC_5_LAB_MYLIST_H
