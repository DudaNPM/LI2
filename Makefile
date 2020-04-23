start_game: main.o logica.o listas.o interface.o dados.o
	gcc -o start_game main.o logica.o listas.o interface.o dados.o -lm

main.o: main.c dados.h interface.h
	gcc -c main.c -lm

logica.o: logica.c dados.h interface.h listas.h logica.h
	gcc -c logica.c -lm

listas.o: listas.c listas.h
	gcc -c listas.c -lm

interface.o: interface.c interface.h logica.h dados.h
	gcc -c interface.c -lm

dados.o: dados.c dados.h logica.h
	gcc -c dados.c -lm

clean:
	rm *.o start_game