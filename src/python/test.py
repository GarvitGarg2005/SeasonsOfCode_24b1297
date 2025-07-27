import torch
from sklearn.metrics import accuracy_score

from data_processor import X_test_scl, y_test
from model import MySimpleNN

model = MySimpleNN(input_dim=X_test_scl.shape[1])
model.load_state_dict(torch.load('models/nn_model.pt'))
model.eval()

x_test_tensor = torch.from_numpy(X_test_scl).float()
with torch.no_grad():
    logits = model(x_test_tensor)
    preds  = torch.argmax(logits, dim=1).numpy()

accuracy = accuracy_score(y_test.to_numpy(), preds)
print(f"Test Accuracy: {accuracy*100:.2f}%")
