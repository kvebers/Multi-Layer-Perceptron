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

void zeros(size_t i)
{
    std::cout << "zeros" << std::endl;
    (void) i;
}

void ones(size_t i)
{
    std::cout << "ones" << std::endl;
    (void) i;
}

void random(size_t i)
{
    std::cout << "random" << std::endl;
    (void) i;
}


map<string, FunctionPointer> functionMap = {
    {"softmax", softmax},
    {"relu", relu},
    {"sigmoid", sigmoid},
    {"tanh", tanh}
};

map<string, FunctionPointer> weightInitializationMap = {
    {"random", random},
    {"zeros", zeros},
    {"ones", ones}
};


FunctionPointer Layer::returnFunctionToExecute(std::string &functionName)
{
    if (weightInitializationMap.find(functionName) != weightInitializationMap.end())
        return weightInitializationMap[functionName];
    else
        return nullptr;
}




void Layer::InitializeWeights(size_t weights, string functionName)
{
    FunctionPointer function = returnFunctionToExecute(functionName);
    if (function == nullptr)
    {
        cerr << "Error: Activation function not found" << endl;
        exit(1);
    }
    for (size_t i = 0; i < weights; i++)
    {
        function(i);
    }
}



void training(vector<pair<string, std::vector<float>>> trainingData, vector<pair<string, std::vector<float>>>  testingData,  Network &network)
{
    (void) trainingData;
    (void) testingData;
    (void) network;
}
