#!/bin/sh

cars=("Toyota" "BMW" "Kia")
colors=("red" "blue" "green")
transmission=("manual" "manual" "automatic")

# Reading the potential pipeline configuration
# map with scripts
declare -A pipeline_scripts
declare -A pipeline_configs

while read index name conf token; do
    if [ $index != "#" ]
    then
	echo "$index : $name, $conf, $token"
	pipeline_scripts[$index]=$name
	pipeline_configs[$index]=$conf
    fi
done < "input.txt"

echo "All keys of hash-map with pipeline_scripts: ${!pipeline_scripts[@]}"
echo "All values of hash-map with pipeline_scripts: ${pipeline_scripts[@]}"
echo "All values of hash-map with pipeline_confs: ${pipeline_configs[@]}"

for index2 in ${!pipeline_scripts[@]}
do
    #echo $index2
    echo "${pipeline_scripts[$index2]} -c ${pipeline_configs[$index2]}"
done
