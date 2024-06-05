#!/bin/bash
blue=$(tput setaf 4)
gray=$(tput setaf 7)
green=$(tput setaf 2)
teal=$(tput setaf 6)
normal=$(tput sgr0)


for representation in "representations/"*; do
    for routine in "routines/"*; do
        for benchmark in "benchmark/generate."*; do
            instance_size=${benchmark##*.}
            
            tmpLogFile=$(mktemp)
            cat > $tmpLogFile <<EOF
$normal============================[INSTANCE SIZE $instance_size]============================$green
Running the $routine benchmark for $representation. 
$normal============================[Input]============================$gray
$(cat $representation $benchmark $routine <(echo $instance_size) <(echo exit))
$normal============================[Program Output]===================$teal 

EOF
            printf "$(more $tmpLogFile)"
            
            tmpFile=$(mktemp)
            run_project="./graph --generate"
            start_time=$(date +%s%N)
            { $run_project < <(cat $representation $benchmark $routine <(echo $instance_size) <(echo exit)) >$tmpFile; } 2>&1
            end_time=$(date +%s%N)
            duration=$(( (end_time - start_time) / 1000000 )) # Obliczenie czasu trwania w milisekundach
            
            
            echo "$(basename $representation),$instance_size,$duration" >> $(basename $routine)_benchmark_time.csv
            
            cat > $tmpLogFile <<EOF

$(cat $tmpFile)
$normal============================[Execution Time]=====================$green
Execution time = $duration milliseconds
Saved to $(basename $routine)_benchmark_time.csv

$normal
EOF
            printf "$(more $tmpLogFile)"
        done
    done
done
