#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "api.h"
#include "params_additionals.h"
#include "common_defs.h"

int keySeedIndex = 0;

void InitializeFramework()
{
	#ifdef DEBUG_MODE
		keySeedIndex = 0;
	#else
		keySeedIndex = rand() % 4;
	#endif


	if(dimension ==16){
		p1 = p1_seed[keySeedIndex];
		p2 = p2_seed[keySeedIndex];
	}else if(dimension == 32){
		p1 = p1_seed[keySeedIndex + 4];
		p2 = p2_seed[keySeedIndex + 4];
	}else if(dimension == 64){
		p1 = p1_seed[keySeedIndex + 8];
		p2 = p2_seed[keySeedIndex + 8];
	}

	int memoryBlockIndex = keySeedIndex;
	int initialPointerPosition = 0;
	
	if(dimension == 32){
		initialPointerPosition = 64;
	}else if(dimension == 64){
		initialPointerPosition = 192;
	}

	for(int i=0;i<dimension;i++){

		int dataIndex = initialPointerPosition + dimension * memoryBlockIndex + i;
		f_original[i] = f_p_seed[dataIndex];
		f_p1 [i] = f_p1_seed[dataIndex];
		f_p2 [i] = f_p2_seed[dataIndex];
	}

}


/*
	For debug, we use an array of 64 integers. If dimension = 16 or 32, only the first 16 or 32 integers are used.
*/
void randombytesDebugKeyGen(unsigned long long* ephemeralKey)
{
	unsigned int debugEphemeralKey[64] = { 8, 24, 13, 28, 5, 8, 4, 4, 26, 17, 17, 4, 26, 19, 10, 15, 12, 2, 7, 3, 5, 7, 12, 1, 27, 29, 15, 15, 10, 27, 11, 3, 24, 12, 7, 12, 2, 4, 29, 29, 17, 1, 7, 10, 25, 0, 1, 5, 20, 22, 20, 13, 16, 9, 23, 5, 21, 5, 11, 19, 24, 2, 28, 24 };

	for (int i = 0; i < wordSize; i++) {
		ephemeralKey[i] = debugEphemeralKey[i];
	}
}

/*
	For debug, we use an array of 64 integers. If dimension = 16 or 32, only the first 16 or 32 integers are used.
*/
void randombytesDebugEncrypt(unsigned long long* ephemeralKey2) {
	
	unsigned int debugEphemeralKey2[64] = { 19, 17, 18, 12, 20, 20, 33, 32, 26, 15, 33, 21, 14, 38, 35, 22, 25, 24, 8, 12, 19, 9, 34, 7, 9, 6, 9, 17, 12, 37, 17, 7, 37, 40, 17, 4, 10, 16, 24, 10, 24, 29,9, 4, 12, 13, 17, 20, 3, 10, 32, 1, 38, 29, 20, 23, 9, 18, 39, 22, 21, 9, 20, 25 };

	for (int i = 0; i < wordSize; i++) {
		ephemeralKey2[i] = debugEphemeralKey2[i];
	}
}

void debugMessage(unsigned long long* message) {

	unsigned int debugMessage[64] = {84,104,105,115,32,105,115,32,97,32,108,111,110,103,32,115,105,122,101,32,109,101,115,115,97,103,101,32,102,111,114,32,116,101,115,116,105,110,103,32,97,110,100,32,100,101,98,117,103,103,105,110,103,32,112,117,114,112,111,115,101,115,33,33};

	for (int i = 0; i < wordSize; i++) {
		message[i] = debugMessage[i];
	}
}


int GenerateKeys(unsigned long long* publicKey, unsigned long long* privateKey, unsigned long long* ephemeralKey)
{
	unsigned long long pivot[dimension];
	GenerateConvolution(pivot, f_p2, ephemeralKey);
	MultiplyByConstant(pivot, pivot, p1);
	ReduceBigModulo(publicKey, pivot, p2);

	memcpy(privateKey, f_p1, 8 * dimension);

	return 0;
}

int Encrypt(unsigned long long* cipherText, unsigned long long* ss, unsigned long long* pk, unsigned long long* noise) {
	unsigned long long randomization[dimension];
	
	unsigned long long pivot[dimension];
	unsigned long long sspivot[dimension];
	unsigned long long cipherTextPivot[dimension];

	GenerateConvolution(randomization, pk, noise);

	//memset(cipherTextPivot, 0, 8 * dimension);

	for(int i=0;i<wordSize/dimension;i++){

		//memset(pivot, 0, 8*dimension);
		//memset(sspivot, 0, 8*dimension);

		for(int j=0;j<dimension;j++){
			sspivot[j] = ss[i*dimension + j];
		}

		AddArraysUIntLong(pivot, sspivot, randomization);
		ReduceBigModulo(cipherTextPivot, pivot, p2);

		for(int j=0;j<dimension;j++){
			cipherText[i*dimension + j] = cipherTextPivot[j];
		}
	}

	return 0;
}

int Decrypt(unsigned long long* ss1, unsigned long long* cipherText, unsigned long long* sk) {
	
	unsigned long long cipherTextPivot[dimension];

	for(int i=0;i<wordSize/dimension;i++){

		for(int j=0;j<dimension;j++){
			cipherTextPivot[j] = cipherText[i*dimension+j];
		}

		unsigned long long pivot[dimension];

		GenerateConvolution(pivot, cipherTextPivot, f_original);

		ReduceBigModulo(pivot, pivot, p2);
		ReduceBigModulo(pivot, pivot, p1);

		unsigned long long secondPivotUncipheredMsg[dimension];

		GenerateConvolution(secondPivotUncipheredMsg, sk, pivot);

		unsigned long long ss1Pivot[dimension];

		ReduceBigModulo(ss1Pivot, secondPivotUncipheredMsg, p1);

		for(int j=0;j<dimension;j++){
			ss1[i*dimension+j] = ss1Pivot[j];
		}
	}

	/*unsigned long long pivot[dimension];

	GenerateConvolution(pivot, cipherText, f_original);

	ReduceBigModulo(pivot, pivot, p2);
	ReduceBigModulo(pivot, pivot, p1);

	unsigned long long secondPivotUncipheredMsg[dimension];

	GenerateConvolution(secondPivotUncipheredMsg, sk, pivot);
	ReduceBigModulo(ss1, secondPivotUncipheredMsg, p1);*/

	return 0;
}

void randombytes(unsigned long long* randomNumbers, int modulo) {
	for (int i = 0; i < wordSize; i++) {
		randomNumbers[i] = rand() % modulo;
	}
}



void MultiplyByConstant(unsigned long long* result, unsigned long long* array, unsigned long long coeff) {
	for(int i=0;i<dimension;i++){
		result[i] = array[i] * coeff;
	}
}

void ReduceBigModulo(unsigned long long* arrayTo, unsigned long long* arrayFrom, unsigned long long modulo){
	for(int i=0;i<dimension;i++){
		arrayTo[i] = arrayFrom[i] % modulo;
	}
}

void AddArraysUIntLong(unsigned long long* result, unsigned long long* f, unsigned long long* g){
	for(int i=0;i<dimension;i++){
		result[i] = f[i] + g[i];
	}
}



void GenerateConvolution(unsigned long long* result, unsigned long long* f, unsigned long long* g)
{

#ifdef FFT
	GenerateConvolutionFFT(result, f, g);
#else
    GenerateConvolutionTraditional(result, f, g);
#endif

}

void GenerateConvolutionFFT(unsigned long long* result, unsigned long long* f, unsigned long long* g)
{
	complex* a;
   	complex* b;
	
	int next_power_of_2;

	next_power_of_2 = 1;
	while (next_power_of_2 < dimension)
		next_power_of_2 <<= 1;

	a = (complex*)malloc(2 * next_power_of_2 * sizeof(complex));
	b = (complex*)malloc(2 * next_power_of_2 * sizeof(complex));

	for (int i = 0; i < dimension; i++)
	{
		a[i].r_complex = (double)f[i];
        a[i].i_complex = 0.0;

		b[i].r_complex = (double)g[i];
		b[i].i_complex = 0.0;
	}

	for (int i = dimension; i < (2 * next_power_of_2); i++)
	{
		a[i].r_complex = 0.0; 
		a[i].i_complex = 0.0;
        b[i].r_complex = 0.0; 
		b[i].i_complex = 0.0;
	}
      
	int n = next_power_of_2;

	poly_mul(a, b, 2*n);

	//clear result
	for(int i=0;i<dimension;i++){
		result[i] = 0;
	}

	for(int i=0;i<(2*n - 1);i++){
		result[i % dimension] += (unsigned long long)round(a[i].r_complex);
	}

	/*free(a);
	free(b);*/

}

void GenerateConvolutionTraditional(unsigned long long* result, unsigned long long* f, unsigned long long* g)
{
    //clear result
    for(int i=0;i<dimension;i++){
		result[i] = 0;
	}

	//Convolution
	for(int i=0;i<dimension;i++){

		int counter = 1;

		for(int j=0;j<dimension;j++){

			 int k=0;

			 if((0<=j) && (j<=i)){
				 k=i-j;
			 }else{
				 k=dimension - counter;
				 counter++;
			 }

			 result[i] += f[j]*g[k];

		}
	}
}