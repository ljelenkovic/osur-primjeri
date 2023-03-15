include $(POCETNI_DIREKTORIJ)/config.ini

VAR1 = 111
VAR2 = 3
CFLAGS += -D VAR1=$(VAR1) -D VAR2=$(VAR2)

OBJEKTI = i1.o i2.o
MODUL = mod-i.o

$(MODUL): $(OBJEKTI)
	$(LD) -r $^ $(LDFLAGS) -o $@

i1.o: i1.c $(POCETNI_DIREKTORIJ)/include/postavke.h
	$(CC) $(CFLAGS) -o $@ -c $<
i2.o: i2.c $(POCETNI_DIREKTORIJ)/include/postavke.h
	$(CC) $(CFLAGS) -o $@ -c $<

# brisanje
.PHONY: brisi
brisi:
	rm -f $(OBJEKTI) $(MODUL)
