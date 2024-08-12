#include <iostream>
#include <bits/stdtr1c++.h>
using namespace std;
class TrieNode
{
public:
    char data;
    TrieNode *children[26];
    bool isTerminal;
    TrieNode(char ch)
    {
        data = ch;
        for (int i = 0; i < 26; i++)
        {
            children[i] = NULL;
        }
        isTerminal = false;
    }
};
class Trie
{
public:
    TrieNode *root;
    Trie()
    {
        root = new TrieNode('\0');
    }
    void insertUtile(TrieNode *root, string word)
    {
        if (word.length() == 0)
        {
            cout << "Word is added" << endl;
            root->isTerminal = true;
            return;
        }
        int index = word[0] - 'A';
        TrieNode *child;
        if (root->children[index] != NULL)
        {
            child = root->children[index];
        }
        else
        {
            child = new TrieNode(word[0]);
            root->children[index] = child;
        }
        insertUtile(child, word.substr(1));
    }

    void insertWord(string word)
    {
        insertUtile(root, word);
    }
    // searching algo
    bool searchUtile(TrieNode *root, string word)
    {
        if (word.length() == 0)
        {
            return root->isTerminal;
        }
        int index = word[0] - 'A';
        TrieNode *child;
        // present
        if (root->children[index] != NULL)
        {
            child = root->children[index];
        }
        // absent
        else
        {
            return false;
        }
        return searchUtile(child, word.substr(1));
    }
    bool search(string word)
    {
        return searchUtile(root, word);
    }
    void removeUtile(TrieNode *root, string word)
    {
        if (word.length() == 0)
        {
            root->isTerminal = false;
            return;
        }
        // Present
        int index = word[0] - 'A';
        TrieNode *child;
        child = root->children[index];
        removeUtile(child,word.substr(1));
    }
    void remove(string word)
    {
        removeUtile(root, word);
    }
};
int main()
{
    Trie *t = new Trie();
    t->insertWord("ABCD");
    string word = "ABCD";
    cout << t->search(word) << endl;
    t->remove("ABCD");
    cout << t->search(word) << endl;

    return 0;
}