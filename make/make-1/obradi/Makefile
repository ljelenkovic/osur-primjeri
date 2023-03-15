obradi.o: obradi1.o obradi2.o
	ld -r obradi1.o obradi2.o -o obradi.o

obradi1.o: obradi1.c obradi2.h

obradi2.o: obradi2.c obradi2.h

.PHONY: brisi
brisi:
	-rm -f obradi.o obradi1.o obradi2.o
