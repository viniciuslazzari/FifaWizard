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

int player_hashFunction(const int key){
    return key % 1000;
}

void player_insertHash(HashTable<int, Player>* table, const int key, const Player data){
    int hash_position = table->hashFunction(key);

    if (getNodeAddress<int, Player>(table->map[hash_position], key) == nullptr)
        table->map[hash_position] = insertNode<int, Player>(table->map[hash_position], key, data);
}

void player_addScore(HashTable<int, Player>* table, const int key, const float score){
    int hash_position = table->hashFunction(key);

    if (getNodeAddress<int, Player>(table->map[hash_position], key) != nullptr){
        table->map[hash_position]->data.score_count++;
        table->map[hash_position]->data.score_total += score;
    }
}