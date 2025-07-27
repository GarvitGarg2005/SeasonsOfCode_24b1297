import pandas as pd
import numpy as np
import torch
import torch.nn as nn
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.preprocessing import LabelEncoder
df=pd.read_csv('hdfc.csv')
df.drop(columns=['Adj Close'],inplace=True)
cols=list(df.columns)
df=df[cols[0:2]+[cols[4]]+cols[2:4]+[cols[5]]]

import strategy_bindings

closes = df['Close'].tolist()
df['MACD_signal'] = [ strategy_bindings.run_MACD_strategy(closes, i) 
                      for i in range(len(closes)) ]
df['bb_signal']   = [ strategy_bindings.run_BB_strategy (closes, i) 
                      for i in range(len(closes)) ]
df['rsi_signal']  = [ strategy_bindings.run_RSI       (closes, i) 
                      for i in range(len(closes)) ]
