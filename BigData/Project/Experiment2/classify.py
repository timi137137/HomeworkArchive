import numpy as np
from scipy.io import loadmat
from sklearn.metrics import accuracy_score

# 加载数据
data = loadmat('ARFace.mat')
train_data = data['train_data']
train_label = data['train_label'].flatten()
test_data = data['test_data']
test_label = data['test_label'].flatten()

# MED分类器
def med_classifier(train_data, train_label, test_data):
    classes = np.unique(train_label)
    class_means = np.array([train_data[train_label == i].mean(axis=0) for i in classes])
    pred_labels = []
    for x in test_data:
        distances = np.linalg.norm(x - class_means, axis=1)
        pred_label = classes[np.argmin(distances)]
        pred_labels.append(pred_label)
    return np.array(pred_labels)

# KNN分类器
def knn_classifier(train_data, train_label, test_data, k):
    pred_labels = []
    for x in test_data:
        distances = np.linalg.norm(train_data - x, axis=1)
        nearest_neighbors = np.argsort(distances)[:k]
        nearest_labels = train_label[nearest_neighbors]
        unique_labels, counts = np.unique(nearest_labels, return_counts=True)
        pred_label = unique_labels[np.argmax(counts)]
        pred_labels.append(pred_label)
    return np.array(pred_labels)

# 使用MED分类器进行分类
med_predictions = med_classifier(train_data, train_label, test_data)
med_accuracy = accuracy_score(test_label, med_predictions)
print(f'MED Classifier Accuracy: {med_accuracy * 100:.2f}%')

# 使用KNN分类器进行分类，并调整K值
k_values = [1, 3, 5, 7, 9]  # 不同的K值
for k in k_values:
    knn_predictions = knn_classifier(train_data, train_label, test_data, k)
    knn_accuracy = accuracy_score(test_label, knn_predictions)
    print(f'KNN Classifier Accuracy with k={k}: {knn_accuracy * 100:.2f}%')