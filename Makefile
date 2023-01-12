CC= gcc        # compilateur
CFLAGS= -Wall  # options de compilation pour les sources C

SPACE_INVADERS : SPACE_INVADERS.o affichage.o vaisseau.o missile.o  space.o 
	gcc -o SPACE_INVADERS SPACE_INVADERS.o  affichage.o vaisseau.o missile.o space.o

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean : 
	rm SPACE_INVADERS.o affichage.o vaisseau.o missile.o space.o ./SPACE_INVADERS