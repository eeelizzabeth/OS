#!/usr/bin/awk -f
{
if($1 == "--" &&  $2 == ID)
{
   getline; print
}


}
