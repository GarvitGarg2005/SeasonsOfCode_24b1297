#create model class
import torch
import torch.nn as nn
class Model(nn.Module):
    def __init__(self,num_features):
        super().__init__()
        self.network=nn.Sequential(
            nn.Linear(num_features, 3),
            nn.ReLU(),
            nn.Linear(3,1),
            nn.Sigmoid()
        )
    def forward(self,features):
        out =self.network(features)
        return out
    
#create dataset
features=torch.rand(10,5)
#create model
model=Model(features.shape[1])
#call model for forward pass
model(features)
print(model(features))

from torchinfo import summary as sm
sm(model,input_size=(10,5))
