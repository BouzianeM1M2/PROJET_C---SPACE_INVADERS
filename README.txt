Space Invaders

Le jeu a été conçu pour être lancé en plein écran sur le terminal.
Pour que le rendu du jeu soit meilleur, veuillez lancer le jeu en plein écran s’il vous plaît. 

Commande pour compiler: make

Commande pour exécuter: ./SPACE_INVADERS

Format du jeu:

Le vaisseau du joueur doit survivre et éliminer les vaisseaux ennemis.
Pour que le jeu soit intéressant, j’ai fait plusieurs modifications:
	▪	J’ai fait en sorte que les missiles du vaisseaux joueur se disparaissent à un certaine distance.
	▪	Les vaisseaux ennemis de la première ligne avancent vers le vaisseau joueur en premier en lui tirant dessus.
	▪	Les vaisseaux de la deuxième ligne commencent à avancer une fois que tous les vaisseaux de la première ligne soient éliminés.
	▪	Les vaisseaux de la troisième ligne commencent à avancer une fois que tous les vaisseaux de la deuxième ligne soient éliminés.


Condition gagnante/perdante:

Le joueur gagne s’il réussi à survivre et éliminer tous les vaisseaux ennemis. Puis la partie se termine avec « Vous avez gagné ».

Le joueur perd s’il perd tous ses points de vie ou les vaisseaux ennemis atteignent le vaisseau joueur. Puis la partie se termine avec « Vous avez perdu ».
