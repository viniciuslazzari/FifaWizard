#ifndef searcher_h
#define searcher_h

#include "string_functions.hpp"
#include "array_functions.hpp"

void printPlayersByNamePrefix(std::string name, TrieNode* trie, HashTable<int, Player>* players_table){
    Node<int, Player>* address;

    std::vector<int> player_keys = returnListOfKeys(trie, name);

    for(int key : player_keys){
        address = players_table->findKeyNodeAddress(key);

        PlayersModel model = PlayersModel(address->key, 
                                          address->data.name,
                                          address->data.player_positions,
                                          address->data.getMedian(),
                                          address->data.score_count);

        model.display();
    }
}

void printRatingsByUser(int user, HashTable<int, User>* users_table, HashTable<int, Player>* players_table){
    Node<int, User>* user_address;
    std::vector<int> user_scores;
    std::vector<Rating> user_ratings;

    user_address = users_table->findKeyNodeAddress(user);
    user_ratings = user_address->data.ratings;

    user_ratings = quicksortObj(user_ratings, 0, user_ratings.size() - 1);

    std::reverse(user_ratings.begin(), user_ratings.end());
    user_ratings = {user_ratings.begin(), user_ratings.begin() + 20}; 

    for(Rating rating : user_ratings){
        Node<int, Player>* player_address = players_table->findKeyNodeAddress(rating.player_key);

        RatingsUserModel model = RatingsUserModel(player_address->key, 
                                                  player_address->data.name,
                                                  player_address->data.getMedian(),
                                                  player_address->data.score_count,
                                                  rating.score);

        model.display();
    }
}

void printPlayerByPosition(std::string position, int amount, HashTable<std::string, Position>* positions_table, HashTable<int, Player>* players_table){
    Node<std::string, Position>* position_address;
    Node<int, Player>* player_address;
    std::vector<int> player_keys;
    std::vector<PlayersModel> models;

    position_address = positions_table->findKeyNodeAddress(position);

    player_keys = position_address->data.player_keys;

    for (int player_key : player_keys){

        player_address = players_table->findKeyNodeAddress(player_key);

        if (player_address->data.score_count < 1000) continue;

        PlayersModel model = PlayersModel(player_address->key, 
                                          player_address->data.name,
                                          player_address->data.player_positions,
                                          player_address->data.getMedian(),
                                          player_address->data.score_count);

        models.push_back(model);
    }

    models = quicksortObj(models, 0, models.size() - 1);

    std::reverse(models.begin(), models.end());
    models = {models.begin(), models.begin() + amount}; 

    for (auto model : models){
        model.display();
    }
}

void printPlayersByTag(std::vector<std::string> tags, HashTable<std::string, Tag>* tags_table, HashTable<int, Player>* players_table){
    Node<std::string, Tag>* tag_address;
    Node<int, Player>* player_address;
    std::vector<int> player_keys, tag_players;

    for (std::string tag : tags){
        tag_address = tags_table->findKeyNodeAddress(tag);

        tag_players = removeDups(tag_address->data.player_keys);

        if (player_keys.size() == 0){
            player_keys = tag_players;
            continue;
        }

        player_keys = intersection(player_keys, tag_players);
    }

    for (int key: player_keys){
        player_address = players_table->findKeyNodeAddress(key);

        PlayersModel model = PlayersModel(player_address->key, 
                                          player_address->data.name,
                                          player_address->data.player_positions,
                                          player_address->data.getMedian(),
                                          player_address->data.score_count);

        model.display();
    }
}

void search(HashTable<int, Player>* players_table, 
            HashTable<std::string, Position>* positions_table, 
            HashTable<int, User>* users_table, 
            HashTable<std::string, Tag>* tags_table,
            TrieNode* players_trie)
{
    std::string input;

    getline(std::cin, input);

    if (input.substr(0,6) == "player"){
        std::string name  = input.substr(7);

        printPlayersByNamePrefix(name, players_trie, players_table);
    } else if (input.substr(0,4) == "user"){
        int user = stoi(input.substr(5));

        printRatingsByUser(user, users_table, players_table);
    } else if (input.substr(0,3) == "top"){
        size_t pos = input.find(' ');

        std::string position = input.substr(pos + 1);
        position = removeChar(position, '\'');

        int amount = stoi(input.substr(3, pos - 3));

        printPlayerByPosition(position, amount, positions_table, players_table);
    } else if (input.substr(0,4) == "tags"){
        size_t pos = input.find(' ');

        std::vector<std::string> tags = splitStringWithQuotes(input.substr(pos + 1));

        printPlayersByTag(tags, tags_table, players_table);
    } else {
        std::cout << "Command not found!" << std::endl;
    }
}

#endif