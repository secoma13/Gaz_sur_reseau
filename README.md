# English
The **report** folder contains the report and the GIF files for all the animations. In principle, the PDF contains links that should open the animations, but this may not always work (they do not work on the university computers, but they do work on my Windows computer). If this happens, the number of each GIF file corresponds to the number referenced in the document.

The **programs** folder contains the optimized code used to perform the calculations associated with each section of the report. Each folder contains a Makefile, and the values of the various constants have already been set to obtain results similar to those shown in the report. Only the `main` function changes, but each folder contains all the functions, making it as easy as possible to run them all.

In all cases, running `make` compiles the program and generates an executable file called `projet`. This executable performs all the calculations required for each step. To generate animations for the sections that include them, you then need to run `animation.py`. In principle, no changes to the Python code should be necessary.

Sometimes, the Python scripts used to generate the plots may not work. If this happens, remove the following lines:

```python
plt.rc('text', usetex=True)
plt.rc('font', family='serif')
```

These lines are only used to enable LaTeX formatting in the plot titles and legends, and may cause problems on some computers.

# Frech
Le dossier **rapport** contient le rapport et les gifs de toutes les animations. En principe, le pdf contient des liens qui doivent ouvrir les animations, mais cela peut ne pas fonctionner (sur les ordinateurs de l'université ne fonctionne pas, mais ça marche sur Windows dans mon ordinateur). Si c'est le cas, le nombre de chaque gif coincide avec celui referencié dans le document.

Le dossier **programmes** contient les codes optimisés pour faire le calcul asocié à chaque partie du rapport. Chacun d'entre eux contient un makefile, et les valeurs des differentes constantes sont déjà fixés pour obtenir des résultats similaires à ceux montrés dans le rapport. Seulement la fonction main change, mais chaque dossier contient tous les fonctions afin, de faire aussi facile que possible l'execution de toutes les fonctions. 

Dans tous le cas, le make permet de compiler le programme et produit un executable qui s'appelle `projet`. Cet executable est ce qui fait tous les calculs nécesaires à chaque étape. Pour faire des animations dans les sections où il y a des animations, il faut ensuite executer `animation.py`. En principe, ce n'est pas nécessaire de modifier aucune partie du code python.

Parfois les codes python utilisés pour faire les graphes ne marchent pas. Si cela est le cas, il faut enlever les lignes:
```python
plt.rc('text', usetex=True)
plt.rc('font', family='serif')
```

elles sert seulement à utiliser Latex dans le titre et les legendes des graphes, et peuvent poser des problèmes dans quelques ordinateurs.
