#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "api.h"

void fprintBstr(FILE* fp, char* S, unsigned long long* arrayToSave, unsigned long long dimensionToSave);
void fprintBstrBinary(FILE* fp, char* S, unsigned long long* arrayToSave, unsigned long long dimensionToSave);

int FindMarker(FILE* infile, const char* marker);
int ReadHex(FILE* infile, unsigned long long* A, int Length, char* str);

#define KAT_SUCCESS          0
#define KAT_FILE_OPEN_ERROR -1
#define KAT_DATA_ERROR      -3
#define KAT_CRYPTO_FAILURE  -4

#define MAX_MARKER_LEN 50

int main(int argc,char* argv[]) {

    bool debugMode = false;
    bool printConsoleMessages = true;

    srand ( time(NULL) );

    if(argc>=2) 
    {
        int stringCompare = 0;
        int argumentCounter = 0;

        for(argumentCounter=0;argumentCounter<argc;argumentCounter++){
            stringCompare= strcmp(argv[argumentCounter],"-noConsoleOutput");
            if(stringCompare == 0)
                printConsoleMessages = false;

            stringCompare= strcmp(argv[argumentCounter],"-debugMode");
            if(stringCompare == 0)
                debugMode = true;
        }
    }

    unsigned long long seed[dimension]; //  ephemeral key (used in keyGen, Encrypt)
    unsigned long long pk[dimension];   //  public key
    unsigned long long sk[dimension];   //  secret key
    unsigned long long ss[dimension];   //  plaintext
    unsigned long long ct[dimension];   //  ciphertext
    unsigned long long ss1[dimension];  //  deciphered plaintext (should be the same as plaintext)

    int count;
    int done;
    int ret_val;

    char fn_req[32], fn_rsp[32], fn_rsp_bin[64];
    FILE* fp_req, * fp_rsp;
    FILE* fp_rsp_binary;

    memset(seed, 0, 8 * dimension);

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
    sprintf(fn_rsp_bin, "PQCkemKAT_%d_binary.rsp", dimension);
    if ((fp_rsp_binary = fopen(fn_rsp_bin, "w")) == NULL)
    {
        printf("Couldn't open <%s> for write\n", fn_rsp_bin);
        return KAT_FILE_OPEN_ERROR;
    }

    for (int i = 0; i < 100; i++)
    {
        fprintf(fp_req, "count = %d\n", i);

        if (!debugMode)
            randombytes(seed, a_tilde);
        else
            randombytesDebugKeyGen(seed);

        fprintBstr(fp_req, "seed = ", seed, dimension);
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
        memset(seed, 0, 8 * dimension);
        memset(ss, 0, 8 * dimension);
        memset(ct, 0, 8 * dimension);
        memset(ss1, 0, 8 * dimension);

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

        if (!ReadHex(fp_req, seed, dimension, "seed = ")) {
            printf("ERROR: unable to read 'seed' from <%s>\n", fn_req);
            return KAT_DATA_ERROR;
        }

        fprintBstr(fp_rsp, "seed = ", seed, dimension);

#pragma region KeyGeneration

        if(printConsoleMessages)
            printf("\n\n====== %d ======\n", count);

        if ((ret_val = GenerateKeys(pk, sk, seed)) != 0)
        {
            printf("crypto_kem_keypair returned <%d>\n", ret_val);
            return KAT_CRYPTO_FAILURE;
        }

#pragma endregion KeyGeneration

        fprintBstr(fp_rsp, "pk = ", pk, dimension);
        fprintBstr(fp_rsp, "sk = ", sk, dimension);

        if (!debugMode) {
            randombytes(ss, r);
            randombytes(seed, b_tilde);
        }
        else {
            debugMessage(ss);
            randombytesDebugEncrypt(seed);
        }

#pragma region Encryption

        if ((ret_val = Encrypt(ct, ss, pk, seed)) != 0)
        {
            printf("crypto_kem_enc returned <%d>\n", ret_val);
            return KAT_CRYPTO_FAILURE;
        }

#pragma endregion Encryption

        fprintBstr(fp_rsp, "ct = ", ct, dimension);
        fprintBstr(fp_rsp, "ss = ", ss, dimension);

        fprintBstrBinary(fp_rsp_binary,"",ct, dimension);

#pragma region Decryption

        if ((ret_val = Decrypt(ss1, ct, sk)) != 0)
        {
            printf("crypto_kem_dec returned <%d>\n", ret_val);
            return KAT_CRYPTO_FAILURE;
        }

#pragma endregion Decryption

        fprintBstr(fp_rsp, "ss1 = ", ss1, dimension);

#pragma region Check for ss == ss1

        bool decipheredSuccessful = true;

        for (int i = 0; i < dimension; i++) {
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
    fclose(fp_rsp_binary);

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

void fprintBstrBinary(FILE* fp, char* S, unsigned long long* arrayToSave, unsigned long long dimensionToSave)
{
    int c, k;

    for (int i = 0; i < dimensionToSave; i++) {
        unsigned long long n = arrayToSave[i];
        
        for (c = 23; c >= 0; c--)
        {
            k = n >> c;

            if (k & 1)
                fprintf(fp,"1");
            else
                fprintf(fp,"0");
        }
        
        //fprintf(fp," ");
        //fprintf(fp, "%llx ", arrayToSave[i]);
    }

    fprintf(fp, "\n");

    // for (int i = 0; i < dimensionToSave; i++) {
    //     fprintf(fp, "%llx ", arrayToSave[i]);
    // }
    
    // fprintf(fp, "\n");

}