#include <iostream>
#include <time.h>
#include <vector>
#include "csv_parser.hpp"
#include "player.cpp"
#include "user.cpp"

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

void processUsers(HashTable<int, User>* table){
    std::ifstream f("data/minirating.csv");
    CsvParser parser(f);

    bool isData = false;

    for (auto& row : parser) {
        if (!isData) {
            isData = true;
            continue;
        }

        int key = std::stoi(row[0]);

        User data = User();

        table->insertHash(table, key, data);
    }
}


void processRatings(HashTable<int, Player>* player_table, HashTable<int, User>* user_table){
    std::ifstream f("data/minirating.csv");
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

        Rating data = Rating();

        data.player_key = player_key;
        data.score = score;

        user_addRating(user_table, user_key, data);
    }
}

void process(){
    HashTable<int, Player> players_table = HashTable<int, Player>(player_hashFunction, player_insertHash);
    HashTable<int, User> users_table = HashTable<int, User>(user_hashFunction, user_insertHash);

    processPlayers(&players_table);
    processUsers(&users_table);

    processRatings(&players_table, &users_table);
}