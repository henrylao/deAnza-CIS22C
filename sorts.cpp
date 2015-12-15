// Thomas Tang
// Yuan Zheng
// Joe-Ming Cheng
// CIS22C Extra Credit Lab 4

#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>


void clearFile(std::string filename = "Output.txt") {
	std::ofstream outfile;
	outfile.open(filename);
	outfile.clear();
	outfile.close();
}

void printLTEArray(int arr[], int end, int start = 0, std::string filename = "Output.txt") {
	std::ofstream outfile;
	outfile.open(filename, std::ios_base::app);
	for (int i = start; i <= end; ++i) {
		std::cout << arr[i] << " ";
		outfile << arr[i] << " ";
	}
	std::cout << "\n";
	outfile << "\n";
}

void printLTArray(int arr[], int end, int start = 0, std::string filename = "Output.txt") {
	std::ofstream outfile;
	outfile.open(filename, std::ios_base::app);
	for (int i = start; i < end; ++i) {
		std::cout << arr[i] << " ";
		outfile << arr[i] << " ";
	}
	std::cout << "\n";
	outfile << "\n";
}

//====================================================================================
// MERGE SORT
//====================================================================================

void merge(int arr[], int left_low, int left_high, int right_low, int right_high) {
	printLTArray(arr, left_high + 1, left_low); // PRINT
	printLTArray(arr, right_high+1, right_low); // PRINT

	int temp_size = right_high + 1;
	int* temp = new int[temp_size];
	int l_cur = left_low;
	int r_cur = right_low;
	int cnt = left_low;
	while (cnt != right_high + 1){
		if (l_cur == right_low){
			temp[cnt] = arr[r_cur++];
		}
		else if (r_cur == right_high + 1){
			temp[cnt] = arr[l_cur++];
		}
		else{
			if (arr[l_cur] < arr[r_cur]){
				temp[cnt] = arr[l_cur++];
			}
			else{
				temp[cnt] = arr[r_cur++];
			}
		}
		cnt++;
	}

	for (int i = left_low; i < right_high + 1; ++i) { 
		arr[i] = temp[i]; 
	}

	delete temp;
}

void mergeSort(int arr[], int low, int high){
	if (high - low < 1)
		return;
	else {
		int mid = (low + high) / 2;

		mergeSort(arr, low, mid);
		mergeSort(arr, mid + 1, high);
		merge(arr, low, mid, mid + 1, high);
		
		printLTArray(arr, high+1, low); // PRINT
	}
}

void mergeSort(int arr[], int length){
	mergeSort(arr, 0, length - 1);
}

//====================================================================================
// QUICK SORT
//====================================================================================

void swap(int& a, int& b){
	int temp = a;
	a = b;
	b = temp;
}

int partition(int arr[], int start, int end) {
	int pivotValue, pivotIndex,  mid;
	mid = (start + end) / 2;
	swap(arr[start], arr[mid]);
	pivotIndex = start;
	pivotValue = arr[start];
	for (int scan = start + 1; scan <= end; scan++) {
		if (arr[scan] < pivotValue) {
			pivotIndex++;
			swap(arr[pivotIndex], arr[scan]);
		}
	}
	swap(arr[start], arr[pivotIndex]);
	return pivotIndex;
}


void quickSort(int arr[], int start, int end) {
	if (end - start >= 0) {
		printLTEArray(arr, end, start); // PRINT
	}

	int pivotPoint;
	if (start < end) {
		pivotPoint = partition(arr, start, end);

		quickSort(arr, start, pivotPoint - 1);
		printLTEArray(arr, pivotPoint - 1, start); // PRINT
		quickSort(arr, pivotPoint + 1, end);
		printLTEArray(arr, end, pivotPoint + 1); // PRINT
	}

	printLTEArray(arr, end, start); // PRINT
}

//====================================================================================
// INSERTION SORT
//====================================================================================
void insertionSort(int arr[], int sz) {
	int j;
	for (int i = 0; i < sz; ++i) {
		j = i;
		while (j > 0 && arr[j] < arr[j - 1]) {
			swap(arr[j], arr[j - 1]);
			j--;
		}
		printLTArray(arr, sz); // PRINT
	}
}





//====================================================================================
// MAIN
//====================================================================================
int main() {
	const int SORT_MAX_SIZE = 32;
	clearFile();
	std::ofstream outfile;
	outfile.open("Output.txt", std::ios_base::app);
	outfile << "Thomas Tang\nYuan Zheng\nJoe-Ming Cheng\nCIS22C Extra Credit Lab 4 \n\n";

	int numElements;
	std::cout << "Enter number of integer elements to sort (at most 32): ";
	outfile << "Enter number of integer elements to sort (at most 32): ";
	std::cin >> numElements;
	outfile << numElements << "\n";

	if (numElements > SORT_MAX_SIZE) {
		std::cout << "The number you entered is greater than 32, so the number of elements is 32.\n";
		outfile << "The number you entered is greater than 32, so the number of elements is 32.\n";
		numElements = SORT_MAX_SIZE;
	}

	int* arr1 = new int[numElements];
	int* arr2 = new int[numElements];
	int* arr3 = new int[numElements];

	std::cout << "Enter " << numElements << " integer elements into the array:\n";

	outfile << "Enter " << numElements << " integer elements into the array:\n";
	for (int i = 0; i < numElements; ++i) {
		std::cin >> arr1[i];
		arr2[i] = arr1[i];
		arr3[i] = arr1[i];
		outfile << arr1[i] << "\n";
	}

	
	
	std::cout << "\n\nBefore Sort: \n";
	outfile << "\n\nBefore Sort: \n";
	outfile.close();
	printLTArray(arr1, numElements);
	


	std::cout << "\n\nSorting: MergeSort\n";
	outfile.open("Output.txt", std::ios_base::app);
	outfile << "\n\nSorting: MergeSort\n";
	outfile.close();
	mergeSort(arr1, numElements);



	std::cout << "\n\nSorting: QuickSort\n";
	outfile.open("Output.txt", std::ios_base::app);
	outfile << "\n\nSorting: QuickSort\n";
	outfile.close();
	quickSort(arr2, 0, numElements - 1);



	std::cout << "\n\nSorting: InsertionSort\n";
	outfile.open("Output.txt", std::ios_base::app);
	outfile << "\n\nSorting: InsertionSort\n";
	outfile.close();
	insertionSort(arr3, numElements);

	
	std::cout << "\n\nAfter sort: \n";
	outfile.open("Output.txt", std::ios_base::app);
	outfile << "\n\nAfter sort: \n";
	outfile.close();
	printLTArray(arr1, numElements);
	
	system("pause");
	return 0;
}