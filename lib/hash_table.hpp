#ifndef hash_table_h
#define hash_table_h

#include "binary_tree.hpp"

const int size = 1000;

template <typename TKey, class TData>
class HashTable {
    public:
        Node<TKey, TData>** map;
        int (*hashFunction)(TKey);
        void (*insertHash)(HashTable<TKey, TData>*, TKey, TData);

        HashTable(int (*hashFunction)(TKey), void (*insertHash)(HashTable<TKey, TData>*, TKey, TData));

        void printBlock(const int block);
        bool keyExists(const TKey block);
};

template <typename TKey, class TData>
HashTable<TKey, TData>::HashTable(int (*hashFunction)(TKey), void (*insertHash)(HashTable<TKey, TData>*, TKey, TData)){
    this->hashFunction = hashFunction;
    this->insertHash = insertHash;

    map = (Node<TKey, TData>**)calloc(size, sizeof(Node<TKey, TData>*));
}

template <typename TKey, class TData>
void HashTable<TKey, TData>::printBlock(const int key){
    printTree(map[key]);
}

template <typename TKey, class TData>
bool HashTable<TKey, TData>::keyExists(const TKey key){
    const int hash_position = (*hashFunction)(key);

    return getNodeAddress(map[hash_position], key) != nullptr;
}

#endif