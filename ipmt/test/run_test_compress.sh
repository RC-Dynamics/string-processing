#!/bin/bash
# sh run.sh
files=`cat files.txt`

for file in $files
do
    result="compress-$file-4095-255.csv"
    `rm $result && touch $result`
    # `echo "$result"`
    for i in `seq 10`;
    do
        # `echo "Iteration: $i"`
        STARTTIME=`date +%s.%N`
        count=`./../bin/ipmt -z ../data/$file`
        ENDTIME=`date +%s.%N`
        TIMEDIFF=`echo "$ENDTIME - $STARTTIME" | bc | awk -F"." '{print $1"."substr($2,1,3)}'`
        `echo "$TIMEDIFF" >> $result`
    done
done

