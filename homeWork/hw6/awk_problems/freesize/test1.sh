#!/bin/bash
# freesize

awk -f freesize.awk ../malloc-out.txt | head -100 | awk '{sum += $1}END{print sum}' > temp.txt
awk -f freesize.awk ../malloc-out.txt | wc -l >> temp.txt
diff -w temp.txt test1.txt > diffs.txt

