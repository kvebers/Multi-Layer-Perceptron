
#include <iostream>
#include <fstream>
#include "../includes/Perception.hpp"

void splitBySeed(const &size_t seed, const size_t &row)
{

}

check_if_file_ex


void spitDataFiles(const string &input_file, const string &training_file, const string &testing_file, const size_t &seed)
{
    ifsteam input(input_file);
    ofstream training(training_file);
    ofstream testing(testing_file);

    if (!input.is_open())
    {
        cerr << "Error opening input file" << endl;
        return;
    }
    std::ofstream training(trainining_file, ios::out);
    std::ofstream testing(testing_file, ios::out);
}