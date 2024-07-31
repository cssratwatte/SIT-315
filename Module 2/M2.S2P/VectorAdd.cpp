#include <iostream>
#include <cstdlib>
#include <time.h>
#include <chrono>

using namespace std::chrono;
using namespace std;

// Function to fill a vector with random values
void randomVector(int vector[], int size)
{
    for (int i = 0; i < size; i++)
    {
        // Generate a random number between 0 and 99
        vector[i] = rand() % 100;
    }
}

int main(){
    unsigned long size = 100000000;

    srand(time(0));

    int *v1, *v2, *v3;

    // Record the start time of the entire operation
    auto start = high_resolution_clock::now();

    // Allocate memory for the vectors
    v1 = (int *) malloc(size * sizeof(int));
    v2 = (int *) malloc(size * sizeof(int));
    v3 = (int *) malloc(size * sizeof(int));

    // Fill vectors v1 and v2 with random values
    randomVector(v1, size);
    randomVector(v2, size);

    // Add the corresponding elements of v1 and v2, store the result in v3
    for (int i = 0; i < size; i++)
    {
        v3[i] = v1[i] + v2[i];
    }

    // Record the end time of the entire operation
    auto stop = high_resolution_clock::now();

    // Calculate the duration of the operation
    auto duration = duration_cast<microseconds>(stop - start);

    // Print the time taken by the function
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;

    // Free allocated memory
    free(v1);
    free(v2);
    free(v3);

    return 0;
}
