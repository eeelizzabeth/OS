#!/bin/bash
./get-submission.awk -v ID=$1 vsfs.txt | md5sum > temp1.txt
echo $2 > temp2.txt
diff -w temp1.txt temp2.txt > diffs.txt
