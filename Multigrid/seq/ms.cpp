#include "../../Helpers.h"

int main (int argc, char * argv[]){

	int gridSize =  atoi(argv[1]);
	
	int numIters = atoi(argv[2]);
	
	if ((gridSize - 5) % 4 != 0){
		cout << "((gridsize - 5) % 4) == 0) for the reduction to work properly!" << endl;
		return 1;
	}
	
	vector<vector<vector<double>>> Matrix;

	auto startTime = std::chrono::high_resolution_clock::now();
	
	Helpers::MultigridInitializeGrid(&Matrix,gridSize);

	for (int i = 0; i < 3; ++i){
		
		Helpers::iterate(Matrix);
		
		Helpers::restrict(&Matrix);
	
	}

	Helpers::restrict(&Matrix);
	
	Helpers::iterate(Matrix,numIters);


	for (int i = 0; i < 3; ++i){
		
		Helpers::interpolate(Matrix);
		
		Helpers::iterate(Matrix);
		
	}
	
	auto endTime = std::chrono::high_resolution_clock::now();
	
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

	printf("%lu\n", duration.count());

	Helpers::writeToFile(Matrix,"./ms.data", gridSize);

	return 0;
}
