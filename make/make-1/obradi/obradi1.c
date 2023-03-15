#include <math.h>

#include "obradi.h"
#include "obradi2.h"

double obradi(long x)
{
	return obradi2(x) + sin(x);
}
