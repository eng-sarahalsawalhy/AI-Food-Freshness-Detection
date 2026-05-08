import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score
from micromlgen import port

# ================= LOAD DATA =================
# Your dataset should have:
# ratio, sensor_volt, label
data = pd.read_csv("data.csv")

X = data[["ratio", "sensor_volt"]]
y = data["label"]  # 0 = Fresh, 1 = Warning, 2 = Spoiled

# ================= SPLIT DATA =================
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

# ================= TRAIN MODEL =================
model = DecisionTreeClassifier(max_depth=5)
model.fit(X_train, y_train)

# ================= EVALUATE =================
y_pred = model.predict(X_test)
accuracy = accuracy_score(y_test, y_pred)

print("Accuracy:", accuracy)

# ================= EXPORT MODEL =================
c_code = port(model)

with open("model_uno_optimized.h", "w") as f:
    f.write(c_code)

print("Model exported to model_uno_optimized.h")
