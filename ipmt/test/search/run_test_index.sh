#!/bin/bash
# sh run.sh
files=`cat files.txt`

for file in $files
do
    result="search3-$file.csv"
    `rm $result && touch $result`
    # `echo "$result"`
    for i in `seq 10`;
    do
        # `echo "Iteration: $i"`
        STARTTIME=`gdate +%s.%N`
        count=`../../bin/ipmt -c A ../../../../data/$file`
        echo $count
        ENDTIME=`gdate +%s.%N`
        TIMEDIFF=`echo "$ENDTIME - $STARTTIME" | bc | awk -F"." '{print $1"."substr($2,1,3)}'`
        `echo "$TIMEDIFF" >> $result`
    done
done

