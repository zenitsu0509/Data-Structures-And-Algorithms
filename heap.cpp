// to find left node of heap  left = i*2;
// to find right node of heap right = i*2 +1;
// to find the leaf nodes [n/2 + 1 to nth];
// priority_queue is a max heap;
// priority_queue<long long, vector <long long> , greater <long long >> pq; to create a min heap
#include <iostream>
#include <bits/stdtr1c++.h>
using namespace std;
class heap
{
public:
    int arr[100];
    int size;
    heap()
    {
        arr[0] = -1;
        size = 0;
    }
    void insert(int val)
    {
        size = size + 1;
        int index = size;
        arr[index] = val;
        while (index > 1)
        {
            int parent = index / 2;
            if (arr[parent] < arr[index])
            {
                swap(arr[parent], arr[index]);
                index = parent;
            }
            else
            {
                return;
            }
        }
    }
    void print()
    {
        for (int i = 1; i <= size; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    void deleteFromHeap()
    {
        if (size == 0)
        {
            cout << "Heap is already empty" << endl;
            return;
        }
        arr[1] = arr[size];
        size--;
        int i = 1;
        while (i <= size)
        {
            int leftIndex = i * 2;
            int rightIndex = i * 2 + 1;
            if (leftIndex <= size && arr[i] < arr[leftIndex])
            {
                swap(arr[i], arr[leftIndex]);
                i = leftIndex;
            }
            else if (rightIndex <= size && arr[i] < arr[rightIndex])
            {
                swap(arr[i], arr[rightIndex]);
                i = rightIndex;
            }
            else
            {
                return;
            }
        }
    }
};
void heapify_algo(int arr[], int n, int i)
{
    int largest = i;
    int left = i * 2;
    int right = i * 2 + 1;

    if (left < n && arr[largest] < arr[left])
    {
        largest = left;
    }
    if (right < n && arr[largest] < arr[right])
    {
        largest = right;
    }
    if (largest != i)
    {
        swap(arr[largest], arr[i]);
        heapify_algo(arr, n, largest);
    }
}
int kthSmallest(int arr[], int s, int k)
{
    priority_queue<int> pq;
    for (int i = 0; i < k ; i++)
    {
        pq.push(arr[i]);
    }
    for (int i = k; i < s; i++)
    {
        if (pq.top() > arr[i])
        {
            pq.pop();
            pq.push(arr[i]);
        }
    }
    return pq.top();
}
int main()
{
    int arr[5] = {7, 10, 14, 20, 15};
    int ans = kthSmallest(arr, 5, 4);
    cout << ans << endl;
    heap h;
    h.insert(55);
    h.insert(56);
    h.insert(34);
    h.insert(12);
    h.insert(60);
    h.insert(2);
    h.print();
    h.deleteFromHeap();
    h.print();
    int arr[6] = {-1, 54, 53, 55, 52, 50};
    int n = 5;

    for (int i = n / 2; i > 0; i--)
    {
        heapify_algo(arr, n, i);
    }
    for (int i = 1; i < 6; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}