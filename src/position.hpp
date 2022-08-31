#ifndef position_h
#define position_h

#include <vector>
#include "hash_table.hpp"

class Position {
    public:
        std::vector<int> player_keys;
};

int position_hashFunction(const int size, const std::string key){
    int result = 0;

    for (size_t i = 0; i < key.length(); i++) {
        result += key[i] * i;
    }

    return result % size;
}

void position_addPlayer(Node<std::string, Position>* address, const int player_key){
    address->data.player_keys.push_back(player_key);
}

void position_insertHash(HashTable<std::string, Position>* table, const std::string key, const Position data){
    int hash_position = table->hashFunction(table->size, key);

    table->map[hash_position] = insertNode<std::string, Position>(table->map[hash_position], key, data);
}

#endif