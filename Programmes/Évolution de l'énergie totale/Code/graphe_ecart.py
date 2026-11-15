import matplotlib.pyplot as plt 
# Para utilizar latex con la fuente bonita
# plt.rc('text', usetex=True)
# plt.rc('font', family='serif')
  
x = [] 
y = [] 
for line in open('ecartype.txt', 'r'): 
    lines = [i for i in line.split()] 
    x.append(int(lines[0])) 
    y.append(float(lines[1])) 
      
plt.title("Écart type de l'énergie") 
plt.xlabel('Itérations') 
plt.ylabel(r'$\sigma_E$')  
plt.plot(x, y, 'r-') 
  
plt.show()

