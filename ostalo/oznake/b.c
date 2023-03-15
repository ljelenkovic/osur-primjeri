#include<stdio.h>

extern int a;
static int b = 7;

static int dohvati_b() {
   return b;
}

void ispisi2 () {
   printf ("B: vanjski a=%d\n", a);//5
   printf ("B: lokalni b=%d\n", b);//7
   printf ("B: dohvati_b=%d\n", dohvati_b()); //7
}
