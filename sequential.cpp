#include <iostream>
#include <random>
#include <time.h>
#include <fstream>
#include <string>
using namespace std;

#define DIM 1001

int first_array[DIM][DIM];
int second_array[DIM][DIM];
int output_array[DIM][DIM];

void array_generator(int array[DIM][DIM])
{
	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
		{
			array[i][j] = rand() % ((100 - 1) + 1) + 1;
		}
	}
}

void array_output(int index, int array_1[DIM][DIM], int array_2[DIM][DIM], int array_out[DIM][DIM])
{
	ofstream output_file(to_string(index) + ".txt");

	output_file << "first array" << endl << "(";

	for (int i = 0; i < DIM; i++) {
		output_file << "(";
		for (int j = 0; j < DIM; j++) {
			output_file << array_1[i][j];
			output_file << " ";
		}
		output_file << ")" << endl;
	}
	output_file << ")" << endl;

	output_file << "second array" << endl << "(";

	for (int i = 0; i < DIM; i++) {
		output_file << "(";
		for (int j = 0; j < DIM; j++) {
			output_file << array_2[i][j];
			output_file << " ";
		}
		output_file << ")" << endl;
	}
	output_file << ")" << endl;

	output_file << "final array " << endl << "(";

	for (int i = 0; i < DIM; i++)
	{
		output_file << ")";
		for (int j = 0; j < DIM; j++) {
			output_file << array_out[i][j];
			output_file << " ";
		}
		output_file << ")" << endl;
	}
	output_file << ")" << endl;
	output_file.close();
}

void sequential(int array_1[DIM][DIM], int array_2[DIM][DIM], int array_out[DIM][DIM])
{
	int value;
	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
		{
			value = 0;
			for (int k = 0; k < DIM; k++)
			{
				value += array_1[i][k] * array_2[k][j];
			}
			array_out[i][j] = value;

		}
	}
}

int main()
{
	clock_t start, end;
	for (int i = 0; i < 5; i++)
	{
		array_generator(first_array);
		array_generator(second_array);

		int start_s = clock();
		sequential(first_array, second_array, output_array);
		int end_s = clock();

		array_output(i, first_array, second_array, output_array);

		cout << "Running time is: " << (end_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << "ms" << endl;
	}
}