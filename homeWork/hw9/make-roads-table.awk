#!/usr/bin/awk -f
# extract road information from an OSM file

BEGIN {
   printf("road,way_id,seq_num,node_id\n")
   count = 1
}
{
  if($1 == "<way")
  {
     split($2,a,"\"")
     #print a[2]
     id =  a[2]
  }
  #if <nd
  if($1 == "<nd")
  {
    split($0,b,"\"");
    #print b[2]
    arr[count] = b[2]
    count++
  }
  if($2 == "k=\"name\"")
  {
    split($0,c, "\"")
   # print c[4]
    name = c[4]
  }
  if($1 == "</way>")
  {
    #print $1
    for(i=1; i < count;i++)
    {
	if(name == "")
        {
	  name = "unnamed"
	}
	print name","id","i","arr[i]
    }
    count = 1
    name = ""
  }

}

