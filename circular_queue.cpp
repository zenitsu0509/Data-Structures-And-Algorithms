#include <iostream>
using namespace std;

class CircularQueue
{
public:
    int *arr;
    int rear;
    int front;
    int size;

    CircularQueue(int size)
    {
        this->size = size;
        arr = new int[size];
        front = rear = -1;
    }

    void push(int element)
    {
        if ((rear + 1) % size == front)
        {
            cout << "Queue is full" << endl;
            return;
        }
        else if (front == -1) // First element insertion
        {
            front = rear = 0;
        }
        else if (rear == size - 1 && front != 0) // Wrap-around case
        {
            rear = 0;
        }
        else // Normal case
        {
            rear = (rear + 1) % size;
        }
        arr[rear] = element;
    }

    void pop()
    {
        if (front == -1) // Queue is empty
        {
            cout << "Queue is empty" << endl;
            return;
        }

        int ans = arr[front];
        arr[front] = -1;

        if (front == rear) // Only one element was in the queue
        {
            front = rear = -1;
        }
        else if (front == size - 1) // Wrap-around case
        {
            front = 0;
        }
        else // Normal case
        {
            front = (front + 1) % size;
        }
    }

    void display()
    {
        if (front == -1)
        {
            cout << "Queue is empty" << endl;
            return;
        }
        cout << "Queue elements: ";
        if (rear >= front)
        {
            for (int i = front; i <= rear; i++)
                cout << arr[i] << " ";
        }
        else
        {
            for (int i = front; i < size; i++)
                cout << arr[i] << " ";
            for (int i = 0; i <= rear; i++)
                cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    CircularQueue q(5);

    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);

    q.display();

    q.pop();
    q.display();

    q.push(60);
    q.display();

    return 0;
}
