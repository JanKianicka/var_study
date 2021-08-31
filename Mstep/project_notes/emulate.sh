#!/bin/sh

# Read input arguments
if [ -z ${1} ]; then
    echo "Missing variable as first cmd line argument";
    echo "Usage: ./emulate.sh <VAR> <System_ID> <path_to_input_data> <path_to_output_data>";
    exit 1;
fi

if [ -z ${2} ]; then
    echo "Missing system id as second cmd line argument";
    echo "Usage: ./emulate.sh <VAR> <System_ID> <path_to_input_data> <path_to_output_data>";
    exit 1;
fi


if [ -z ${3} ]; then
    echo "Missing path_to_input_data as third cmd line argument";
    echo "Usage: ./emulate.sh <VAR> <System_ID> <path_to_input_data> <path_to_output_data>";
    exit 1;
fi

if [ -z ${4} ]; then
    echo "Missing path_to_output_data as fourth cmd line argument";
    echo "Usage: ./emulate.sh <VAR> <System_ID> <path_to_input_data> <path_to_output_data>";
    exit 1;
fi

echo "Launching time shifting of LIDAR HPL data."
Variable="${1}"
SystemID="${2}"
Path_to_input_data="${3}"
Path_to_output_data="${4}"
Matching_pattern="$Variable\_$SystemID\_*"

# Time shifting between file name time and actual start time - there is some simulated delay
TIME_SHIFT=5


echo "Variable: $Variable"
echo "SystemID: $SystemID"
echo "Path_to_input_data: $Path_to_input_data"
echo "Path_to_output_data: $Path_to_output_data"

# Test of existence of directories
if [ ! -e $Path_to_input_data -a ! -d $Path_to_input_data ]; then
   echo "Directory: $Path_to_input_data  does not exist.";
   exit 1;
fi

if [ ! -e $Path_to_output_data -a ! -d $Path_to_output_data ]; then
   echo "Directory: $Path_to_output_data  does not exist.";
   exit 1;
fi

declare -i current_number=0

# Counter which will choose just one file always.
# Name of counter according the data variable
pathToCounter=`pwd`/$Variable\_Count.txt
input=$pathToCounter

# If the counter file does not exist initiate with 0
if [ ! -e $pathToCounter ]; then
    echo -e "0" > $pathToCounter
fi

while IFS= read -r line
do
 current_number="$line"
done < "$input"

current_date=$(date '+%Y%m%d');
current_time=$(date '+%H%M%S');

end_date=$(date -d "+$TIME_SHIFT sec" +'%Y%m%d');
end_time=$(date -d "+$TIME_SHIFT sec" +'%H:%M:%S');
echo "Current date: $current_date"
echo "Current time: $current_time"
echo "Shifted start date: $end_date"
echo "Shifted start time: $end_time"

arrFiles=()

for entry in $Path_to_input_data/$Matching_pattern
do
  arrFiles+=("$entry");
done

echo "Coping input file num: $current_number"
nameOfFile="${arrFiles[$current_number]}"

echo "Input file: $nameOfFile";
outFile=$Path_to_output_data/$Variable\_$SystemID\_$current_date\_$current_time\.hpl
echo "Output file: $outFile"
echo "Copy:"
cp $nameOfFile $outFile -v

# Patching of file name
baseNameSource=`basename $nameOfFile`
baseNameDest=`basename $outFile`
echo "Replacing file name in the header."
sed -i -e "s/${baseNameSource}/${baseNameDest}/g" $outFile

echo "Replacing start time."
sed -i -e "s/^Start time:.*$/Start time:     $end_date $end_time/" $outFile

# Then we deploy all input variables and test it - may be tomorrow - tomorrow at 13 home

# Using input file names to evaluate the counter
len=${#arrFiles[@]}
len=`expr $len - 1`
if [ $current_number -lt $len ]
then
    current_number=$((current_number))+1
    echo $current_number > $pathToCounter
else
    echo 0 > $pathToCounter
    echo "Reset counter $pathToCounter"
fi

echo "New input time shift data generated."
