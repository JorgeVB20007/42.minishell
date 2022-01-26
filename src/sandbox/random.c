#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/random.h>
#include <stdio.h>

int main (void)
{
	int randomData = open("/dev/random", O_RDONLY);
	int entropy;
	int result;

	result = ioctl(randomData, RNDGETENTCNT, &entropy);
	if (!result)
	{
		// Error - /dev/random isn't actually a random device return;
	}
	if ((unsigned long)entropy < sizeof(int) * 8)
	{
		// Error - there's not enough bits of entropy in the random device to fill the buffer return;
	}
	int myRandomInteger;
	size_t randomDataLen = 0;
	while (randomDataLen < sizeof myRandomInteger)
	{
		ssize_t result = read(randomData, ((char*)&myRandomInteger) + randomDataLen, (sizeof myRandomInteger) - randomDataLen);
		if (result < 0)
		{
			// error, unable to read /dev/random
		}
		randomDataLen += result;
		printf("result->%zu\trandomDataLen->%zu\n", result, randomDataLen);
	}
	close(randomData);
}
// clang -Wall -Wextra -Werror -g3 -fsanitize=address -pedantic src/sandbox/random.c -o sandboxtest && ./sandboxtest && rm -rf  sandboxtest*
//Fuente: https://www.iteramos.com/pregunta/27781/como-utilizar-devrandom-o-urandom-en-c
// Fuente: https://www.iteramos.com/pregunta/27781/como-utilizar-devrandom-o-urandom-en-c

