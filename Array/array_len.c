#include <stdio.h>

int main() {
	int array[10] = {1,2,3,4,5,6,7};
	size_t size = sizeof(array)/sizeof(array[0]);

	printf("Array Size is: %lu\n", size);

	return 0;
}
