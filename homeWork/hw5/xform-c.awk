#!/usr/bin/awk -f
# YOUR CODE HERE
BEGIN {
   FS = ","
}

{
   
   #printf $4
   if($4 == "prob_desc")
   {
	print $1","$2","$3"," "comments"
   }
   if($2 == "1" )
   {
	if($3 == "0")
	{
	  $3 = "10"
	}
	else
	{
	  $3 = "0"
	}
	$2 = "3_a"
   }
   else if($2 == "2")
   {
	$2 = "3_b"
	if($3 == "0")
	{
	   $3 = "5"
	}
	else{
	   $3 = "0"
	}
   }
   else if($2 == "3")
   {
	$2 = "3_c"
	if($3 == "0")
	{
	   $3 = "5"
	}
	else {
	   $3 = "0"
	}
   } 
   else if($2 == "4")
   {
	$2 = "3_d"
	if($3 == "0")
	{
	  $3 = "5"
	}
	else {
	  $3 = "0"
	}
   }
   else
   {
	$2 = "3_e"
	if($3 == "0")
	{
	  $3 = "5"
	}
	else {
	  $3 = "0"
	}
   }
   
   if($1 != "Identifier")
   {
	print "Participant " $1","$2","$3","$4
   }
   #if($2 == "1")
   #{
	#printf "3_a"
   #}
   #printf $4

   
   #if($2 == "1")
   #{
     #printf "3_a"  
   #}
   #if($2 == "2")
   #{
     #printf "3_b"
   #}
   #if($2 == "3")
   #{
     #printf "3_c"
   #}
   #if($2 == "4")
   #{
     #printf "3_d"
   #}
   #if($2 == "5")
   #{
     #printf "3_e"
   #}


   #if($3 == "1")
   #{
     #printf "0"
   #}
   #if($3 == "0" && $2 == "1")
   #{
     #printf $2 "10"
   #}
   #if($3 == "0" && $2 == "2" || $2 == "3" || $2 == "4" || $2 == "5")
   #{
     #printf $2 "5"
   #}
   #print("")




}
