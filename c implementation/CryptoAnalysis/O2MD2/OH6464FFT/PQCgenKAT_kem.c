#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include <stdlib.h>

#include "api.h"

void fprintBstrDec(FILE* fp, char* S, unsigned long long* arrayToSave, unsigned long long dimensionToSave);

void fprintBstr(FILE* fp, char* S, unsigned long long* arrayToSave, unsigned long long dimensionToSave);
int FindMarker(FILE* infile, const char* marker);
int ReadHex(FILE* infile, unsigned long long* A, int Length, char* str);

#define KAT_SUCCESS          0
#define KAT_FILE_OPEN_ERROR -1
#define KAT_DATA_ERROR      -3
#define KAT_CRYPTO_FAILURE  -4

#define MAX_MARKER_LEN 50

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

    srand ( time(NULL) );
    InitializeFramework();

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

    unsigned long long seed[wordSize]; //  ephemeral key (used in keyGen, Encrypt)
    unsigned long long pk[dimension];   //  public key
    unsigned long long sk[dimension];   //  secret key
    unsigned long long ss[wordSize];   //  plaintext
    unsigned long long ct[wordSize];   //  ciphertext
    unsigned long long ss1[wordSize];  //  deciphered plaintext (should be the same as plaintext)

    int count;
    int done;
    int ret_val;

    char fn_req[32], fn_rsp[32];
    FILE* fp_req, * fp_rsp;

    memset(seed, 0, 8 * wordSize);

    sprintf(fn_req, "PQCkemKAT_%d.req", dimension);
    if ((fp_req = fopen(fn_req, "w")) == NULL)
    {
        printf("Couldn't open <%s> for write\n", fn_req);
        return KAT_FILE_OPEN_ERROR;
    }
    sprintf(fn_rsp, "PQCkemKAT_%d.rsp", dimension);
    if ((fp_rsp = fopen(fn_rsp, "w")) == NULL)
    {
        printf("Couldn't open <%s> for write\n", fn_rsp);
        return KAT_FILE_OPEN_ERROR;
    }

    for (int i = 0; i < 100; i++)
    {
        fprintf(fp_req, "count = %d\n", i);

        #ifdef DEBUG_MODE
            randombytesDebugKeyGen(seed);
        #else
            randombytes(seed, a_tilde);
        #endif
        
        fprintBstr(fp_req, "seed = ", seed, wordSize);
        
        fprintf(fp_req, "pk =\n");
        fprintf(fp_req, "sk =\n");
        fprintf(fp_req, "ct =\n");
        fprintf(fp_req, "ss =\n");
        fprintf(fp_req, "ss1 =\n");
        fprintf(fp_req, "pass? =\n\n");
    }
    fclose(fp_req);

    if ((fp_req = fopen(fn_req, "r")) == NULL)
    {
        printf("Couldn't open <%s> for read\n", fn_req);
        return KAT_FILE_OPEN_ERROR;
    }

    fprintf(fp_rsp, "# %s\n\n", CRYPTO_ALGNAME);
    done = 0;

    do {

#pragma region Clear arrays

        memset(pk, 0, 8 * dimension);
        memset(sk, 0, 8 * dimension);
        memset(seed, 0, 8 * wordSize);
        memset(ss, 0, 8 * wordSize);
        memset(ct, 0, 8 * wordSize);
        memset(ss1, 0, 8 * wordSize);

#pragma endregion 

        if (FindMarker(fp_req, "count = ")) {
            int getNextCase = fscanf(fp_req, "%d", &count);
            
            if (getNextCase != 1) {
                printf("ERROR: unable to read 'count' from <%s>\n", fn_req);
                return KAT_DATA_ERROR;
            }
        }
        else
        {
            done = 1;
            break;
        }
        fprintf(fp_rsp, "count = %d\n", count);

        if (!ReadHex(fp_req, seed, wordSize, "seed = ")) {
            printf("ERROR: unable to read 'seed' from <%s>\n", fn_req);
            return KAT_DATA_ERROR;
        }

        fprintBstr(fp_rsp, "seed = ", seed, wordSize);

        #ifdef DEBUG_MODE
            fprintBstrDec(fp_rsp, "seedDec = ", seed, wordSize);
        #endif

#pragma region KeyGeneration

        if(printConsoleMessages)
            printf("\n\n====== %d ======\n", count);

        start = get_nanos();

        if ((ret_val = GenerateKeys(pk, sk, seed)) != 0)
        {
            printf("crypto_kem_keypair returned <%d>\n", ret_val);
            return KAT_CRYPTO_FAILURE;
        }

        end = get_nanos();

        printStatistics(count, "keyGeneration", start, end, keyGenTime, printConsoleMessages);

#pragma endregion KeyGeneration

        fprintBstr(fp_rsp, "pk = ", pk, dimension);
        #ifdef DEBUG_MODE
            fprintBstrDec(fp_rsp, "pkDec = ", pk, dimension);
        #endif

        fprintBstr(fp_rsp, "sk = ", sk, dimension);
        #ifdef DEBUG_MODE
            fprintBstrDec(fp_rsp, "skDec = ", sk, dimension);
        #endif

        #ifndef DEBUG_MODE
            randombytes(ss, r);
            randombytes(seed, b_tilde);
        #else
            debugMessage(ss);
            randombytesDebugEncrypt(seed);
        #endif
        
#pragma region Encryption

        start = get_nanos();

        if ((ret_val = Encrypt(ct, ss, pk, seed)) != 0)
        {
            printf("crypto_kem_enc returned <%d>\n", ret_val);
            return KAT_CRYPTO_FAILURE;
        }

        end = get_nanos();

        printStatistics(count, "Encryption", start, end, encryptionTime, printConsoleMessages);

#pragma endregion Encryption

        fprintBstr(fp_rsp, "ss = ", ss, wordSize);
        #ifdef DEBUG_MODE
            fprintBstrDec(fp_rsp, "ssDec = ", ss, wordSize);
        #endif

        fprintBstr(fp_rsp, "ct = ", ct, wordSize);
        #ifdef DEBUG_MODE
            fprintBstrDec(fp_rsp, "ctDec = ", ct, wordSize);
        #endif

#pragma region Decryption

        start = get_nanos();

        if ((ret_val = Decrypt(ss1, ct, sk)) != 0)
        {
            printf("crypto_kem_dec returned <%d>\n", ret_val);
            return KAT_CRYPTO_FAILURE;
        }

        end = get_nanos();

        printStatistics(count, "Decryption", start, end, decryptionTime, printConsoleMessages);

#pragma endregion Decryption

        fprintBstr(fp_rsp, "ss1 = ", ss1, wordSize);
        #ifdef DEBUG_MODE
            fprintBstrDec(fp_rsp, "ss1Dec = ", ss1, wordSize);
        #endif

#pragma region Check for ss == ss1

        bool decipheredSuccessful = true;

        for (int i = 0; i < wordSize; i++) {
            if (ss[i] != ss1[i]) {
                decipheredSuccessful = false;
                break;
            }
        }
        if(printConsoleMessages)
            printf("ss==ss1 : %s\n", decipheredSuccessful ? "true" : "false");
        
        fprintf(fp_rsp, "pass? = %s\n", decipheredSuccessful ? "true" : "false");

        fprintf(fp_rsp, "\n");

#pragma endregion

    } while (!done);

    fclose(fp_req);
    fclose(fp_rsp);

    printStatisticsFile(keyGenTime, encryptionTime, decryptionTime);

    return 0;
}


int ReadHex(FILE* infile, unsigned long long* A, int Length, char* str) {

    unsigned long long temp = 0;

    int counter = 0;

    if (Length == 0) {
        A[0] = 0;
        return 1;
    }
    memset(A, 0, 8 * Length);   //it is unsigned long long

    if (FindMarker(infile, str))
        while (fscanf(infile, "%llx ", &temp) == 1) {
            A[counter] = temp;
            counter++;
        }
    else
        return 0;

    return 1;
}


int FindMarker(FILE* infile, const char* marker)
{
    char line[MAX_MARKER_LEN];
    int i, len;
    int curr_line;

    len = (int)strlen(marker);
    if (len > MAX_MARKER_LEN - 1)
        len = MAX_MARKER_LEN - 1;

    for (i = 0; i < len; i++)
    {
        curr_line = fgetc(infile);
        line[i] = curr_line;
        if (curr_line == EOF)
            return 0;
    }
    line[len] = '\0';

    while (1)
    {
        if (!strncmp(line, marker, len))
            return 1;

        for (i = 0; i < len - 1; i++)
            line[i] = line[i + 1];
        curr_line = fgetc(infile);
        line[len - 1] = curr_line;
        if (curr_line == EOF)
            return 0;
        line[len] = '\0';
    }

    // shouldn't get here
    return 0;
}

void fprintBstr(FILE* fp, char* S, unsigned long long* arrayToSave, unsigned long long dimensionToSave)
{
    fprintf(fp, "%s", S);

    for (int i = 0; i < dimensionToSave; i++) {
        fprintf(fp, "%llx ", arrayToSave[i]);
    }
    
    fprintf(fp, "\n");
}

void fprintBstrDec(FILE* fp, char* S, unsigned long long* arrayToSave, unsigned long long dimensionToSave)
{
    fprintf(fp, "%s", S);

    for (int i = 0; i < dimensionToSave; i++) {
        fprintf(fp, "%llu ", arrayToSave[i]);
    }
    
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

    char fileNameBuffer[100];
   
    #ifdef FFT
        snprintf(fileNameBuffer, sizeof(char)*50, "totalStatistics-O2MD2-OH%d64FFT.csv",dimension);
        statsFile = fopen(fileNameBuffer, "w+");
    #else
        snprintf(fileNameBuffer, sizeof(char)*50, "totalStatistics-O2MD2-OH%d64.csv",dimension);
        statsFile = fopen(fileNameBuffer, "w+");
    #endif

    

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