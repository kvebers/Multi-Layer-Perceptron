#ifndef PERCEPTION_H
#define PERCEPTION_H

#include <iostream>
#include <fstream>

using std::string;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::cerr;
using std::size_t;
using std::getline;

void splitDataFiles(const string &input_file, const string &training_file, const string &testing_file, const size_t &seed);

#endif