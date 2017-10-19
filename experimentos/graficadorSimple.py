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
# data = pd.read_csv('pcaKaggle.csv')
# data_kaggle = data.groupby('alpha')

data_knn = pd.read_csv('knnTiempos.csv')
data_psa = pd.read_csv('psaTiempos.csv')

data_knn['tiempo'] = data_knn['tiempo'] / 1000000000
data_psa['tiempo'] = data_psa['tiempo'] / 1000000000
datas_knn = data_knn.groupby('cantImagenes')
datas_psa = data_psa.groupby('cantImagenes')

plt.clf()

plot_grafo = (datas_knn['tiempo'].median()).plot(fontsize=13, figsize=(11,8), color=colores[0],
                linestyle='--', marker='o')
(datas_psa['tiempo'].median()).plot(
    ax=plot_grafo,
    fontsize=13, figsize=(11,8), color=colores[1],
                linestyle='--', marker='o'
    )


plot_grafo.set_title("Tiempos en segundos variando la cantidad de imágenes", fontsize = 15)
plot_grafo.set_ylabel("Tiempo (segundos)", size = 14)
plot_grafo.set_xlabel("Cantidad de imágenes", size = 14)
plot_grafo.legend(["kNN", "PCA"], fontsize = 14)

# plt.ylim([0.9,1.04])
# plt.xlim([25,38])

plt.show()
