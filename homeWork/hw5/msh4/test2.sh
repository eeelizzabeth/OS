#!/bin/bash
# in and out redirection

# input
cat > temp-in.txt <<zzz
wc -c < test1.sh > temp.txt
exit
zzz

# correct output
cat > gold-out.txt << zzz
56
zzz

# actual output
./msh < temp-in.txt > temp2.txt
mv temp.txt temp-out.txt

diff -w temp-out.txt gold-out.txt > diffs.txt
