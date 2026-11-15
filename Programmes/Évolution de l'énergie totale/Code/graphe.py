import matplotlib.pyplot as plt
import numpy as np

# Para utilizar latex con la fuente bonita
# plt.rc('text', usetex=True)
# plt.rc('font', family='serif')

project = 'energy.txt'
energies = np.loadtxt(project)


# Hacemos los gráficos
plt.figure(1, dpi = 120)
# El dpi es para la resolución
plt.title("Évolution de l'énergie.")
plt.plot(energies,  "-", color = "red", label = "Título del conjunto de datos")
# Con esto ponemos títulos a los ejes
plt.xlabel("Itéractions")
plt.ylabel("E/kb (K)")
plt.show()
# cambiamos el -- por _ para poner líneas continuas o discretas
# cambiamos color para poner colores distintos.
# El titulo de label aparece solo cuando ponemos leyendas

