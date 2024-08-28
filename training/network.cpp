#include "../includes/Perception.hpp"

InputLayer::InputLayer(size_t size, string activationFunction) : size(size), activationFunction(activationFunction)
{
}

InputLayer::~InputLayer()
{
}

OutputLayer::OutputLayer(size_t size, string activationFunction, string weightInitialization) : size(size), activationFunction(activationFunction), weightInitialization(weightInitialization)
{
}

OutputLayer::~OutputLayer()
{
}

HiddenLayer::HiddenLayer(size_t size, string activationFunction, string weightInitialization) : size(size), activationFunction(activationFunction), weightInitialization(weightInitialization)
{
}

HiddenLayer::~HiddenLayer()
{
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