//
// Created by yann on 2021/3/3.
//

#ifndef TRIE_TRIE_H
#define TRIE_TRIE_H

#include "map"
#include "string"

class Trie {
private:
    class Node {
    public:
        bool isWord;
        std::map<char, Node> next;

        Node(bool isWord) {
            this->isWord = isWord;
        }

        Node() : isWord(false), next() {}
    };

    Node *root;
    int size;

public:
    Trie() {
        root = new Node();
        size = 0;
    }

    int getSize() const {
        return size;
    }

    void add(const std::string &word) {

        Node *cur = root;
        for (char c : word) {
            if (cur->next.find(c) == cur->next.end()) {
                cur->next.insert(std::make_pair(c, new Node()));
            }

            cur = &cur->next.find(c)->second;
        }

        if (!cur->isWord) {
            cur->isWord = true;
            ++size;
        }
    }

    bool contain(const std::string &word) {

        Node *cur = root;
        for (char c : word) {
            if (cur->next.find(c) == cur->next.end()) {
                return false;
            }

            cur = &cur->next.find(c)->second;
        }

        return cur->isWord;
    }

    bool isPrefix(const std::string& word){

        Node* cur = root;
        for (char c : word){
            if (cur->next.find(c) == cur->next.end())
                return false;

            cur = &cur->next.find(c)->second;
        }

        return true;
    }





};

#endif //TRIE_TRIE_H
