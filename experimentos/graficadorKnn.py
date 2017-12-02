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

T_PRECISION = "precision"
T_RECALL = "recall"
T_F1 = "f1"
T_TIEMPO = "tiempo"

data_iters = pd.read_csv('knnMediciones.csv')
data_iters['tiempo'] = data_iters['tiempo'] / 1000000000
dataPorClase = data_iters.groupby('clase')
dataPorKClase = data_iters.groupby(['k', 'clase'])

tipo = T_PRECISION
maxk = 34

dataPlotPrecision = {}
dataPlotRecall = {}
dataPlotF1 = {}

for i in range(10):
    dataPlotPrecision[i] = dataPorClase[T_PRECISION].get_group(i)
    dataPlotPrecision[i].index = [str(x) for x in range(1, maxk+1)]

    dataPlotRecall[i] = dataPorClase[T_RECALL].get_group(i)
    dataPlotRecall[i].index = [str(x) for x in range(1, maxk+1)]

    dataPlotF1[i] = dataPorClase[T_F1].get_group(i)
    dataPlotF1[i].index = [str(x) for x in range(1, maxk+1)]

dataPlot = [dataPlotPrecision, dataPlotRecall, dataPlotF1]

clasePlot = 9
logy = False

# Los maximos se obtienen en:
argmaximos = [dataPlotF1[clase].values.argmax() + 1 for clase in range(10)]
print(argmaximos)
print(np.mean(argmaximos))

plt.clf()

plot_grafo = (dataPlotPrecision[clasePlot]).plot(fontsize = 13, figsize=(11,8), logy=logy, color=colores[1])
dataPlotRecall[clasePlot].plot(ax=plot_grafo, fontsize = 13, figsize=(11,8), logy=logy, color=colores[0])
dataPlotF1[clasePlot].plot(ax=plot_grafo, fontsize = 13, figsize=(11,8), logy=logy, color=colores[2])



# clases = [1, 2, 5, 7]
# axes_val = [(0,0), (0,1), (1,0), (1,1)]

# fig, axes = plt.subplots(nrows=2, figsize=(13,10), ncols=2, subplot_kw={'ylim': (0.8, 1.0)})
# fig.subplots_adjust(hspace=.6, wspace=.3)

# for i in range(len(clases)):
#     for j in range(3):
#         dataPlot[j][clases[i]].plot(ax=axes[ axes_val[i][0] , axes_val[i][1] ], color=colores[j])

#     axes[ axes_val[i][0] , axes_val[i][1] ].set_title("\nClase: " + str(clases[i]))
#     axes[ axes_val[i][0] , axes_val[i][1] ].set_ylabel("Puntaje", size = 14)
#     axes[ axes_val[i][0] , axes_val[i][1] ].legend(["Precision", "Recall", "F1"], fontsize = 11)
#     axes[ axes_val[i][0] , axes_val[i][1] ].set_xlabel("k de kNN", size = 12)



plot_grafo.set_title("Clase: " + str(clasePlot) + "\nValores de Precision, Recall y F1", fontsize = 15)
plot_grafo.set_ylabel("Puntaje", size = 14)
plot_grafo.legend(["Precision", "Recall", "F1"], fontsize = 14)
plot_grafo.set_xlabel("k de kNN", size = 14)

# plt.ylim([0.8,1.1])

plt.show()
