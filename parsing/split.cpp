#include "../includes/Perception.hpp"

void splitDataFiles(const string &input_file, const string &training_file, const string &testing_file, const size_t &seed)
{
    ifstream input(input_file);
    ofstream training(training_file);
    ofstream testing(testing_file);
    if (!input.is_open())
    {
        cerr << "Error opening input file" << endl;
        return;
    }
    srand(seed);
    for (string line; getline(input, line);)
    {
        if (rand() % 2) training << line << endl;
        else testing << line << endl;
    }
}
