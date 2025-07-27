import torch
import torch.optim as optim
from torch.utils.data import TensorDataset, DataLoader

from data_processor import X_train_scl, y_train  # import what you returned/saved
from model import MySimpleNN

x_train_tensor = torch.from_numpy(X_train_scl).float()
y_train_tensor = torch.from_numpy(y_train.to_numpy()).long()
train_ds       = TensorDataset(x_train_tensor, y_train_tensor)
loader         = DataLoader(train_ds, batch_size=32, shuffle=True)

model     = MySimpleNN(input_dim=x_train_tensor.shape[1])
criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(model.parameters(), lr=0.01)

epochs = 30
for epoch in range(epochs):
    total_loss = 0
    for xb, yb in loader:
        preds = model(xb)
        loss  = criterion(preds, yb)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        total_loss += loss.item()
    print(f"Epoch {epoch+1}, Loss: {total_loss/len(loader):.4f}")

torch.save(model.state_dict(), 'models/nn_model.pt')
import torch
import torch.optim as optim
from torch.utils.data import TensorDataset, DataLoader

from data_processor import X_train_scl, y_train  # import what you returned/saved
from model import MySimpleNN

x_train_tensor = torch.from_numpy(X_train_scl).float()
y_train_tensor = torch.from_numpy(y_train.to_numpy()).long()
train_ds       = TensorDataset(x_train_tensor, y_train_tensor)
loader         = DataLoader(train_ds, batch_size=32, shuffle=True)

model     = MySimpleNN(input_dim=x_train_tensor.shape[1])
criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(model.parameters(), lr=0.01)

epochs = 30
for epoch in range(epochs):
    total_loss = 0
    for xb, yb in loader:
        preds = model(xb)
        loss  = criterion(preds, yb)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        total_loss += loss.item()
    print(f"Epoch {epoch+1}, Loss: {total_loss/len(loader):.4f}")

torch.save(model.state_dict(), 'models/nn_model.pt')
