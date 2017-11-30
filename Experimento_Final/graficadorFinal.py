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

CLASE = 7

# data_raw_pca = pd.read_csv('result_knnPCA_rango_amplio.csv')
data_raw_pca = pd.read_csv('result_pca_rango_amplio_vol2.csv')
data_raw_pca = data_raw_pca[ data_raw_pca['clase'] == CLASE ]
data_pca = data_raw_pca.groupby('cant_entrenemiento')

data_raw_knn = pd.read_csv('result_knn_SIN_PCA_rango_amplio.csv')
data_raw_knn = data_raw_knn[ data_raw_knn['clase'] == CLASE ]
data_knn = data_raw_knn.groupby('cant_entrenemiento')


plt.clf()

# plot_grafo = (datas_knn['tiempo'].median()).plot(fontsize=13, figsize=(11,8), color=colores[0],
#                 linestyle='--', marker='o')
# (datas_psa['tiempo'].median()).plot(
#     ax=plot_grafo,
#     fontsize=13, figsize=(11,8), color=colores[1],
#                 linestyle='--', marker='o'
#     )

plot_grafo = (data_pca['f1'].mean()).plot(fontsize=13, figsize=(11,8), color=colores[0],
                linestyle='--', marker='o')

# (data_knn['f1'].median()).plot(#ax=plot_grafo,
#     fontsize=13, figsize=(11,8), color=colores[1],
#                 linestyle='--', marker='o')


plot_grafo.set_title("Calidad variando la cantidad de imágenes - Clase " + str(CLASE), fontsize = 15)
plot_grafo.set_ylabel("Score F1", size = 14)
plot_grafo.set_xlabel("Cantidad de imágenes", size = 14)
plot_grafo.legend(["F1 - PCA + kNN", "F1 - kNN"], fontsize = 17)



# plt.ylim([0.95,0.98])
# plt.ylim([0.95,0.97])
# plt.xlim([25,38])
plt.xlim([-500,42600])

plt.show()
