#include <iostream>
#include <time.h>
#include <vector>

#include "csv_parser.hpp"

#include "player.cpp"
#include "user.cpp"
#include "tag.cpp"

using namespace aria::csv;

void processPlayers(HashTable<int, Player>* table){
    std::ifstream f("data/players.csv");
    CsvParser parser(f);

    bool isData = false;

    for (auto& row : parser) {
        if (!isData) {
            isData = true;
            continue;
        }

        int key = std::stoi(row[0]);

        Player data = Player();

        data.name = row[1];
        data.player_positions = row[2];

        table->insertHash(table, key, data);
    }
}

void processRatings(HashTable<int, Player>* player_table, HashTable<int, User>* user_table){
    std::ifstream f("data/rating.csv");
    CsvParser parser(f);

    bool isData = false;

    for (auto& row : parser) {
        if (!isData) {
            isData = true;
            continue;
        }

        int user_key = std::stoi(row[0]);
        int player_key = std::stoi(row[1]);
        float score = std::stod(row[2]);

        player_addScore(player_table, player_key, score);

        if (user_table->keyExists(user_key)){
            Rating rating = Rating();

            rating.player_key = player_key;
            rating.score = score;

            user_addRating(user_table, user_key, rating);
        } else {
            User user = User();

            user_table->insertHash(user_table, user_key, user);
        }
    }
}

void processTags(HashTable<std::string, Tag>* table){
    std::ifstream f("data/tags.csv");
    CsvParser parser(f);

    bool isData = false;

    for (auto& row : parser) {
        if (!isData) {
            isData = true;
            continue;
        }

        std::string key = row[2];
        int player_key = std::stoi(row[1]);

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
    auto players_table = HashTable<int, Player>(player_hashFunction, player_insertHash);
    auto users_table = HashTable<int, User>(user_hashFunction, user_insertHash);
    auto tags_table = HashTable<std::string, Tag>(tag_hashFunction, tag_insertHash);

    clock_t tStart = clock();

    processPlayers(&players_table);
    processRatings(&players_table, &users_table);
    processTags(&tags_table);

    double time_spend = (double)(clock() - tStart) / CLOCKS_PER_SEC;

    std::cout << time_spend << std::endl;
}