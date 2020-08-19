#!/bin/bash
# list-sizes

awk -f list_sizes.awk ../malloc-out.txt | head -20 | tail -1 > temp.txt
diff -w temp.txt test1.txt > diffs.txt
