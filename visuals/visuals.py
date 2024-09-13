#!/usr/bin/env python3

import matplotlib.pyplot as plt
import pandas as pd

training = pd.read_csv('training.csv')
plt.figure()
plt.plot(training['Epoch'], training['Loss'], label='Training Loss', color='blue')
plt.plot(training['Epoch'], training['Accuracy'], label='Training Accuracy', color='green')
plt.plot(training['Epoch'], training['Test Accuracy'], label='Test Accuracy', color='red')
plt.xlabel('Epoch')
plt.ylabel('Value')
plt.title('Training Progress over Epochs')
plt.legend()
plt.show()