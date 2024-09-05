#include "../includes/Perception.hpp"


extern map<string, WeightInitFunctionPointer> weightInitializationMap;
extern map<string, ActivationFunctionPointer> activationFunctionMap;

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
        neurons.push_back(0.0);
        vector<float> temp;
        for (size_t j = 0; j < previousLayerSize; j++) temp.push_back(initFunction(i, neuronCount));
        weights.push_back(temp);
		cout << weights[i].size() << endl;
		cout << weights.size() << endl;
    }
}


void Network::predict()
{
	
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