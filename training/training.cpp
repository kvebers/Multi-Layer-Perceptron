#include "../includes/Perception.hpp"

extern map<string, WeightInitFunctionPointer> weightInitializationMap;
extern map<string, ActivationFunctionPointer> activationFunctionMap;

vector<float> myOwnTanh(vector<float> x);

// return value between 0 and infinity
vector<float> relu(vector<float> x)
{
    vector<float> outputs;
    outputs.reserve(x.size());
    for (size_t i = 0; i < x.size(); i++) outputs.push_back(static_cast<float>(max(0.0, static_cast<double>(x[i]))));
    return outputs;
}


vector<float> softmax(vector<float> x)
{
    vector<float> outputs;
    outputs.reserve(x.size());
    float sum = 0.0;
    for (size_t i = 0; i < x.size(); i++) sum += exp(x[i]);
    for (size_t i = 0; i < x.size(); i++) outputs.push_back(exp(x[i]) / sum);
    return outputs;
}

//s(x)= 1/(1+e^−x)
// return  value between 0 and 1
vector<float> sigmoid(vector<float> x)
{
    vector<float> outputs;
    outputs.reserve(x.size());
    for (size_t i = 0; i < x.size(); i++) outputs.push_back(1.0 / (1.0 + exp(-x[i])));
    return outputs;
}

// return value between -1 and 1
vector<float> myOwnTanh(vector<float> x)
{
    vector<float> outputs;
    outputs.reserve(x.size());
    for (size_t i = 0; i < x.size(); i++) outputs.push_back(tanh(x[i]));
    return outputs;
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

void training(vector<pair<string, std::vector<float>>> trainingData, vector<pair<string, std::vector<float>>>  testingData,  Network &network, size_t epochs, float learningRate)
{
    network.CheckValidNetwork();
    network.initializeNeuralNetworkWeights();
    network.initializeLabels(trainingData);
    (void) learningRate;
    for (size_t i = 0; i < epochs; i++)
    {
        for (size_t i = 0; i < trainingData.size(); i++)
        {
            std::vector<float> temp = network.predict(trainingData[i]);
            
            network.backpropagation(temp, trainingData[i].first);
        }
    }
    (void) testingData;
}
