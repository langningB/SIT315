#include <iostream>
#include <random>
#include <time.h>
#include <windows.h>
#include <string>
#include <fstream>
using namespace std;

#define volumn 1500
#define NUM_OF_THREADS 4

int first_array[volumn][volumn];
int second_array[volumn][volumn];
int output_array[volumn][volumn];

void starting_array(int array[volumn][volumn])
{
	for (int i = 0; i < volumn; i++)
	{
		for (int j = 0; j < volumn; j++)
		{
			array[i][j] = rand() % ((100 - 1) + 1) + 1;
		}
	}
}

void array_output(int index, int array_1[volumn][volumn], int array_2[volumn][volumn], int array_out[volumn][volumn])
{
	ofstream output (to_string(index) + ".txt");

	output  << "First array" << endl << "(";

	for (int i = 0; i < volumn; i++) {
		output  << "(";
		for (int j = 0; j < volumn; j++) {
			output  << array_1[i][j];
			output  << " ";
		}
		output  << ")" << endl;
	}
	output  << ")" << endl;

	output  << "Second array" << endl << "(";

	for (int i = 0; i < volumn; i++) {
		output  << "(";
		for (int j = 0; j < volumn; j++) {
			output  << array_2[i][j];
			output  << " ";
		}
		output  << ")" << endl;
	}
	output  << ")" << endl;

	output  << "Output Array " << endl << "(";

	for (int i = 0; i < volumn; i++)
	{
		output  << "(";
		for (int j = 0; j < volumn; j++) {
			output  << array_out[i][j];
			output  << " ";
		}
		output  << ")" << endl;
	}
	output  << ")" << endl;
	output .close();
}

DWORD WINAPI one_thread(LPVOID IP)
{
	int value;
	for (int i = 0; i < volumn; i++)
	{
		for (int j = 0; j < volumn; j++)
		{
			value = 0;
			for (int k = 0; k < volumn; k++)
			{
				value += first_array[i][k] * second_array[k][j];
			}
			output_array[i][j] = value;

		}
	}
	return 0L;
}

int main()
{
	clock_t start, stop;
	cout << volumn << " Rows:" << volumn << " columns: " << endl;

	for (int i = 0; i < NUM_OF_THREADS; i++)
	{
		cout << i << "numebr of threads: " << NUM_OF_THREADS << " threads" << endl;
		starting_array(first_array);
		starting_array(second_array);

		int start_s = clock(); 
		HANDLE hThread = CreateThread(NULL, 0, one_thread, NULL, 0, NULL);
		CloseHandle(hThread);
		int stop_s = clock();
		cout << "time took: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << "ms" << endl;
	}
}
