#include "../includes/Perception.hpp"

int main()
{
    // data preprocessing
    size_t seed = 2002;
    string input_file = "data.csv";
    string trainingFile = "training.csv";
    string testingFile = "testing.csv";
    vector<size_t> params;
    size_t prediction = 1;
    vector<pair<string, std::vector<float>>> trainingData;
    vector<pair<string, std::vector<float>>> testingData;
    for (size_t i = 2; i < 32; i++)
    {
        params.push_back(i);
    }
    params.reserve(30);

    // data spliting training / testing
    splitDataFiles(input_file, trainingFile, testingFile, seed);
    trainingData = splitDataInVectors(trainingFile, params, prediction);
    testingData = splitDataInVectors(testingFile, params, prediction);

    // create network
    auto inputLayer = std::make_unique<InputLayer>(10, "relu");
    auto hiddenLayer = std::make_unique<HiddenLayer>(5, "sigmoid", "he");
    auto hiddenLayer2 = std::make_unique<HiddenLayer>(5, "tanh", "he");
    auto outputLayer = std::make_unique<OutputLayer>(2, "softmax", "random");
    Network network;
    network.addLayer();
    network.addLayer(move(hiddenLayer));
    network.addLayer(move(hiddenLayer2));
    network.addLayer(move(outputLayer));
    network.CheckValidNetwork();
    // training
    training(trainingData, testingData, network, 100, 0.01);
    
    // testing
    // predict();
    return 0;
}