#include <iostream>
#include <vector>
#include <algorithm>

#include "processor.hpp"
#include "searcher.hpp"

int main(){
    auto players_table = HashTable<int, Player>(20000, player_hashFunction, player_insertHash);
    auto positions_table = HashTable<std::string, Position>(30, position_hashFunction, position_insertHash);
    auto users_table = HashTable<int, User>(200000, user_hashFunction, user_insertHash);
    auto tags_table = HashTable<std::string, Tag>(800, tag_hashFunction, tag_insertHash);

    auto players_trie = TrieNode();

    process(&players_table, &positions_table, &users_table, &tags_table, &players_trie);

    while (true){
        search(&players_table, &positions_table, &users_table, &tags_table, &players_trie);
    }
}