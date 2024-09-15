#include "../includes/Perception.hpp"

int main(int argc, char **argv)
{
    // data preprocessing
    if (argc < 2) {cerr << "Usage: ./exec argv1 argv2 argv3" << endl; exit(1);}
    size_t seed = 2002;
    string input_file = "data/data_normalized.csv";
    string trainingFile = "data/training.csv";
    string testingFile = "data/testing.csv";
    string networkFile = "networks/network.csv";
    string exportFile = "networks/network.txt";
    vector<size_t> params;
    size_t prediction = 1;
    vector<pair<string, std::vector<float>>> trainingData;
    vector<pair<string, std::vector<float>>> testingData;
    for (size_t i = 2; i < 32; i++) params.push_back(i);

        // data spliting training / testing
    if (argc >= 2 && string(argv[1]) == "pre") splitDataFiles(input_file, trainingFile, testingFile, seed);
    trainingData = splitDataInVectors(trainingFile, params, prediction);
    testingData = splitDataInVectors(testingFile, params, prediction);
    if (testingData.size() == 0) {cerr << "Testing Data is empty" << endl; exit(1);}
    if (trainingData.size() == 0) {cerr << "Training Data is empty" << endl; exit(1);}
    // create network
    Network network;
    network.importNetwork(networkFile, trainingData, params);
    if (argc >= 3 && string(argv[2]) == "pre") {
        training(trainingData, testingData, network, 100, 0.01);
        network.exportNetwork(exportFile);
    }
    // prediction
    if (argc >= 4 && string(argv[3]) == "pre" && string(argv[2]) != "pre")
    {
        network.CheckValidNetwork();
        network.initializeNeuralNetworkWeights();
        network.importWeights(exportFile);
        network.initializeLabels(trainingData);
    }
    if (argc >= 4 && string(argv[3]) == "pre")
    {
        float count = 0;
        for (size_t i = 0; i < testingData.size(); i++)
        {
            vector<float> output = network.predict(testingData[i]);
            string prediction = network.extractPrediction(output);
            cout << "Prediction: " << prediction << " Label: " << testingData[i].first << endl;
            if (prediction == testingData[i].first) count++;
        }
        cout << "Accuracy: " << count / testingData.size() << endl;
    }
    return 0;
}