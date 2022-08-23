#include <vector>
#include "hash_table.hpp"

class Rating {
    public:
        int player_key;
        float score;
};

class User {
    public:
        std::vector<Rating> ratings;
};

int user_hashFunction(const int key){
    return key % 1000;
}

void user_addRating(HashTable<int, User>* table, const int key, const Rating rating){
    int hash_position = table->hashFunction(key);

    table->map[hash_position]->data.ratings.push_back(rating);
}

void user_insertHash(HashTable<int, User>* table, const int key, const User data){
    int hash_position = table->hashFunction(key);

    table->map[hash_position] = insertNode<int, User>(table->map[hash_position], key, data);
}