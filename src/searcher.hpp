#ifndef searcher_h
#define searcher_h

#include "array_functions.hpp"

void printPlayersByNamePrefix(TrieNode* trie, HashTable<int, Player>* players_table){
    std::string name;
    Node<int, Player>* address;

    std::cin >> name;

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

void printRatingsByUser(HashTable<int, User>* users_table, HashTable<int, Player>* players_table){
    Node<int, User>* user_address;
    std::string input;
    std::vector<int> user_scores;
    std::vector<Rating> user_ratings;
    int user_key;

    getline(std::cin, input);

    user_key = stoi(input);

    user_address = users_table->findKeyNodeAddress(user_key);
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

void printPlayerByPosition(HashTable<std::string, Position>* positions_table, HashTable<int, Player>* players_table){
    std::string input;
    Node<std::string, Position>* position_address;
    Node<int, Player>* player_address;
    std::vector<int> player_keys;
    std::vector<PlayersModel> models;

    getline(std::cin, input);

    position_address = positions_table->findKeyNodeAddress(input);

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
    models = {models.begin(), models.begin() + 10}; 

    for (auto model : models){
        model.display();
    }
}

void printPlayersByTag(HashTable<std::string, Tag>* tags_table, HashTable<int, Player>* players_table){
    std::string name;
    Node<std::string, Tag>* tag_address;
    Node<int, Player>* player_address;
    std::vector<int> player_keys, tag_players;

    getline(std::cin, name);

    std::vector<std::string> tags = splitStringWithQuotes(name);

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

void mainSearch(){
    
}

#endif