#include "../includes/Perception.hpp"

vector<pair<string, std::vector<float>>> splitDataInVectors(const string &file, std::vector<size_t> &params, const size_t &prediction)
{
    ifstream input(file);
    vector<pair<string, std::vector<float>>> data;
    if (!input.is_open()) { cerr << "Error opening input file" << endl; return data;}
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
    catch (const std::exception &e){cerr << e.what() << endl; exit(1);}
}


void splitDataFiles(const string &inputFile, const string &trainingFile, const string &testingFile, const size_t &seed)
{
    ifstream input(inputFile);
    ofstream training(trainingFile);
    ofstream testing(testingFile);
    if (!input.is_open()){cerr << "Error opening input file" << endl; exit(1);}
    srand(seed);
    for (string line; getline(input, line);)
    {
        if (rand() % 2) training << line << endl;
        else testing << line << endl;
    }
}


size_t identityLabels(vector<pair<string, std::vector<float>>> &data) {
    map<string, int> uniqueLabels;
    for (auto &pair : data) uniqueLabels[pair.first] += 1;
    return uniqueLabels.size();
}