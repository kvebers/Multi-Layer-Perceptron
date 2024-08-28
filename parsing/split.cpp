#include "../includes/Perception.hpp"

vector<pair<string, std::vector<float>>> splitDataInVectors(const string &file, std::vector<size_t> &params, const size_t &prediction)
{
    ifstream input(file);
    vector<pair<string, std::vector<float>>> data;
    if (!input.is_open())
    {
        cerr << "Error opening input file" << endl;
        return data;
    }
    try
    {
        for (string line; getline(input, line);)
        {
            vector<float> values;
            size_t pos = 0;
            size_t collumName = 0;
            string label;
            values.reserve(params.size());
            while (pos < line.size())
            {
                size_t nextPos = line.find(',', pos);
                if (nextPos == string::npos) nextPos = line.size();
                string value = line.substr(pos, nextPos - pos);
                if (collumName == prediction) label = value;
                else if (find(params.begin(), params.end(), collumName) != params.end()) values.push_back(stof(value));
                collumName++;
                pos = nextPos + 1;
            }
            data.push_back({label, values});
        }
        return data;
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << endl;
        exit(1);
    }
}


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


size_t identityLabels(vector<pair<string, std::vector<float>>> &data)
{
    size_t count = 0;
    map <string, int> uniqueLabels;
    for (auto &pair : data) uniqueLabels[pair.first];
    std::cout << "Unique labels: " << uniqueLabels.size() << std::endl;
    return uniqueLabels.size();
}
