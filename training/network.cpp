#include "../includes/Perception.hpp"


extern map<string, WeightInitFunctionPointer> weightInitializationMap;
extern map<string, ActivationFunctionPointer> activationFunctionMap;
extern map<string, DerivativeActivationFunctionPointer> derivativeActivationFunctionMap;

WeightInitFunctionPointer Layer::returnFunctionToInit(string &functionName, map<string, WeightInitFunctionPointer> &functionMap) {
    if (functionMap.find(functionName) != functionMap.end()) return functionMap[functionName];
    else return nullptr;
}

ActivationFunctionPointer Layer::returnFunctionToExecute(string &functionName, map<string, ActivationFunctionPointer> &functionMap) {
    if (functionMap.find(functionName) != functionMap.end()) return functionMap[functionName];
    else return nullptr;
}

Layer::Layer(string layerName, size_t size, string activationFunction, string weightInitialization)
    : layerName(layerName), size(size), weightInitialization(weightInitialization), activationFunction(activationFunction)
{
	(void) size;
}

Layer::~Layer()
{
	(void) size;
}


Network::Network()
{
}

Network::~Network()
{
}


void Network::importNetwork(const string &file)
{
	(void) file;
}

void Network::exportNetwork(const string &file)
{
	(void) file;
}

void Network::addLayer(string layerName, size_t size, string activationFunction, string weightInitialization)
{
	if (layerName == "Input" || layerName == "Hidden" || layerName == "Output")
        layers.push_back(std::make_unique<Layer>(layerName, size, activationFunction, weightInitialization));
	else
	{
		cerr << "Invalid Layer Name" << endl;
		exit(1);
	}
}


void Network::initializeNeuralNetworkWeights()
{
	if (layers.size() < 2)
	{
		cerr << "Network needs to have Input and Output Layers" << endl;
		exit(1);
	}
	layers[0]->neurons.reserve(layers[0]->size);
    for (size_t i = 0; i < layers[0]->size; i++) {
		layers[0]->neurons.push_back(0.0);
		vector<float> temp;
	}
	for (size_t i = 1; i < layers.size(); i++)
		layers[i]->InitializeWeights(layers[i]->size, layers[i]->weightInitialization, layers[i - 1]->size);
}

void Layer::InitializeWeights(size_t neuronCount, string functionName, size_t previousLayerSize)
{
    WeightInitFunctionPointer initFunction = returnFunctionToInit(functionName, weightInitializationMap);
    if (initFunction == nullptr)
    {
        cerr << "Error: Activation function not found" << endl;
        exit(1);
    }
    for (size_t i = 0; i < neuronCount; i++)
    {
		gradientNeuronBias.push_back(0.0);
        neurons.push_back(initFunction(i, neuronCount));
		bias.push_back(initFunction(i, neuronCount));
        vector<float> temp;
		temp.reserve(previousLayerSize);
		vector<float> tempBias;
		tempBias.reserve(previousLayerSize);
        for (size_t j = 0; j < previousLayerSize; j++)
		{
			temp.push_back(initFunction(i, neuronCount));
			tempBias.push_back(0.0);
		}
        weights.push_back(temp);
		gradientWeights.push_back(tempBias);
    }
}

vector<float> Network::createTargetVector(string &label)
{
	vector<float> target;
	for (size_t i = 0; i < labels.size(); i++)
	{
		if (labels[i] == label) target.push_back(1.0);
		else target.push_back(0.0);
	}
	return target;
}

void Network::applyGradients(float &learningRate)
{
	for (size_t layer = 1; layer < layers.size(); layer++)
	{
		for (size_t neuron = 0; neuron < layers[layer]->neurons.size(); neuron++)
		{
			for (size_t weight = 0; weight < layers[layer - 1]->size;  weight++)
			{
				layers[layer]->weights[neuron][weight] -= layers[layer]->gradientWeights[neuron][weight] * learningRate;
				layers[layer]->gradientWeights[neuron][weight] = 0.0;
			}
			layers[layer]->bias[neuron] -= layers[layer]->gradientNeuronBias[neuron] * learningRate;
			layers[layer]->gradientNeuronBias[neuron] = 0.0;
		}
	}
}



void Network::backpropagation(vector<float> &output, vector<float> &target) {
    vector<float> delta(layers.back()->neurons.size());
    for (size_t i = 0; i < layers.back()->neurons.size(); i++)
        delta[i] = output[i] - target[i];
    for (size_t layer = layers.size() - 1; layer > 0; layer--) {
        vector<float> newDelta(layers[layer - 1]->neurons.size());
        for (size_t prevNeuron = 0; prevNeuron < layers[layer - 1]->neurons.size(); prevNeuron++) {
            float error = 0.0;
            for (size_t neuron = 0; neuron < layers[layer]->neurons.size(); ++neuron) {
                float weightGradient = delta[neuron] * layers[layer - 1]->neurons[prevNeuron];
                layers[layer]->gradientWeights[neuron][prevNeuron] += weightGradient;
                error += delta[neuron] * layers[layer]->weights[neuron][prevNeuron];
            }
            newDelta[prevNeuron] = error * derivativeActivationFunctionMap[layers[layer - 1]->activationFunction](layers[layer - 1]->neurons)[prevNeuron];
        }
        delta = newDelta;
        for (size_t neuron = 0; neuron < layers[layer]->neurons.size(); neuron++)
            layers[layer]->gradientNeuronBias[neuron] += delta[neuron];
    }
}

vector<float> Network::predict(pair<string, std::vector<float>> &input)
{
	if (input.second.size() != layers[0]->size)  {cerr << "Input size does not match the input layer size" << endl; exit(1);}
	for (size_t i = 0; i < input.second.size(); i++) layers[0]->neurons[i] = input.second[i];
	for (size_t layer = 1; layer < layers.size(); layer++)
	{
		for (size_t neuron = 0; neuron < layers[layer]->size; neuron++)
		{
			float sum = 0.0;
			layers[layer]->neurons[neuron] = layers[layer]->bias[neuron];
			for (size_t weight = 0; weight < layers[layer - 1]->size;  weight++)
				sum += layers[layer - 1]->neurons[weight] * layers[layer]->weights[neuron][weight];
			layers[layer]->neurons[neuron] += sum;
		}
		ActivationFunctionPointer function = layers[layer]->returnFunctionToExecute(layers[layer]->activationFunction, activationFunctionMap);
		if (function == nullptr) { cerr << "Error: Activation function not found " << layers[layer]->activationFunction <<endl; exit(1);}
		layers[layer]->neurons = function(layers[layer]->neurons);	
	}	
	return layers[layers.size() - 1]->neurons;
}

void Network::initializeLabels(vector<pair<string, std::vector<float>>> &data)
{
	if (data.size() == 0) {cerr << "Data is empty" << endl; exit(1);}
	for (size_t i = 0; i < data.size(); i++)
	{
		bool found = false;
		for (size_t j = 0; j < labels.size(); j++)
			if (labels[j] == data[i].first) {found = true; break;}
		if (!found) labels.push_back(data[i].first);
	}
}

string Network::extractPrediction(vector<float> &output)
{
	if (output.size() == 0) {cerr << "Output is empty" << endl; exit(1);}
	size_t index = 0;
	float max = output[index];
	for (size_t i = 1; i < output.size(); i++)
		if (output[i] > max) {max = output[i]; index = i;}
	return labels[index];
}

float Network::calculateBinaryCrossEntropy(vector<float> &output, string label)
{
	if (output.size() == 0) {cerr << "Output is empty" << endl; exit(1);}
	size_t labelIndex = 0;
	for (size_t i = 1; i < output.size(); i++)
		if (labels[i] == label) labelIndex = i;
	size_t index = 0;
	float max = output[index];
	for (size_t i = 1; i < output.size(); i++)  
		if (output[i] > max) {max = output[i]; index = i;}
	float falseProbability = clamp(output[index], 0.0001f, 0.9999f);
	float probability = clamp(output[labelIndex], 0.0001f, 0.9999f);
	float loss = -(log(probability) * 1.0f + log(falseProbability) * 0.0f); // Optimisation return -(log(probability));
	// max output 4.56
    return loss;
}

void Network::CheckValidNetwork()
{
	if (layers.size() < 3)
	{
		cerr << "Network needs to have Input and Output Layers" << endl;
		cerr << "and at least one Hidden Layer is Recomended So I will hard limit it" << endl;
		exit(1);
	}
	for (size_t i = 0; i < layers.size(); i++)
	{
		if (i == 0)
		{
			if (layers[i]->layerName != "Input")
			{
				cerr << "First layer must be an Input Layer" << endl;
				exit(1);
			}
		}
		else if (i == layers.size() - 1)
		{
			if (layers[i]->layerName != "Output")
			{
				cerr << "Last layer must be an Output Layer" << endl;
				exit(1);
			}
		}
		else
		{
			if (layers[i]->layerName != "Hidden")
			{
				cerr << "Middle layers must be Hidden Layers" << endl;
				exit(1);
			}
		}
	}
}