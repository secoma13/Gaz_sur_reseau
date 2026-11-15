#include<vector>
#include<math.h>
#include "randomc.h"
using namespace std;

double Energycalc(vector<vector<int> >& grid, vector<vector<int> >& pos, double a, int n, int m, double e, double sigma){ 
	// function to calculate the energy obtained from the potential calculating the interaction between every pair of atoms
	// this function calculates the energy taking every pair into account. This makes it very unefficient to calculate new energy at every step, because we
	// only change the position of one particle. We only use this function once, when the grid is filled for the first time to calculate the energy.
int i, j;
double E = 0; // the energy is initialised to 0
double k = sigma/a; // to write it on the potential
double r; // distance 

// we use double loop to check the iteraction between every pair. The coordinadas of the position of particle i are on the ith line of the matrix pos
//pos[0] constains the x coordinarte and pos[1] the y coordinate.
// At each iteration of the loop we add the new interaction energy to the total value.

for(i=0; i<m; i++){
	for(j=i+1; j<m; j++){
		r = sqrt( (pos[i][0] - pos[j][0])*(pos[i][0] - pos[j][0]) + (pos[i][1] - pos[j][1])*(pos[i][1] - pos[j][1]) );
		E = E + 4*e*( pow(k/r, 12) - pow(k/r, 6));
	}
}

return E;
}

double energychange(vector<vector<int> >& grid, vector<vector<int> >& pos, int m, int aux, double e, double a, double sigma){ 
	// we use this function to calculate the energy change whenever we move one single particle. 
	// Since only one particle moves, there is no need to calculate again all the interactions. 
	// the value of E gives the energy corresponding to the interaction of ONE particle (the particle identified by the index aux) with all other particles
int j;
double r;
double k = sigma/a;
double E = 0;

// inside the loop, we skip the term that would calculate the interaction of the particle with itself.

for(j=0; j<m; j++){
		if ( aux-1 != j ){
		r = sqrt( (pos[aux-1][0] - pos[j][0])*(pos[aux-1][0] - pos[j][0]) + (pos[aux-1][1] - pos[j][1])*(pos[aux-1][1] - pos[j][1]) );
		E = E + 4*e*( pow(k/r, 12) - pow(k/r, 6));
		}
  	}
return E;
}
