#include <iostream>

using namespace std;

void print(int a[], int n) {
	for(int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

void quickSort(int arr[], int left, int right, int n) {
	int i = left, j = right;
	int tmp;
	int pivot = arr[(left + right) / 2];
	
	print(arr, n);
	
	while(i <= j) {
		while(arr[i] < pivot) i++;
		while(arr[j] > pivot) j--;
		if(i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	}
	if(left < j) quickSort(arr, left, j, n);
	if(i < right) quickSort(arr, i, right, n);
}

int main() {
	int a[] = {4,2,3,1,6,9,1,2,10};
	int n = (sizeof(a) / sizeof(a[0]));
	quickSort(a, 0, n - 1, n);
	print(a, n);
}
