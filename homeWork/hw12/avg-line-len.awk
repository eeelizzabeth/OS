#!/usr/bin/awk -f
# return average length of line in input file

# YOUR CODE HERE
{
 if($0 != "") {
    cNum += length($0)
    lines++
 }
}
END {
  print int(cNum / lines)
}
