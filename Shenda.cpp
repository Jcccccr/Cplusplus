#define _CRT_SECURE_NO_WARNINGS 1

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>


char* convert(char* input)
{
     
}

int main() {
	char* res;

	char* _input;
	_input = (char *)malloc(512000 * sizeof(char));
	scanf("\n%[^\n]", _input);

	res = convert(_input);
	printf("%s\n", res);

	return 0;

}
