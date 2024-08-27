#include "../includes/Perception.hpp"

int main()
{
    size_t seed = 2002;
    string input_file = "data.csv";
    string training_file = "training.csv";
    string testing_file = "testing.csv";
    splitDataFiles(input_file, training_file, testing_file, seed);
    return 0;
}