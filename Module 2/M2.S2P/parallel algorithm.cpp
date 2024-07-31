#include <iostream>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <thread>
#include <cmath>
#include <array>

using namespace std::chrono;
using namespace std;

/*
    Returns an array of ints containing a number of elements equalling numPartitions with
    each element being the length of a partition. Ensures remainder is as evenly distributed as
    possible.
*/
int* getPartitions(int length, int numPartitions) {
    int partition_size = floor(length / numPartitions);
    int remainder = length % numPartitions;
    int *arr = (int *) malloc(numPartitions * sizeof(int *));

    for (int i = 0; i < numPartitions; i++) {
        arr[i] = partition_size;
        if (remainder > 0) {
            arr[i]++;
            remainder--;
        }
    }

    return arr;
}

/*
    Random initialises a partition of the target vector with random numbers from 0 to 99
*/
void partitionedRandomVector(int vector[], int partition_start, int partition_size) {
    for (int i = 0; i < partition_size; i++) {
        // get random number modulo 100 and set at location i + partition_start in array
        vector[partition_start + i] = rand() % 100;
    }
}

/*
    Takes a vector and randomly initialises it. Using parallisation through numPartitions.
    Runs numPartitions as threads in paralell.
*/
void parallelRandomVector(int vector[], int size, int numPartitions) {
    int* partitions = getPartitions(size, numPartitions);
    thread threads[numPartitions];

    int vector_position = 0; // position/index in vector
    for (int i = 0; i < numPartitions; i++) {
        threads[i] = thread(partitionedRandomVector, vector, vector_position, partitions[i]);
        vector_position += partitions[i];
    }

    for (int i = 0; i < numPartitions; i++) {
        if (threads[i].joinable()) {
            threads[i].join();
        }
    }
    delete partitions;
}

/*
    Adds partitions of v1 and v2 = v3
*/
void partitionedVectorAdd(int v1[], int v2[], int v3[], int partition_start, int partition_size) {
    // within partition does i + partition_start to do v3[i] = sum of v1[i] and v2[i]
    for (int i = 0; i < partition_size; i++) {
        v3[i + partition_start] = v1[i + partition_start] + v2[i + partition_start];
        //cout << "\n" << partition_start << " " << v3[i + partition_start]; // used for debugging
    }
}

/*
    Breaks down v1, v2 and v3 into numPartitions of the most equal size possible
    Then for each partition runs a thread which does vector add of v3[i] = v1[i] + v2[i]
*/
void parallelVectorAdd(int v1[], int v2[], int v3[], int size, int numPartitions) {
    int* partitions = getPartitions(size, numPartitions);
    thread threads[numPartitions];

    int vector_position = 0; // position/index in vector
    for (int i = 0; i < numPartitions; i++) {
        threads[i] = thread(partitionedVectorAdd, v1, v2, v3, vector_position, partitions[i]);
        vector_position += partitions[i];
    }

    for (int i = 0; i < numPartitions; i++) {
        if (threads[i].joinable()) {
            threads[i].join();
        }
    }
    delete partitions;
}

int main(){
    unsigned long size = 100000000;
    int16_t numPartitions = 5000;
    srand(time(0));
    int *v1, *v2, *v3;

    // get the current time using this c++ implementation's clock with the smallest tick period / finest resolution
    auto start = high_resolution_clock::now();

    // for each of v1, v2, v3       
    // allocate contiguous space in heap of size * size in bytes of pointer to int
    // cast as usable pointer
    v1 = (int *) malloc(size * sizeof(int *));
    v2 = (int *) malloc(size * sizeof(int *));
    v3 = (int *) malloc(size * sizeof(int *));
    parallelRandomVector(v1, size, numPartitions);
    parallelRandomVector(v2, size, numPartitions);

    parallelVectorAdd(v1, v2, v3, size, numPartitions);

    auto stop = high_resolution_clock::now();

    // time taken to run = stop time minus start time, then cast to microseconds
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "\nTime taken by function: " << duration.count() << " microseconds" << endl;

    return 0;
}
