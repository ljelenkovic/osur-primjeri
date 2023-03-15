.PHONY: arch1 arch2 brisi
arch1:
	make -C programs/prog1
	make -C kernel
	make -C arch arch1
	gcc -o program programs/prog1/y.o kernel/y.o arch/y.o

arch2:
	make -C programs/prog1
	make -C kernel
	make -C arch arch2
	gcc -o program programs/prog1/y.o kernel/y.o arch/y.o

brisi:
	-rm -f program programs/prog1/y.o kernel/y.o arch/y.o
