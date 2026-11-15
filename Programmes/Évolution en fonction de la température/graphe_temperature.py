import matplotlib.pyplot as plt
import numpy as np

# Para utilizar latex con la fuente bonita
plt.rc('text', usetex=True)
plt.rc('font', family='serif')

energy, temperature = np.loadtxt("temperature.txt", unpack = True)


# Hacemos los gráficos
plt.figure(1, dpi = 120)
# El dpi es para la resolución
plt.title("Évolution de l'énergie en fonction de la température.")
plt.plot(energy, temperature,  "-", color = "red", label = "Título del conjunto de datos")
# titles of the axis
plt.xlabel(r'$T(K)$')
plt.ylabel(r'E/k_b (K)')
plt.show()


