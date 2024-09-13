#include "../includes/Perception.hpp"

extern map<string, WeightInitFunctionPointer> weightInitializationMap;
extern map<string, ActivationFunctionPointer> activationFunctionMap;



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

//derivativeRelu(x)[i] = 1 if x[i] > 0 else 0
vector<float> derivativeRelu(vector<float> x)
{
    vector<float> outputs;
    outputs.reserve(x.size());
    for (size_t i = 0; i < x.size(); i++)
    {
        if (x[i] > 0) outputs.push_back(1);
        else outputs.push_back(0);
    }
    return outputs;
}

//derivativeSoftmax(x)[i] = softmax(x)[i] * (1 - softmax(x)[i])
vector<float> derivativeSoftmax(vector<float> x)
{
    vector<float> outputs;
    outputs.reserve(x.size());
    for (size_t i = 0; i < x.size(); i++)
    {
        float sum = 0.0;
        for (size_t j = 0; j < x.size(); j++) sum += exp(x[j]);
        outputs.push_back(exp(x[i]) * (sum - exp(x[i])) / (sum * sum));
    }
    return outputs;
}
 
//derivativeSigmoid(x) = sigmoid(x) * (1 - sigmoid(x))
vector<float> derivativeSigmoid(vector<float> x)
{
    vector<float> outputs;
    outputs.reserve(x.size());
    for (size_t i = 0; i < x.size(); i++) outputs.push_back(x[i] * (1 - x[i]));
    return outputs;
}


// Tanh(x) = 1 - tanh(x)^2
vector<float> derivativeMyOwnTanh(vector<float> x)
{
    vector<float> outputs;
    outputs.reserve(x.size());
    for (size_t i = 0; i < x.size(); i++) outputs.push_back(1 - x[i] * x[i]);
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
    float earlyStopping = 0.88;
    ofstream training("./visuals/training.csv");
    training << "Epoch,Loss,Accuracy,Test Accuracy"<< endl;
    for (size_t trainingCount = 0; trainingCount < epochs; trainingCount++)
    {
        
        float deltaError = 0.0;
        float correct = 0;
        random_device rd;
        mt19937 gen(rd());
        shuffle(trainingData.begin(), trainingData.end(), gen);
        for (size_t i = 0; i < trainingData.size(); i++)
        {
            vector<float> predictinFloats = network.predict(trainingData[i]);
            string prediction = network.extractPrediction(predictinFloats);
            float loss = network.calculateBinaryCrossEntropy(predictinFloats, trainingData[i].first);
            vector<float> target = network.createTargetVector(trainingData[i].first);
            network.backpropagation(predictinFloats, target);
            if (i % 20) network.applyGradients(learningRate);
            deltaError += loss;
            if (prediction == trainingData[i].first) correct++;
        }
        network.applyGradients(learningRate);
        deltaError /= trainingData.size();
        float correctTests = 0;
        for (size_t i = 0; i < testingData.size(); i++)
        {
            vector<float> predictinFloats = network.predict(testingData[i]);
            string prediction = network.extractPrediction(predictinFloats);
            if (prediction == testingData[i].first) correctTests++;
        }
        cout << "Ecoch: " <<trainingCount << " Loss: " << deltaError << " Accuracy: " << correct / trainingData.size() << " Test count: " <<correct << "/" << trainingData.size();
        cout << " Testing Data: " << correctTests / testingData.size() <<  " Test count: " << correctTests << "/" << testingData.size() << endl;
        training << trainingCount << "," << deltaError << "," << correct / trainingData.size() << "," << correctTests / testingData.size() << endl;
        if (correctTests / testingData.size() > earlyStopping && correct / trainingData.size() > earlyStopping) break;
    }
    training.close();
}
