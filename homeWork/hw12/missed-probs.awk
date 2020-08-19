#!/usr/bin/awk -f
# for *every* problem ID in input, give number of incorrect (non-0) answers

# YOUR CODE HERE
BEGIN {
  FS = ","
  print "prob_id,num_missed"
  count[9] = 0
}
/^[0-9]/{ 
  if($3 != "0")
  {
   count[$2]++; 
  } 
} 
END {
 for(i=1; i < length(count); i++)
 {
   if(count[i] == 0)
   {
     count[i] = 0
   }
   print i "," count[i]
 }
}

