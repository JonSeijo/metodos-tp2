import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np

def getFilename(cantImgs, alpha):
    return "psa/psa_" + str(cantImgs) + "_alpha_" + str(alpha) + "result.txt"

verde = '#55A868'
rojo = '#C44E52'
azul = '#4C72B0'
naranja = '#FFA420'
violeta = '#af73b7'

colores = [azul, verde, rojo, naranja, violeta]
# colores = [violeta, verde, rojo, naranja, azul]

T_PRECISION = "precision"
T_RECALL = "recall"
T_F1 = "f1"
T_TIEMPO = "tiempo"

datas = []
#alphas = [20,25,30,35,40]
alphas = [30]

for alpha in alphas:
    data_iters = pd.read_csv(getFilename(42000, alpha))
    data_iters['tiempo'] = data_iters['tiempo'] / 1000000000
    dataPorClase = data_iters.groupby('clase')
    dataPorKClase = data_iters.groupby(['k', 'clase'])

    tipo = T_PRECISION
    maxk = 29

    dataPlotPrecision = {}
    dataPlotRecall = {}
    dataPlotF1 = {}

    for i in range(10):
        dataPlotPrecision[i] = dataPorClase[T_PRECISION].get_group(i)[:maxk]
        dataPlotPrecision[i].index = [str(x) for x in range(1, maxk+1)]

        dataPlotRecall[i] = dataPorClase[T_RECALL].get_group(i)[:maxk]
        dataPlotRecall[i].index = [str(x) for x in range(1, maxk+1)]

        dataPlotF1[i] = dataPorClase[T_F1].get_group(i)[:maxk]
        dataPlotF1[i].index = [str(x) for x in range(1, maxk+1)]

    datas.append({T_PRECISION: dataPlotPrecision, T_RECALL: dataPlotRecall, T_F1: dataPlotF1})



# Los maximos se obtienen en:

for a in range(len(alphas)):
    argmaximos = [datas[a][T_F1][clase].values.argmax() + 1 for clase in range(10)]
    print("\nalpha: " + str(alphas[a]))
    print(argmaximos)
    print(str(np.mean(argmaximos)) +  "   " + str(np.median(argmaximos)))


plt.clf()


clases = [1, 2, 5, 7]
# clases = [4, 5, 6, 7]
# clases = [8, 9, 8, 9]
axes_val = [(0,0), (0,1), (1,0), (1,1)]

#"""

# fig, axes = plt.subplots(nrows=2, figsize=(13,10), ncols=2, subplot_kw={'ylim': (0.8, 1.1)})
# fig.subplots_adjust(hspace=.6, wspace=.3)

# for i in range(len(clases)):
#     #for j in range(len(alphas)):
#     datas[0][T_PRECISION][clases[i]].plot(ax=axes[ axes_val[i][0] , axes_val[i][1] ], color=colores[1])
#     datas[0][T_RECALL][clases[i]].plot(ax=axes[ axes_val[i][0] , axes_val[i][1] ], color=colores[0])
#     datas[0][T_F1][clases[i]].plot(ax=axes[ axes_val[i][0] , axes_val[i][1] ], color=colores[2])


#     axes[ axes_val[i][0] , axes_val[i][1] ].set_title("\nClase: " + str(clases[i]))
#     axes[ axes_val[i][0] , axes_val[i][1] ].set_ylabel("Score", size = 14)
#     axes[ axes_val[i][0] , axes_val[i][1] ].legend(["Precision", "Recall", "F1"], fontsize = 11)
#     axes[ axes_val[i][0] , axes_val[i][1] ].set_xlabel("k de kNN", size = 12)


# fig, axes = plt.subplots(nrows=2, figsize=(13,10), ncols=2, subplot_kw={'ylim': (0.8, 1.1)})
# fig.subplots_adjust(hspace=.6, wspace=.3)



# clasePlot = 5
# logy = False
# TIPO = T_F1

# plot_grafo = (datas[0][TIPO][clasePlot]).plot(fontsize = 13, figsize=(11,8), logy=logy, color=colores[0])
# for i in range(1, len(alphas)):
#     datas[i][TIPO][clasePlot].plot(ax=plot_grafo, fontsize = 13, figsize=(11,8), logy=logy, color=colores[i])
# #dataPlotF1[clasePlot].plot(ax=plot_grafo, fontsize = 13, figsize=(11,8), logy=logy, color=colores[2])

# plot_grafo.set_title("Clase: " + str(clasePlot) + "\nValores " + TIPO + " para distintos alphas, variando k", fontsize = 15)
# plot_grafo.set_ylabel("F1 Score", size = 14)
# plot_grafo.legend(["Alpha " + str(alpha) for alpha in alphas], fontsize = 14)
# plot_grafo.set_xlabel("k de kNN", size = 14)

TIPO = "Precision"

ax = datas[0][T_PRECISION][clases[0]].plot(linestyle='--', marker='.')
for i in range(1, len(clases)):
    datas[0][T_PRECISION][clases[i]].plot(ax=ax, linestyle='--', marker='.')
    # datas[0][T_RECALL][clases[i]].plot(ax=ax, color=colores[i])
    # datas[0][T_F1][clases[i]].plot(ax=ax, color=colores[i])


plt.title(TIPO + ' por clase', fontsize=14)
plt.ylabel(TIPO)
plt.xlabel('k de kNN')
plt.legend(["Clase " + str(clase) for clase in clases])

plt.ylim([0.95,1.00])
# plt.ylim([0.92,1.02])

plt.show()
