include $(POCETNI_DIREKTORIJ)/config.ini

VAR1 = 11
VAR2 = 2
CFLAGS += -D VAR1=$(VAR1) -D VAR2=$(VAR2)

OBJEKTI = a1.o
MODULI = i/mod-i.o ii/mod-ii.o
MODUL = mod-a.o

$(MODUL): $(OBJEKTI) $(MODULI)
	$(LD) -r $^ $(LDFLAGS) -o $@

a1.o: a1.c $(POCETNI_DIREKTORIJ)/include/postavke.h
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: $(MODULI)
$(MODULI):
	$(MAKE) -C $(dir $@)

# brisanje
.PHONY: brisi
brisi:
	$(MAKE) -C i  brisi
	$(MAKE) -C ii brisi
	rm -f $(OBJEKTI) $(MODUL)
