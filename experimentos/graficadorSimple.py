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

data = pd.read_csv('kkaggle.csv')
data_kaggle = data.groupby('k')

plt.clf()

plot_grafo = (data_kaggle['score'].median()).plot(fontsize=13, figsize=(11,8), color=colores[0],
                linestyle='--', marker='o')

plot_grafo.set_title("Score en Kaggle - Sólo kNN\n42000 imágenes de training", fontsize = 15)
plot_grafo.set_ylabel("Score", size = 14)
plot_grafo.set_xlabel("k (kNN)", size = 14)
plot_grafo.legend(["Score - Training 42000"], fontsize = 14)

plt.ylim([0.9,1.04])
plt.xlim([0,21])

plt.show()
