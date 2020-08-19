#!/usr/bin/awk -f
BEGIN {
  printf("Identifier,\"Full name\",") 	
} 
{

  if(NF == 1)
  {
    if($1 == "{")
    {
      counter++
    }
    else 
    {
      counter--
    }
  }
  if(NF == 2)
  {
    arr[counter] = $1
  }
  else if(NF > 2)
  {
    arr[counter] = $1

    for(i=1; i <= counter; i++)
    {
      
      if(i == counter)
      {
        printf("%s,", substr(arr[i], 2, 1))
      }
      else 
      {
        printf("%s_", substr(arr[i], 2, 1))
      }
    }
  }
}
END {
  printf("comments\n")
}
