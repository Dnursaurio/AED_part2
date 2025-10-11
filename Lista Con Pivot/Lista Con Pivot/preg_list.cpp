#include <iostream>
#include <stdexcept>

class Node
{
public:
    Node(int value);

    int data;
    Node* next;
    Node* prev;
};

class DoublyLinkedList
{
public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    
    void push_front(int value);
    void push_back(int value);
    void pop_front();
    void pop_back();
    void print();
    
    Node* get_head();
    Node* get_tail();
    
    void split_list(Node* pivot);

private:
    Node* head;
    Node* tail;
};

Node::Node(int value)
{
    data = value;
    next = 0;
    prev = 0;
}

DoublyLinkedList::DoublyLinkedList()
{
    head = 0;
    tail = 0;
}

DoublyLinkedList::~DoublyLinkedList()
{
    while (head)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void DoublyLinkedList::push_front(int value)
{
    Node* newNode = new Node(value);
    if (head == 0)
        head = tail = newNode;
    else
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

void DoublyLinkedList::push_back(int value)
{
    Node* newNode = new Node(value);
    if (tail == 0)
        head = tail = newNode;
    else
    {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
}

void DoublyLinkedList::pop_front()
{
    if (head == 0)
        throw std::runtime_error("The list is empty");
    
    Node* temp = head;
    head = head->next;
    if (head)
        head->prev = 0;
    else
        tail = 0;
    delete temp;
}

void DoublyLinkedList::pop_back()
{
    if (tail == 0)
        throw std::runtime_error("The list is empty");
    
    Node* temp = tail;
    tail = tail->prev;
    if (tail)
        tail->next = 0;
    else
        head = 0;
    delete temp;
}

void DoublyLinkedList::print()
{
    Node* current = head;
    while (current)
    {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

Node* DoublyLinkedList::get_head()
{   return head;    }

Node* DoublyLinkedList::get_tail()
{   return tail;    }

void DoublyLinkedList::split_list(Node* pivot)
{
    //code go here
    Node* i;
    for (i = head; i; i = i->next)
    {
        if (i == pivot)
        {
            continue;
        }
        else
        {
            if (i->data < pivot->data)
            {
                if (i == head)
                {
                    continue;
                }
                else
                {
                    if (i->prev)
                    {
                        i->prev->next = i->next;
                    }
                    if (i->next)
                    {
                        i->next->prev = i->prev;
                    }
                    i->prev = head->prev;
                    head->prev = i;
                    i->next = head;
                    head = head->prev;
                }
            }
            else
            {
                if (i == tail)
                {
                    continue;
                }
                else
                {
                    if (i->next)
                    {
                        i->next->prev = i->prev;
                    }
                    if (i->prev)
                    {
                        i->prev->next = i->next;
                    }
                    i->prev = tail;
                    i->next = tail->next;
                    tail->next = i;
                    tail = tail->next;
                }
            }
        }
    }
}

int main()
{
    DoublyLinkedList l;
    l.push_back(43);    l.push_back(67);    l.push_back(34);
    l.push_back(20);    l.push_back(71);    l.push_back(12);
    l.push_back(61);    l.push_back(77);    l.push_back(68);
    l.push_back(3);     l.push_back(26);    l.push_back(70);
    l.push_back(74);    l.push_back(88);    l.push_back(57);
    l.print();
    
    l.split_list(l.get_head()); l.print();
    l.split_list(l.get_tail()); l.print();
    l.split_list(l.get_head()); l.print();
    l.split_list(l.get_tail()); l.print();

    return 0;
}
