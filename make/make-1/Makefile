# koriste se implicitna pravila pa je potrebno definirati ove varijable
CFLAGS = -Iispisi -Iobradi -Izaprimi
LDFLAGS = -O2
LDLIBS = -lm

program: main.o zaprimi/zaprimi.o obradi/obradi.o ispisi/ispisi.o
	gcc $(LDFLAGS) main.o zaprimi/zaprimi.o obradi/obradi.o ispisi/ispisi.o \
	$(LDLIBS) -o program

.PHONY: zaprimi/zaprimi.o obradi/obradi.o ispisi/ispisi.o
zaprimi/zaprimi.o:
	make -C zaprimi
obradi/obradi.o:
	make -C obradi
ispisi/ispisi.o:
	make -C ispisi

.PHONY: brisi
brisi:
	make -C zaprimi brisi
	make -C obradi brisi
	make -C ispisi brisi
	-rm -f main.o program

.PHONY: pokreni
pokreni: program
	./program
