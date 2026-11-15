#include <iostream>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <fstream>

// To use the random number generator
#include "randomc.h"
#include "mersenne.cpp"
using namespace std;


// functions in he other source files
void iter(vector<vector<int> >& grid, vector<vector<int> >& pos, int n, int m, CRandomMersenne & RandGen, double T, double& energy, double sigma, double e, double a);
double Energycalc(vector<vector<int> >& grid, vector<vector<int> >& pos, double a, int n, int m, double e, double sigma);
double energychange(vector<vector<int> >& grid, vector<vector<int> >& pos, int m, int aux, double e, double a, double sigma);



void swap( int & i, int & j){ // function to swap the value of two variables
	int a;
	a = j;
	j = i;
	i = a;

}

int main(){
// we start the Marsenne random number generator
CRandomMersenne RandGen((int)time(NULL));

// We are going to model our gas as particles on a 2D square grid.
// Our grid is a 2D matrix that constains zeros at all the unoccupied positions, and integers numbering the particles at all occupied positions.
// This matrix can be used to visualize the grid when its dimension is small. We call it grid
// We also create a m x 2 matrix, where the line indicates the particle and the columns its position coordinates. For example, the 5th line constains
// the x and y coordinates of the 5th particle (on the first and second columns respectively). We call it pos


int n = 50; // dimension of the grid
vector<vector<int>> grid(n,vector<int>(n,0)); // our grid is a vector of vectors
int m = 500; // we call m the number of particles in the grid, which is another parameter we can modify
vector<vector<int>> pos(m,vector<int>(2,0)); // vector to save the positions of the particles


// the number of iterations. We will interpret it as time. At any "unit time" only one interaction happens. Moreover, whenever a time unit passes one particle 
//may or may not move
int t = 500000; 

double energyi;
int i, j;
int x, y;

// sigma, e and a are physical parameters that depend on the gas chosen. The values we give are those of Argon (obtained experimentally)
double sigma = 0.333; // sigma constant in nm 0.333
double e = 125.2; // epsilon constant in units of temperature /kb. 125.7
double a = 0.30; // a in the distance corresponding to he separation between two particles in the grid
double T = 1; // temperature in K.

// we open a string to write our solutions in an external file that we will use to visualise the grid afterwards.

// The stream f is used to store the value of the energy at each iteration, so that we can plot it afterwards as a function of the number of iterations
// and see how our system evolves. More precisely, we can use this to see how the energy of the system evolves, and how it fluctuates.
fstream f;
f.open("energy.txt", ios::out);

fstream f2;
f2.open("temperature.txt", ios::out);

// We are going to use this last stream to write the positions of the pqrticles to a external file
// after some number of iterations; We then make the animation using python
fstream f3;
f3.open("position.txt", ios::out);

// we start by choosing m random sites to place our particles at the initial time
// to do so, we choose a random position on the grid. If it is unoccupied, we place there a particle. If it is occupied, we choose another position.
// we do this until we place all m particles.
j = 0;
while(j < m){
	// coordinates of the place at which a particle will be located
	x = floor(RandGen.Random()*n);
	y = floor(RandGen.Random()*n);
	if (grid[x][y] == 0){ // then the position is unoccupied
			grid[x][y] = j + 1;
			pos[j][0] = x; // first coordinate of pos to store the line
			pos[j][1] = y; // first coordinate of pos to store the line
			j = j + 1;
			
	}
	// if the place already ha1d a particle, we repeat
}

// We save the energy of the initial configuration
energyi = Energycalc(grid, pos, a, n, m, e, sigma);
f << energyi << endl;


// To calculate the standard deviation, we are going to use the expression <E²> - <E>², where <> represent averages.
// So to see how it changes, we calculate it using the energies of tp iterations
int tp = t/50; // number of iterations for wich we calculate the standard deviation


// movement of particles
// In this loop we carry out the simulation. With each iteration we calculate the new disposition of the system using the iter function, and we save the value
// of the energy. 
// We also add the energies and their squares to calculte the standard deviations.
for(i=1; i<t ; i++){
	
	iter(grid, pos, n, m, RandGen, T, energyi, sigma, e, a);
	f << energyi << endl;
	
	// Whenever we arrive to a multiple of tp, we calculate the standard deviation using the previous tp iterations and the formula stated above.
	// after the calculation, we store the value and we reset the sum variables, so that they can be used to calculate the deviation of the next tp iterations
	if(i%tp == 0){ 
		// This part of the code is used to modify the temperature inside the loop
		// we use this when we want to study howw temperature changes affect to the termalisation
		// of the system
		T = T + 8.5;
		// we store the energy and the temperature to be a able to represent them later.
		f2 << T << " " << energyi << endl;		
	}
		
	// This part of the code is used if we want to see an animation with all the frames (one per iteration)
	// every 100 iterations, we store the position of each particle on a txt file.
	// We do not do it every iteration because we would have a very long animation at the end, and the program would take very long to run
	if(i%1000 == 0){ 
		for(j=0; j<m; j++){
		f3 << pos[j][0] << "," << pos[j][1] << endl;
		}
	}	

}

f.close();
f2.close();
f3.close();

return 0;
}
