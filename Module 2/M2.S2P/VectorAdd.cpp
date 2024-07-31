#include <iostream>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <thread>

using namespace std::chrono;
using namespace std;

// Function to fill a vector with random values
void randomVector(int vector[], int size)
{
    for (int i = 0; i < size; i++)
    {
        // get random number modulo 100 and set at location i in array
        vector[i] = rand() % 100;
    }
}

int main(){

    unsigned long size = 100000000;

    srand(time(0));

    int *v1, *v2, *v3;

    // get the current time using this C++ implementation's clock with the smallest tick period / finest resolution
    auto start = high_resolution_clock::now();

    // for each of v1, v2, v3       
    // allocate contiguous space in heap of size * sizeof(int) bytes and cast as usable pointer
    v1 = (int *) malloc(size * sizeof(int));
    v2 = (int *) malloc(size * sizeof(int));
    v3 = (int *) malloc(size * sizeof(int));

    // Fill vectors v1 and v2 with random values
    randomVector(v1, size);
    randomVector(v2, size);

    // for loop counting up from 0 to size variable. element at v3[i] = sum of v1[i] and v2[i]
    for (int i = 0; i < size; i++)
    {
        v3[i] = v1[i] + v2[i];
    }

    auto stop = high_resolution_clock::now();

    // time taken to run = stop time minus start time, then cast to microseconds
    auto duration = duration_cast<microseconds>(stop - start);

    // Print the time taken by the function
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;

    // Free allocated memory
    free(v1);
    free(v2);
    free(v3);

    return 0;
}
