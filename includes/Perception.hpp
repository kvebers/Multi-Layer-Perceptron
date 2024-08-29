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

using FunctionPointer = void(*)(size_t);

void softmax(size_t i);
void relu(size_t i);
void sigmoid(size_t i);
void tanh(size_t i);


class Layer
{
    public:
        virtual ~Layer() = default;
        void InitializeWeights(size_t weights, string functionName);
    private:
        FunctionPointer returnFunctionToExecute(string &functionName);
};

class InputLayer : public Layer
{
    public:
        InputLayer(size_t size, string activationFunction);
        ~InputLayer();
    private:
        string layerName = "Input";
        size_t size;
        string activationFunction;

};

class HiddenLayer : public Layer
{
    public:
        HiddenLayer(size_t size, string activationFunction, string weightInitialization);
        ~HiddenLayer();
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
        ~OutputLayer();
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
size_t identityLabels(vector<pair<string, std::vector<float>>> &data);

#endif