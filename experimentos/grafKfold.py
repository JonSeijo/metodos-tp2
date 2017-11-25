from mpl_toolkits.mplot3d.axes3d import Axes3D
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import seaborn as sns


Kkfold = []
knn = []
clase = []
clase0 = []
clase1 = []
clase2 = []
clase3 = []
clase4 = []
clase5 = []
clase6 = []
clase7 = []
clase8 = []
clase9 = []
precision = []
recall = []
f1 = []
tiempototalknn = []
tiempototalfold = []
rango = []

with open('result.txt') as my_file:
    for line in my_file:
        #gauss.append(float(line.rstrip()))
        if line != "" and line[0] == '3':
        	comas = 0
        	for i in range(0, len(line)):
        		if line[i] == ",":
        			escribir = ""
        			comas += 1
        			if comas == 1:
        				inicio = i+1
        				while(line[inicio] != ','):

        					if line[inicio] != ' ':
        						escribir += line[inicio]
        					inicio+=1
        				Kkfold.append(float(escribir))
        			elif comas == 2:
        				inicio = i+1
        				while(line[inicio] != ','):

        					if line[inicio] != ' ':
        						escribir += line[inicio]
        					inicio+=1
        				clase.append(float(escribir))
        			elif comas == 3:
        				inicio = i+1
        				while(line[inicio] != ','):

        					if line[inicio] != ' ':
        						escribir += line[inicio]
        					inicio+=1
        				precision.append(float(escribir))
        			elif comas == 4:
        				inicio = i+1
        				while(line[inicio] != ','):

        					if line[inicio] != ' ':
        						escribir += line[inicio]
        					inicio+=1
        				recall.append(float(escribir))
        			elif comas == 5:
        				inicio = i+1
        				while(line[inicio] != ','):

        					if line[inicio] != ' ':
        						escribir += line[inicio]
        					inicio+=1
        				f1.append(float(escribir))
        			elif comas == 7:
        				inicio = i+1
        				while(line[inicio] != ','):

        					if line[inicio] != ' ':
        						escribir += line[inicio]
        					inicio+=1
        				tiempototalknn.append(float(escribir))
        			elif comas == 8:
        				inicio = i+1
        				while(line[inicio] != '\n'):

        					if line[inicio] != ' ':
        						escribir += line[inicio]
        					inicio+=1
        				tiempototalfold.append(float(escribir))


tiempototalfold_0 = []
tiempototalknn_0 = []
pres_0 = []
recall_0 = []
f1_0 = []
eje_x = []

clase_elegida = 9

precision_por_clase = [[] for _ in range(10)]
recall_por_clase = [[] for _ in range(10)]
f1_por_clase = [[] for _ in range(10)]
ejex_por_clase = [[] for _ in range(10)]

for j in range(0, len(precision)):
    # if j%10 == clase_elegida: #cambiar acá para hacer un grafico para c/ clase

    clase_actual = j%10
    precision_por_clase[clase_actual].append(precision[j])
    recall_por_clase[clase_actual].append(recall[j])
    f1_por_clase[clase_actual].append(f1[j])
    ejex_por_clase[clase_actual].append(Kkfold[j])

    # tiempototalknn_0.append(tiempototalknn[j])
    # tiempototalfold_0.append(tiempototalfold[j])


# for j in range(0, len(precision)):
#     if j%10 == clase_elegida: #cambiar acá para hacer un grafico para c/ clase
#         pres_0.append(precision[j])
#         recall_0.append(recall[j])
#         f1_0.append(f1[j])
#         eje_x.append(Kkfold[j])

#         tiempototalknn_0.append(tiempototalknn[j])
#         tiempototalfold_0.append(tiempototalfold[j])


# for j in range(0, len(tiempototalfold_0)):
#     tiempototalfold_0[j] /= 1000000000.0
#     tiempototalknn_0[j] /= 1000000000.0

# print(precision)
# print(pres_0)

#range = []
#with open('range.txt') as my_file:
    #for line in my_file:
        #range.append(float(line.rstrip()))


#eje_y.append(float(0))
#for k in range (1, 10):
    #eje_y.append(float(1/k))
#eje_y = np.array[0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]
#plt.plot(eje_x, tiempototalfold_0, '-o', label="Tiempo total")

# plt.plot(eje_x, pres_0, '-o', label="precision")
# plt.plot(eje_x, recall_0, '-o', label="recall")
# plt.plot(eje_x, f1_0, '-o',  label="f1")

t_PRECISION = "Precision"
t_RECALL = "Recall"
t_F1 = "F1"

# TIPO = t_PRECISION
# TIPO = t_RECALL
TIPO = t_F1

clases = [0, 1, 2, 5, 7, 9]
plt.title(TIPO + ' por clase', fontsize=14)
plt.ylabel(TIPO)
plt.xlabel('K-fold')

for clase in clases:
    if (TIPO == t_PRECISION):
        plt.plot(ejex_por_clase[clase], precision_por_clase[clase])
    elif (TIPO == t_RECALL):
        plt.plot(ejex_por_clase[clase], recall_por_clase[clase])
    elif (TIPO == t_F1):
        plt.plot(ejex_por_clase[clase], f1_por_clase[clase])


# plt.plot(eje_x, pres_0, label="precision")
# plt.plot(eje_x, f1_0,  label="f1")
# plt.plot(eje_x, recall_0, label="recall")

# plt.ylim([0.85,0.98])

# #plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)

plt.legend(["Clase " + str(clase) for clase in clases])

# plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3,
           # ncol=2, mode="expand", borderaxespad=0.)

plt.show()