include $(POCETNI_DIREKTORIJ)/config.ini

VAR1 = 2
VAR2 = 1
CFLAGS += -D VAR1=$(VAR1) -D VAR2=$(VAR2)

OBJEKTI = B1.o
MODUL = mod-B.o

$(MODUL): $(OBJEKTI)
	$(LD) -r $^ $(LDFLAGS) -o $@

B1.o: B1.c $(POCETNI_DIREKTORIJ)/include/postavke.h
	$(CC) $(CFLAGS) -o $@ -c $<

# brisanje
.PHONY: brisi
brisi:
	rm -f $(OBJEKTI) $(MODUL)
