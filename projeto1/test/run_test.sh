#!/bin/sh
patterns=`cat patterns.txt`
files=`cat files.txt`
errors=`cat errors.txt`
result_exata='result-exata.csv'
result_aprox='result-aprox.csv'
`rm $result_exata && rm $result_aprox && touch $result_exata && touch $result_aprox `

for file in $files
do
    for pat in $patterns
    do
        for algo in "aho-corasick" "shift-or"
        do
            STARTTIME=`date +%s.%N`
            count=`./../bin/pmt -a $algo -c $pat ../data/$file`
            ENDTIME=`date +%s.%N`
            TIMEDIFF=`echo "$ENDTIME - $STARTTIME" | bc | awk -F"." '{print $1"."substr($2,1,3)}'`
            `echo "$algo, $file, $pat, $TIMEDIFF, $count" >> $result_exata`
        done
        STARTTIME=`date +%s.%N`
        count=`grep -c $pat ../data/$file`
        ENDTIME=`date +%s.%N`
        TIMEDIFF=`echo "$ENDTIME - $STARTTIME" | bc | awk -F"." '{print $1"."substr($2,1,3)}'`
        `echo "grep, $file, $pat, $TIMEDIFF, $count" >> $result_exata`
    done
done

for file in $files
do
    for pat in $patterns
    do
        for error in $errors
        do
            for algo in "wu-manber" "sellers"
            do
                STARTTIME=`date +%s.%N`
                count=`./../bin/pmt -a $algo -c -e $error $pat ../data/$file`
                ENDTIME=`date +%s.%N`
                TIMEDIFF=`echo "$ENDTIME - $STARTTIME" | bc | awk -F"." '{print $1"."substr($2,1,3)}'`
                `echo "$algo, $file, $pat, $error, $TIMEDIFF, $count" >> $result_aprox`
            done
            STARTTIME=`date +%s.%N`
            count=`agrep -c -d '\n' -I1 -D1 -S1 -$error $pat ../data/$file`
            ENDTIME=`date +%s.%N`
            TIMEDIFF=`echo "$ENDTIME - $STARTTIME" | bc | awk -F"." '{print $1"."substr($2,1,3)}'`
            `echo "agrep, $file, $pat, $error, $TIMEDIFF, $count" >> $result_aprox`
        done
    done
done