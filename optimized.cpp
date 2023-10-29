// SIMD
#include <iostream>
#include <vector>
#include <ctime>
#include <immintrin.h>

// Grid properties
const int numRows = 350;
const int numCols = 350;
const double rodLengthX = 10.0;
const double rodLengthY = 10.0;

// Material properties
const double thermalConductivity = 1.0;

// Simulation time (in seconds)
const double simulationTime = 15.0;

int main() {
    // Initialize the grid as a 1D array
    const int gridSize = numRows * numCols;
    std::vector<double> temperatureGrid(gridSize, 0.0);

    // Element size
    const double elementSizeX = rodLengthX / numRows;
    const double elementSizeY = rodLengthY / numCols;

    // Calculate the number of time steps to reach the desired simulation time
    const int numTimeSteps = static_cast<int>(simulationTime / (elementSizeX * elementSizeY * thermalConductivity));

    // Start the timer
    std::time_t start_time = std::time(nullptr);

    // Simulation loop
    for (int step = 0; step < numTimeSteps; ++step) {
        for (int i = 1; i < numRows - 1; ++i) {
            for (int j = 1; j < numCols - 1; ++j) {
                int index = i * numCols + j;
                __m256d neighbors = _mm256_setr_pd(temperatureGrid[index + numCols], temperatureGrid[index - numCols], temperatureGrid[index + 1], temperatureGrid[index - 1]);
                __m256d current = _mm256_set1_pd(temperatureGrid[index]);
                __m256d factor = _mm256_set1_pd(thermalConductivity * elementSizeX * elementSizeY);
                __m256d newTemperature = _mm256_fmadd_pd(factor, neighbors, current);
                _mm256_storeu_pd(&temperatureGrid[index], newTemperature);
            }
        }
    }

    // End the timer
    std::time_t end_time = std::time(nullptr);

    std::cout << "Simulation completed in " << difftime(end_time, start_time) << " seconds." << std::endl;

    return 0;
}
