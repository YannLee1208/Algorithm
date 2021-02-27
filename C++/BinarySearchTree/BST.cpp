//
// Created by yann on 2021/2/27.
//

#include <stack>
#include <queue>
#include "iostream"

using namespace std;

template<typename Key, typename Value>
class BST {

private:
    struct Node {
        Key key;
        Value value;
        Node *left;
        Node *right;

        Node(Key key, Value value) : key(key), value(value), left(NULL), right(NULL) {
        }
    };

    Node *root;
    int count;

    // 向以node为根的BST中插入 返回插入后的root
    Node *insert(Node *node, Key key, Value value) {

        if (node == NULL) {
            count++;
            return new Node(key, value);
        }

        if (key == node->key)
            node->value = value;
        else if (key < node->key)
            node->left = insert(node->left, key, value);
        else
            node->right = insert(node->right, key, value);

        return node;
    }

    bool contain(Node *node, Key key) {

        if (node == NULL)
            return false;

        if (node->key == key)
            return true;
        else if (node->key > key)
            return contain(node->left, key);
        else
            return contain(node->right, key);
    }

    Value *search(Node *node, Key key) {
        if (node == NULL)
            return NULL;

        if (node->key == key)
            return &(node->value);
        else if (node->key > key)
            return search(node->left, key);
        else
            return search(node->right, key);
    }

    void preOrder(Node *node) {

        if (node != NULL) {
            cout << node->key << endl;
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void destroy(Node *node) {

        if (node != NULL) {
            destroy(node->left);
            destroy(node->right);
            delete node;
            count--;
        }
    }

    Node *minNode(Node *node) {
        if (node->left == NULL)
            return node;
        else
            return minNode(node->left);
    }

    Node *removeMin(Node *node) {

        if (node->left == NULL) {

            Node *rightNode = node->right;
            delete node;
            count--;
            return rightNode;
        }

        node->left = removeMin(node->left);
        return node;
    }

    Node *remove(Node *node, Key key) {

        if (node == NULL)
            return NULL;

        if (key < node->key){
            node->left = remove(node->left, key);
            return node;
        } else if (key > node->key){
            node->right = remove(node->right, key);
            return node;
        } else{
            if ( node->left == NULL){
                Node* rightNode = node->right;
                delete node;
                count --;
                return rightNode;
            } else if (node->right == NULL){
                Node *leftNode = node->left;
                delete node;
                count --;
                return leftNode;
            } else{
                Node *succesor = new Node(minNode(node->right));
                count ++;
                succesor->right = removeMin(node->right);
                succesor->left = node->left;
                delete node;
                count --;

                return succesor;
            }
        }
    }

public:
    BST() {
        root = NULL;
        count = 0;
    }

    ~BST() {
        destroy(root);
    }

    int size() { return count };

    int isEmpty() { return count == 0; }

    void insert(Key key, Value value) {
        root = insert(root, key, value);
    }

    bool contain(Key key) {
        return contain(root, key);
    }

    Value *search(Key key) {
        return search(root, key);
    }

    // 前序
    void preOrder() {
        preOrder(root);
    }

    void preOrderNonCur() {

        if (root == NULL)
            return;

        stack<Node *> stack;
        stack.push(root);
        while (!stack.empty()) {

            Node *node = stack.top();
            stack.pop();
            cout << node->value;

            if (node->right != NULL)
                stack.push(node->right);

            if (node->left != NULL)
                stack.push(node->left);
        }
    }

    void preorderTraversalNew(Node *root, vector<Value> &path) {
        stack<pair<Node *, bool> > s;
        s.push(make_pair(root, false));
        bool visited;
        while (!s.empty()) {
            root = s.top().first;
            visited = s.top().second;
            s.pop();
            if (root == NULL)
                continue;
            if (visited) {
                path.push_back(root->val);
            } else {
                s.push(make_pair(root->right, false));
                s.push(make_pair(root->left, false));
                s.push(make_pair(root, true));
            }
        }
    }

    void levelOrder() {

        queue<Node *> q;
        q.push(root);
        while (!q.empty()) {
            Node *node = q.pop();
            cout << node->value;

            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
        }
    }

    Key minimum() {
        Node *minNode = minimum(root);
        return minNode->key;
    }

    void removeMin() {
        if (root == NULL)
            return;

        root = removeMin(root);
    }


    void remove(Key key) {
        root = remove(root, key);
    }

};

