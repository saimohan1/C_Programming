#include <stdio.h>

int main() {
	int arr[] = {1,2,3,4,5};

	printf("Sizeof array is:%lu\n", sizeof(arr));
	printf("Sizeof array without sizeof operator:%lu\n", (char*)(&arr + 1) - (char *)(&arr));
	return 0;
}
