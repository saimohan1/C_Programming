#include <stdio.h>

int main() {
	int arr[] = {1,2,3,4,5,6,7};
	int target = 9;
	int first = 0;
	int last = (sizeof(arr)/sizeof(arr[0])) - 1;
	
	while (first < last) {
		if (arr[first] + arr[last] > target) {
			last--;
		} else if (arr[first] + arr[last] < target) {
			first++;
		} else if (arr[first] + arr[last] == target) {
			printf("Piar (%d, %d)\n", arr[first], arr[last]);
			first++;
			last--;
		}
	}

	return 0;
}
