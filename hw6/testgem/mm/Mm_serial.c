/************************************************************************
Name : Mounika Ponugoti
File : Matrix_multiplication_serial.c
Discricption : Multipliying two matrices MatrixA, MatrixB and the result
			   is in MatrixC. All the three are square matrices of size 
			   matrixSizeN, which is supplied through command line from 
			   the user.  
*************************************************************************/
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MX_SZ 320
#define SEED 2397           /* random number seed */
#define MAX_VALUE  100.0    /* maximum size of Matrices */

int matrixSizeN;
/* Reading the command line */
void get_index_size(int argc,char *argv[]) {
   if(argc!=2) {
     printf( "usage:  mm_mult_serial [matrixSizeN] \n");
      exit(1);
   }
   else 
         matrixSizeN = atoi(argv[1]);
 
   if (matrixSizeN <= 0 ) {
     printf("Error: number of rows and/or columns must be greater than 0 \n");
      exit(1);
   }
}
/* Filling the matrices using random generator */
void fill_matrix(double **array,int matrixSizeN)
{
   int i, j;
   for(i = 0; i < matrixSizeN; i++) {
      for (j = 0; j < matrixSizeN; j++) {
         array[i][j] = drand48()*MAX_VALUE;
      }
   }
}
/* For debugging */
/*
void print_matrix(double **array, int matrixSizeN)
{
   for(int i = 0; i < matrixSizeN; i++) {
      for (int j = 0; j < matrixSizeN; j++) {
         printf("%f  ",array[i][j]);// printf(" ");
      }
      printf("\n");
   }
}
*/
/* Main program */

int main( int argc, char *argv[])
{
	get_index_size(argc,argv);
	double **matrixA, **matrixB, **matrixC;
	double dot_product;
	int i,j,k;
	FILE *ptr_myfile;
	/* Allocate memory */
	matrixA = malloc(matrixSizeN * sizeof *matrixA);
	matrixB = malloc(matrixSizeN * sizeof *matrixB);
	matrixC = malloc(matrixSizeN * sizeof *matrixC);
	for (i=0; i<matrixSizeN; i++){
		matrixA[i] = malloc(matrixSizeN * sizeof *matrixA[i]);
		matrixB[i] = malloc(matrixSizeN * sizeof *matrixB[i]);
		matrixC[i] = malloc(matrixSizeN * sizeof *matrixC[i]);
	}
	/* Fill the matrices using random generator */
	srand48(SEED);
	fill_matrix(matrixA,matrixSizeN);
	fill_matrix(matrixB,matrixSizeN);

	/* Open the output file */
	ptr_myfile=fopen("test_serial.bin","wb");
	if (!ptr_myfile){
		printf("Unable to open file!");
		return 1;
	}
	/* For debugging */
	/*  printf( "\n A matrix = \n");
	print_matrix(matrixA,matrixSizeN);

	printf( "\n B matrix = \n");
	print_matrix(matrixB,matrixSizeN); */
   
	/* Multiply the matrices */
	for (i = 0; i < matrixSizeN; i++) {
		for (j = 0; j < matrixSizeN; j++) {
			dot_product = 0.0;
			for (k = 0; k < matrixSizeN; k++) {
				dot_product += matrixA[i][k]*matrixB[k][j];
			}
			matrixC[i][j]= dot_product;
		}
	}
	/* Write to the output file */
	for (i = 0; i < matrixSizeN; i++) {
		for (j = 0; j < matrixSizeN; j++) {
			fwrite(&matrixC[i][j], sizeof(double), 1, ptr_myfile);
		}
	}
	fclose(ptr_myfile); 
	/*  printf("C matrix = \n");
	print_matrix(matrixC,matrixSizeN);

	/* deallocate the array */
	for (i=0; i<matrixSizeN; i++){
		free(matrixA[i]);
		free(matrixB[i]);
		free(matrixC[i]);
	}
	free(matrixA);
	free(matrixB);
	free(matrixC);
	return 0;
}
