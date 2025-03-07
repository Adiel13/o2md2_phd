clear

echo "Crypto generator"

# Algorithms folders

FOLDER_O2MD2_OH6416="O2MD2/OH6416"
FOLDER_O2MD2_OH6432="O2MD2/OH6432"
FOLDER_O2MD2_OH6464="O2MD2/OH6464"
FOLDER_O2MD2_OH6416FFT="O2MD2/OH6416FFT"
FOLDER_O2MD2_OH6432FFT="O2MD2/OH6432FFT"
FOLDER_O2MD2_OH6464FFT="O2MD2/OH6464FFT"

FOLDER_NTRU_HPS2048509="NIST/NTRU/ntru-hps2048509"
FOLDER_NTRU_HPS2048677="NIST/NTRU/ntru-hps2048677"
FOLDER_NTRU_HPS4096821="NIST/NTRU/ntru-hps4096821"
FOLDER_NTRU_HRSS701="NIST/NTRU/ntru-hrss701"

FOLDER_NTRUPRIME_NTRULPR653="NIST/NTRU-Prime/ntrulpr653"
FOLDER_NTRUPRIME_NTRULPR761="NIST/NTRU-Prime/ntrulpr761"
FOLDER_NTRUPRIME_NTRULPR857="NIST/NTRU-Prime/ntrulpr857"
FOLDER_NTRUPRIME_SNTRUP653="NIST/NTRU-Prime/sntrup653"
FOLDER_NTRUPRIME_SNTRUP761="NIST/NTRU-Prime/sntrup761"
FOLDER_NTRUPRIME_SNTRUP857="NIST/NTRU-Prime/sntrup857"

FOLDER_FRODO_640="NIST/Frodo/Reference_Implementation/reference/FrodoKEM-640"
FOLDER_FRODO_976="NIST/Frodo/Reference_Implementation/reference/FrodoKEM-976"
FOLDER_FRODO_1344="NIST/Frodo/Reference_Implementation/reference/FrodoKEM-1344"

FOLDER_CRYSTAL_512="NIST/Crystal/kyber512"
FOLDER_CRYSTAL_768="NIST/Crystal/kyber768"
FOLDER_CRYSTAL_1024="NIST/Crystal/kyber1024"

FOLDER_THREEBEARS_BABY="NIST/ThreeBears/BabyBear"
FOLDER_THREEBEARS_MAMA="NIST/ThreeBears/MamaBear"
FOLDER_THREEBEARS_PAPA="NIST/ThreeBears/PapaBear"

# Statistics files

FILE_O2MD2_OH6416="totalStatistics-O2MD2-OH6416.csv"
FILE_O2MD2_OH6432="totalStatistics-O2MD2-OH6432.csv"
FILE_O2MD2_OH6464="totalStatistics-O2MD2-OH6464.csv"
FILE_O2MD2_OH6416FFT="totalStatistics-O2MD2-OH6416FFT.csv"
FILE_O2MD2_OH6432FFT="totalStatistics-O2MD2-OH6432FFT.csv"
FILE_O2MD2_OH6464FFT="totalStatistics-O2MD2-OH6464FFT.csv"

FILE_NTRU_HPS2048509="totalStatisticsNTRU-hps2048509-Nano.csv"
FILE_NTRU_HPS2048677="totalStatisticsNTRU-hps2048677-Nano.csv"
FILE_NTRU_HPS4096821="totalStatisticsNTRU-hps4096821-Nano.csv"
FILE_NTRU_HRSS701="totalStatisticsNTRU-hrss701-Nano.csv"

FILE_NTRUPRIME_NTRULPR653="totalStatisticsNTRU-Prime-ntrulpr653-Nano.csv"
FILE_NTRUPRIME_NTRULPR761="totalStatisticsNTRU-Prime-ntrulpr761-Nano.csv"
FILE_NTRUPRIME_NTRULPR857="totalStatisticsNTRU-Prime-ntrulpr857-Nano.csv"
FILE_NTRUPRIME_SNTRUP653="totalStatisticsNTRU-Prime-sntrup653-Nano.csv"
FILE_NTRUPRIME_SNTRUP761="totalStatisticsNTRU-Prime-sntrup761-Nano.csv"
FILE_NTRUPRIME_SNTRUP857="totalStatisticsNTRU-Prime-sntrup857-Nano.csv"

FILE_FRODO_640="totalStatisticsFRODOKEM-Nano-0640.csv"
FILE_FRODO_976="totalStatisticsFRODOKEM-Nano-0976.csv"
FILE_FRODO_1344="totalStatisticsFRODOKEM-Nano-1344.csv"

FILE_CRYSTAL_512="totalStatisticsCRYSTAL0512-Nano.csv"
FILE_CRYSTAL_768="totalStatisticsCRYSTAL0768-Nano.csv"
FILE_CRYSTAL_1024="totalStatisticsCRYSTAL1024-Nano.csv"

FILE_THREEBEARS_BABY="totalStatisticsThreeBears-Baby-Nano.csv"
FILE_THREEBEARS_MAMA="totalStatisticsThreeBears-Mama-Nano.csv"
FILE_THREEBEARS_PAPA="totalStatisticsThreeBears-Papa-Nano.csv"

# Statistics folder

FOLDER_STATISTICS="Statistics"

# Statistics merger

FOLDER_STATISTICS_MERGER="StatisticsMerger"
FILE_STATISTICS_MERGER="StatisticsTotal.csv"

# Main

echo "This will make and run the following algorithms:"
echo "	01. O2MD2: OH6416"
echo "	02. O2MD2: OH6432"
echo "	03. O2MD2: OH6464"
echo "	04. O2MD2: OH6416FFT"
echo "	05. O2MD2: OH6432FFT"
echo "	06. O2MD2: OH6464FFT"

echo "	07. NTRU: HPS2048509"
echo "	08. NTRU: HPS2048677"
echo "	09. NTRU: HPS4096821"
echo "	10. NTRU: HRSS701"

echo "	11. NTRU-Prime: NTRULPR653"
echo "	12. NTRU-Prime: NTRULPR761"
echo "	13. NTRU-Prime: NTRULPR857"
echo "	14. NTRU-Prime: SNTRUP653"
echo "	15. NTRU-Prime: SNTRUP761"
echo "	16. NTRU-Prime: SNTRUP857"

echo "	17. FRODO: FRODOKEM-640"
echo "	18. FRODO: FRODOKEM-976"
echo "	19. FRODO: FRODOKEM-1344"

echo "	20. CRYSTAL: KYBER512"
echo "	21. CRYSTAL: KYBER768"
echo "	22. CRYSTAL: KYBER1024"

echo "	23. THREEBEARS: BABYBEAR"
echo "	24. THREEBEARS: MAMABEAR"
echo "	25. THREEBEARS: PAPABEAR"


echo "Status:"

# ===== 1. O2MD2-OH6416 =====

LOCAL_FOLER="$FOLDER_O2MD2_OH6416"
LOCAL_FILE="$FILE_O2MD2_OH6416"
ALGORITHM_NAME="O2MD2-OH6416"
index=1

echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/PQCgenKAT_kem"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && bash spinner.sh ./PQCgenKAT_kem -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

# ===== 2. O2MD2-OH6432 =====

LOCAL_FOLER="$FOLDER_O2MD2_OH6432"
LOCAL_FILE="$FILE_O2MD2_OH6432"
ALGORITHM_NAME="O2MD2-OH6432"
index=2

echo " "
echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/PQCgenKAT_kem"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && bash spinner.sh ./PQCgenKAT_kem -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
	exit 1
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

# ===== 3. O2MD2-OH6464 =====

LOCAL_FOLER="$FOLDER_O2MD2_OH6464"
LOCAL_FILE="$FILE_O2MD2_OH6464"
ALGORITHM_NAME="O2MD2-OH6464"
index=3

echo " "
echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/PQCgenKAT_kem"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && bash spinner.sh ./PQCgenKAT_kem -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
	exit 1
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

# ===== 4. O2MD2-OH6416FFT =====

LOCAL_FOLER="$FOLDER_O2MD2_OH6416FFT"
LOCAL_FILE="$FILE_O2MD2_OH6416FFT"
ALGORITHM_NAME="O2MD2-OH6416FFT"
index=4

echo " "
echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/PQCgenKAT_kem_fft"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && bash spinner.sh ./PQCgenKAT_kem_fft -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
	exit 1
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

# ===== 5. O2MD2-OH6416FFT =====

LOCAL_FOLER="$FOLDER_O2MD2_OH6432FFT"
LOCAL_FILE="$FILE_O2MD2_OH6432FFT"
ALGORITHM_NAME="O2MD2-OH6432FFT"
index=5

echo " "
echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/PQCgenKAT_kem_fft"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && bash spinner.sh ./PQCgenKAT_kem_fft -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
	exit 1
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

# ===== 6. O2MD2-OH6416FFT =====

LOCAL_FOLER="$FOLDER_O2MD2_OH6464FFT"
LOCAL_FILE="$FILE_O2MD2_OH6464FFT"
ALGORITHM_NAME="O2MD2-OH6464FFT"
index=6

echo " "
echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/PQCgenKAT_kem_fft"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && bash spinner.sh ./PQCgenKAT_kem_fft -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
	exit 1
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

# ===== 7. NTRU-HPS2048509 =====

LOCAL_FOLER="$FOLDER_NTRU_HPS2048509"
LOCAL_FILE="$FILE_NTRU_HPS2048509"
ALGORITHM_NAME="NTRU-HPS2048509"
index=7

echo " "
echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/PQCgenKAT_kem"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && bash spinner.sh ./PQCgenKAT_kem -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
	exit 1
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

# ===== 8. NTRU-HPS2048677 =====

LOCAL_FOLER="$FOLDER_NTRU_HPS2048677"
LOCAL_FILE="$FILE_NTRU_HPS2048677"
ALGORITHM_NAME="NTRU-HPS2048677"
index=8

echo " "
echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/PQCgenKAT_kem"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && bash spinner.sh ./PQCgenKAT_kem -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
	exit 1
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

# ===== 9. NTRU-HPS4096821 =====

LOCAL_FOLER="$FOLDER_NTRU_HPS4096821"
LOCAL_FILE="$FILE_NTRU_HPS4096821"
ALGORITHM_NAME="NTRU-HPS4096821"
index=9

echo " "
echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/PQCgenKAT_kem"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && bash spinner.sh ./PQCgenKAT_kem -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
	exit 1
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

# ===== 10. NTRU-HRSS701 =====

LOCAL_FOLER="$FOLDER_NTRU_HRSS701"
LOCAL_FILE="$FILE_NTRU_HRSS701"
ALGORITHM_NAME="NTRU-HRSS701"
index=10

echo " "
echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/PQCgenKAT_kem"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && bash spinner.sh ./PQCgenKAT_kem -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
	exit 1
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

# ===== 11. NTRUPRIME_NTRULPR653 =====

LOCAL_FOLER="$FOLDER_NTRUPRIME_NTRULPR653"
LOCAL_FILE="$FILE_NTRUPRIME_NTRULPR653"
ALGORITHM_NAME="NTRUPRIME_NTRULPR653"
index=11

echo " "
echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/run"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && chmod 764 ./run)
(cd $LOCAL_FOLER && chmod 764 ./build)
(cd $LOCAL_FOLER && chmod 764 ./kat)
{
	(cd $LOCAL_FOLER && ./build)
} &> /dev/null
(cd $LOCAL_FOLER && bash spinner.sh ./run -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
	exit 1
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

# ===== 12. NTRUPRIME_NTRULPR761 =====

LOCAL_FOLER="$FOLDER_NTRUPRIME_NTRULPR761"
LOCAL_FILE="$FILE_NTRUPRIME_NTRULPR761"
ALGORITHM_NAME="NTRUPRIME_NTRULPR761"
index=12

echo " "
echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/run"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && chmod 764 ./run)
(cd $LOCAL_FOLER && chmod 764 ./build)
(cd $LOCAL_FOLER && chmod 764 ./kat)
{
	(cd $LOCAL_FOLER && ./build)
} &> /dev/null
(cd $LOCAL_FOLER && bash spinner.sh ./run -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
	exit 1
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

# ===== 13. NTRUPRIME_NTRULPR857 =====

LOCAL_FOLER="$FOLDER_NTRUPRIME_NTRULPR857"
LOCAL_FILE="$FILE_NTRUPRIME_NTRULPR857"
ALGORITHM_NAME="NTRUPRIME_NTRULPR857"
index=13

echo " "
echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/run"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && chmod 764 ./run)
(cd $LOCAL_FOLER && chmod 764 ./build)
(cd $LOCAL_FOLER && chmod 764 ./kat)
{
	(cd $LOCAL_FOLER && ./build)
} &> /dev/null
(cd $LOCAL_FOLER && bash spinner.sh ./run -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
	exit 1
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

# ===== 14. NTRUPRIME_SNTRUP653 =====

LOCAL_FOLER="$FOLDER_NTRUPRIME_SNTRUP653"
LOCAL_FILE="$FILE_NTRUPRIME_SNTRUP653"
ALGORITHM_NAME="NTRUPRIME_SNTRUP653"
index=14

echo " "
echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/run"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && chmod 764 ./run)
(cd $LOCAL_FOLER && chmod 764 ./build)
(cd $LOCAL_FOLER && chmod 764 ./kat)
{
	(cd $LOCAL_FOLER && ./build)
} &> /dev/null
(cd $LOCAL_FOLER && bash spinner.sh ./run -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
	exit 1
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

# ===== 15. NTRUPRIME_SNTRUP761 =====

LOCAL_FOLER="$FOLDER_NTRUPRIME_SNTRUP761"
LOCAL_FILE="$FILE_NTRUPRIME_SNTRUP761"
ALGORITHM_NAME="NTRUPRIME_SNTRUP761"
index=15

echo " "
echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/run"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && chmod 764 ./run)
(cd $LOCAL_FOLER && chmod 764 ./build)
(cd $LOCAL_FOLER && chmod 764 ./kat)
{
	(cd $LOCAL_FOLER && ./build)
} &> /dev/null
(cd $LOCAL_FOLER && bash spinner.sh ./run -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
	exit 1
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

# ===== 16. NTRUPRIME_SNTRUP857 =====

LOCAL_FOLER="$FOLDER_NTRUPRIME_SNTRUP857"
LOCAL_FILE="$FILE_NTRUPRIME_SNTRUP857"
ALGORITHM_NAME="NTRUPRIME_SNTRUP857"
index=16

echo " "
echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/run"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && chmod 764 ./run)
(cd $LOCAL_FOLER && chmod 764 ./build)
(cd $LOCAL_FOLER && chmod 764 ./kat)
{
	(cd $LOCAL_FOLER && ./build)
} &> /dev/null
(cd $LOCAL_FOLER && bash spinner.sh ./run -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
	exit 1
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

# ===== 17. FRODO_640 =====

LOCAL_FOLER="$FOLDER_FRODO_640"
LOCAL_FILE="$FILE_FRODO_640"
ALGORITHM_NAME="FRODO_640"
index=17

echo " "
echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/frodo/PQCtestKAT_kem"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && bash spinner.sh ./frodo/PQCtestKAT_kem -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
	exit 1
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

# ===== 18. FRODO_976 =====

LOCAL_FOLER="$FOLDER_FRODO_976"
LOCAL_FILE="$FILE_FRODO_976"
ALGORITHM_NAME="FRODO_976"
index=18

echo " "
echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/frodo/PQCtestKAT_kem"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && bash spinner.sh ./frodo/PQCtestKAT_kem -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
	exit 1
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

# ===== 19. FRODO_1344 =====

LOCAL_FOLER="$FOLDER_FRODO_1344"
LOCAL_FILE="$FILE_FRODO_1344"
ALGORITHM_NAME="FRODO_1344"
index=19

echo " "
echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/frodo/PQCtestKAT_kem"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && bash spinner.sh ./frodo/PQCtestKAT_kem -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
	exit 1
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

# ===== 20. CRYSTAL_512 =====

LOCAL_FOLER="$FOLDER_CRYSTAL_512"
LOCAL_FILE="$FILE_CRYSTAL_512"
ALGORITHM_NAME="CRYSTAL_512"
index=20

echo " "
echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/PQCgenKAT_kem"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && bash spinner.sh ./PQCgenKAT_kem -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
	exit 1
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

# ===== 21. CRYSTAL_768 =====

LOCAL_FOLER="$FOLDER_CRYSTAL_768"
LOCAL_FILE="$FILE_CRYSTAL_768"
ALGORITHM_NAME="CRYSTAL_768"
index=21

echo " "
echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/PQCgenKAT_kem"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && bash spinner.sh ./PQCgenKAT_kem -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
	exit 1
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

# ===== 22. CRYSTAL_1024 =====

LOCAL_FOLER="$FOLDER_CRYSTAL_1024"
LOCAL_FILE="$FILE_CRYSTAL_1024"
ALGORITHM_NAME="CRYSTAL_1024"
index=22

echo " "
echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/PQCgenKAT_kem"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && bash spinner.sh ./PQCgenKAT_kem -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
	exit 1
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

# ===== 23. THREEBEARS_BABY =====

LOCAL_FOLER="$FOLDER_THREEBEARS_BABY"
LOCAL_FILE="$FILE_THREEBEARS_BABY"
ALGORITHM_NAME="THREEBEARS_BABY"
index=23

echo " "
echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/build/genkat"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && bash spinner.sh ./build/genkat -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
	exit 1
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

# ===== 24. THREEBEARS_MAMA =====

LOCAL_FOLER="$FOLDER_THREEBEARS_MAMA"
LOCAL_FILE="$FILE_THREEBEARS_MAMA"
ALGORITHM_NAME="THREEBEARS_MAMA"
index=24

echo " "
echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/build/genkat"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && bash spinner.sh ./build/genkat -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
	exit 1
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

# ===== 25. THREEBEARS_MAMA =====

LOCAL_FOLER="$FOLDER_THREEBEARS_PAPA"
LOCAL_FILE="$FILE_THREEBEARS_PAPA"
ALGORITHM_NAME="THREEBEARS_PAPA"
index=25

echo " "
echo "$index. $ALGORITHM_NAME: Make and run. [Please wait...]"

{
	(cd $LOCAL_FOLER && make clean)
	(cd $LOCAL_FOLER && make)
} &> /dev/null

if test -f "$LOCAL_FOLER/build/genkat"; then
	echo "	$index.1 Make: OK"
else
	echo "	$index.1 Make: Unsuccessful"
	exit 1
fi

(cd $LOCAL_FOLER && bash spinner.sh ./build/genkat -noConsoleOutput)

if test -f "$LOCAL_FOLER/$LOCAL_FILE"; then
	echo "	$index.2 Created statistics file: OK"
else
	echo "	$index.2 Created statistics file: Unsuccessful"
	exit 1
fi

if [ ! -d "$FOLDER_STATISTICS" ]; then
	mkdir $FOLDER_STATISTICS
fi

cp $LOCAL_FOLER/$LOCAL_FILE $FOLDER_STATISTICS/$LOCAL_FILE

if test -f "$FOLDER_STATISTICS/$LOCAL_FILE"; then
	echo "	$index.3 Moved statistics file: OK"
else
	echo "	$index.3 Moved statistics file: Unsuccessful"
	exit 1
fi

echo " "
echo "Statistics Merger:"

{
	(cd $FOLDER_STATISTICS_MERGER && make clean)
	(cd $FOLDER_STATISTICS_MERGER && make)
} &> /dev/null

if test -f "$FOLDER_STATISTICS_MERGER/statisticsMerger"; then
	echo "	1. Make: OK"
else
	echo "	1. Make: Unsuccessful"
	exit 1
fi

(cd $FOLDER_STATISTICS_MERGER && bash spinner.sh ./statisticsMerger)

if test -f "$FOLDER_STATISTICS_MERGER/$FILE_STATISTICS_MERGER"; then
	echo "	2. Created statistics file: OK"
else
	echo "	2. Created statistics file: Unsuccessful"
	exit 1
fi

cp $FOLDER_STATISTICS_MERGER/$FILE_STATISTICS_MERGER $FILE_STATISTICS_MERGER

if test -f "$FILE_STATISTICS_MERGER"; then
	echo "	3. Moved statistics file: OK"
	echo " "
	echo "DONE!"
else
	echo "	3. Moved statistics file: Unsuccessful"
	exit 1
fi

