#!/bin/bash
files=`cat files.txt`
errors=`cat errors.txt`
algo=$1
result="result-$algo.csv"
`rm $result && touch $result`
patterns=()

IFS=''
while read pat
do
    patterns+=($pat)
done < patterns.txt

`unset IFS`
IFS=" $(echo t | tr t \\t)
"

for file in $files
do
    for pat in "${patterns[@]}"
    do
        if [ "$algo" = "aho-corasick" -o "$algo" = "shift-or" ]
        then
            echo "./../bin/pmt -a $algo -c $pat ../data/$file"
            STARTTIME=`date +%s.%N`
            count=`./../bin/pmt -a $algo -c $pat ../data/$file`
            ENDTIME=`date +%s.%N`
            TIMEDIFF=`echo "$ENDTIME - $STARTTIME" | bc | awk -F"." '{print $1"."substr($2,1,3)}'`
            `echo "$algo, $file, $pat, $TIMEDIFF, $count" >> $result`
        elif [ "$algo" = "grep" ]
        then
            echo "grep -c "$pat" ../data/$file"
            STARTTIME=`date +%s.%N`
            count=`grep -c "$pat" ../data/$file`
            ENDTIME=`date +%s.%N`
            TIMEDIFF=`echo "$ENDTIME - $STARTTIME" | bc | awk -F"." '{print $1"."substr($2,1,3)}'`
            `echo "grep, $file, $pat, $TIMEDIFF, $count" >> $result`
        else
            for error in $errors
            do
                if [ "$algo" = "wu-manber" -o "$algo" = "sellers" ]
                then
                    echo "./../bin/pmt -a $algo -c -e $error $pat ../data/$file"
                    STARTTIME=`date +%s.%N`
                    count=`./../bin/pmt -a $algo -c -e $error $pat ../data/$file`
                    ENDTIME=`date +%s.%N`
                    TIMEDIFF=`echo "$ENDTIME - $STARTTIME" | bc | awk -F"." '{print $1"."substr($2,1,3)}'`
                    `echo "$algo, $file, $pat, $error, $TIMEDIFF, $count" >> $result`
                elif [ "$algo" = "agrep" ]
                then
                    echo "agrep -c -d '\n' -I1 -D1 -S1 -$error $pat ../data/$file"
                    STARTTIME=`date +%s.%N`
                    count=`agrep -c -d '\n' -I1 -D1 -S1 -$error $pat ../data/$file`
                    ENDTIME=`date +%s.%N`
                    TIMEDIFF=`echo "$ENDTIME - $STARTTIME" | bc | awk -F"." '{print $1"."substr($2,1,3)}'`
                    `echo "agrep, $file, $pat, $error, $TIMEDIFF, $count" >> $result`
                else
                    echo "Algoritmo nao encontrado"
                fi
            done
        fi
    done
done

