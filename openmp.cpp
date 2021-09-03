#include <stdio.h>
#include <iostream>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#include <omp.h>
using namespace std;

#define N 1500
int NUM_THREADS;
pthread_mutex_t mutx;

int inputArray[N][N];
int secondarray[N][N];
int finalarray[N][N];

void generateArray(int array[N][N]) {
	cout << 'generating array ';
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			array[i][j] = rand() % ((100 - 1) + 1) + 1;
		}
	}
	cout << 'array completed' << endl;
}

void displayArray(int array[N][N]) {
	cout << '（';
	for (int i = 0; i < N; i++) {
		cout << '（';
		for (int j = 0; j < N; j++) {
			cout << array[i][j];
			std::cout << ' ';
		}
		std::cout << '）\n';
	}
	std::cout << '）\n\n';
}

void sequential()
{
	int amount;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			amount = 0;
			for (int k = 0; k < N; k++)
			{
				amount += inputArray[i][k] * secondarray[k][j];
			}
			finalarray[i][j] = amount;
		}
	}
}

void* pthread(void* ID)
{
	long tid = (long)ID;
	long amount;

	int variation = N / NUM_THREADS;
	int initiate = tid * variation;
	int finish = initiate + variation;

	for (int i = initiate; i < finish; i++)
	{
		for (int j = 0; j < N; j++)
		{
			amount = 0;
			for (int k = 0; k < N; k++)
			{
				amount += inputArray[i][k] * secondarray[k][j];
			}
			finalarray[i][j] = amount;
		}
	}
	pthread_exit(NULL);
}
void openmp()
{
	#pragma omp parallel
	{	
		#pragma omp for
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				int amount = 0;
				for (int k = 0; k < N; k++)
				{
					amount += inputArray[i][k] * secondarray[k][j];
				}
				finalarray[i][j] = amount;
			}
		}
	}
}

int main(int argc, char* argv[])
{
	NUM_THREADS = atoi(argv[1]);
	struct timeval calculatetime;

	pthread_t threads[NUM_THREADS];
	pthread_mutex_init(&mutx, NULL);

	omp_set_num_threads(NUM_THREADS);

	cout << 'Size of matrix: ' << N << endl;
	generateArray(inputArray);
	generateArray(secondarray);

	cout << 'Sequential matrix is \t\tTime elapsed: ';
	gettimeofday(&calculatetime, NULL);

	long timestarted = (long)calculatetime.tv_sec * 1000 + (long)calculatetime.tv_usec / 1000;

	sequential();

	gettimeofday(&calculatetime, NULL);
	long timeended = (long)calculatetime.tv_sec * 1000 + (long)calculatetime.tv_usec / 1000;

	double time_took = timeended - timestarted;
	cout << time_took << 'ms' << endl;

	cout << 'pthread Matrix , number of threads' << NUM_THREADS << ' threads.\tTime took: ';

	gettimeofday(&calculatetime, NULL);

	timestarted = (long)calculatetime.tv_sec * 1000 + (long)calculatetime.tv_usec / 1000;

	for (long tid = 0; tid < NUM_THREADS; tid++) {
		pthread_create(&threads[tid], NULL, pthread, (void*)tid);
	}

	for (long tid = 0; tid < NUM_THREADS; tid++) {
		pthread_join(threads[tid], NULL);
	}

	gettimeofday(&calculatetime, NULL);
	timeended = (long)calculatetime.tv_sec * 1000 + (long)calculatetime.tv_usec / 1000;

	time_took = timeended - timestarted;
	cout << time_took << 'ms' << endl;

	cout << 'OpenMP Matrix, number of threads' << NUM_THREADS << ' threads.\tTime took: ';

	gettimeofday(&calculatetime, NULL);

	timestarted = (long)calculatetime.tv_sec * 1000 + (long)calculatetime.tv_usec / 1000;

	openmp();

	gettimeofday(&calculatetime, NULL);
	timeended = (long)calculatetime.tv_sec * 1000 + (long)calculatetime.tv_usec / 1000;

	time_took = timeended - timestarted;
	cout << time_took << 'ms' << endl;

	return 0;
}