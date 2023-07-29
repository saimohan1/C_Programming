/*
 * Write a C program to find missing number from
 * Array
 */

#include <stdio.h>

int main() {
	int arr[] = {1,2,3,4,5,7,8,9};
	int size = sizeof(arr)/sizeof(arr[0]);
	int sum = 0;	
	/* Adding 1 to the size is because the size is
	 * not included the missing number
	 */
	sum = ((size + 1) * ((size + 1) + 1))/2;

	printf("Sum:%d\n", sum);	
	
	for (int i =0; i < size; i++) {
		sum -= arr[i];
	}

	printf("Missing number is:%d\n", sum);
	return 0;
}
