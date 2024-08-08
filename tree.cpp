#include <bits/stdc++.h>
using namespace std;

class node
{
public:
    int data;
    node *left;
    node *right;
    node(int d)
    {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};

node *buildTree(node *root)
{
    cout << "Enter the data: ";
    int data;
    cin >> data;
    if (data == -1)
    {
        return NULL;
    }
    root = new node(data);
    cout << "Enter data for inserting in left of " << data << ": ";
    root->left = buildTree(root->left);
    cout << "Enter data for inserting in right of " << data << ": ";
    root->right = buildTree(root->right);
    return root;
}
vector<vector<int>> verticalTraversal(node *root)
{
    map<int, map<int, multiset<int>>> nodes;
    queue<pair<node *, pair<int, int>>> todo;
    todo.push({root, {0, 0}});
    while (!todo.empty())
    {
        auto p = todo.front();
        todo.pop();
        node *nd = p.first;
        int x = p.second.first;
        int y = p.second.second;
        nodes[x][y].insert(nd->data);
        if (nd->left)
        {
            todo.push({nd->left, {x - 1, y - +1}});
        }
        if (nd->right)
        {
            todo.push({nd->right, {x + 1, y + 1}});
        }
    }
    vector<vector<int>> ans;
    for (auto p : nodes)
    {
        vector<int> col;
        for (auto q : p.second)
        {
            col.insert(col.end(), q.second.begin(), q.second.end());
        }
    }
    return ans;
}
void levelOrderTraversal(node *root)
{
    if (root == NULL)
        return;
    queue<node *> q;
    q.push(root);
    vector<vector<int>> lot;
    while (!q.empty())
    {
        int size = q.size();
        vector<int> level;
        for (int i = 0; i < size; i++)
        {
            node *temp = q.front();
            q.pop();
            if (temp->left)
                q.push(temp->left);
            if (temp->right)
                q.push(temp->right);
            level.push_back(temp->data);
        }
        lot.push_back(level);
    }

    // Printing level order traversal
    for (const auto &level : lot)
    {
        for (int val : level)
        {
            cout << val << " ";
        }
        cout << endl;
    }
}

// In-order traversal (recursive)
void inOrder(node *root)
{
    if (root == NULL)
    {
        return;
    }
    inOrder(root->left);
    cout << root->data << " ";
    inOrder(root->right);
}

// In-order traversal (iterative)
void inOrder_it(node *root)
{
    if (root == NULL)
        return;
    stack<node *> st;
    while (root != NULL || !st.empty())
    {
        while (root != NULL)
        {
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
void preOrder(node *root)
{
    if (root == NULL)
    {
        return;
    }
    cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}

// Pre-order traversal (iterative)
void preOrder_it(node *root)
{
    if (root == NULL)
        return;
    stack<node *> st;
    st.push(root);
    while (!st.empty())
    {
        node *curr = st.top();
        st.pop();
        cout << curr->data << " ";
        if (curr->right)
            st.push(curr->right);
        if (curr->left)
            st.push(curr->left);
    }
}

// Post-order traversal (recursive)
void postOrder(node *root)
{
    if (root == NULL)
    {
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";
}

// Post-order traversal (iterative)
void postOrder_it(node *root)
{
    if (root == NULL)
        return;
    stack<node *> st, st2;
    st.push(root);
    while (!st.empty())
    {
        node *curr = st.top();
        st.pop();
        st2.push(curr);
        if (curr->left)
            st.push(curr->left);
        if (curr->right)
            st.push(curr->right);
    }
    while (!st2.empty())
    {
        cout << st2.top()->data << " ";
        st2.pop();
    }
}

// Maximum depth of binary tree
int maxDepth(node *root)
{
    if (root == NULL)
        return 0;
    int lh = maxDepth(root->left);
    int rh = maxDepth(root->right);
    return 1 + max(lh, rh);
}

// Check if the tree is balanced
bool checkBalance(node *root)
{
    if (root == NULL)
        return true;

    int lh = maxDepth(root->left);
    int rh = maxDepth(root->right);

    return abs(lh - rh) < 1 && checkBalance(root->left) && checkBalance(root->right);
}

// Diameter of the tree
int diameterUtil(node *root, int &diameter)
{
    if (root == NULL)
        return 0;

    int lh = diameterUtil(root->left, diameter);
    int rh = diameterUtil(root->right, diameter);

    diameter = max(diameter, lh + rh);

    return 1 + max(lh, rh);
}

int diameter(node *root)
{
    int diameter = 0;
    diameterUtil(root, diameter);
    return diameter;
}
int maxPathSum(node *root, int &maxx)
{
    if (root == NULL)
        return 0;
    int leftSum = max(0, maxPathSum(root->left, maxx));
    int rightSum = max(0, maxPathSum(root->right, maxx));
    maxx = max(maxx, leftSum + rightSum + root->data);
    return root->data + max(leftSum, rightSum);
}
bool isSameTree(node *p, node *q)
{
    if (p == NULL || q == NULL)
        return p == q;
    return (p->data == q->data) && (isSameTree(p->left, q->left)) && (isSameTree(p->right, q->right));
}
bool sumTargetUtil(node *root, int currSum, int target)
{
    if (root == NULL)
    {
        return false;
    }
    currSum += root->data;
    if (root->left == NULL && root->right == NULL)
        return currSum == target;
    return sumTargetUtil(root->left, currSum, target) || sumTargetUtil(root->right, currSum, target);
}
bool sumTarget(node *root, int target)
{
    if (root == NULL)
        return false;
    return sumTargetUtil(root, 0, target);
}
bool isLeaf(node *root)
{
    return root->left == NULL && root->right == NULL;
}
void addLeft(node *root, vector<int> &result)
{
    node *temp = root->left;
    while (temp)
    {
        if (!isLeaf(temp))
        {
            result.push_back(temp->data);
        }
        if (temp->left)
            temp = temp->left;
        else
            temp = temp->right;
    }
}
void addLeaf(node *root, vector<int> &result)
{
    if (isLeaf(root))
    {
        result.push_back(root->data);
        return;
    }
    if (root->left)
        addLeaf(root->left, result);
    if (root->right)
        addLeaf(root->right, result);
}
void addRight(node *root, vector<int> &result)
{
    vector<int> temp;
    node *nd = root->right;
    while (nd)
    {
        if (!isLeaf(nd))
        {
            temp.push_back(nd->data);
        }
        if (nd->left)
            nd = nd->left;
        else
            nd = nd->right;
    }
    for (int i = temp.size() - 1; i >= 0; i--)
        result.push_back(temp[i]);
}
vector<int> boundaryTraversal(node *root)
{
    vector<int> result;
    if (root == NULL)
        return {};
    if (!isLeaf(root))
    {
        result.push_back(root->data);
    }
    addLeft(root, result);
    addLeaf(root, result);
    addRight(root, result);
    return result;
}
void topVeiw(node *root)
{
    if (root == NULL)
    {
        return;
    }
    vector<int> ans;
    map<int, int> mp;
    queue<pair<node *, int>> q;
    q.push({root, 0});
    while (!q.empty())
    {
        auto it = q.front();
        q.pop();
        node *nd = it.first;
        int level = it.second;
        if (mp.find(level) == mp.end())
            mp[level] = nd->data;
        if (nd->left != NULL)
            q.push({nd->left, level - 1});
        if (nd->right != NULL)
            q.push({nd->right, level + 1});
    }
    for (auto it : mp)
        ans.push_back(it.second);
    for (auto i : ans)
        cout << i << " ";
    cout << endl;
}
void bottomView(node *root)
{
    if (root == NULL)
    {
        return;
    }
    vector<int> ans;
    map<int, int> mp;
    queue<pair<node *, int>> q;
    q.push({root, 0});
    while (!q.empty())
    {
        auto it = q.front();
        q.pop();
        node *nd = it.first;
        int level = it.second;
        mp[level] = nd->data;
        if (nd->left != NULL)
            q.push({nd->left, level - 1});
        if (nd->right != NULL)
            q.push({nd->right, level + 1});
    }
    for (auto it : mp)
        ans.push_back(it.second);
    for (auto i : ans)
        cout << i << " ";
    cout << endl;
}
void dfs(node *root, int level, vector<int> &ans)
{
    if (root == NULL)
    {
        return;
    }
    if (ans.size() == level)
        ans.push_back(root->data);
    dfs(root->right, level + 1, ans);
    dfs(root->left, level + 1, ans);
}
void rightSideView(node *root)
{
    vector<int> ans;
    dfs(root, 0, ans);
    for(int i : ans){
        cout<<i<<" ";
    }
    cout<<endl;
}
int minTime(node* root, map<node*, node*>& mpp) {
    queue<node*> q;
    map<node*, bool> vis;
    q.push(root);
    vis[root] = true;
    int maxi = 0;
    while (!q.empty()) {
        int n = q.size();
        bool flag = false;
        for (int i = 0; i < n; i++) {
            node* it = q.front();
            q.pop();
            if (it->left != NULL && !vis[it->left]) {
                flag = true;
                q.push(it->left);
                vis[it->left] = true;
            }
            if (it->right != NULL && !vis[it->right]) {
                flag = true;
                q.push(it->right);
                vis[it->right] = true;
            }
            if (mpp[it] != NULL && !vis[mpp[it]]) {
                flag = true;
                q.push(mpp[it]);
                vis[mpp[it]] = true;
            }
        }
        if (flag) {
            maxi++;
        }
    }
    return maxi;
}
node* bfsToMap(node* root,int target,map<node*,node*>& mpp){
    node* res;
    queue<node*> q;
    q.push(root);
    while(!q.empty()){
        auto it = q.front();
        q.pop();
        if(it->data == target) res = it;
        if(it->left != NULL){
            mpp[it->left] = it;
            q.push(it->left); 
        }
        if(it->right != NULL){
            mpp[it->right] = it;
            q.push(it->right);
        }
    }
    return res;
}
void minTimeToburnTree(node* root,int target){
    map<node*,node*> mpp;
    node* start = bfsToMap(root,target,mpp);
    int maxi = minTime(start,mpp);
    cout<<maxi<<" "<<endl;
}
int main()
{
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

    if (checkBalance(root))
        cout << "Tree is Balanced" << endl;
    else
        cout << "Tree is not Balanced" << endl;

    cout << "Diameter of the tree: " << diameter(root) << endl;

    int sum = 0;
    maxPathSum(root, sum);
    cout << "The maximum path Sum:" << sum << " " << endl;

    if (sumTarget(root, 16))
        cout << "equal" << endl;
    else
        cout << "not equal" << endl;

    vector<int> result = boundaryTraversal(root);
    cout << "boundary traversal:";
    for (int i : result)
        cout << i << " ";
    cout << endl;

    cout << "top view:";
    topVeiw(root);

    cout << "bottom view:";
    bottomView(root);

    cout<<"right view:";
    rightSideView(root);

    cout<<"min time to burn tree from root:";
    minTimeToburnTree(root,10);
    cout<<endl;
    return 0;
}
