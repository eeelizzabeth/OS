#!/bin/bash
# count_allocs

awk -f count_allocs.awk ../malloc-out.txt > temp.txt
diff -w temp.txt test1.txt > diffs.txt

