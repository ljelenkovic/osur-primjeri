#!/bin/bash

# pokrenuti sa: source provjeri-repozitorij.sh url-repozitorija
# ili najprije: chmod 755 provjeri-repozitorij.sh
# pa onda: ./provjeri-repozitorij.sh url-repozitorija

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

if [ $# -lt 1 ]; then
	echo -e "${RED}Upotreba: ./provjeri-repozitorij.sh url-repozitorija${NC}"
	echo -e "${RED}    npr.: ./provjeri-repozitorij.sh git@github.com:student/osur.git${NC}"
	exit 1
fi
URL=$1

if [ $# -gt 1 ]; then
	DIR=$2
else
	DIR=osur_test_lab   #ne postaviti ime koji inače koristite!
fi

if [ -d $DIR ]; then
	rm -rf $DIR
fi

echo -e "${GREEN}Započinjem provjeru repozitorija $URL (lokalno $DIR)${NC}"

dohvati_repozitorij() 
{
	if [ ! -d $DIR ]; then
		git clone $URL $DIR &> /dev/null

		if [ $? -ne 0 ]; then
			echo -e "${RED}Neka greška:${NC}"
			rm -rf $DIR
			git clone $URL $DIR
			exit 1
		fi
	fi
}

provjeri_grane() 
{
	dohvati_repozitorij 

	cd $DIR
	cnt=0
	for lab in master lab1 lab2 lab3 lab4 lab5 lab6; do
		git checkout $lab &> /dev/null
		if [  $? -ne 0 ] ; then
			echo -e "${RED}NEMA GRANE $lab${NC}"
		else
			let cnt=cnt+1
		fi
	done

	if [ $cnt -lt 7 ]; then
		echo -e "${RED}Nema svih potrebnih grana${NC}"
		exit 1
	else
		echo -e "${GREEN}Sve potrebne grane na broju${NC}"
	fi

	if [ ! -e student.txt ] ; then
			echo -e "${RED}Nema datoteke: student.txt${NC}"
			exit 1
	fi

	x=($(head -1 student.txt))
	echo -e "${YELLOW}Provjerite ispravnost datoteke student.txt:${NC}"
	echo -e "${YELLOW}JMBAG: ${x[0]}${NC}"
	echo -e "${YELLOW}ime: ${x[1]}${NC}"
	echo -e "${YELLOW}prezime: ${x[2]}${NC}"
	#echo -e "${YELLOW}e-mail: ${x[3]}${NC}"
	#echo -e "${YELLOW}grupa: ${x[4]}${NC}"

	cd ..
}

usporedi_grane ()
{
	dohvati_repozitorij 

	cd $DIR
	for lab in $1 $2; do
		git checkout $lab &> /dev/null
		if [  $? -ne 0 ] ; then
			echo -e "${RED}NEMA GRANE $lab${NC}"
		fi
	done
	git checkout $2 &> /dev/null
	echo -e "${GREEN}Usporedba grana $1 i $2:${NC}"
	git diff $1

	cd ..
}

pogledaj_lab1 ()
{
	dohvati_repozitorij 

	cd $DIR
	git checkout lab1 &> /dev/null
	#cd Chapter_02_Source_tree/04_Debugging
	#make qemu > /dev/null
	#make cleanall > /dev/null
	git diff master
	#cd ../..
	if [ -d "lab1" ]; then
		cd lab1
		make > /dev/null
		make pokreni
		make brisi > /dev/null
		cd ..
	else
		echo -e "${YELLOW}Ne mogu naci direktorij lab1${NC}"
	fi
	cd ..
}

#provjeri da su sve grane napravljene
provjeri_grane

#ovo u nastavku je opcionalno; odkomentirati ako je potrebno

#echo "(stisni enter za nastavak)"
#read -s

#usporedi_grane master lab1

pogledaj_lab1

#makni lokalno dohvaćeni repozitorij
#rm -rf $DIR