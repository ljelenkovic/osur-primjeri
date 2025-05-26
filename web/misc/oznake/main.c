#include<stdio.h>

void ispisi1();
void ispisi2();
int dohvati_b();

int main() {
   ispisi1();  //5, 6
   ispisi2();  //5, 7, 7
   printf("M: b=%d\n", dohvati_b());//6
   return 0;
}
