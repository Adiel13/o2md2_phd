#ifndef API_H
#define API_H

#include "params.h"

#define CRYPTO_ALGNAME "O2MD2-OH6464"

void InitializeFramework();

void randombytesDebugKeyGen(unsigned long long* ephemeralKey);

void randombytesDebugEncrypt(unsigned long long* ephemeralKey2);

void debugMessage(unsigned long long* message);

int GenerateKeys(unsigned long long* publicKey, unsigned long long* privateKey, unsigned long long* ephemeralKey);

int Encrypt(unsigned long long* cipherText, unsigned long long* ss, unsigned long long* pk, unsigned long long* noise);

int Decrypt(unsigned long long* ss1, unsigned long long* cipherText, unsigned long long* sk);

void randombytes(unsigned long long* randomNumbers, int modulo);

void MultiplyByConstant(unsigned long long* result, unsigned long long* array, unsigned long long coeff);

void ReduceBigModulo(unsigned long long* arrayTo, unsigned long long* arrayFrom, unsigned long long modulo);

void AddArraysUIntLong(unsigned long long* result, unsigned long long* f, unsigned long long* g);

void GenerateConvolution(unsigned long long* result, unsigned long long* f, unsigned long long* g);

void GenerateConvolutionTraditional(unsigned long long* result, unsigned long long* f, unsigned long long*g);

void GenerateConvolutionFFT(unsigned long long* result, unsigned long long* f, unsigned long long* g);

int keySeedIndex;


#endif