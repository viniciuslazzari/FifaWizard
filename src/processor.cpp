#include <iostream>
#include <time.h>

#include "csv_parser.hpp"

#include "player.cpp"
#include "user.cpp"
#include "tag.cpp"

const std::string players_csv = "C:/Users/vinil/dev/Fifa/data/players.csv";
const std::string ratings_csv = "C:/Users/vinil/dev/Fifa/data/rating.csv";
const std::string tags_csv = "C:/Users/vinil/dev/Fifa/data/tags.csv";

void processPlayers(HashTable<int, Player>* table){
    io::CSVReader<3, io::trim_chars<' '>, io::double_quote_escape<',', '\"'>> in(players_csv);

    in.read_header(io::ignore_extra_column, "sofifa_id", "name", "player_positions");

    int key; std::string name; std::string player_positions;

    while(in.read_row(key, name, player_positions)){
        Player data = Player();

        data.name = name;
        data.player_positions = player_positions;

        table->insertHash(table, key, data);
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

void processTags(HashTable<std::string, Tag>* table){
    io::CSVReader<3> in(tags_csv);

    in.read_header(io::ignore_extra_column, "user_id", "sofifa_id", "tag");

    int user_key; int player_key; std::string key;

    while(in.read_row(user_key, player_key, key)){
        if (table->keyExists(key)){
            tag_addPlayer(table, key, player_key);
        } else {
            Tag tag = Tag();

            tag.player_keys.push_back(player_key);

            table->insertHash(table, key, tag);
        }
    }
}

void process(){
    auto players_table = HashTable<int, Player>(1000000, player_hashFunction, player_insertHash);
    auto users_table = HashTable<int, User>(1000000, user_hashFunction, user_insertHash);
    auto tags_table = HashTable<std::string, Tag>(1000000, tag_hashFunction, tag_insertHash);

    time_t start = time(NULL); 

    processPlayers(&players_table);
    processRatings(&players_table, &users_table);
    processTags(&tags_table);

    time_t end = time(NULL); 

    std::cout << (double)end - start << " sec" << std::endl;
}