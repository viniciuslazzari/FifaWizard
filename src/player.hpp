#ifndef player_h
#define player_h

#include <vector>
#include "hash_table.hpp"

class Player {
    public:
        std::string name;
        std::string player_positions;
        int score_count = 0;
        float score_total;

        double getMedian(){
            return (double)this->score_total / this->score_count;
        }
};

class PlayersModel {
    public:
        int key;
        std::string name;
        std::string positions;
        double median;
        int count;

        PlayersModel(int key, std::string name, std::string positions, double median, int count){
            this->key = key;
            this->name = name;
            this->positions = positions;
            this->median = median;
            this->count = count;
        }

        void display(){
            std::cout << this->key << " " 
                      << this->name << " " 
                      << this->positions << " "
                      << this->median << " " 
                      << this->count << std::endl;
        }
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

#endif