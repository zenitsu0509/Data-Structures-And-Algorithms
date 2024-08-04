#include <bits/stdc++.h>
using namespace std;

class node {
public:
    int data;
    node *left;
    node *right;
    node(int d) {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};

node *buildTree(node *root) {
    cout << "Enter the data: ";
    int data;
    cin >> data;
    if (data == -1) {
        return NULL;
    }
    root = new node(data);
    cout << "Enter data for inserting in left of " << data << ": ";
    root->left = buildTree(root->left);
    cout << "Enter data for inserting in right of " << data << ": ";
    root->right = buildTree(root->right);
    return root;
}

void levelOrderTraversal(node *root) {
    if (root == NULL) return;
    queue<node *> q;
    q.push(root);
    vector<vector<int>> lot;
    while (!q.empty()) {
        int size = q.size();
        vector<int> level;
        for (int i = 0; i < size; i++) {
            node* temp = q.front();
            q.pop();
            if (temp->left) q.push(temp->left);
            if (temp->right) q.push(temp->right);
            level.push_back(temp->data);
        }
        lot.push_back(level);
    }
    
    // Printing level order traversal
    for (const auto& level : lot) {
        for (int val : level) {
            cout << val << " ";
        }
        cout << endl;
    }
}

// In-order traversal (recursive)
void inOrder(node *root) {
    if (root == NULL) {
        return;
    }
    inOrder(root->left);
    cout << root->data << " ";
    inOrder(root->right);
}

// In-order traversal (iterative)
void inOrder_it(node* root) {
    if (root == NULL) return;
    stack<node*> st;
    while (root != NULL || !st.empty()) {
        while (root != NULL) {
            st.push(root);
            root = root->left;
        }
        root = st.top();
        st.pop();
        cout << root->data << " ";
        root = root->right;
    }
}

// Pre-order traversal (recursive)
void preOrder(node *root) {
    if (root == NULL) {
        return;
    }
    cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}

// Pre-order traversal (iterative)
void preOrder_it(node *root) {
    if (root == NULL) return;
    stack<node*> st;
    st.push(root);
    while (!st.empty()) {
        node* curr = st.top();
        st.pop();
        cout << curr->data << " ";
        if (curr->right) st.push(curr->right);
        if (curr->left) st.push(curr->left);
    }
}

// Post-order traversal (recursive)
void postOrder(node *root) {
    if (root == NULL) {
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";
}

// Post-order traversal (iterative)
void postOrder_it(node* root) {
    if (root == NULL) return;
    stack<node*> st, st2;
    st.push(root);
    while (!st.empty()) {
        node* curr = st.top();
        st.pop();
        st2.push(curr);
        if (curr->left) st.push(curr->left);
        if (curr->right) st.push(curr->right);
    }
    while (!st2.empty()) {
        cout << st2.top()->data << " ";
        st2.pop();
    }
}

// Maximum depth of binary tree
int maxDepth(node* root) {
    if (root == NULL) return 0;
    int lh = maxDepth(root->left);
    int rh = maxDepth(root->right);
    return 1 + max(lh, rh);
}

// Check if the tree is balanced
bool checkBalance(node* root) {
    if (root == NULL) return true;

    int lh = maxDepth(root->left);
    int rh = maxDepth(root->right);

    return abs(lh - rh) <= 1 && checkBalance(root->left) && checkBalance(root->right);
}

// Diameter of the tree
int diameterUtil(node* root, int& diameter) {
    if (root == NULL) return 0;

    int lh = diameterUtil(root->left, diameter);
    int rh = diameterUtil(root->right, diameter);

    diameter = max(diameter, lh + rh);

    return 1 + max(lh, rh);
}

int diameter(node* root) {
    int diameter = 0;
    diameterUtil(root, diameter);
    return diameter;
}

int main() {
    node *root = NULL;
    // Creating a tree
    root = buildTree(root);
    // Example input: 1 5 10 -1 -1 12 -1 -1 6 13 -1 -1 14 -1 -1
 
    // Traversing the tree
    cout << endl;
    cout << "Printing level order traversal:" << endl;
    levelOrderTraversal(root);

    cout << "Printing in-order traversal (recursive):" << endl;
    inOrder(root);
    cout << endl;

    cout << "Printing in-order traversal (iterative):" << endl;
    inOrder_it(root);
    cout << endl;

    cout << "Printing pre-order traversal (recursive):" << endl;
    preOrder(root);
    cout << endl;

    cout << "Printing pre-order traversal (iterative):" << endl;
    preOrder_it(root);
    cout << endl;

    cout << "Printing post-order traversal (recursive):" << endl;
    postOrder(root);
    cout << endl;

    cout << "Printing post-order traversal (iterative):" << endl;
    postOrder_it(root);
    cout << endl;

    cout << "Maximum depth of the tree: " << maxDepth(root) << endl;

    if (checkBalance(root)) cout << "Tree is Balanced" << endl;
    else cout << "Tree is not Balanced" << endl;

    cout << "Diameter of the tree: " << diameter(root) << endl;

    return 0;
}
