import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np

def getFilename(cantImgs, alpha):
    return "psaPOSTA/psa/psa_" + str(cantImgs) + "_alpha_" + str(alpha) + "result.txt"

verde = '#55A868'
rojo = '#C44E52'
azul = '#4C72B0'
naranja = '#FFA420'
violeta = '#af73b7'

# colores = [azul, verde, rojo, naranja, violeta]
colores = [violeta, verde, rojo, naranja, azul]

T_PRECISION = "precision"
T_RECALL = "recall"
T_F1 = "f1"
T_TIEMPO = "tiempo"

datas = []
alphas = [15,20,25,30,35]

K_FIJO = 5
# KAES = [3, 4, 5, 6, 7]
KAES = [4]


dataPosta = [[[] for _ in range(10)] for __ in range(len(KAES))]
dataPostaPres = [[[] for _ in range(10)] for __ in range(len(KAES))]
dataPostaRec = [[[] for _ in range(10)] for __ in range(len(KAES))]


# losalphas = [a for a in range(1,41)]
losalphas = [40,50,60,75,100,150,200,400,600]
cantidadImagenes = 20000


for alpha in losalphas:
    data_iters = pd.read_csv(getFilename(cantidadImagenes, alpha))
    data_iters['tiempo'] = data_iters['tiempo'] / 1000000000
    dataPorClase = data_iters.groupby('clase')
    dataPorKClase = data_iters.groupby(['k', 'clase'])

    maxk = 1

    for ki in range(len(KAES)):

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

            dataPosta[ki][i].append(dataPlotF1[i][0])
            dataPostaPres[ki][i].append(dataPlotPrecision[i][0])
            dataPostaRec[ki][i].append(dataPlotRecall[i][0])


        #datas.append({T_PRECISION: dataPlotPrecision, T_RECALL: dataPlotRecall, T_F1: dataPlotF1})
        # datas.append({T_F1: dataPlotF1})



# K=4 -> KAES[1]
# K=5 -> KAES[2]

# Los maximos se obtienen en:

"""
alphaizq = 20

maximos = [np.array(dataPosta[1][clase][alphaizq:]).max()  for clase in range(10)]
print(maximos)
print(str(np.mean(maximos)) +  "   " + str(np.median(maximos)))

argmaximos = [np.array(dataPosta[1][clase][alphaizq:]).argmax() + alphaizq for clase in range(10)]
print(argmaximos)
print(str(np.mean(argmaximos)) +  "   " + str(np.median(argmaximos)))

plt.clf()
"""

clases = [1, 2, 5, 7]
# clases = [4, 5, 6, 7]
# clases = [8, 9, 8, 9]
axes_val = [(0,0), (0,1), (1,0), (1,1)]

#"""

fig, axes = plt.subplots(nrows=2, figsize=(13,10), ncols=2
    , subplot_kw={'ylim': (0.93, 1.0)}
)
fig.subplots_adjust(hspace=.6, wspace=.3)


for i in range(0,len(clases)):
    #for ki in range(len(KAES)):

    # axes[ axes_val[i][0] , axes_val[i][1] ].plot(
    #     np.array(losalphas),
    #     np.array(dataPostaPres[0][clases[i]]),
    #     linestyle='--', marker='o'
    # )

    # axes[ axes_val[i][0] , axes_val[i][1] ].plot(
    #     np.array(losalphas),
    #     np.array(dataPostaRec[0][clases[i]]),
    #     linestyle='--', marker='o'
    # )

    # F1
    axes[ axes_val[i][0] , axes_val[i][1] ].plot(
        np.array(losalphas),
        np.array(dataPosta[0][clases[i]]),
        linestyle='--', marker='o', color=rojo
    )

    axes[ axes_val[i][0] , axes_val[i][1] ].set_title("\nClase: " + str(clases[i]))
    axes[ axes_val[i][0] , axes_val[i][1] ].set_ylabel("Score", size = 14)
    # axes[ axes_val[i][0] , axes_val[i][1] ].legend(["Precision", "Recall", "F1"], fontsize = 11)
    axes[ axes_val[i][0] , axes_val[i][1] ].legend(["F1"], fontsize = 11)
    axes[ axes_val[i][0] , axes_val[i][1] ].set_xlabel("Alpha", size = 12)

"""
clasePlot = 4
logy = False
TIPO = T_F1

for ki in range(len(KAES)):
    plt.plot(
        np.array([i for i in range(1,41)]), np.array(dataPosta[ki][clasePlot])
    )


#, fontsize = 13, figsize=(11,8), logy=logy, color=colores[0])
#for i in range(1, len(alphas)):
#    datas[i][TIPO][clasePlot].plot(ax=plot_grafo, fontsize = 13, figsize=(11,8), logy=logy, color=colores[i])
#dataPlotF1[clasePlot].plot(ax=plot_grafo, fontsize = 13, figsize=(11,8), logy=logy, color=colores[2])

plt.title("Clase: " + str(clasePlot) + "\nScores " + TIPO + " variando distintos alphas", fontsize = 15)
plt.ylabel("F1 Score", size = 14)
plt.legend(["k " + str(ks) for ks in KAES], fontsize = 14)
plt.xlabel("Alpha de PCA", size = 14)

plt.ylim([0.8,1.1])
#plt.ylim([0.92,1.02])
#plt.ylim([0.970,1])
"""
plt.show()
