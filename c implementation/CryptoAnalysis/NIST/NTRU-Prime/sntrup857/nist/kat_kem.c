/*
   PQCgenKAT_kem.c
   Created by Bassham, Lawrence E (Fed) on 8/29/17.
   Copyright © 2017 Bassham, Lawrence E (Fed). All rights reserved.
   + mods from djb: see KATNOTES
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rng.h"
#include "crypto_kem.h"

#include <time.h>
#include <stdbool.h>

#define KAT_SUCCESS          0
#define KAT_FILE_OPEN_ERROR -1
#define KAT_CRYPTO_FAILURE  -4

void    fprintBstr(FILE *fp, char *S, unsigned char *A, unsigned long long L);

unsigned char entropy_input[48];
unsigned char seed[100][48];

#pragma region StatisticFunc: Functions for statistics

static unsigned long long get_nanos(void);
void printStatistics(int iteration, char* actionMsg, unsigned long long clockStart, unsigned long long clockFinish, unsigned long long* timeArray, bool printConsoleMessages);
void printStatisticsFile(unsigned long long* keyGenTimeArray, unsigned long long* encryptionTimeArray, unsigned long long* decryptionTimeArray);

#pragma endregion

#pragma region StatisticVars : Variables for statistics

unsigned long long start, end;

unsigned long long cpu_time_used;
unsigned long long keyGenTime[100];
unsigned long long encryptionTime[100];
unsigned long long decryptionTime[100];

#pragma endregion

int main(int argc,char* argv[]) {

    bool printConsoleMessages = true;

    if(argc>=2) 
    {
        int stringCompare = 0;
        int argumentCounter = 0;
        for(argumentCounter=0;argumentCounter<argc;argumentCounter++){

            stringCompare= strcmp(argv[argumentCounter],"-noConsoleOutput");

            if(stringCompare == 0)
                printConsoleMessages = false;
        }
    }
    if(printConsoleMessages)
        printf("\n===== NTRU PRIME =====\n");


    FILE                *fp_req, *fp_rsp;
    int                 ret_val;
    int i;
    unsigned char *ct = 0;
    unsigned char *ss = 0;
    unsigned char *ss1 = 0;
    unsigned char *pk = 0;
    unsigned char *sk = 0;

    //int KATNUM = 100;

    for (i=0; i<48; i++)
        entropy_input[i] = i;
    randombytes_init(entropy_input, NULL, 256);

    for (i=0; i<KATNUM; i++)
        randombytes(seed[i], 48);

    fp_req = fdopen(8, "w");
    if (!fp_req)
        return KAT_FILE_OPEN_ERROR;

    for (i=0; i<KATNUM; i++) {
        fprintf(fp_req, "count = %d\n", i);
        fprintBstr(fp_req, "seed = ", seed[i], 48);
        fprintf(fp_req, "pk =\n");
        fprintf(fp_req, "sk =\n");
        fprintf(fp_req, "ct =\n");
        fprintf(fp_req, "ss =\n\n");
    }

    fp_rsp = fdopen(9, "w");
    if (!fp_rsp)
        return KAT_FILE_OPEN_ERROR;

    fprintf(fp_rsp, "# kem/%s\n\n", crypto_kem_PRIMITIVE);

    for (i=0; i<KATNUM; i++) {
        if (!ct) ct = malloc(crypto_kem_CIPHERTEXTBYTES);
        if (!ct) abort();
        if (!ss) ss = malloc(crypto_kem_BYTES);
        if (!ss) abort();
        if (!ss1) ss1 = malloc(crypto_kem_BYTES);
        if (!ss1) abort();
        if (!pk) pk = malloc(crypto_kem_PUBLICKEYBYTES);
        if (!pk) abort();
        if (!sk) sk = malloc(crypto_kem_SECRETKEYBYTES);
        if (!sk) abort();

        randombytes_init(seed[i], NULL, 256);

        fprintf(fp_rsp, "count = %d\n", i);
        fprintBstr(fp_rsp, "seed = ", seed[i], 48);

#pragma region KeGeneration

        start = get_nanos();
        
        if ( (ret_val = crypto_kem_keypair(pk, sk)) != 0) {
            fprintf(stderr, "crypto_kem_keypair returned <%d>\n", ret_val);
            return KAT_CRYPTO_FAILURE;
        }

        end = get_nanos();

        printStatistics(i, "keyGeneration", start, end, keyGenTime, printConsoleMessages);

#pragma endregion KeyGeneration

        fprintBstr(fp_rsp, "pk = ", pk, crypto_kem_PUBLICKEYBYTES);
        fprintBstr(fp_rsp, "sk = ", sk, crypto_kem_SECRETKEYBYTES);

#pragma region Encryption

        start = get_nanos();
        
        if ( (ret_val = crypto_kem_enc(ct, ss, pk)) != 0) {
            fprintf(stderr, "crypto_kem_enc returned <%d>\n", ret_val);
            return KAT_CRYPTO_FAILURE;
        }

        end = get_nanos();

        printStatistics(i, "Encryption", start, end, encryptionTime, printConsoleMessages);

#pragma endregion Encryption

#pragma region Decryption

        fprintBstr(fp_rsp, "ct = ", ct, crypto_kem_CIPHERTEXTBYTES);
        fprintBstr(fp_rsp, "ss = ", ss, crypto_kem_BYTES);
        
        fprintf(fp_rsp, "\n");

        start = get_nanos();
        
        if ( (ret_val = crypto_kem_dec(ss1, ct, sk)) != 0) {
            fprintf(stderr, "crypto_kem_dec returned <%d>\n", ret_val);
            return KAT_CRYPTO_FAILURE;
        }

        end = get_nanos();

        printStatistics(i, "Decryption", start, end, decryptionTime, printConsoleMessages);
        
        if ( memcmp(ss, ss1, crypto_kem_BYTES) ) {
            fprintf(stderr, "crypto_kem_dec returned bad 'ss' value\n");
            return KAT_CRYPTO_FAILURE;
        }

#pragma endregion Decryption

    }

    printStatisticsFile(keyGenTime,encryptionTime,decryptionTime);

    return KAT_SUCCESS;
}

void
fprintBstr(FILE *fp, char *S, unsigned char *A, unsigned long long L)
{
    unsigned long long i;

    fprintf(fp, "%s", S);

    for ( i=0; i<L; i++ )
        fprintf(fp, "%02X", A[i]);

    if ( L == 0 )
        fprintf(fp, "00");

    fprintf(fp, "\n");
}

void printStatistics(int iteration, char* actionMsg, unsigned long long clockStart, unsigned long long clockFinish, unsigned long long* timeArray, bool printConsoleMessages)
{
    unsigned long long timeUsed = ((unsigned long long)(clockFinish - clockStart));

    if(printConsoleMessages)
        printf("%s_%d = %llu ns.\n", actionMsg, iteration, timeUsed);

    timeArray[iteration] = timeUsed;
}

void printStatisticsFile(unsigned long long* keyGenTimeArray, unsigned long long* encryptionTimeArray, unsigned long long* decryptionTimeArray) {

    FILE* statsFile;
    statsFile = fopen("totalStatisticsNTRU-Prime-sntrup857-Nano.csv", "w+");

    fprintf(statsFile, "case No.,KeyGen(ns),Encrypt(ns),Decrypt(ns)\n");

    for (int i = 0; i < 100; i++)
    {
        fprintf(statsFile, "%d,%llu,%llu,%llu\n", i, keyGenTimeArray[i], encryptionTimeArray[i], decryptionTimeArray[i]);
    }

    fclose(statsFile);

}

static unsigned long long get_nanos(void) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (unsigned long long)ts.tv_sec * 1000000000ull + ts.tv_nsec;
}
