#include "../../Helpers.h"

int main (int argc, char * argv[]){

    vector<vector<vector<double> > > Matrix;

	int gridSize = atoi(argv[1]);

    int numberOfIterations = atoi(argv[2]);

	int numWorkers = atoi(argv[3]);

    Helpers::initializeGrid(&Matrix,gridSize);

    auto startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numberOfIterations; ++i) Helpers::JacobiUpdateMatrix(&Matrix,gridSize,numWorkers);

    auto maxDifference = Helpers::maxDiff(Matrix,gridSize);

    auto endTime = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

    printf("%lu\n", duration.count());

    Helpers::writeToFile(Matrix,"./jc.data",gridSize);
   
    return 0;
}

