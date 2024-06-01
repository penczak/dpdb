#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define name_size = 32;

struct column {
	char name[name_size];
	int data_size;
};

struct table {
	char name[name_size];
	struct column columns[];
};

int main() {

	return 0;
}