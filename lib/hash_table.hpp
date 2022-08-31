#ifndef hash_table_h
#define hash_table_h

#include "binary_tree.hpp"
#include <iomanip>

template <typename TKey, class TData>
class HashTable {
    public:
        int size;
        Node<TKey, TData>** map;
        int (*hashFunction)(int size, TKey);
        void (*insertHash)(HashTable<TKey, TData>*, TKey, TData);

        HashTable(int size, int (*hashFunction)(int, TKey), void (*insertHash)(HashTable<TKey, TData>*, TKey, TData));

        void printBlock(const int block);
        Node<TKey, TData>* findKeyNodeAddress(const TKey key);

        void returnOccupation(){
            double count = 0;

            for(int i = 0; i < size; i++){
                if (this->map[i]) {
                    count++;
                }
            }

            double ocupation = count / this->size;

            std::cout << ocupation << std::fixed << std::setprecision(5) << std::endl;
        }
};

template <typename TKey, class TData>
HashTable<TKey, TData>::HashTable(int size, int (*hashFunction)(int, TKey), void (*insertHash)(HashTable<TKey, TData>*, TKey, TData)){
    this->size = size;
    this->hashFunction = hashFunction;
    this->insertHash = insertHash;

    map = (Node<TKey, TData>**)calloc(size, sizeof(Node<TKey, TData>*));
}

template <typename TKey, class TData>
void HashTable<TKey, TData>::printBlock(const int key){
    printTree(map[key]);
}

template <typename TKey, class TData>
Node<TKey, TData>* HashTable<TKey, TData>::findKeyNodeAddress(const TKey key){
    const int hash_position = (*hashFunction)(this->size, key);

    return getNodeAddress(map[hash_position], key);
}

#endif