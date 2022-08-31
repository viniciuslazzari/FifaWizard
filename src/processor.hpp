#ifndef processor_h
#define processor_h

#include <iostream>
#include <time.h>

#include "csv_parser.hpp"
#include "player.hpp"
#include "position.hpp"
#include "user.hpp"
#include "tag.hpp"
#include "prefix_trie.hpp"
#include "string_functions.hpp"

const std::string players_csv = "C:/Users/vinil/dev/Fifa/data/players.csv";
const std::string ratings_csv = "C:/Users/vinil/dev/Fifa/data/rating.csv";
const std::string tags_csv = "C:/Users/vinil/dev/Fifa/data/tags.csv";

void handlePlayer(HashTable<int, Player>* table, int key, std::string name, std::string player_positions){
    Player data = Player();

    data.name = name;
    data.player_positions = player_positions;

    table->insertHash(table, key, data);
}

void handlePosition(HashTable<std::string, Position>* table, std::string key, int player_key){
    Node<std::string, Position>* position_node_address = table->findKeyNodeAddress(key);

    if (position_node_address == nullptr){
        Position position = Position();

        position.player_keys.push_back(player_key);

        table->insertHash(table, key, position);
    }else{
        position_addPlayer(position_node_address, player_key);
    }
}

void processPlayers(HashTable<int, Player>* players_table, TrieNode* trie, HashTable<std::string, Position>* positions_table){
    io::CSVReader<3, io::trim_chars<' '>, io::double_quote_escape<',', '\"'>> in(players_csv);

    in.read_header(io::ignore_extra_column, "sofifa_id", "name", "player_positions");

    int key; 
    std::string name; 
    std::string player_positions;

    std::vector<std::string> player_positions_arr;

    while(in.read_row(key, name, player_positions)){
        player_positions_arr = splitString(player_positions, ", ");

        handlePlayer(players_table, key, name, player_positions);
        insertNodeTrie(trie, name, key);

        for(std::string position : player_positions_arr){
            handlePosition(positions_table, position, key);
        }
    }
}

void handlePlayerRating(HashTable<int, Player>* player_table, int player_key, float score){
    Node<int, Player>* player_node_address = player_table->findKeyNodeAddress(player_key);

    player_addScore(player_node_address, score);
}

void handleUser(HashTable<int, User>* user_table, int user_key, int player_key, float score){
    Rating rating = Rating();

    rating.player_key = player_key;
    rating.score = score;

    Node<int, User>* user_node_address = user_table->findKeyNodeAddress(user_key);

    if (user_node_address == nullptr){
        User user = User();

        user.ratings.push_back(rating);

        user_table->insertHash(user_table, user_key, user);
    }else{
        user_addRating(user_node_address, rating);
    }
}

void processRatings(HashTable<int, Player>* player_table, HashTable<int, User>* user_table){
    io::CSVReader<3> in(ratings_csv);

    in.read_header(io::ignore_extra_column, "user_id", "sofifa_id", "rating");

    int user_key; int player_key; float score;

    while(in.read_row(user_key, player_key, score)){
        handlePlayerRating(player_table, player_key, score);
        handleUser(user_table, user_key, player_key, score);
    }
}

void handleTag(HashTable<std::string, Tag>* table, int player_key, std::string key){
    Node<std::string, Tag>* tag_node_address = table->findKeyNodeAddress(key);

    if (tag_node_address == nullptr){
        Tag tag = Tag();

        tag.player_keys.push_back(player_key);

        table->insertHash(table, key, tag);
    }else{
        tag_addPlayer(tag_node_address, player_key);
    }
}

void processTags(HashTable<std::string, Tag>* table){
    io::CSVReader<3> in(tags_csv);

    in.read_header(io::ignore_extra_column, "user_id", "sofifa_id", "tag");

    int user_key; 
    int player_key; 
    std::string key;

    while(in.read_row(user_key, player_key, key)){
        handleTag(table, player_key, key);
    }
}

void process(HashTable<int, Player>* players_table, 
             HashTable<std::string, Position>* positions_table, 
             HashTable<int, User>* users_table, 
             HashTable<std::string, Tag>* tags_table,
             TrieNode* players_trie)
{
    time_t start = time(NULL); 

    processPlayers(players_table, players_trie, positions_table);
    processRatings(players_table, users_table);
    processTags(tags_table);

    // players_table.returnOccupation();
    // positions_table.returnOccupation();
    // users_table.returnOccupation();
    // tags_table.returnOccupation();

    time_t end = time(NULL); 

    std::cout << (double)end - start << " sec" << std::endl;
}

#endif