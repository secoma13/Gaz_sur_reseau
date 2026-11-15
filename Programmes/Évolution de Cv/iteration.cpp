#include<vector>
#include<math.h>
#include "randomc.h"
using namespace std;

double energychange(vector<vector<int> >& grid, vector<vector<int> >& pos, int m, int aux, double e, double a, double sigma);

void iter(vector<vector<int> >& grid, vector<vector<int> >& pos, int n, int m, CRandomMersenne & RandGen, double T, double& energy, double sigma, double e, double a){
	
// This function is used to simulate the random movement of particles according to the Metropolis method

	int m1, m2; // position of the particle that moves
	int aux = 0;
	double En;
	// double sigma = 0.333; // sigma constant in nm
	// double e = 125.7; // epsilon constant in units of temperature /kb
	// double a = 0.5;
	double Fboltz;
	
	while(aux == 0){
	// we start by choosing a random variable. The positions of the grid that contain particles have non-zero numbers, so we choose a random position
	// in the grid until we find one that has a particle
	
		m1 = floor(RandGen.Random()*n);
		m2 = floor(RandGen.Random()*n);
		
		// here we check if there is a particle in the position we choose
		
		aux = grid[m1][m2]; 
		// if there is a particle aux changes to its number. We use this afterwards to calculate the energy change.
	}
	double Eo = energychange(grid, pos, m, aux, e, a, sigma);
	// To use the function energychange to calculate Delta E after moving a particle we proceed as follows
	// 1. Once we have chosen the particle that is going to move, we calculate the part of the energy that corresponds to the interaction of that particle with all others
	// 2. Once the direction of movemenr has been chosen, we calculate the the interaction energy of ONLY that particle with all other particles.
	// 3. Since all other particles remain at their positions, their interactions do not change, hence Delta E is due only to the particle that moved, and can therefore
	// be calculated as the difference between the interaction energy of the particle that moves after moving, minus its energy before moving,

	
	// Now that we have selected a particle, we choose a random direction for the particle to move to. 
	//To do so, we choose a random integer number between 0 and 3, and assing to each number a direction movement. All 4 directions are equiprobable.
	// 0 is moving to the left, 1 upwadrs, 2 to the right and 3 upwards
	int direction = floor(RandGen.Random()*4);

	// Now we have to check several things:
	// 1. The position our particle is supposed to move to must be empty.
	// 2. If our particle was going to hit a wall, then nothing happends.
	// 3. Even if both previous conditions are met, we have to check the energy change and compare it to the Boltmann factor to see if the particle moves.
	switch(direction){
		case 0:
			if(m2 !=0 && grid[m1][m2-1] == 0){ // we do not make anything if there is already a particle in the chose direction or the particle is on a wall
				// if the particle can move to the selected position, we move it there. Now the initial position is empty, so we have to put a 0 there
				swap(grid[m1][m2-1], grid[m1][m2]);
				
				// to keep track of changes, and to be able to use the energy change function, we must change the coordinates of the particle indexed by aux in the 
				// position matrix
				pos[aux-1][1]= pos[aux-1][1]-1;
				
				// Now we calculate the energy when the particle moves as alredy explained
				En = energychange(grid, pos, m, aux, e, a, sigma);
 				
 				energy = energy + (En-Eo); // we update the value of the energy
 				// if the energy change is negative or zero, then we move the particle and nothing else happens
 				// if not, we compare it to the boltzmann factor
 				
 					if ( En-Eo >0 ){ 
 					Fboltz = exp((Eo-En)/T);
 						if (Fboltz < RandGen.Random()){ 
							// Since the Boltzmann factor is smaller that the random number, the particle does not have to move. However, we have already moved it
							// this means that we have to undo everything we have done: the grid and the pos matrices have to be changed to the form they have before moving
							// and the we add En-Eo (which we had substracted before) to gat the original value of the energy
 							swap (grid[m1][m2-1], grid[m1][m2]);
 							pos[aux-1][1]= pos[aux-1][1]+1;
 							energy = energy - (En-Eo); // we see that the particle does not move, we give the energy its previous value
 						}
 					}
			}
			break;
			
			// For all other cases the reasoning is the same
		case 1:
			if(m1 !=0 && grid[m1-1][m2] == 0){
				swap(grid[m1-1][m2], grid[m1][m2]);
				pos[aux-1][0]= pos[aux-1][0]-1;
				En = energychange ( grid, pos, m, aux, e, a, sigma);
 				energy = energy + (En-Eo); // we update the value of the energy
 					if ( En-Eo > 0 ){
 						Fboltz = exp((Eo-En)/T);
 							if (Fboltz < RandGen.Random() ){
 								swap (grid[m1-1][m2], grid[m1][m2]);
 								pos[aux-1][0]= pos[aux-1][0]+1;
 								energy = energy - (En-Eo); // we see that the particle does not move, we give the energy its previous value
 							}
 						}
			}
			break;
		case 2:
			if(m2 != n-1 && grid[m1][m2+1] == 0){
				swap(grid[m1][m2+1], grid[m1][m2]);
				pos[aux-1][1] = pos[aux-1][1]+1;
				En = energychange( grid, pos, m, aux, e, a, sigma);
 				 energy = energy + (En-Eo); // we update the value of the energy
  					if ( En-Eo >0 ){
 						Fboltz = exp((Eo-En)/T);
 							if (Fboltz < RandGen.Random() ){
 								swap (grid[m1][m2+1], grid[m1][m2]);
 								pos[aux-1][1] = pos[aux-1][1]-1;
 								energy = energy - (En-Eo); // we see that the particle does not move, we give the energy its previous value
 							}
 						}
			}

			break;
		default:
			if(m1 != n-1 && grid[m1+1][m2] == 0){
				swap(grid[m1+1][m2], grid[m1][m2]);
				pos[aux-1][0]= pos[aux-1][0]+1;
				En = energychange ( grid, pos, m, aux, e, a, sigma);
 				 energy = energy + (En-Eo); // we update the value of the energy
  					if ( En-Eo >0 ){
 						Fboltz = exp((Eo-En)/T);
 							if (Fboltz < RandGen.Random() ){
 								swap (grid[m1+1][m2], grid[m1][m2]);
 								pos[aux-1][0]= pos[aux-1][0]-1;
 								energy = energy - (En-Eo); // we see that the particle does not move, we give the energy its previous value
 							}
 						}
			}
			break;	
	}

}
