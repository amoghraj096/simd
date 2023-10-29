//2D Heat Diffusion Simulation using Finite Difference Method
//Original 

#include <iostream>
#include <vector>
#include <ctime>

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
    // Initialize the grid
    std::vector<std::vector<double>> temperatureGrid(numRows, std::vector<double>(numCols, 0.0));

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
                // Calculate the new temperature using a simple finite difference method
                temperatureGrid[i][j] = temperatureGrid[i][j] + thermalConductivity * (temperatureGrid[i + 1][j] + temperatureGrid[i - 1][j] + temperatureGrid[i][j + 1] + temperatureGrid[i][j - 1] - 4 * temperatureGrid[i][j]);
            }
        }
    }

    // End the timer
    std::time_t end_time = std::time(nullptr);

    std::cout << "Simulation completed in " << difftime(end_time, start_time) << " seconds." << std::endl;

    return 0;
}
