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


void xavier(size_t i)
{
    std::cout << "xavier" << std::endl;
    (void) i;
}

void he(size_t i)
{
    std::cout << "he" << std::endl;
    (void) i;
}

void lecun(size_t i)
{
    std::cout << "lecun" << std::endl;
    (void) i;
}

void constant(size_t i)
{
    std::cout << "constant" << std::endl;
    (void) i;
}

void orthognal(size_t i)
{
    std::cout << "orthognal" << std::endl;
    (void) i;
}

void uniform(size_t i)
{
    std::cout << "uniform" << std::endl;
    (void) i;
}

void normal(size_t i)
{
    std::cout << "normal" << std::endl;
    (void) i;
}

void lecunNormal(size_t i)
{
    std::cout << "lecunNormal" << std::endl;
    (void) i;
}

void heNormal(size_t i)
{
    std::cout << "heNormal" << std::endl;
    (void) i;
}

void xavierNormal(size_t i)
{
    std::cout << "xavierNormal" << std::endl;
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
    {"ones", ones},
    {"xavier", xavier},
    {"he", he},
    {"lecun", lecun},
    {"constant", constant},
    {"orthognal", orthognal},
    {"uniform", uniform},
    {"normal", normal},
    {"lecunNormal", lecunNormal},
    {"heNormal", heNormal},
    {"xavierNormal", xavierNormal}
};




FunctionPointer Layer::returnFunctionToExecute(std::string &functionName, map<string, FunctionPointer> &functionMap)
{
    if (functionMap.find(functionName) != functionMap.end())
        return functionMap[functionName];
    else
        return nullptr;
}



void Layer::InitializeWeights(size_t weights, string functionName)
{
    FunctionPointer function = returnFunctionToExecute(functionName, weightInitializationMap);
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
