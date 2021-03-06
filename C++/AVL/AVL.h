//
// Created by yann on 2021/3/4.
//

#ifndef AVL_AVL_H
#define AVL_AVL_H

#include "algorithm"
#include "cassert"
#include "iostream"
#include "vector"

using namespace std;
template<typename Key, typename Value>
class AVLTree {
private:
    struct Node {
        Key key;
        Value value;
        Node *left;
        Node *right;
        int height;

        Node(Key key, Value value) {
            this->key = key;
            this->value = value;
            this->left = this->right = nullptr;
            height = 1;
        }

        Node(Node *node) {
            this->key = node->key;
            this->value = node->value;
            this->left = node->left;
            this->right = node->right;
            this->height = 1;
        }
    };

    Node *root;
    int size;


public:

    AVLTree() {
        root = nullptr;
        size = 0;
    }

    ~AVLTree() {
        destroy(root);
    }

    int getSize() {
        return size;
    }

    int isEmpty() {
        return size == 0;
    }

    int getHeight(Node *node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int getBalanceFactor(Node *node) {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    bool isBST(){

        vector<Key> keys;
        inOrder(root, keys);
        for (int i = 1; i < keys.size(); ++i) {
            if (keys.at(i - 1) < keys.at(i)) {
                return false;
            }
        }
        return true;
    }

    bool isBalanced(){
        return isBalanced(root);
    }

    void add(Key key, Value value) {
        root = add(root, key, value);
    }

    bool contains(Key key) {
        return getNode(root, key) != nullptr;
    }

    Value *get(Key key) {
        Node *node = getNode(root, key);
        return node == nullptr ? nullptr : &(node->value);
    }

    void set(Key key, Value newValue) {
        Node *node = getNode(root, key);
        if (node != nullptr) {
            node->value = newValue;
        }
    }

    // 从二叉树中删除键值为key的节点
    Value *remove(Key key) {
        Node *node = getNode(root, key);
        if (node != nullptr) {
            root = remove(root, key);
            return &(node->value);
        }
        return nullptr;
    }

private:

    void inOrder(Node *root, vector<Key> & keys){

        if (root == NULL)
            return;

        inOrder(root->left, keys);
        keys.push_back(root->key);
        inOrder(root->right, keys);
    }

    bool isBalanced(Node* root){
        if (root == NULL)
            return true;

        int balanceFactor = getBalanceFactor(root);
        if (abs(balanceFactor) > 1)
            return false;

        return isBalanced(root->left) && isBalanced(root->right);
    }


    // 向以node为根的二叉搜索树中,插入节点(key, value)
    // 返回插入新节点后的二叉搜索树的根
    Node *add(Node *node, Key key, Value value) {
        if (node == nullptr) {
            size++;
            return new Node(key, value);
        }
        if (key == node->key) {
            node->value = value;
        } else if (key < node->key) {
            node->left = add(node->left, key, value);
        } else {
            node->right = add(node->right, key, value);
        }
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        int balanceFactor = getBalanceFactor(node);
        if(std::abs(balanceFactor) > 1) {
            std::cout << "unbalanced : " << balanceFactor;
        }

        // 平衡维护
        if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0)
            return rightRotate(node);

        if (balanceFactor < -1 && getBalanceFactor(node->right) >=0)
            return leftRotate(node);

        // LR
        if (balanceFactor > 1 && getBalanceFactor(node->left) < 0){
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL
        if (balanceFactor < -1 && getBalanceFactor(node->right) > 0){
            node->right= rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* rightRotate(Node* y){

        Node* x = y->left;
        Node* T3 = x->right;

        x->right = y;
        y->left = T3;

        // 更新height
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* y){

        Node* x = y->right;
        Node* T3 = x->left;

        x->left = y;
        y->right = T3;

        // 更新height
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    // 在以node为根的二叉搜索树中查找key所对应的Node
    Node *getNode(Node *node, Key key) {
        if (node == nullptr) {
            return nullptr;
        }
        if (key == node->key) {
            return node;
        } else if (key < node->key) {
            return getNode(node->left, key);
        } else {
            return getNode(node->right, key);
        }
    }

    void destroy(Node *node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
            size--;
        }
    }

    // 在以node为根的二叉搜索树中,返回最小键值的节点
    Node *minimum(Node *node) {
        if (node->left == nullptr)
            return node;
        return minimum(node->left);
    }

    // 在以node为根的二叉搜索树中,返回最大键值的节点
    Node *maximum(Node *node) {
        if (node->right == nullptr)
            return node;
        return maximum(node->right);
    }

    // 删除掉以node为根的二分搜索树中的最小节点
    // 返回删除节点后新的二分搜索树的根
    Node *removeMin(Node *node) {
        if (node->left == nullptr) {
            Node *rightNode = node->right;
            delete node;
            size--;
            return rightNode;
        }

        node->left = removeMin(node->left);
        return node;
    }

    // 删除掉以node为根的二分搜索树中的最大节点
    // 返回删除节点后新的二分搜索树的根
    Node *removeMax(Node *node) {
        if (node->right == nullptr) {
            Node *leftNode = node->left;
            delete node;
            size--;
            return leftNode;
        }

        node->right = removeMax(node->right);
        return node;
    }

    // 删除掉以node为根的二分搜索树中键值为key的节点
    // 返回删除节点后新的二分搜索树的根
    Node *remove(Node *node, Key key) {
        if (node == nullptr) {
            return nullptr;
        }

        Node* retNode;
        if (key < node->key) {
            node->left = remove(node->left, key);
            retNode = node;
        } else if (key > node->key) {
            node->right = remove(node->right, key);
            retNode = node;
        } else {
            if (node->left == nullptr) {
                Node *rightNode = node->right;
                delete node;
                size--;
                retNode =  rightNode;
            }

            else if (node->right == nullptr) {
                Node *leftNode = node->left;
                delete node;
                size--;
                retNode =  leftNode;
            }

            else {
                Node *successor = new Node(minimum(node->right));
                //Node *precursor = new Node(maximum(node->right));
                size++;

                successor->right = remove(node->right, successor);
                successor->left = node->left;
                //precursor->left = removeMax(node->left);
                //precursor->right = node->right;

                delete node;
                size--;

                retNode = successor;
                //return precursor;
            }
        }

        if (retNode == nullptr)
            return nullptr;

        retNode->height = 1 + std::max(getHeight(retNode->left), getHeight(retNode->right));
        int balanceFactor = getBalanceFactor(retNode);
        if(std::abs(balanceFactor) > 1) {
            std::cout << "unbalanced : " << balanceFactor;
        }

        // 平衡维护
        if (balanceFactor > 1 && getBalanceFactor(retNode->left) >= 0)
            return rightRotate(retNode);

        if (balanceFactor < -1 && getBalanceFactor(retNode->right) >=0)
            return leftRotate(retNode);

        // LR
        if (balanceFactor > 1 && getBalanceFactor(retNode->left) < 0){
            retNode->left = leftRotate(retNode->left);
            return rightRotate(retNode);
        }

        // RL
        if (balanceFactor < -1 && getBalanceFactor(retNode->right) > 0){
            retNode->right= rightRotate(retNode->right);
            return leftRotate(retNode);
        }

        return retNode;
    }

};


#endif //AVL_AVL_H
