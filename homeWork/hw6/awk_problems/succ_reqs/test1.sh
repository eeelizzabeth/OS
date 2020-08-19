#!/bin/bash
# succ_reqs

awk -f succ_reqs.awk ../malloc-out.txt | head -10 | tail -1 > temp.txt
diff -w temp.txt test1.txt > diffs.txt
