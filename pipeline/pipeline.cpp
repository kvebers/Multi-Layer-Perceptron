#include "../includes/Perception.hpp"

int main()
{
    size_t seed = 2002;
    string input_file = "data.csv";
    string training_file = "training.csv";
    string testing_file = "testing.csv";
    vector<size_t> params;
    size_t prediction = 1;
    vector<pair<string, std::vector<float>>> training_data;
    vector<pair<string, std::vector<float>>> testing_data;
    params.reserve(30);
    for (size_t i = 2; i < 32; i++)
    {
        params.push_back(i);
    }
    splitDataFiles(input_file, training_file, testing_file, seed);
    training_data = splitDataInVectors(training_file, params, prediction);
    testing_data = splitDataInVectors(testing_file, params, prediction);
    cout << testing_data.size() << endl;
    cout << training_data.size() << endl;
    for (size_t i = 0; i < testing_data.size(); i++)
    {
        cout << testing_data[i].first << " ";
        for (size_t j = 0; j < testing_data[i].second.size(); j++)
        {
            cout << testing_data[i].second[j] << " ";
        }
        cout << endl;
    }
    // training(params);
    // predict();
    return 0;
}