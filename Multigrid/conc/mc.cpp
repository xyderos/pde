#include "../../Helpers.h"

int main (int argc, char * argv[]){
	
    int gridSize =  atoi(argv[1]);
	
	int numIters = atoi(argv[2]);
	
	int numWorkers = atoi(argv[3]);
	
	if ((gridSize - 5) % 4 != 0){
		cout << "((gridsize - 5) % 4) == 0) for the reduction to work properly!" << endl;
		return 1;
	}
	
	vector<vector<vector<double>>> Matrix;

	auto startTime = std::chrono::high_resolution_clock::now();
	
	Helpers::MultigridInitializeGrid(&Matrix,gridSize);

	for (int i = 0; i < 3; ++i){
	
		Helpers::iterateP(numWorkers, Matrix);
	
		Helpers::restrict(&Matrix);
	}

	Helpers::restrict(&Matrix);
	
	Helpers::iterateP(numWorkers, numIters, Matrix);

	for (int i = 0; i < 3; ++i){
		
		Helpers::interpolate(Matrix);
		
		Helpers::iterateP(numWorkers, Matrix);
	}
	
	auto endTime = std::chrono::high_resolution_clock::now();
	
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

	printf("%lu\n", duration.count());

	Helpers::writeToFile(Matrix,"./mc.data",gridSize);
	
	return 0;
}
