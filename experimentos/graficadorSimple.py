import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np

verde = '#55A868'
rojo = '#C44E52'
azul = '#4C72B0'
amarillo = '#EAEA25'
violeta = '#591463'

colores = [azul, verde, rojo, amarillo, violeta]

# data = pd.read_csv('kkaggle.csv')
data = pd.read_csv('pcaKaggle.csv')
data_kaggle = data.groupby('alpha')

plt.clf()

plot_grafo = (data_kaggle['score'].median()).plot(fontsize=13, figsize=(11,8), color=colores[0],
                linestyle='--', marker='o')

plot_grafo.set_title("Accuracy en Kaggle - PSA + kNN, k = 4, \n42000 imágenes de training", fontsize = 15)
plot_grafo.set_ylabel("Accuracy", size = 14)
plot_grafo.set_xlabel("Alpha", size = 14)
plot_grafo.legend(["Accuracy PCA - 42000"], fontsize = 14)

plt.ylim([0.9,1.04])
plt.xlim([25,38])

plt.show()
