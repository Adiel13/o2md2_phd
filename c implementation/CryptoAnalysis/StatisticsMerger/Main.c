#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "params.h"
#include "statisticsFileNames.h"

int columnAmount = 3 * 25;  //25 algorithms

void MergeStatistics(char totalStatistics[100][columnAmount][50]);    //100 KATs - 3*25 columns (25 algorithms) - 50 char variables
void GetValues(char totalStatistics[100][columnAmount][50], FILE *readFile, int keyGenColumNumber, int encryptColumnNumber, int decryptColumnNUmber);


int main(int argc,char* argv[]) {

    bool printConsoleMessages = true;

    char totalStatistics[100][columnAmount][50]; //100 KAT - 3 columns per algorithm (25 algorithms)

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

    //Clear totalStatistics array
    for(int i=0;i<100;i++){
        for(int j=0;j<columnAmount;j++){
            memset(totalStatistics[i][j],0,50);
        }
    }

    FILE *fp_O2MD2_OH6416 = fopen(STATS_O2MD2_OH6416, "r");
    FILE *fp_O2MD2_OH6432 = fopen(STATS_O2MD2_OH6432, "r");
    FILE *fp_O2MD2_OH6464 = fopen(STATS_O2MD2_OH6464, "r");

    FILE *fp_O2MD2_OH6416FFT = fopen(STATS_O2MD2_OH6416FFT, "r");
    FILE *fp_O2MD2_OH6432FFT = fopen(STATS_O2MD2_OH6432FFT, "r");
    FILE *fp_O2MD2_OH6464FFT = fopen(STATS_O2MD2_OH6464FFT, "r");

    FILE *fp_NTRU_HPS2048509 = fopen(STATS_NTRU_HPS2048509, "r");
    FILE *fp_NTRU_HPS2048677 = fopen(STATS_NTRU_HPS2048677, "r");
    FILE *fp_NTRU_HPS4096821 = fopen(STATS_NTRU_HPS4096821, "r");
    FILE *fp_NTRU_HRSS701 = fopen(STATS_NTRU_HRSS701, "r");

    FILE *fp_NTRULPR653 = fopen(STATS_NTRULPR653, "r");
    FILE *fp_NTRULPR761 = fopen(STATS_NTRULPR761, "r");
    FILE *fp_NTRULPR857 = fopen(STATS_NTRULPR857, "r");

    FILE *fp_SNTRUP653 = fopen(STATS_SNTRUP653, "r");
    FILE *fp_SNTRUP761 = fopen(STATS_SNTRUP761, "r");
    FILE *fp_SNTRUP857 = fopen(STATS_SNTRUP857, "r");

    FILE *fp_FRODOKEM_640 = fopen(STATS_FRODOKEM_640, "r");
    FILE *fp_FRODOKEM_976 = fopen(STATS_FRODOKEM_976, "r");
    FILE *fp_FRODOKEM_1344 = fopen(STATS_FRODOKEM_1344, "r");

    FILE *fp_KYBER512 = fopen(STATS_KYBER512, "r");
    FILE *fp_KYBER768 = fopen(STATS_KYBER768, "r");
    FILE *fp_KYBER1024 = fopen(STATS_KYBER1024, "r");

    FILE *fp_THREEBEARS_BABYBEAR = fopen(STATS_THREEBEARS_BABYBEAR, "r");
    FILE *fp_THREEBEARS_MAMABEAR = fopen(STATS_THREEBEARS_MAMABEAR, "r");
    FILE *fp_THREEBEARS_PAPABEAR = fopen(STATS_THREEBEARS_PAPABEAR, "r");


    if (!fp_O2MD2_OH6416    || !fp_O2MD2_OH6432     || !fp_O2MD2_OH6464 || 
        !fp_O2MD2_OH6416FFT || !fp_O2MD2_OH6432FFT  || !fp_O2MD2_OH6464FFT  ||
        !fp_NTRU_HPS2048509 || !fp_NTRU_HPS2048677  || !fp_NTRU_HPS4096821  || !fp_NTRU_HRSS701 ||
        !fp_NTRULPR653      || !fp_NTRULPR761       || !fp_NTRULPR857   ||
        !fp_SNTRUP653       || !fp_SNTRUP761        || !fp_SNTRUP857    ||
        !fp_FRODOKEM_640    || !fp_FRODOKEM_976     || !fp_FRODOKEM_1344    ||
        !fp_KYBER512        || !fp_KYBER768         || !fp_KYBER1024    ||
        !fp_THREEBEARS_BABYBEAR || !fp_THREEBEARS_MAMABEAR  || !fp_THREEBEARS_PAPABEAR
        ) 
    {
        printf("Cannot open statistic files.\n");
        return -1;
    }

    GetValues(totalStatistics, fp_O2MD2_OH6416, o2md2_OH6416_columnKeygen, o2md2_OH6416_columnEncrypt, o2md2_OH6416_columnDecrypt);
    GetValues(totalStatistics, fp_O2MD2_OH6432, o2md2_OH6432_columnKeygen, o2md2_OH6432_columnEncrypt, o2md2_OH6432_columnDecrypt);
    GetValues(totalStatistics, fp_O2MD2_OH6464, o2md2_OH6464_columnKeygen, o2md2_OH6464_columnEncrypt, o2md2_OH6464_columnDecrypt);
    GetValues(totalStatistics, fp_O2MD2_OH6416FFT, o2md2_OH6416FFT_columnKeygen, o2md2_OH6416FFT_columnEncrypt, o2md2_OH6416FFT_columnDecrypt);
    GetValues(totalStatistics, fp_O2MD2_OH6432FFT, o2md2_OH6432FFT_columnKeygen, o2md2_OH6432FFT_columnEncrypt, o2md2_OH6432FFT_columnDecrypt);
    GetValues(totalStatistics, fp_O2MD2_OH6464FFT, o2md2_OH6464FFT_columnKeygen, o2md2_OH6464FFT_columnEncrypt, o2md2_OH6464FFT_columnDecrypt);

    GetValues(totalStatistics, fp_NTRU_HPS2048509, ntru_hps2048509_columnKeygen, ntru_hps2048509_columnEncrypt, ntru_hps2048509_columnDecrypt);
    GetValues(totalStatistics, fp_NTRU_HPS2048677, ntru_hps2048677_columnKeygen, ntru_hps2048677_columnEncrypt, ntru_hps2048677_columnDecrypt);
    GetValues(totalStatistics, fp_NTRU_HPS4096821, ntru_hps4096821_columnKeygen, ntru_hps4096821_columnEncrypt, ntru_hps4096821_columnDecrypt);
    GetValues(totalStatistics, fp_NTRU_HRSS701, ntru_hrss701_columnKeygen, ntru_hrss701_columnEncrypt, ntru_hrss701_columnDecrypt);

    GetValues(totalStatistics, fp_NTRULPR653, ntruprime_ntrulpr653_columnKeygen, ntruprime_ntrulpr653_columnEncrypt, ntruprime_ntrulpr653_columnDecrypt);
    GetValues(totalStatistics, fp_NTRULPR761, ntruprime_ntrulpr761_columnKeygen, ntruprime_ntrulpr761_columnEncrypt, ntruprime_ntrulpr761_columnDecrypt);
    GetValues(totalStatistics, fp_NTRULPR857, ntruprime_ntrulpr857_columnKeygen, ntruprime_ntrulpr857_columnEncrypt, ntruprime_ntrulpr857_columnDecrypt);
    GetValues(totalStatistics, fp_SNTRUP653, ntruprime_sntrup653_columnKeygen, ntruprime_sntrup653_columnEncrypt, ntruprime_sntrup653_columnDecrypt);
    GetValues(totalStatistics, fp_SNTRUP761, ntruprime_sntrup761_columnKeygen, ntruprime_sntrup761_columnEncrypt, ntruprime_sntrup761_columnDecrypt);
    GetValues(totalStatistics, fp_SNTRUP857, ntruprime_sntrup857_columnKeygen, ntruprime_sntrup857_columnEncrypt, ntruprime_sntrup857_columnDecrypt);

    GetValues(totalStatistics, fp_FRODOKEM_640, FrodoKEM_640_columnKeygen, FrodoKEM_640_columnEncrypt, FrodoKEM_640_columnDecrypt);
    GetValues(totalStatistics, fp_FRODOKEM_976, FrodoKEM_976_columnKeygen, FrodoKEM_976_columnEncrypt, FrodoKEM_976_columnDecrypt);
    GetValues(totalStatistics, fp_FRODOKEM_1344, FrodoKEM_1344_columnKeygen, FrodoKEM_1344_columnEncrypt, FrodoKEM_1344_columnDecrypt);

    GetValues(totalStatistics, fp_KYBER512, kyber512_columnKeygen, kyber512_columnEncrypt, kyber512_columnDecrypt);
    GetValues(totalStatistics, fp_KYBER768, kyber768_columnKeygen, kyber768_columnEncrypt, kyber768_columnDecrypt);
    GetValues(totalStatistics, fp_KYBER1024, kyber1024_columnKeygen, kyber1024_columnEncrypt, kyber1024_columnDecrypt);

    GetValues(totalStatistics, fp_THREEBEARS_BABYBEAR, ThreeBears_BabyBear_columnKeygen, ThreeBears_BabyBear_columnEncrypt, ThreeBears_BabyBear_columnDecrypt);
    GetValues(totalStatistics, fp_THREEBEARS_MAMABEAR, ThreeBears_MamaBear_columnKeygen, ThreeBears_MamaBear_columnEncrypt, ThreeBears_MamaBear_columnDecrypt);
    GetValues(totalStatistics, fp_THREEBEARS_PAPABEAR, ThreeBears_PapaBear_columnKeygen, ThreeBears_PapaBear_columnEncrypt, ThreeBears_PapaBear_columnDecrypt);

    MergeStatistics(totalStatistics);
    
    return 0;
}

void GetValues(char totalStatistics[100][columnAmount][50], FILE *readFile, int keyGenColumNumber, int encryptColumnNumber, int decryptColumnNUmber)
{
    char buf[1024];
    int row_count = 0;
    int field_count = 0;

    while (fgets(buf, 1024, readFile)) {
        field_count = 0;
        row_count++;

        if (row_count == 1) {
            continue;   //jump header
        }

        char *field = strtok(buf, ",");
        while (field) {
            if (field_count == 0) {
                //jump first column (case number)
            }
            if (field_count == 1) {
                //keygen
                memcpy(totalStatistics[row_count - 2][keyGenColumNumber],field,strlen(field)+1);
            }
            if (field_count == 2) {
                //decrypt
                memcpy(totalStatistics[row_count - 2][encryptColumnNumber],field,strlen(field)+1);
            }
            if (field_count == 3) {
                //encrypt
                memcpy(totalStatistics[row_count - 2][decryptColumnNUmber],field,strlen(field)+1);
            }

            //printf("%s\n", field);
            field = strtok(NULL, ",");

            field_count++;
        }
        //printf("\n");
    }

    fclose(readFile);
}


void MergeStatistics(char totalStatistics[100][columnAmount][50])
{
    FILE* statsFile;
    statsFile = fopen("StatisticsTotal.csv", "w+");

    fprintf(statsFile, " ,OH6416, OH6416, OH6416, ");  //O2MD2-OH6416
    fprintf(statsFile, "OH6432, OH6432, OH6432, ");  //O2MD2-OH6432
    fprintf(statsFile, "OH6464, OH6464, OH6464, ");  //O2MD2-OH6464
    fprintf(statsFile, "OH6416FFT, OH6416FFT, OH6416FFT, ");  //O2MD2-OH6416FFT
    fprintf(statsFile, "OH6432FFT, OH6432FFT, OH6432FFT, ");  //O2MD2-OH6432FFT
    fprintf(statsFile, "OH6464FFT, OH6464FFT, OH6464FFT, ");  //O2MD2-OH6464FFT

    fprintf(statsFile, "ntru-hps2048509, ntru-hps2048509, ntru-hps2048509, ");  //ntru-hps2048509
    fprintf(statsFile, "ntru-hps2048677, ntru-hps2048677, ntru-hps2048677, ");  //ntru-hps2048677
    fprintf(statsFile, "ntru-hps4096821, ntru-hps4096821, ntru-hps4096821, ");  //ntru-hps4096821
    fprintf(statsFile, "ntru-hrss701, ntru-hrss701, ntru-hrss701, ");  //ntru-hrss701

    fprintf(statsFile, "ntrulpr653, ntrulpr653, ntrulpr653, ");  //ntrulpr653
    fprintf(statsFile, "ntrulpr761, ntrulpr761, ntrulpr761, ");  //ntrulpr761
    fprintf(statsFile, "ntrulpr857, ntrulpr857, ntrulpr857, ");  //ntrulpr857
    fprintf(statsFile, "sntrup653, sntrup653, sntrup653, ");  //sntrup653
    fprintf(statsFile, "sntrup761, sntrup761, sntrup761, ");  //sntrup761
    fprintf(statsFile, "sntrup857, sntrup857, sntrup857, ");  //sntrup857

    fprintf(statsFile, "FrodoKEM-640, FrodoKEM-640, FrodoKEM-640, ");  //FrodoKEM-640
    fprintf(statsFile, "FrodoKEM-976, FrodoKEM-976, FrodoKEM-976, ");  //FrodoKEM-976
    fprintf(statsFile, "FrodoKEM-1344, FrodoKEM-1344, FrodoKEM-1344, ");  //FrodoKEM-1344

    fprintf(statsFile, "kyber512, kyber512, kyber512, ");  //kyber512
    fprintf(statsFile, "kyber768, kyber768, kyber768, ");  //kyber768
    fprintf(statsFile, "kyber1024, kyber1024, kyber1024, ");  //kyber1024

    fprintf(statsFile, "BabyBear, BabyBear, BabyBear, ");  //BabyBear
    fprintf(statsFile, "MamaBear, MamaBear, MamaBear, ");  //MamaBear
    fprintf(statsFile, "PapaBear, PapaBear, PapaBear\n");  //PapaBear


    fprintf(statsFile, "case No., KeyGen(ns), Encrypt(ns), Decrypt(ns), ");  //O2MD2-OH6416
    fprintf(statsFile, "KeyGen(ns), Encrypt(ns), Decrypt(ns), ");   //O2MD2-OH6432
    fprintf(statsFile, "KeyGen(ns), Encrypt(ns), Decrypt(ns), ");   //O2MD2-OH6464
    fprintf(statsFile, "KeyGen(ns), Encrypt(ns), Decrypt(ns), ");  //O2MD2-OH6416FFT
    fprintf(statsFile, "KeyGen(ns), Encrypt(ns), Decrypt(ns), ");  //O2MD2-OH6432FFT
    fprintf(statsFile, "KeyGen(ns), Encrypt(ns), Decrypt(ns), ");  //O2MD2-OH6464FFT

    fprintf(statsFile, "KeyGen(ns), Encrypt(ns), Decrypt(ns), ");  //ntru-hps2048509
    fprintf(statsFile, "KeyGen(ns), Encrypt(ns), Decrypt(ns), ");  //ntru-hps2048677
    fprintf(statsFile, "KeyGen(ns), Encrypt(ns), Decrypt(ns), ");  //ntru-hps4096821
    fprintf(statsFile, "KeyGen(ns), Encrypt(ns), Decrypt(ns), ");  //ntru-hrss701
    
    fprintf(statsFile, "KeyGen(ns), Encrypt(ns), Decrypt(ns), ");  //ntrulpr653
    fprintf(statsFile, "KeyGen(ns), Encrypt(ns), Decrypt(ns), ");  //ntrulpr761
    fprintf(statsFile, "KeyGen(ns), Encrypt(ns), Decrypt(ns), ");  //ntrulpr857
    fprintf(statsFile, "KeyGen(ns), Encrypt(ns), Decrypt(ns), ");  //sntrup653
    fprintf(statsFile, "KeyGen(ns), Encrypt(ns), Decrypt(ns), ");  //sntrup761
    fprintf(statsFile, "KeyGen(ns), Encrypt(ns), Decrypt(ns), ");  //sntrup857
    
    fprintf(statsFile, "KeyGen(ns), Encrypt(ns), Decrypt(ns), ");  //FrodoKEM-640
    fprintf(statsFile, "KeyGen(ns), Encrypt(ns), Decrypt(ns), ");  //FrodoKEM-976
    fprintf(statsFile, "KeyGen(ns), Encrypt(ns), Decrypt(ns), ");  //FrodoKEM-1344
    
    fprintf(statsFile, "KeyGen(ns), Encrypt(ns), Decrypt(ns), ");  //kyber512
    fprintf(statsFile, "KeyGen(ns), Encrypt(ns), Decrypt(ns), ");  //kyber768
    fprintf(statsFile, "KeyGen(ns), Encrypt(ns), Decrypt(ns), ");  //kyber1024

    fprintf(statsFile, "KeyGen(ns), Encrypt(ns), Decrypt(ns), ");  //BabyBear
    fprintf(statsFile, "KeyGen(ns), Encrypt(ns), Decrypt(ns), ");  //MamaBear
    fprintf(statsFile, "KeyGen(ns), Encrypt(ns), Decrypt(ns)\n");  //PapaBear
       
    for (int i = 0; i < 100; i++)
    {
        for(int j=0;j < columnAmount; j++){   //originally 27+3+3
            totalStatistics[i][j][ strcspn(totalStatistics[i][j],"\n") ] = '\0';
        }
        
        fprintf(statsFile, "%d, ", i);     //Counter

        fprintf(statsFile, "%s, %s, %s, ", totalStatistics[i][o2md2_OH6416_columnKeygen], totalStatistics[i][o2md2_OH6416_columnEncrypt], totalStatistics[i][o2md2_OH6416_columnDecrypt]);     
        fprintf(statsFile, "%s, %s, %s, ", totalStatistics[i][o2md2_OH6432_columnKeygen], totalStatistics[i][o2md2_OH6432_columnEncrypt], totalStatistics[i][o2md2_OH6432_columnDecrypt]);     
        fprintf(statsFile, "%s, %s, %s, ", totalStatistics[i][o2md2_OH6464_columnKeygen], totalStatistics[i][o2md2_OH6464_columnEncrypt], totalStatistics[i][o2md2_OH6464_columnDecrypt]);     
        fprintf(statsFile, "%s, %s, %s, ", totalStatistics[i][o2md2_OH6416FFT_columnKeygen], totalStatistics[i][o2md2_OH6416FFT_columnEncrypt], totalStatistics[i][o2md2_OH6416FFT_columnDecrypt]);     
        fprintf(statsFile, "%s, %s, %s, ", totalStatistics[i][o2md2_OH6432FFT_columnKeygen], totalStatistics[i][o2md2_OH6432FFT_columnEncrypt], totalStatistics[i][o2md2_OH6432FFT_columnDecrypt]);     
        fprintf(statsFile, "%s, %s, %s, ", totalStatistics[i][o2md2_OH6464FFT_columnKeygen], totalStatistics[i][o2md2_OH6464FFT_columnEncrypt], totalStatistics[i][o2md2_OH6464FFT_columnDecrypt]);     

        fprintf(statsFile, "%s, %s, %s, ", totalStatistics[i][ntru_hps2048509_columnKeygen], totalStatistics[i][ntru_hps2048509_columnEncrypt], totalStatistics[i][ntru_hps2048509_columnDecrypt]);     
        fprintf(statsFile, "%s, %s, %s, ", totalStatistics[i][ntru_hps2048677_columnKeygen], totalStatistics[i][ntru_hps2048677_columnEncrypt], totalStatistics[i][ntru_hps2048677_columnDecrypt]);     
        fprintf(statsFile, "%s, %s, %s, ", totalStatistics[i][ntru_hps4096821_columnKeygen], totalStatistics[i][ntru_hps4096821_columnEncrypt], totalStatistics[i][ntru_hps4096821_columnDecrypt]);     
        fprintf(statsFile, "%s, %s, %s, ", totalStatistics[i][ntru_hrss701_columnKeygen], totalStatistics[i][ntru_hrss701_columnEncrypt], totalStatistics[i][ntru_hrss701_columnDecrypt]);     

        fprintf(statsFile, "%s, %s, %s, ", totalStatistics[i][ntruprime_ntrulpr653_columnKeygen], totalStatistics[i][ntruprime_ntrulpr653_columnEncrypt], totalStatistics[i][ntruprime_ntrulpr653_columnDecrypt]);     
        fprintf(statsFile, "%s, %s, %s, ", totalStatistics[i][ntruprime_ntrulpr761_columnKeygen], totalStatistics[i][ntruprime_ntrulpr761_columnEncrypt], totalStatistics[i][ntruprime_ntrulpr761_columnDecrypt]);     
        fprintf(statsFile, "%s, %s, %s, ", totalStatistics[i][ntruprime_ntrulpr857_columnKeygen], totalStatistics[i][ntruprime_ntrulpr857_columnEncrypt], totalStatistics[i][ntruprime_ntrulpr857_columnDecrypt]);     
        fprintf(statsFile, "%s, %s, %s, ", totalStatistics[i][ntruprime_sntrup653_columnKeygen], totalStatistics[i][ntruprime_sntrup653_columnEncrypt], totalStatistics[i][ntruprime_sntrup653_columnDecrypt]);     
        fprintf(statsFile, "%s, %s, %s, ", totalStatistics[i][ntruprime_sntrup761_columnKeygen], totalStatistics[i][ntruprime_sntrup761_columnEncrypt], totalStatistics[i][ntruprime_sntrup761_columnDecrypt]);     
        fprintf(statsFile, "%s, %s, %s, ", totalStatistics[i][ntruprime_sntrup857_columnKeygen], totalStatistics[i][ntruprime_sntrup857_columnEncrypt], totalStatistics[i][ntruprime_sntrup857_columnDecrypt]);     

        fprintf(statsFile, "%s, %s, %s, ", totalStatistics[i][FrodoKEM_640_columnKeygen], totalStatistics[i][FrodoKEM_640_columnEncrypt], totalStatistics[i][FrodoKEM_640_columnDecrypt]);     
        fprintf(statsFile, "%s, %s, %s, ", totalStatistics[i][FrodoKEM_976_columnKeygen], totalStatistics[i][FrodoKEM_976_columnEncrypt], totalStatistics[i][FrodoKEM_976_columnDecrypt]);     
        fprintf(statsFile, "%s, %s, %s, ", totalStatistics[i][FrodoKEM_1344_columnKeygen], totalStatistics[i][FrodoKEM_1344_columnEncrypt], totalStatistics[i][FrodoKEM_1344_columnDecrypt]);     

        fprintf(statsFile, "%s, %s, %s, ", totalStatistics[i][kyber512_columnKeygen], totalStatistics[i][kyber512_columnEncrypt], totalStatistics[i][kyber512_columnDecrypt]);     
        fprintf(statsFile, "%s, %s, %s, ", totalStatistics[i][kyber768_columnKeygen], totalStatistics[i][kyber768_columnEncrypt], totalStatistics[i][kyber768_columnDecrypt]);     
        fprintf(statsFile, "%s, %s, %s, ", totalStatistics[i][kyber1024_columnKeygen], totalStatistics[i][kyber1024_columnEncrypt], totalStatistics[i][kyber1024_columnDecrypt]);     

        fprintf(statsFile, "%s, %s, %s, ", totalStatistics[i][ThreeBears_BabyBear_columnKeygen], totalStatistics[i][ThreeBears_BabyBear_columnEncrypt], totalStatistics[i][ThreeBears_BabyBear_columnDecrypt]);     
        fprintf(statsFile, "%s, %s, %s, ", totalStatistics[i][ThreeBears_MamaBear_columnKeygen], totalStatistics[i][ThreeBears_MamaBear_columnEncrypt], totalStatistics[i][ThreeBears_MamaBear_columnDecrypt]);     
        fprintf(statsFile, "%s, %s, %s\n", totalStatistics[i][ThreeBears_PapaBear_columnKeygen], totalStatistics[i][ThreeBears_PapaBear_columnEncrypt], totalStatistics[i][ThreeBears_PapaBear_columnDecrypt]);     
        
    }

    fclose(statsFile);
}