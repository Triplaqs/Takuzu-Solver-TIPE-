Dans le cadre de mon TIPE (pour mon année de MPI au Lycée Thiers en 2024, thème : sport et jeux) j'ai développé ici en C :

* Un solveur de Takuzu (grille de taille quelconque, renvoie la grille complétée, si une solution existe) dans le fichier _takuzu.c_ (ainsi que tout les éléments nécessaires à ce solveur).

* Un algorithme ainsi que ses fonctions intermédiaires dans le fichier _preuve.c_ qui prend en paramètre une dimension de grille de Takuzu et renvoie le nombre de cases minimum à dévoiler afin que cette grille admette une unique solution. \
  Empiriquement on se rendra compte que le résultat est toujours pour une dimension d fixée : d^2 - 4 cases minimum à dévoiler (à partir de 4, on peut former un carré qui cache 2 solutions possibles).

* Avec à cotés mes diverses présentations en LaTeX effectuées pour présenter le TIPE (dans _/docs/_)

* Un fichier Python (_binairo.py_ dans _/scripts/_) qui prend une suite de 0 et de 1 et essaye de la découper en séquence de grilles de Takuzus.
