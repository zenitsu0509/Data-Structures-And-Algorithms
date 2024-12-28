#include <iostream>
#include <bits/stdtr1c++.h>
using namespace std;
class Node
{
public:
    int data;
    Node *next;
    Node *prev;
    // constructer
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
        this->prev = NULL;
    }
};
void insertAtPosition(Node *&tail, int element, int data)
{
    Node *temp = new Node(data);
    if (tail == NULL)
    {
        tail = temp;
        temp->next = temp;
        temp->prev = temp;
    }
    else
    {
        Node *current = tail;
        while (current->data != element)
        {
            current = current->next;
        }
        temp->next = current->next;
        current->next->prev = temp;
        current->next = temp;
        temp->prev = current;
    }
}
void print(Node *tail)
{
    Node *temp = tail;
    do
    {
        cout << tail->data << " ";
        tail = tail->next;
    } while (temp != tail);
}
int main()
{
    Node *tail = NULL;
    insertAtPosition(tail, 5, 10);
    insertAtPosition(tail, 10, 20);
    insertAtPosition(tail, 20, 30);
    insertAtPosition(tail, 30, 40);
    print(tail);
    return 0;
}
