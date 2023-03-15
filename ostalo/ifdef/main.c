#include<stdio.h>

#include "a.h"
#include "b.h"

int main() {
	struct a a = {.a = 7};
	struct b b = {.b = 5, .a = a };

	printf ("a=%d, b=%d %d\n", a.a, b.b, b.a.a);
	return 0;
}
