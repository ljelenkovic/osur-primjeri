#include<stdio.h>

int a = 5;
static int b = 6;

int dohvati_b() {
   return b;
}
void ispisi1 () {
   printf ("A: lokalni a=%d\n", a);//5
   printf ("A: lokalni b=%d\n", b);//6
}
