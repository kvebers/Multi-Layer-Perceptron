#ifndef PERCEPTION_H
#define PERCEPTION_H

#include <iostream>
#include <fstream>

using namespace std::string;
using namespace std::ifstream;
using namespace std::ofstream;
using namespace std::cout;
using namespace std::endl;
using namespace std::cerr;
using namespace std::ios;


void splitBySeed(const &size_t seed, const size_t &row);
void spitDataFiles(const string &input_file, const string &training_file, const string &testing_file, const size_t &seed);

#endif