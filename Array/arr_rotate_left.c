/*
 * Write a c program to left rotate an array by d size
 */
#include <stdio.h>

static void rotate(int *arr, int start, int end)
{
	while (start < end) {
		int tmp = arr[start];
		arr[start] = arr[end];
		arr[end] = tmp;
		start++;
		end--;
	}		
}

static void print_arr(int *arr, size_t size)
{
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main() {
	int arr[] = {1,2,3,4,5,6,7};
	size_t size = sizeof(arr)/sizeof(arr[0]);
	int d = 3;
	
	/* First Rotate the array from start to d */
	rotate(arr, 0, d);
	print_arr(arr, size);
	/* Now Rotate the second hald from d + 1 to end */	
	rotate(arr, d+1, size-1);
	print_arr(arr, size);	
	/* Now rotate the complete array */
	rotate(arr, 0, size-1);
	print_arr(arr, size);	

	return 0;
}
