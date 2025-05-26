#include <stdio.h>

//samo preprocesor: gcc main.c -E -P

#define TEXT		"nesto"
#define BROJ		42

#define FUN1(X,Y)	X * Y
#define FUN2(X,Y)	((X) * (Y))

#define FUN3(X,Y)		\
do {				\
	typeof(X) _x = X;	\
	typeof(Y) _y = Y;	\
	X = _y;			\
	Y = _x;			\
} while(0)

#define FUN4(X,Y)	#X "---" #Y
#define FUN5(X,Y)	X ## Y

int main()
{
	int a=5, b=6, c=7, d=8, ab = 101;

	printf ("Tekst: %s\n", TEXT);		//printf ("Tekst: %s\n", "nesto");
	printf ("Broj: %d\n", BROJ);		//printf ("Broj: %d\n", 42);

	printf ("Fun1: %d\n", FUN1(a,b));	//printf ("Fun1: %d\n", a * b);
	printf ("Fun1: %d\n", FUN1(a+b, c+d));	//printf ("Fun1: %d\n", a+b * c+d);
	printf ("Fun2: %d\n", FUN2(a+b, c+d));	//printf ("Fun2: %d\n", ((a+b) * (c+d)));

	printf ("a=%d, b=%d\n", a, b);

	if (a < b)
		FUN3(a,b);	//do { typeof(a) _x = a; typeof(b) _y = b; a = _y; b = _x; } while(0);
	else
		FUN3(a,c);	//do { typeof(a) _x = a; typeof(c) _y = c; a = _y; c = _x; } while(0);

	printf ("a=%d, b=%d\n", a, b);

	printf ("Fun4: %s\n", FUN4(a, b));	//printf ("Fun4: %s\n", "a" "---" "b");

	printf ("Fun5: %d\n", FUN5(a, b));	//printf ("Fun5: %d\n", ab);

	return 0;
}
