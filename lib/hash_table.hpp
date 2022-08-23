#include "binary_tree.hpp"

const int size = 1000;

template <typename TKey, class TData>
class HashTable {
    public:
        Node<TKey, TData>** map;
        int (*hashFunction)(TKey);

        HashTable(int (*hashFunction)(TKey));

        void insertHash(const TKey key, const TData data);
        void printBlock(const TKey block);
};

template <typename TKey, class TData>
HashTable<TKey, TData>::HashTable(int (*hashFunction)(TKey)){
    this->hashFunction = hashFunction;
    map = (Node<TKey, TData>**)calloc(size, sizeof(Node<TKey, TData>*));
}

template <typename TKey, class TData>
void HashTable<TKey, TData>::insertHash(const TKey key, const TData data){
    int hash_position = (*hashFunction)(key);

    if (getNodeAddress(map[hash_position], key) == nullptr){
        map[hash_position] = insertNode(map[hash_position], key, data);
        return;
    }

    map[hash_position]->data.count++;
    map[hash_position]->data.total_score += data.total_score;
}

template <typename TKey, class TData>
void HashTable<TKey, TData>::printBlock(const TKey block){
    printTree(map[block]);
}