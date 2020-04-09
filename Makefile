start_game: main.o logica.o listas.o interface.o dados.o
	gcc -o start_game main.o logica.o listas.o interface.o dados.o

main.o: main.c dados.h interface.h
	gcc -c main.c

logica.o: logica.c dados.h interface.h
	gcc -c logica.c

listas.o: listas.c listas.h
	gcc -c listas.c

interface.o: interface.c interface.h logica.h dados.h
	gcc -c interface.c

dados.o: dados.c dados.h logica.h
	gcc -c dados.c

clean:
	rm *.o start_game