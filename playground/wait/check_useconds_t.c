#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main(void)
{
	long 		i;
	useconds_t	k;

	i = -1;
	k = (useconds_t)i;
	printf("%o", k);
	if (k < 2)
		printf("YES\n");
}
