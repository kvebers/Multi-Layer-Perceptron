#include "../includes/Perception.hpp"

int main()
{
    // data preprocessing
    size_t seed = 2002;
    string input_file = "data_normalized.csv";
    string trainingFile = "training.csv";
    string testingFile = "testing.csv";
    vector<size_t> params;
    size_t prediction = 1;
    vector<pair<string, std::vector<float>>> trainingData;
    vector<pair<string, std::vector<float>>> testingData;
    params.reserve(30);
    for (size_t i = 2; i < 32; i++) params.push_back(i);

    // data spliting training / testing
    splitDataFiles(input_file, trainingFile, testingFile, seed);
    trainingData = splitDataInVectors(trainingFile, params, prediction);
    testingData = splitDataInVectors(testingFile, params, prediction);

    // create network
    Network network;
    network.addLayer("Input", params.size(), "relu", "zeros");
    network.addLayer("Hidden", 10, "sigmoid", "he");
    network.addLayer("Hidden", 10, "tanh", "he");
    network.addLayer("Output", identityLabels(trainingData), "softmax", "random");
    // training 1000 epochs with learning rate 0.0001
    training(trainingData, testingData, network, 100, 0.01);
    
    // testing
    // predict();
    return 0;
}