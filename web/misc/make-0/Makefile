brojke: a.o b.o brojke.o
	gcc a.o b.o brojke.o -lm -o brojke

a.o: a.c a.h b.h
	gcc -c a.c

b.o: b.c b.h
	@gcc -c b.c

brojke.o: brojke.c a.h
	gcc -c brojke.c
