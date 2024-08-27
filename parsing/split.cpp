
#include "../includes/Perception.hpp"


void splitBySeed(const size_t &seed, const size_t &row)
{
    (void) seed;
    (void) row;
    return;
}

void spitDataFiles(const string &input_file, const string &training_file, const string &testing_file, const size_t &seed)
{
    ifstream input(input_file);
    ofstream training(training_file);
    ofstream testing(testing_file);
    if (!input.is_open())
    {
        cerr << "Error opening input file" << endl;
        return;
    }
}
