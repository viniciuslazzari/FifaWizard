#include <iostream>
#include <time.h>
#include "csv_parser.hpp"
#include "hash_table.hpp"

using namespace aria::csv;

class RatingData {
    public:
        int count = 1;
        float total_score;
};

int hash(const int id){
    return id % 1000;
}

int main()
{
    HashTable<int, RatingData> table = HashTable<int, RatingData>(hash);

    std::ifstream f("data/rating.csv");
    CsvParser parser(f);

    time_t start, end;

    start = time(NULL);

    bool isData = false;

    for (auto& row : parser) {
        if (!isData) {
            isData = true;
            continue;
        }

        RatingData data = RatingData();

        data.total_score = std::stod(row[2]);

        int id = std::stoi(row[1]);

        table.insertHash(id, data);
    }

    end = time(NULL);

    double time_taken = double(end - start);

    table.printBlock(5);

    std::cout << "Time taken by program is : " << time_taken << std::endl;
}