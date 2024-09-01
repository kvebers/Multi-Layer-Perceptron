#ifndef PERCEPTION_H
#define PERCEPTION_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>


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
using std::max;

using WeightInitFunctionPointer = float(*)(size_t, size_t); 
using ActivationFunctionPointer = vector<float>(*)(vector<float>);

vector<float> relu(vector<float> x);
vector<float> softmax(vector<float> x);
vector<float> sigmoid(vector<float> x);
vector<float> myOwnTanh(vector<float> x);

float zeros(size_t i, size_t j);
float ones(size_t i, size_t j);
float random(size_t i, size_t j);
float he(size_t i, size_t j);
float heNormal(size_t i, size_t j);




class Layer
{
    public:
        virtual ~Layer() = default;
        void InitializeWeights(size_t neuronCount, string functionName, size_t previousLayerSize);
        vector<float> neurons;
        vector<vector<float>> weights;
        string activationFunction;
        string layerName;
        WeightInitFunctionPointer returnFunctionToExecute(std::string &functionName, std::map<std::string, WeightInitFunctionPointer> &functionMap);
        ActivationFunctionPointer returnFunctionToExecute(string &functionName, map<string, ActivationFunctionPointer> &functionMap);
};

class InputLayer : public Layer
{
    public:
        InputLayer(size_t size, string activationFunction);
        ~InputLayer();
        string layerName;
        size_t size;
        string activationFunction;
};

class HiddenLayer : public Layer
{
    public:
        HiddenLayer(size_t size, string activationFunction, string weightInitialization);
        ~HiddenLayer();
        size_t size;
        string activationFunction;
        string weightInitialization;
};

class OutputLayer : public Layer
{
    public:
        OutputLayer(size_t size, string activationFunction, string weightInitialization);
        ~OutputLayer();
        string activationFunction;
        string weightInitialization;
        size_t size;
};

class Network
{
    public:
        Network();
        ~Network();
        void addLayer(Layer &layer);
        void CheckValidNetwork();
        vector<Layer> layers;

};


void splitDataFiles(const string &input_file, const string &training_file, const string &testing_file, const size_t &seed);
vector<pair<string, std::vector<float>>> splitDataInVectors(const string &file, std::vector<size_t> &params, const size_t &prediction);
void training(vector<pair<string, std::vector<float>>> trainingData, vector<pair<string, std::vector<float>>>  testingData,  Network &network, size_t epochs, float learningRate);
size_t identityLabels(vector<pair<string, std::vector<float>>> &data);

#endif