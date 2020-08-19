#!/bin/bash
# num_bytes

awk -f num_bytes.awk ../malloc-out.txt | head -100 | awk '{sum += $1}END{print sum}' > temp.txt
diff -w temp.txt test1.txt > diffs.txt

