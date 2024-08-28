#include "../includes/Perception.hpp"




void Layer::InitializeWeights(string functionName)
{
    if (functionName == "random")  someFunction();
    else if (functionName == "xavier")  someFunction();
    else if (functionName == "he") someFunction();
    else
    {
        cerr << "Invalid weight initialization function" << endl;
        exit(1);
    }
}




void softmax()
{

}

void training(vector<pair<string, std::vector<float>>> trainingData, vector<pair<string, std::vector<float>>>  testingData,  Network &network)
{
    (void) trainingData;
    (void) testingData;
    (void) network;
}
