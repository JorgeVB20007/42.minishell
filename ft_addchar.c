#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *addchar(char *initstr, char add)
{
	int a;
	char	*result;

	a = 0;
	while (initstr[a])
		a++;
	result = malloc(a + 1);
	result[a] = 0;
	a = 0;
	while (initstr[a])
		result[a] = initstr[a];
}