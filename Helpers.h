#pragma once

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <vector>
#include <omp.h>

using std::cout;
using std::endl;
using std::vector;

namespace Helpers{

    //Laplace's PDE, or Nabla² takes the limit of each point tending towards the average of its neighbours points,
    //and how this varies with time. This is why it is sometimes called the heat equation: given an input in 1d, 2d, 3d ...
    //where each point has a value corresponding to its temperature, where the temperature is given as f(x,y,z..) , as time -> infinity,
    //the temperatures will reach an equilibrium across the entire input space. A hot point surrounded by very cold points will get colder quickly
    //and the cold points will get slightly warmer, until all of the points reach the same value. Laplaces PDE: Nabla²(f(x,y,z...) = 0.
    //This method simulates this, by updating each point on the matrix to the average of its neighbouring 4 points.
    static void JacobiUpdateMatrix(vector<vector<vector<double> > > *Matrix,int gridSize){

        //do the calculations for all internal points of the grid (not boundary points)
        for (int i = 1; i < gridSize - 1; ++i)for (int j = 1; j < gridSize - 1; ++j)
            Matrix[1][i][j] = ((Matrix[0][i-1][j]) + (Matrix[0][i+1][j]) + (Matrix[0][i][j-1]) + (Matrix[0][i][j+1])) * .25;

        //make new matrix old matrix to prepare for next iteration, save old matrix in new matrix so we can calculate maxdiff still
        vector<vector<double> > temp;

        vector<vector<double> > * p1 = reinterpret_cast<vector<vector<double>> *>(&Matrix[0]);

        vector<vector<double> > * p2 = reinterpret_cast<vector<vector<double>> *>(&Matrix[1]);

        temp = *p2;

        *p2 = *p1;

        *p1 = temp;
    }

    static void JacobiUpdateMatrix(vector<vector<vector<double> > > *Matrix,int gridSize, int numWorkers){
        //set the number of threads we wish to use, taken from the commandline. Do the parallelize the for loop with omp.
        omp_set_num_threads(numWorkers);

        #pragma omp parallel for
        //do the calculations for all internal points of the grid (not boundary points)
        for (int i = 1; i < gridSize - 1; ++i) for (int j = 1; j < gridSize - 1; ++j)
            Matrix[1][i][j] = ((Matrix[0][i-1][j]) + (Matrix[0][i+1][j]) + (Matrix[0][i][j-1]) + (Matrix[0][i][j+1])) * .25;
        //make new matrix old matrix to prepare for next iteration, save old matrix in new matrix so we can calculate maxdiff still
        vector<vector<double> > temp;

        vector<vector<double> > * p1 = reinterpret_cast<vector<vector<double>> *>(&Matrix[0]);

        vector<vector<double> > * p2 = reinterpret_cast<vector<vector<double>> *>(&Matrix[1]);

        temp = *p2;

        *p2 = *p1;

        *p1 = temp;
    }

    //Calculate the values delta of each point from this iteration and last, and return the value of the highest one. The smaller this value is,
    //the less effective each subsequent iteration is, and the closer we are to the limit.
    static double maxDiff(const vector<vector<vector<double> > > &Matrix,int gridSize){

        double maxDiff = 0;
        for (int i = 0; i < gridSize; ++i){
            for (int j = 0; j < gridSize; ++j){
                double currentDiff = (1 - Matrix[0][i][j]);
                if (maxDiff < currentDiff)maxDiff = currentDiff;
            }
        }
        return maxDiff;
    }

    static void printMatrix(const vector<vector<vector<double> > > &Matrix,int gridSize, int current){
        for (int i = 0; i < gridSize; ++i){
            for (int j = 0; j < gridSize; ++j){
                cout << "|";
                cout << Matrix[current][i][j];
                cout << "|";
            }
            cout << endl;
        }
    }

//a method which takes the gridsize and initializes our matrix to what it's supposed to be (border cells = 1, everything else = 0)
    void initializeGrid(vector<vector<vector<double> > > *Matrix,int gridSize){
        //initialize the global matrix
        Matrix->resize(2);
        Matrix[0].resize(gridSize);
        Matrix[1].resize(gridSize);
        for (int i = 0; i < gridSize; ++i){
            Matrix[0][i].resize(gridSize);
            Matrix[1][i].resize(gridSize);
        }

    //set boundary values to 1
        for (int i = 0; i < gridSize; i += gridSize - 1){
            for (int j = 0; j < gridSize; ++j){
            Matrix[0][i][j] = 1;
            Matrix[0][j][i] = 1;
            Matrix[1][i][j] = 1;
            Matrix[1][j][i] = 1;
            }
        }
        //set internal values to 0
        for (int i = 1; i < gridSize - 1; ++i)for (int j = 1; j < gridSize - 1; ++j)Matrix[0][i][j] = 0;
    }

    void writeToFile(const vector<vector<vector<double> > > &Matrix, const std::string &name, int gridSize){

        std::ofstream out(name);

        for (int i = 0; i < gridSize; ++i){
            for (int j = 0; j < gridSize; ++j){
                out << "|" << Matrix[0][i][j] << "|";
            }
            out << endl;
        }
    }

    void MultigridUpdateMatrix(vector<vector<vector<double>>> &Matrix){
        
        int gridSize = Matrix[0].size();

        //do the calculations for all internal points of the grid (not boundary points)

        for (int i = 1; i < gridSize - 1; ++i) for (int j = 1; j < gridSize - 1; ++j)Matrix[1][i][j] = (Matrix[0][i-1][j]+Matrix[0][i+1][j]+Matrix[0][i][j-1]+Matrix[0][i][j+1]) * .25;

        //make new matrix old matrix to prepare for next iteration, save old matrix in new matrix so we can calculate maxdiff still

        vector<vector<double>> temp;

        vector<vector<double>> * p1 = &Matrix[0];

        vector<vector<double>> * p2 = &Matrix[1];

        temp = *p2;

        *p2 = *p1;

        *p1 = temp;
    }
    
    void MultigridUpdateMatrix( vector<vector<vector<double>>> &Matrix,int numWorkers){

        int gridSize = Matrix[0].size();

        //set the number of threads we wish to use, taken from the commandline. Do the parallelize the for loop with omp.	

        omp_set_num_threads(numWorkers);

    #pragma omp parallel for

        //do the calculations for all internal points of the grid (not boundary points)

        for (int i = 1; i < gridSize - 1; ++i) for (int j = 1; j < gridSize - 1; ++j)Matrix[1][i][j] = (Matrix[0][i-1][j]+Matrix[0][i+1][j]+Matrix[0][i][j-1]+Matrix[0][i][j+1]) * .25;

        //make new matrix old matrix to prepare for next iteration, save old matrix in new matrix so we can calculate maxdiff still

        vector<vector<double>> temp;

        vector<vector<double>> * p1 = &Matrix[0];

        vector<vector<double>> * p2 = &Matrix[1];

        temp = *p2;

        *p2 = *p1;

        *p1 = temp;
    }

    void iterate(vector<vector<vector<double>>> &Matrix){

        for (int i = 0; i < 4; ++i)MultigridUpdateMatrix(Matrix);

    }

    void iterate(vector<vector<vector<double>>> &Matrix,int numIters){

        for (int i = 0; i < numIters; ++i) MultigridUpdateMatrix(Matrix);

    }

    void iterateP(int numWorkers, vector<vector<vector<double>>> &Matrix){

        for (int i = 0; i < 4; ++i) MultigridUpdateMatrix(Matrix,numWorkers);

    }

    void iterateP(int numWorkers, int numIters, vector<vector<vector<double>>> &Matrix){

        for (int i = 0; i < numIters; ++i) MultigridUpdateMatrix(Matrix, numWorkers);

    }

    void resize(vector<vector<vector<double>>> *Matrix,int gridSize){
	
        Matrix->resize(2);
	
        Matrix[0].resize(gridSize);
	
        Matrix[1].resize(gridSize);
	
        for (int i = 0; i < gridSize; ++i){
	
    	    Matrix[0][i].resize(gridSize);
	
    	    Matrix[1][i].resize(gridSize);
	    }
    }

    static void restrict(vector<vector<vector<double>>> *Matrix){
	
        int newSize = (Matrix[0].size() + 1) / 2;
	    
        vector<vector<vector<double>>> tempMatrix;	

	    initializeGrid(&tempMatrix,newSize);
	
	//for each interior point, update it according to G. Andrews textbook p. 550-51
	    for (int i = 1; i < newSize - 1; ++i){
		    for (int j = 1; j < newSize - 1; ++j){
		    	int correspondingI = 2*i;
		    	int correspondingJ = 2*j;
			    tempMatrix[0][i][j] = Matrix[0][correspondingI][correspondingJ] * 0.5 + (Matrix[0][correspondingI - 1][correspondingJ] + Matrix[0][correspondingI + 1][correspondingJ] + Matrix[0][correspondingI][correspondingJ - 1] + Matrix[0][correspondingI][correspondingJ + 1]) * 0.125;
		}
	}

	Matrix = &tempMatrix;
}

void interpolate(vector<vector<vector<double>>> &Matrix){
	int newSize = Matrix[0].size() * 2 - 1;
	vector<vector<vector<double>>> tempMatrix;

	//initialize the new matrix to size we want + boundary conditions
	initializeGrid(&tempMatrix,newSize);

	//iterate only over directly corresponding points	
	for (int i = 2; i < newSize - 1; i += 2){
		
        for (int j = 2; j < newSize - 1; j += 2){
			
            //update the directly corresponding points
			int correspondingI = i/2;
			
            int correspondingJ = j/2;
			
            tempMatrix[0][i][j] = Matrix[0][correspondingI][correspondingJ];
			
			//update the points directly next to directly corresponding points
			tempMatrix[0][i - 1][j] += tempMatrix[0][i][j] * 0.5;
		
        	tempMatrix[0][i + 1][j] += tempMatrix[0][i][j] * 0.5;
		
        	tempMatrix[0][i][j - 1] += tempMatrix[0][i][j] * 0.5;
		
        	tempMatrix[0][i][j + 1] += tempMatrix[0][i][j] * 0.5;
			
			//update the adjacent points
			tempMatrix[0][i - 1][j - 1] += tempMatrix[0][i][j] * 0.25;
			
            tempMatrix[0][i - 1][j + 1] += tempMatrix[0][i][j] * 0.25;
		
        	tempMatrix[0][i + 1][j - 1] += tempMatrix[0][i][j] * 0.25;
		
        	tempMatrix[0][i + 1][j + 1] += tempMatrix[0][i][j] * 0.25;
		}
	}
	Matrix = tempMatrix;
}

void MultigridInitializeGrid(vector<vector<vector<double>>> *Matrix, int gridSize){

	resize(Matrix,gridSize);

	setDirichletBoundaryConditions(Matrix);

	for (int i = 1; i < gridSize - 1; ++i) for (int j = 1; j < gridSize - 1; ++j)Matrix[0][i][j] = 0;
	
	}
}

void setDirichletBoundaryConditions(vector<vector<vector<double>>> *Matrix){

	int gridSize = Matrix[0].size();
	
    for (int i = 0; i < gridSize; i += gridSize - 1){
		
        for (int j = 0; j < gridSize; ++j){
		
        	Matrix[0][i][j] = 1;
		
        	Matrix[0][j][i] = 1;
		
        	Matrix[1][i][j] = 1;
		
        	Matrix[1][j][i] = 1;
		} 
	}
}

}