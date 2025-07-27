import torch
import torch.nn as nn

class MySimpleNN(nn.Module):
    def __init__(self, input_dim, output_dim=3):
        super(MySimpleNN, self).__init__()
        self.linear = nn.Linear(input_dim, output_dim)
        
    def forward(self, x):
        return self.linear(x)
