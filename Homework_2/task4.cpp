#include <cmath>
#include <iostream>

void moreMagic(int* read, int count, int exp, int* write) {
	int table[10] = { 0 };

	for (int c = 0; c < count; c++) {
		const int index = (read[c] / exp) % 10;
		table[index]++;
	}

	for (int c = 1; c < 10; c++) {
		table[c] += table[c - 1];
	}

	for (int c = count - 1; c >= 0; c--) {
		const int index = (read[c] / exp) % 10;
		write[table[index] - 1] = read[c];
		table[index]--;
	}

	//int* a = read;
	//read = write;
	//write = a;
	for (int i = 0; i < count; i++) 
	{
		int temp = read[i];
		read[i] = write[i];
		write[i] = temp;
	}
}

void magic(int* a, int count, int* b) {
	if (count < 2) {
		return;
	}
	int find = a[0];
	for (int c = 1; c < count; c++) //find the index of the max element in array a;
	{
		if (a[c] > a[find]) {
			find = c;
		}
	}
	const int max = a[find];
	const int base = log10(max) + 1;

	for (int c = 0, exp = 1; c < base + (base & 1); c++, exp *= 10) {
		moreMagic(a, count, exp, b);
	}
}


int main() 
{
	int n{0};
	std::cin >> n;
	int* a = new int[n];
	int* b = new int[n];
	for (int c = 0; c < n; c++) 
	{
		std::cin >> a[c];
	}
	magic(a, n, b);
	for (int c = 0; c < n; c++) 
	{
		std::cout << a[c] << ' ';
	}
	delete[] a;
	delete[] b;
	return 0;
}
//The code represented sorting algorithm for sorting arrays.