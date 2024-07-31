#include <iostream>
#include <bits/stdtr1c++.h>
using namespace std;
class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node(int data)
    {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};
void levelOrderTraversal(Node *root)
{
    queue<Node *> q;
    q.push(root);
    q.push(NULL);
    while (!q.empty())
    {
        Node *temp = q.front();
        q.pop();
        if (temp == NULL)
        {
            cout << endl;
            if (!q.empty())
            {
                q.push(NULL);
            }
        }
        else
        {
            cout << temp->data << " ";

            if (temp->left)
            {
                q.push(temp->left);
            }
            if (temp->right)
            {
                q.push(temp->right);
            }
        }
    }
}
Node *insertInBST(Node *root, int data)
{
    if (root == NULL)
    {
        root = new Node(data);
        return root;
    }
    if (data > root->data)
    {
        root->right = insertInBST(root->right, data);
    }
    else
    {
        root->left = insertInBST(root->left, data);
    }
    return root;
}
void takeRootData(Node *&root)
{
    int d;
    cin >> d;
    while (d != -1)
    {
        root = insertInBST(root, d);
        cin >> d;
    }
}
bool searchInBST(Node *root, int x)
{
    if (root == NULL)
    {
        return false;
    }
    if (root->data == x)
    {
        return true;
    }
    if (root->data < x)
    {
        return searchInBST(root->right, x);
    }
    else
    {
        return searchInBST(root->left, x);
    }
}
int minInBST(Node *root)
{
    Node *temp = root;
    while (temp != NULL)
    {
        temp = temp->left;
        if (temp->left == NULL)
        {
            return temp->data;
        }
    }
}
int maxInBST(Node *root)
{
    Node *temp = root;
    while (temp != nullptr)
    {
        temp = temp->right;
        if (temp->right == NULL)
            return temp->data;
    }
}
Node *deleteFromBST(Node *root, int val)
{
    if (root == NULL)
    {
        return root;
    }
    if (root->data == val)
    {
        // 0 child
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            return NULL;
        }
        // 1 child
        // left is null
        if (root->left == NULL && root->right != NULL)
        {
            Node *temp = root;
            delete root;
            return temp;
        }
        //  right is null
        if (root->left != NULL && root->right == NULL)
        {
            Node *temp = root;
            delete root;
            return temp;
        }
        // 2 child  
        if(root->left != NULL && root->right != NULL){
            int mini = minInBST(root->right);
            root->data = mini;
            root->right = deleteFromBST(root->right, mini);
            delete root;
            
        }
    }
    else if (root->data > val)
    {
        root->left = deleteFromBST(root->left, val);
        return root;
    }
    else
    {
        root->right = deleteFromBST(root->right, val);
        return root;
    }
}
int main()
{
    Node *root = NULL;
    cout << "Enter data to create BST" << endl;
    takeRootData(root);
    cout << "printing BST" << endl;
    levelOrderTraversal(root);
    int ans = minInBST(root);
    cout << ans << endl;
    int ans2 = maxInBST(root);
    cout << "max element in the BST " << ans2 << endl;
    Node* temp = deleteFromBST(root,5);
    levelOrderTraversal(root);
    return 0;
}