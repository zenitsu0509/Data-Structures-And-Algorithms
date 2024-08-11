#include <iostream>
#include <bits/stdtr1c++.h>
using namespace std;
class Queue
{
public:
    int *arr;
    int size;
    int front;
    int rear;
    Queue(int size)
    {
        this->size = size;
        arr = new int[size];
        front = 0;
        rear = 0;
    }
    void push(int element)
    {
        if (rear == size)
        {
            cout << "queue is overflow" << endl;
        }
        else
        {
            arr[rear] = element;
            rear++;
        }
    }
    int peek()
    {
        if (arr[front] >= 0)
        {
            return arr[front];
        }
        else
        {
            cout << "queue is empty" << endl;
            return -1;
        }
    }
    void pop()
    {
        if (rear == front)
        {
            cout << "queue is empty" << endl;
        }

        else
        {
            arr[front] = -1;
            front++;
            if (front == rear)
            {
                front = 0;
                rear = 0;
            }
        }
    }
    bool isEmpty()
    {
        if (rear == front)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
int main()
{
    Queue q(2);
    q.push(5);
    q.push(6);
    q.pop();
    cout << q.isEmpty() << endl;
    return 0;
}