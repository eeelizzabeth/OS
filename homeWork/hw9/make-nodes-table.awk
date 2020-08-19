#!/usr/bin/awk -f
# extract node information from an OSM file

# YOUR CODE HERE
BEGIN {
   printf("node_id,lat,long\n")
}

/node /{
    split($0, a, "\"");
  
    print a[2] "," a[4] ","a[6]
      
}

