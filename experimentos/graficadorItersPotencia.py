#@JonSeijo

"""
Graficador

IMPORTANTE:
Para hacerlo funcionar es NECESARIO que existan los archivos que se cargan.
No hace falta que tengan contenido,
pero la pirmera linea DEBE ser aquellas en las que se hace groupby en 'crear_lista_dataframes'
"""

import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np

# El orden debe ser preciso: tiempo, tamClique, frontera
def crear_lista_dataframes(datos, tope=None):
    print("Creando dataframes..")
    return [
        (datos.groupby('iters')['tiempo'].mean() / 1000000000)[:tope],
        ] + [
            (datos.groupby('iters')[str(i)].mean())[:tope] for i in range(11)
        ]



verde = '#55A868'
rojo = '#C44E52'
azul = '#4C72B0'
amarillo = '#EAEA25'
violeta = '#591463'

colores = [azul, verde, rojo, amarillo, violeta]
# colores = [verde, amarillo, rojo,  azul, violeta]

T_TIEMPO = (0, "Tiempo total de entrenamiendo por iteraciones del método de potencia.", "Segundos")
T_ACC_TOTAL = (11, "Accuracy total para distinta cantidad de iteraciones.", "Accuracy")

# Elegir al menos uno de cada uno!

tipo = T_ACC_TOTAL
titulo = "Método de la potencia.\n"

# mostrar_optimo = False
logy = False

data_iters = pd.read_csv('iterPotencias.csv')

data = [
    crear_lista_dataframes(data_iters)
]

plt.clf()

plt.text(20, 0.96, r'Exact value = ' + str(0.928377))

print("Plotteando..")
plot_grafo = data[0][tipo[0]].plot(fontsize = 13, figsize=(11,8), logy=logy, color=colores[0])
plot_grafo.set_title(titulo + tipo[1], fontsize = 15)
plot_grafo.set_ylabel(tipo[2], size = 14)


# data[0].plot(ax=plot_grafo, color=colores[i])

# plot_grafo.legend([algo[1] for algo in algos], fontsize = 14)
plot_grafo.set_xlabel("Iteraciones del método de la potencia", size = 14)


plt.ylim([0,1.3])
plt.xlim([0,360])
plt.show()


