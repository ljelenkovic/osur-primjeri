include $(POCETNI_DIREKTORIJ)/config.ini

VAR1 = 1
VAR2 = 1
CFLAGS += -D VAR1=$(VAR1) -D VAR2=$(VAR2)

OBJEKTI = A1.o A2.o
MODULI = a/mod-a.o b/mod-b.o
MODUL = mod-A.o

$(MODUL): $(OBJEKTI) $(MODULI)
	$(LD) -r $^ $(LDFLAGS) -o $@ 

A1.o: A1.c $(POCETNI_DIREKTORIJ)/include/postavke.h
	$(CC) $(CFLAGS) -o $@ -c $<
A2.o: A2.c $(POCETNI_DIREKTORIJ)/include/postavke.h
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: $(MODULI)
$(MODULI):
	$(MAKE) -C $(dir $@)

# brisanje
.PHONY: brisi
brisi:
	$(MAKE) -C a brisi
	$(MAKE) -C b brisi
	rm -f $(OBJEKTI) $(MODUL)
