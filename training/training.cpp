#include "../includes/Perception.hpp"


#include <algorithm>

float relu(float x)
{
    return std::max(0.0, x);
}


float softmax(float x)
{
    return 
}

//s(x)= 1/(1+e^−x)
float sigmoid(float x)
{
    std::cout << "sigmoid" << std::endl;
}

float tanh(float x)
{
    std::cout << "tanh" << std::endl;
}


// Initialization Functions
float zeros(size_t i, size_t j)
{
    (void) i;
    (void) j;
    return 0.0;
}

// 1
float ones(size_t i, size_t j)
{
    (void) i;
    (void) j;
    return 1.0;
}

float random(size_t i, size_t j)
{
    (void) i;
    (void) j;
    float rand = random() % 200 / 100.0 - 1.0;
    return rand;
}

// takes the number of input parameters to calculate the limit
float he(size_t i, size_t j)
{
    (void) i;
    float limit = sqrt(6.0f / j);
    return (static_cast<float>(random()) / RAND_MAX) * 2 * limit - limit;
}

// normal distribution with mean 0 and std 1
float heNormal(size_t i, size_t j)
{
    (void) i;
    float stddev = sqrt(2.0f / j);
    return stddev * ((static_cast<float>(random()) / RAND_MAX) * 2 - 1);
}

map<string, WeightInitFunctionPointer> weightInitializationMap = {
    {"random", random},
    {"zeros", zeros},
    {"ones", ones},
    {"he", he},
    {"heNormal", heNormal}
};

WeightInitFunctionPointer Layer::returnFunctionToExecute(string &functionName, map<string, WeightInitFunctionPointer> &functionMap) {
    if (functionMap.find(functionName) != functionMap.end()) return functionMap[functionName];
    else return nullptr;
}



void Layer::InitializeWeights(size_t weights, string functionName)
{
    WeightInitFunctionPointer initFunction = returnFunctionToExecute(functionName, weightInitializationMap);
    if (initFunction == nullptr)
    {
        cerr << "Error: Activation function not found" << endl;
        exit(1);
    }
    neurons.resize(weights);
    for (size_t i = 0; i < weights; i++) neurons.push_back(initFunction(i, weights));
}

void training(vector<pair<string, std::vector<float>>> trainingData, vector<pair<string, std::vector<float>>>  testingData,  Network &network)
{
    (void) trainingData;
    (void) testingData;
    (void) network;

}
