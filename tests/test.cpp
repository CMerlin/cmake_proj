#include <stdio.h>
#include <string.h>
#include "common.h"

int main()
{
	printf("[%s]:line:%d\n", __func__, __LINE__);
	netFunc1();
	return 0;
}
