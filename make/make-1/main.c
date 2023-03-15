// simulacija rada u tri faze

#include <ispisi.h>
#include <obradi.h>
#include <zaprimi.h>

int main ()
{
	int i;
	for (i = 0; i < 5; i++)
		ispisi(obradi(zaprimi()));

	return 0;
}
