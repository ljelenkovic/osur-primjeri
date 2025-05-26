#include <stdio.h>
#include <string.h>
#include <math.h>
#include <postavke.h>

int funkcija_Aa1 ( const char *prefiks )
{
	char p[DULJINA];

	strcpy ( p, prefiks );
	strcat ( p, " -- funkcija_Aa1" );

	printf ( "%s %d %g\n", p, VAR1, sqrt(VAR2) );

	funkcija_Aai1 ( p );
	funkcija_Aai2 ( p );
	funkcija_Aaii1 ( p );

	return 0;
}
