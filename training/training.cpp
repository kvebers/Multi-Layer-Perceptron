#include "../includes/Perception.hpp"


void relu(size_t i)
{
    std::cout << "relu" << std::endl;
    (void) i;
}

void softmax(size_t i)
{
    std::cout << "softmax" << std::endl;
    (void) i;
}

void sigmoid(size_t i)
{
    std::cout << "sigmoid" << std::endl;
    (void) i;
}

void tanh(size_t i)
{
    std::cout << "tanh" << std::endl;
    (void) i;
}


// Initialization Functions
float zeros(size_t i, size_t j)
{
    (void) i;
    (void) j;
    return 0.0;
}

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



std::map<std::string, ActivationFunctionPointer> functionMap = {
    {"softmax", softmax},
    {"relu", relu},
    {"sigmoid", sigmoid},
    {"tanh", tanh}
};

std::map<std::string, WeightInitFunctionPointer> weightInitializationMap = {
    {"random", random},
    {"zeros", zeros},
    {"ones", ones},
    {"he", he},
    {"heNormal", heNormal}
};

ActivationFunctionPointer Layer::returnFunctionToExecute(string &functionName, map<string, ActivationFunctionPointer> &functionMap) {
    if (functionMap.find(functionName) != functionMap.end())
        return functionMap[functionName];
    else
        return nullptr;
}

WeightInitFunctionPointer Layer::returnFunctionToExecute(string &functionName, map<string, WeightInitFunctionPointer> &functionMap) {
    if (functionMap.find(functionName) != functionMap.end())
        return functionMap[functionName];
    else
        return nullptr;
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
    for (size_t i = 0; i < weights; i++)
    {
        std::cout << initFunction(i, weights) << std::endl;
    }
}



void training(vector<pair<string, std::vector<float>>> trainingData, vector<pair<string, std::vector<float>>>  testingData,  Network &network)
{
    (void) trainingData;
    (void) testingData;
    (void) network;
}
