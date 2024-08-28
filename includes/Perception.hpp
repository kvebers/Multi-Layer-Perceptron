#ifndef PERCEPTION_H
#define PERCEPTION_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>


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
using std::map;

class Layer
{
    public:
        virtual ~Layer() = default;
};

class InputLayer : public Layer
{
    public:
        InputLayer(size_t size, string activationFunction);
    private:
        string layerName = "Input";
        size_t size;
        string activationFunction;

};

class HiddenLayer : public Layer
{
    public:
        HiddenLayer(size_t size, string activationFunction, string weightInitialization);
    private:
        string layerName = "Hidden";
        size_t size;
        string activationFunction;
        string weightInitialization;
};

class OutputLayer : public Layer
{
    public:
        OutputLayer(size_t size, string activationFunction, string weightInitialization);
    private:
        string layerName = "Output";
        size_t size;
        string activationFunction;
        string weightInitialization;
};

class Network
{
    public:
        Network();
        ~Network();
        void addLayer(Layer &layer);
    private:
        vector<Layer> layers;
};


void splitDataFiles(const string &input_file, const string &training_file, const string &testing_file, const size_t &seed);
vector<pair<string, std::vector<float>>> splitDataInVectors(const string &file, std::vector<size_t> &params, const size_t &prediction);
void training(vector<pair<string, std::vector<float>>> trainingData, vector<pair<string, std::vector<float>>>  testingData,  Network &network);

#endif