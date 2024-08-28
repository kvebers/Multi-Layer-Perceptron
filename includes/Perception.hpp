#ifndef PERCEPTION_H
#define PERCEPTION_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>


using std::string;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::cerr;
using std::size_t;
using std::getline;
using std::vector;
using std::pair;

void splitDataFiles(const string &input_file, const string &training_file, const string &testing_file, const size_t &seed);
vector<pair<string, std::vector<float>>> splitDataInVectors(const string &file, std::vector<size_t> &params, const size_t &prediction);

#endif