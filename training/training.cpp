#include "../includes/Perception.hpp"

void training(const vector<size_t> &parameters, const size_t &prediction, const string &training_file, const string &testing_file)
{
    // Function implementation
    for (const size_t &param : parameters)
    {
        std::cout << param << std::endl;
    }
    std::cout << prediction << std::endl;
    std::cout << training_file << std::endl;
    std::cout << testing_file << std::endl;
}