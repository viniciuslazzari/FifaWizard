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

int user_hashFunction(const int size, const int key){
    return key % size;
}

void user_addRating(Node<int, User>* address, const Rating rating){
    address->data.ratings.push_back(rating);
}

void user_insertHash(HashTable<int, User>* table, const int key, const User data){
    int hash_position = table->hashFunction(table->size, key);

    table->map[hash_position] = insertNode<int, User>(table->map[hash_position], key, data);
}