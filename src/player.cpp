#include <iostream>
#include <vector>
#include "hash_table.hpp"

class Player {
    public:
        std::string name;
        std::string player_positions;
        int score_count = 0;
        float score_total;
};

int player_hashFunction(const int size, const int key){
    return key % size;
}

void player_insertHash(HashTable<int, Player>* table, const int key, const Player data){
    int hash_position = table->hashFunction(table->size, key);

    table->map[hash_position] = insertNode(table->map[hash_position], key, data);
}

void player_addScore(Node<int, Player>* address, const float score){
    address->data.score_count++;
    address->data.score_total += score;
}