#include <iostream>
#include <bits/stdtr1c++.h>
using namespace std;

class Node
{
public:
    int data;
    Node *next;

    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
    // distructor
    ~Node()
    {
        // int value = this->data;
        if (this->next != NULL)
        {
            // code to free memory
            delete next;
            this->next = NULL;
        }
    }
};
void atHead(Node *&head, int data)
{
    Node *temp = new Node(data);
    temp->next = head;
    head = temp;
}

void printLinkeedList(Node *&head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
}

void atTail(Node *&tail, int data)
{
    Node *temp = new Node(data);
    if (tail == nullptr)
    {
        // If the list is empty, set both head and tail to the new node
        tail = temp;
    }
    else
    {
        tail->next = temp;
        tail = temp;
    }
}
void insertAtPosition(Node *&head, int data, int position)
{
    Node *temp = head;
    int cnt = 1;
    while (cnt < position - 1)
    {
        temp = temp->next;
        cnt++;
    }
    // creating node for data
    Node *nodeToInsert = new Node(data);
    nodeToInsert->next = temp->next;
    temp->next = nodeToInsert;
}
void deleteThePosition(Node *&head, int position, Node *&tail)
{
    if (position == 1)
    {
        Node *temp = head;
        // deleting the fisrt position
        head = head->next;
        temp->next = NULL;
        delete temp;
    }
    else
    {
        // deleting any middle or last node
        int cnt = 1;
        Node *current = head;
        Node *previus = NULL;
        while (cnt < position)
        {
            previus = current;
            current = current->next;
            cnt++;
        }
        if (current->next == NULL)
        {
            tail = previus;
        }
        previus->next = current->next;
        current->next = NULL;
        delete current;
    }
}
int main()
{
    Node *node1 = new Node(60);
    Node *head = node1;
    Node *tail = node1;

    cout << endl
         << "tail" << endl;
    atTail(tail, 0);
    atTail(tail, 1);
    atTail(tail, 2);
    atTail(tail, 4);
    atTail(tail, 5);
    atTail(tail, 6);
    insertAtPosition(head, 3, 5);

    printLinkeedList(head);
    cout << endl;
    cout << "tail is " << tail->data << endl;
    deleteThePosition(head, 8, tail);
    printLinkeedList(head);
    cout << endl;
    cout << "tail is " << tail->data << endl;
    // Deallocate memory to avoid memory leaks

    return 0;
}
