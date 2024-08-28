#include "../includes/Perception.hpp"

InputLayer::InputLayer(size_t size, string activationFunction) : size(size), activationFunction(activationFunction)
{
}
InputLayer::~InputLayer()
{
    (void) size;
}

OutputLayer::OutputLayer(size_t size, string activationFunction, string weightInitialization) : size(size), activationFunction(activationFunction), weightInitialization(weightInitialization)
{
}

OutputLayer::~OutputLayer()
{
    (void) size;
}

HiddenLayer::HiddenLayer(size_t size, string activationFunction, string weightInitialization) : size(size), activationFunction(activationFunction), weightInitialization(weightInitialization)
{
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