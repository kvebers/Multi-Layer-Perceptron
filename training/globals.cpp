#include "../includes/Perception.hpp"

map<string, WeightInitFunctionPointer> weightInitializationMap = {
    {"random", random},
    {"zeros", zeros},
    {"ones", ones},
    {"he", he},
    {"heNormal", heNormal}
};

map<string, ActivationFunctionPointer> activationFunctionMap = {
    {"relu", relu},
    {"softmax", softmax},
    {"sigmoid", sigmoid},
    {"tanh", myOwnTanh}
};

map<string, DerivativeActivationFunctionPointer> derivativeActivationFunctionMap = {
    {"relu", derivativeRelu},
    {"softmax", derivativeSoftmax},
    {"sigmoid", derivativeSigmoid},
    {"tanh", derivativeMyOwnTanh}
};
