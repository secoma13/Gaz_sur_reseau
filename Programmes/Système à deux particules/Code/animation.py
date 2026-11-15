import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import PillowWriter
 
X, Y = np.loadtxt('position.txt', delimiter=',', unpack=True)

fig = plt.figure()
l, = plt.plot([],[], linestyle = 'None', marker = 'o')
plt.ylim((-1,8))
plt.xlim((-1,8))
plt.xlabel("X-axis")
plt.ylabel("Y-axis")
plt.title("Évolution de la position des particules du gaz.")

metadata = dict(title ='Animation1', artirst = 'fgt')
writer = PillowWriter(fps = 15, metadata = metadata)

with writer.saving(fig, "animation1.gif", 100):
	for i in range(0, 500):
		#l.set_data(X[i*2+1:(i+1)*2-1], Y[i*2+1:(i+1)*2-1])
		l.set_data(X[i*2:(i+1)*2], Y[i*2:(i+1)*2])
		writer.grab_frame()

