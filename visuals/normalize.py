#!/usr/bin/env python3

import pandas as pd
from sklearn.preprocessing import MinMaxScaler

df = pd.read_csv('../data.csv', header=None)
features = df.iloc[:, 2:]
scaler = MinMaxScaler()
normalized_features = scaler.fit_transform(features)
df.iloc[:, 2:] = normalized_features
df.to_csv('data_normalized.csv', index=False)
print(df.head())
