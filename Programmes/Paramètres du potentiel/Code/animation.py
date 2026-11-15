import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import PillowWriter
 
X, Y = np.loadtxt('position.txt', delimiter=',', unpack=True)

fig = plt.figure()
l, = plt.plot([],[], linestyle = 'None', marker = 'o')
plt.ylim((-2,52))
plt.xlim((-2,52))
plt.xlabel("X-axis")
plt.ylabel("Y-axis")
plt.title("Évolution de la position des particules du gaz.")

metadata = dict(title ='Animation1', artirst = 'fgt')
writer = PillowWriter(fps = 45, metadata = metadata)

with writer.saving(fig, "animation1.gif", 100):
	for i in range(0, 500):
		l.set_data(X[i*500+1:(i+1)*500-1], Y[i*500+1:(i+1)*500-1])
		writer.grab_frame()

