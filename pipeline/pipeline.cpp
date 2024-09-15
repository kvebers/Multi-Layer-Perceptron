#include "../includes/Perception.hpp"

int main(int argc, char **argv)
{
    // data preprocessing
    if (argc < 2) {cerr << "Usage: ./exec argv1 argv2 argv3" << endl; exit(1);}
    size_t seed = 2002;
    string input_file = "data_normalized.csv";
    string trainingFile = "training.csv";
    string testingFile = "testing.csv";
    string networkFile = "network.csv";
    vector<size_t> params;
    size_t prediction = 1;
    vector<pair<string, std::vector<float>>> trainingData;
    vector<pair<string, std::vector<float>>> testingData;
    for (size_t i = 2; i < 32; i++) params.push_back(i);

    if (argc >= 2 && string(argv[1]) == "pre")
    {
        // data spliting training / testing
        splitDataFiles(input_file, trainingFile, testingFile, seed);
    }
    trainingData = splitDataInVectors(trainingFile, params, prediction);
    testingData = splitDataInVectors(testingFile, params, prediction);
    // create network
    Network network;
    network.importNetwork("network.csv", trainingData, params);
    // network.addLayer("Input", params.size(), "relu", "zeros");
    // network.addLayer("Hidden", 4, "sigmoid", "zeros");
    // network.addLayer("Hidden", 2, "tanh", "he");
    // network.addLayer("Output", identityLabels(trainingData), "softmax", "random");
    // training 1000 epochs with learning rate 0.0001
    training(trainingData, testingData, network, 100, 0.01);
    
    // testing
    // predict();
    return 0;
}