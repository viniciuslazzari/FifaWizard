#ifndef prefix_trie_h
#define prefix_trie_h

#include <iostream>
#include <vector>

#include "string_functions.hpp"

#define ALPHABET_SIZE 30

class TrieNode {
    public:
        TrieNode* children [ALPHABET_SIZE];

        int player_id;
        bool isEnd;

    TrieNode();
};

TrieNode::TrieNode(){
    for (int i = 0; i < ALPHABET_SIZE; i++)
        this->children[i] = nullptr;

    this->isEnd = false;
    this->player_id = 0;
}

int getCharIndex(const char key){
    if (key == ' ') return 26;
    if (key == '-') return 27;
    if (key == '.') return 28;
    if (key == '\'') return 29;

    return key - 'a';
}

void insertNodeTrie(TrieNode* root, std::string key, int player_key){
    TrieNode* node = root;

    key = stringTolower(key);

    for (size_t i = 0; i < key.length(); i++) {
        int index = getCharIndex(key[i]);

        if (!node->children[index])
            node->children[index] = new TrieNode();

        node = node->children[index];
    }

    node->player_id = player_key;
    node->isEnd = true;
}

void returnAllValues(TrieNode* root, std::vector<int>* keys){
    if (root->isEnd) keys->push_back(root->player_id);

    for (size_t i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            returnAllValues(root->children[i], keys);
}

std::vector<int> returnListOfKeys(TrieNode* root, std::string prefix){
    TrieNode* node = root;
    std::vector<int> keys;

    prefix = stringTolower(prefix);

    for (size_t i = 0; i < prefix.length(); i++) {
        int index = getCharIndex(prefix[i]);

        if (!node->children[index])
            return keys;

        node = node->children[index];
    }

    returnAllValues(node, &keys);

    return keys;
}

#endif