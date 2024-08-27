#include "../includes/Perception.hpp"

int main()
{
    size_t seed = 2002;
    string input_file = "data.csv";
    string training_file = "training.csv";
    string testing_file = "testing.csv";
    vector<size_t> params;
    size_t prediction = 1;
    params.reserve(30);
    for (size_t i = 2; i < 32; i++)
    {
        params.push_back(i);
    }
    splitDataFiles(input_file, training_file, testing_file, seed);
    training(params, prediction, training_file, testing_file);
    return 0;
}