/*
		Metropolis algorithm

		Vivas,A;Arango,C;Arguelles,A;Rodriguez,K;
		Solid state theory group		
		Lascilab
		  
		Last updated: January 24, 2017

	This program is in development. 

*/
#include <stdlib.h>	/* Standard Libary: malloc, calloc, free, ralloc functions */
#include <stdio.h> 	/* Standard I/O Library: printf */
#include <math.h>	/* Standard Math Library */
#include <time.h>	/* Standard for time functions */

#define pi 3.14159265358979323846

/* random number Function Generator by using a linear congruential generator (LCG)
is an algorithm that yields a sequence of pseudo-randomized numbers calculated
with a discontinuous piecewise linear equation.	*/
double random_eng()
{	
	clock_t t;
	t=clock();
	double tc;
	tc = (((float)t)/CLOCKS_PER_SEC);
	double X = fmod((pi*t)+(pi/tc),(pi/tc));/*Seed*/
	double M = 2147483648,n;
	int a = 1103515245,c=12345,i;
	for(i=1;i<5;i++)
	{
		X = fmod((a*X+c),M);// Linear congruence
		n = (X/(M-1));
		}  
	return n;// Returns a number n with a [0,1) domain
}

void latticeload(int* B,int Nx,int Ny){
    	for(int i = 0; i < Nx*Ny; i++) {
	double	spin = random_eng();
	B[i] = (spin < 0.5)? 0:1;
	}	
}

int switchspin(int* B,int i){
    	if ( B[i] == 0 ) B[i] = 1;
		else if ( B[i] ==1 ) B[i] = 0;	
	return B[i];
}

int metropolis(int * B,int nx, int ny, int i){
	int row = 0, col = 0;
	row = i / nx, col = i % nx;

	double up = ( row - 1 < 0 || B[ i - nx ] == 0 ) ? 0 : 0.25;
	double down = ( row + 1 >= ny || B[ i + nx ] == 0 ) ? 0 : 0.25;
	double left = ( col - 1 < 0 || B[ i - 1 ] == 0 ) ? 0 : 0.25;
	double right = ( col + 1 >= nx || B[ i + 1 ] == 0) ? 0 : 0.25;
	double sum = up + down + left + right;
	double dice = random_eng();

	return ( dice > sum ) ? switchspin(B,i) : B[i];
}

int convergence(int * B, int nx, int ny){

}

void evolve(int * B, int nx, int ny){
	for (int i = 0; i < nx * ny; ++i) B[i] = metropolis(B,nx,ny,i);
}

int main(int argc, char const **argv)
{
	int Nx = 10;
    	int Ny = 10;

	int * B = NULL;

	B = (int *) malloc( Nx * Ny * sizeof(int));

	latticeload(B,Nx,Ny);

	for (int i = 1; i <= Nx * Ny; i++)
	{
	printf("%d\t", B[i-1]);
	if(i % Nx == 0) printf("\n");
	}

	printf("\n");

	evolve(B,Nx,Ny);

	for (int i = 1; i <= Nx * Ny; i++)
	{
	printf("%d\t", B[i-1]);
	if(i % Nx == 0) printf("\n");
	}
	/*FILE *dskw1;
	char FileName[100];
	int file;
	file=sprintf(FileName,"./Outputdata/MtrMthd_v1.0_%d_Matrix.dat",Nx*Ny);
	file++;
  	dskw1=fopen(FileName,"w+");

	for (int i = 0 ; i < Nx * Ny; i++) {

	evolve(B,Nx,Ny);
	
	for (i = 1; i <= Nx * Ny; i++)
	{
		fprintf(dskw1,"%d\t", B[i-1]);
		if(i % Nx == 0) fprintf(dskw1,"\n");
	}

	}*/
	
	free(B);

	return 0;
}
