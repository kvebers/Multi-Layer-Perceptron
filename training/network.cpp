#include "../includes/Perception.hpp"

InputLayer::InputLayer(size_t size, string activationFunction) : size(size), activationFunction(activationFunction)
{
	layerName = "Input";
}

InputLayer::~InputLayer()
{
	(void) size;
}

OutputLayer::OutputLayer(size_t size, string activationFunction, string weightInitialization) : size(size), activationFunction(activationFunction), weightInitialization(weightInitialization)
{
	layerName = "Output";
	InitializeWeights(size, weightInitialization);
}

OutputLayer::~OutputLayer()
{
	(void) size;
}

HiddenLayer::HiddenLayer(size_t size, string activationFunction, string weightInitialization) : size(size), activationFunction(activationFunction), weightInitialization(weightInitialization)
{
	layerName = "Hidden";
	InitializeWeights(size, weightInitialization);
}

HiddenLayer::~HiddenLayer()
{
	(void) size;
}

Network::Network()
{
}

Network::~Network()
{
}

void Network::addLayer(Layer &layer)
{
	layers.push_back(layer);
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
			if (layers[i].layerName != "Input")
			{
				cerr << "First layer must be an Input Layer" << endl;
				exit(1);
			}
		}
		else if (i == layers.size() - 1)
		{
			if (layers[i].layerName != "Output")
			{
				cerr << "Last layer must be an Output Layer" << endl;
				exit(1);
			}
		}
		else
		{
			if (layers[i].layerName != "Hidden")
			{
				cerr << "Middle layers must be Hidden Layers" << endl;
				exit(1);
			}
		}
	}
}