#create model class
import torch
import torch.nn as nn
class Model(nn.Module):
    def __init__(self,num_features):
        super().__init__()
        self.linear= nn.Linear(num_features, 3)
        self.relu= nn.ReLU()
        self.linear2=nn.Linear(3,1)
        self.sigmoid=nn.Sigmoid()
    def forward(self,features):
        out = self.linear(features)
        out=self.relu(out)
        out=self.linear2(out)
        out= self.sigmoid(out)

        return out
    
#create dataset
features=torch.rand(10,5)
#create model
model=Model(features.shape[1])
#call model for forward pass
model(features)
print(model(features))

#show model weights
print(model.linear.weight)
print(model.linear.bias)
from torchinfo import summary as sm
sm(model,input_size=(10,5))
