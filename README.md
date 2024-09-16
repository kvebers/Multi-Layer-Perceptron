# Multi-Layer-Perceptron

This is neural network project written from screatch in C++

## Define network in network.csv

### The first value is Layer name, neuron count, activation function, initialization function

![Network Topology](./img/network.png)

### Supported activation functions:

relu, softmax sigmoid tanh

### Supportedd initialization functions:

zeros, ones, random, he, heNormal

## Spliting Data

Afterwards you can train the split the data in 2 parts using ./split.sh, that will run C++ code with seed 2002 to split the data in 2 parts training.csv and testing.csv

```
./split.sh
```

## Training

run ./train.sh it will run C++ code that does training of the program

```
./train.sh
```

Afterwards python code will run showcasing the acuracy and predictions of the program, the program is using early stoping to prevent overfitting and to use less compute.

![Training](./img/training.png)

After the process the network topology is exported in network.txt file

## Predict

In prediction fase the neural network is loaded from network.csv file and network.txt file

```
./predict.sh
```

![Predict](./img/predict.png)

## Prediction code

```
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
```


## Backpropagation code

```
void Network::backpropagation(vector<float> &output, vector<float> &target) {
	DerivativeActivationFunctionPointer function = derivativeActivationFunctionMap[layers.back()->activationFunction];
	vector<float> outputDerivative = function(layers.back()->neurons);
    vector<float> delta(layers.back()->neurons.size());
    for (size_t i = 0; i < layers.back()->neurons.size(); i++)
        delta[i] = output[i] - target[i];
    for (size_t layer = layers.size() - 1; layer > 0; layer--) {
        vector<float> newDelta(layers[layer - 1]->neurons.size());
		function = derivativeActivationFunctionMap[layers[layer - 1]->activationFunction];
        for (size_t prevNeuron = 0; prevNeuron < layers[layer - 1]->neurons.size(); prevNeuron++) {
            float error = 0.0;
			vector<float> temp = function(layers[layer - 1]->neurons);
            for (size_t neuron = 0; neuron < layers[layer]->neurons.size(); neuron++) {
        		float weightGradient = delta[neuron] * layers[layer - 1]->neurons[prevNeuron];
        		layers[layer]->gradientWeights[neuron][prevNeuron] += weightGradient * temp[prevNeuron];
        		error += delta[neuron] * layers[layer]->weights[neuron][prevNeuron];
            }
            newDelta[prevNeuron] = error * temp[prevNeuron];
        }
        for (size_t neuron = 0; neuron < layers[layer]->neurons.size(); neuron++)
            layers[layer]->gradientNeuronBias[neuron] += delta[neuron];
        delta = newDelta;
    }
}

```