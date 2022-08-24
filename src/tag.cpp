#include <vector>
#include "hash_table.hpp"

class Tag {
    public:
        std::vector<int> player_keys;
};

int tag_hashFunction(const int size, const std::string key){
    int result = 0;

    for (size_t i = 0; i < key.length(); i++) {
        result += key[i] * i;
    }

    return result % size;
}

void tag_addPlayer(HashTable<std::string, Tag>* table, const std::string key, const int player_key){
    int hash_position = table->hashFunction(table->size, key);

    Node<std::string, Tag>* address = getNodeAddress(table->map[hash_position], key);

    address->data.player_keys.push_back(player_key);
}

void tag_insertHash(HashTable<std::string, Tag>* table, const std::string key, const Tag data){
    int hash_position = table->hashFunction(table->size, key);

    table->map[hash_position] = insertNode<std::string, Tag>(table->map[hash_position], key, data);
}