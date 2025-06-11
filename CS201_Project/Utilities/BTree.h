// BTree.h
#ifndef BTREE_H
#define BTREE_H
#include<bits/stdc++.h>
using namespace std;

class BTreeNode {
public:
    vector<long long> keys;
    vector<BTreeNode*> childrens;
    long long n;
    bool leaf;

    BTreeNode(bool is_leaf) : leaf(is_leaf), n(0) {
        keys.resize(2 * 100 - 1); // Size according to the degree
        childrens.resize(2 * 100); // Size according to the degree
    }
};

class BTree {
    private:
        BTreeNode* root;
        long long t = 100;

    public:
        BTree() {
            root = NULL;
        }

    private:void splitChild(BTreeNode* parent, long long index) {
        BTreeNode* child = parent->childrens[index];
        BTreeNode* newNode = new BTreeNode(child->leaf);
        newNode->n = t - 1;

        for (long long i = 0; i < t - 1; ++i) {
            newNode->keys[i] = child->keys[t + i];
        }

        if (!child->leaf) {
            for (long long i = 0; i < t; ++i) {
                newNode->childrens[i] = child->childrens[i + t];
            }
        }

        child->n = t - 1;

        for (long long i = parent->n; i >= index + 1; --i) {
            parent->childrens[i + 1] = parent->childrens[i];
        }
        parent->childrens[index + 1] = newNode;

        for (long long i = parent->n - 1; i >= index; --i) {
            parent->keys[i + 1] = parent->keys[i];
        }
        parent->keys[index] = child->keys[t - 1];
        parent->n += 1;
    }

    private: void insertNonFull(BTreeNode* node, long long value) {
        long long index = node->n - 1;
        if (node->leaf) {
            while (index >= 0 && node->keys[index] > value) {
                node->keys[index + 1] = node->keys[index];
                index--;
            }
            node->keys[index + 1] = value;
            node->n += 1;
        } else {
            while (index >= 0 && node->keys[index] > value) {
                index--;
            }
            index++;

            BTreeNode* child = node->childrens[index];
            if (child->n == 2 * t - 1) {
                splitChild(node, index);
                if (node->keys[index] < value) {
                    index++;
                }
            }
            insertNonFull(node->childrens[index], value);
        }
    }

    public:void insert(long long value) {
        if (!root) {
            root = new BTreeNode(true);
        }
        if (root->n == 2 * t - 1) {
            BTreeNode* newNode = new BTreeNode(false);
            newNode->childrens[0] = root;
            splitChild(newNode, 0);
            root = newNode;
        }
        insertNonFull(root, value);
    }

    private:void Traverse(BTreeNode* node) {
        if (node) {
            for (long long i = 0; i < node->n; i++) {
                if (!node->leaf) {
                    Traverse(node->childrens[i]);
                }
                cout << node->keys[i] << " ";
            }
            if (!node->leaf) {
                Traverse(node->childrens[node->n]);
            }
        }
    }

    public:void inOrderTraverse() {
        Traverse(root);
    }

    public:bool search(long long key) {
        BTreeNode* current = root;
        while (current) {
            long long index = 0;
            while (index < current->n && current->keys[index] < key) {
                index++;
            }
            if (index < current->n && current->keys[index] == key) {
                return true;
            }
            if (current->leaf) {
                return false;
            }
            current = current->childrens[index];
        }
        return false;
    }
};

#endif // BTREE_H
