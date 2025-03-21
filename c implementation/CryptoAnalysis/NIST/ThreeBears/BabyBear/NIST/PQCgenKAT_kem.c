
//
//  PQCgenKAT_kem.c
//
//  Created by Bassham, Lawrence E (Fed) on 8/29/17.
//  Copyright © 2017 Bassham, Lawrence E (Fed). All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "rng.h"
#include "api.h"

#include <time.h>
#include <stdbool.h>

#define	MAX_MARKER_LEN		50
#define KAT_SUCCESS          0
#define KAT_FILE_OPEN_ERROR -1
#define KAT_DATA_ERROR      -3
#define KAT_CRYPTO_FAILURE  -4

int		FindMarker(FILE *infile, const char *marker);
int		ReadHex(FILE *infile, unsigned char *A, int Length, char *str);
void	fprintBstr(FILE *fp, char *S, unsigned char *A, unsigned long long L);

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
        printf("=== Statistics BabyBear ===\n");
    
    char                fn_req[32], fn_rsp[32];
    FILE                *fp_req, *fp_rsp;
    unsigned char       seed[48];
    unsigned char       entropy_input[48];
    unsigned char       ct[CRYPTO_CIPHERTEXTBYTES], ss[CRYPTO_BYTES], ss1[CRYPTO_BYTES];
    int                 count;
    int                 done;
    unsigned char       pk[CRYPTO_PUBLICKEYBYTES], sk[CRYPTO_SECRETKEYBYTES];
    int                 ret_val;
    
    // Create the REQUEST file
    sprintf(fn_req, "PQCkemKAT_%d.req", CRYPTO_SECRETKEYBYTES);
    if ( (fp_req = fopen(fn_req, "w")) == NULL ) {
        printf("Couldn't open <%s> for write\n", fn_req);
        return KAT_FILE_OPEN_ERROR;
    }
    sprintf(fn_rsp, "PQCkemKAT_%d.rsp", CRYPTO_SECRETKEYBYTES);
    if ( (fp_rsp = fopen(fn_rsp, "w")) == NULL ) {
        printf("Couldn't open <%s> for write\n", fn_rsp);
        return KAT_FILE_OPEN_ERROR;
    }
    
    for (int i=0; i<48; i++)
        entropy_input[i] = i;

    randombytes_init(entropy_input, NULL, 256);
    for (int i=0; i<100; i++) {
        fprintf(fp_req, "count = %d\n", i);
        randombytes(seed, 48);
        fprintBstr(fp_req, "seed = ", seed, 48);
        fprintf(fp_req, "pk =\n");
        fprintf(fp_req, "sk =\n");
        fprintf(fp_req, "ct =\n");
        fprintf(fp_req, "ss =\n\n");
    }
    fclose(fp_req);
    
    //Create the RESPONSE file based on what's in the REQUEST file
    if ( (fp_req = fopen(fn_req, "r")) == NULL ) {
        printf("Couldn't open <%s> for read\n", fn_req);
        return KAT_FILE_OPEN_ERROR;
    }
    
    fprintf(fp_rsp, "# %s\n\n", CRYPTO_ALGNAME);
    done = 0;
    do {
        if ( FindMarker(fp_req, "count = ") ) {
            int ret = fscanf(fp_req, "%d", &count);
            if (ret <= 0) return ret ? ret : -1; /* MH: avoid unused result warning */
        } else {
            break;
        }
        fprintf(fp_rsp, "count = %d\n", count);
        
        if ( !ReadHex(fp_req, seed, 48, "seed = ") ) {
            printf("ERROR: unable to read 'seed' from <%s>\n", fn_req);
            return KAT_DATA_ERROR;
        }
        fprintBstr(fp_rsp, "seed = ", seed, 48);
        
        randombytes_init(seed, NULL, 256);

#pragma region KeyGeneration

        if(printConsoleMessages)
            printf("\n\n====== %d ======\n", count);
        
        start = get_nanos();

        // Generate the public/private keypair
        if ( (ret_val = crypto_kem_keypair(pk, sk)) != 0) {
            printf("crypto_kem_keypair returned <%d>\n", ret_val);
            return KAT_CRYPTO_FAILURE;
        }

        end = get_nanos();
        printStatistics(count, "keyGeneration", start, end, keyGenTime, printConsoleMessages);

        fprintBstr(fp_rsp, "pk = ", pk, CRYPTO_PUBLICKEYBYTES);
        fprintBstr(fp_rsp, "sk = ", sk, CRYPTO_SECRETKEYBYTES);

#pragma endregion KeyGeneration

#pragma region Encryption

        start = get_nanos();
        
        if ( (ret_val = crypto_kem_enc(ct, ss, pk)) != 0) {
            printf("crypto_kem_enc returned <%d>\n", ret_val);
            return KAT_CRYPTO_FAILURE;
        }

        end = get_nanos();
        printStatistics(count, "Encryption", start, end, encryptionTime, printConsoleMessages);

        fprintBstr(fp_rsp, "ct = ", ct, CRYPTO_CIPHERTEXTBYTES);
        fprintBstr(fp_rsp, "ss = ", ss, CRYPTO_BYTES);
        
        fprintf(fp_rsp, "\n");

#pragma endregion Encryption

#pragma region Decryption

        start = get_nanos();
        
        if ( (ret_val = crypto_kem_dec(ss1, ct, sk)) != 0) {
            printf("crypto_kem_dec returned <%d>\n", ret_val);
            return KAT_CRYPTO_FAILURE;
        }

        end = get_nanos();
        printStatistics(count, "Decryption", start, end, decryptionTime, printConsoleMessages);
        
        if ( memcmp(ss, ss1, CRYPTO_BYTES) ) {
            printf("crypto_kem_dec returned bad 'ss' value\n");
            return KAT_CRYPTO_FAILURE;
        }

#pragma endregion Decryption

    } while ( !done );
    
    fclose(fp_req);
    fclose(fp_rsp);

    printStatisticsFile(keyGenTime,encryptionTime,decryptionTime);

    return KAT_SUCCESS;
}



//
// ALLOW TO READ HEXADECIMAL ENTRY (KEYS, DATA, TEXT, etc.)
//
int
FindMarker(FILE *infile, const char *marker)
{
	char	line[MAX_MARKER_LEN];
	int		i, len, tmp;

	len = (int)strlen(marker);
	if ( len > MAX_MARKER_LEN-1 )
		len = MAX_MARKER_LEN-1;

	for ( i=0; i<len; i++ ) {
	  line[i] = tmp = fgetc(infile);
	  if (tmp == EOF )
	    return 0;
	}
	  
	line[len] = '\0';

	while ( 1 ) {
		if ( !strncmp(line, marker, len) )
			return 1;

		for ( i=0; i<len-1; i++ )
			line[i] = line[i+1];
		line[len-1] = tmp = fgetc(infile);
		if ( tmp == EOF )
			return 0;
		line[len] = '\0';
	}

	// shouldn't get here
	return 0;
}

//
// ALLOW TO READ HEXADECIMAL ENTRY (KEYS, DATA, TEXT, etc.)
//
int
ReadHex(FILE *infile, unsigned char *A, int Length, char *str)
{
	int			i, ch, started;
	unsigned char	ich;

	if ( Length == 0 ) {
		A[0] = 0x00;
		return 1;
	}
	memset(A, 0x00, Length);
	started = 0;
	if ( FindMarker(infile, str) )
		while ( (ch = fgetc(infile)) != EOF ) {
			if ( !isxdigit(ch) ) {
				if ( !started ) {
					if ( ch == '\n' )
						break;
					else
						continue;
				}
				else
					break;
			}
			started = 1;
			if ( (ch >= '0') && (ch <= '9') )
				ich = ch - '0';
			else if ( (ch >= 'A') && (ch <= 'F') )
				ich = ch - 'A' + 10;
			else if ( (ch >= 'a') && (ch <= 'f') )
				ich = ch - 'a' + 10;
            else // shouldn't ever get here
                ich = 0;
			
			for ( i=0; i<Length-1; i++ )
				A[i] = (A[i] << 4) | (A[i+1] >> 4);
			A[Length-1] = (A[Length-1] << 4) | ich;
		}
	else
		return 0;

	return 1;
}

void
fprintBstr(FILE *fp, char *S, unsigned char *A, unsigned long long L)
{
	unsigned long long  i;

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
    statsFile = fopen("totalStatisticsThreeBears-Baby-Nano.csv", "w+");

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