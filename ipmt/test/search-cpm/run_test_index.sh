#!/bin/bash
# sh run.sh
files=`cat files.txt`

for file in $files
do
    result="index-compress-$file.csv"
    `rm $result && touch $result`
    # `echo "$result"`
    for i in `seq 5`;
    do
        # `echo "Iteration: $i"`
        STARTTIME=`date +%s.%N`
        count=`../../bin/ipmt -i ../../../../data/$file`
        echo $count
        ENDTIME=`date +%s.%N`
        TIMEDIFF=`echo "$ENDTIME - $STARTTIME" | bc | awk -F"." '{print $1"."substr($2,1,3)}'`
        `echo "$TIMEDIFF" >> $result`
    done
done

