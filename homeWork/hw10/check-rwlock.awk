#!/usr/bin/awk -f
BEGIN {

 rTest = "PASS"
 wTest = "PASS"
 
 maxR = 0
 maxW = 0

}
{
 if($1 == "sr")
 {
   readC++
   if(readC > maxR) 
   {
     maxR = readC
   }
   if(writeC > 0)
   {
     rTest = "FAIL"
   }
 }
 else if($1 == "dr")
 {
   readC--
 }
 else if($1 == "sw")
 {
   writeC++
   if(readC > 0)
   {
     rTest = "FAIL"
   }
   if(writeC > maxW)
   {
     maxW = writeC
   }
 }
 else if($1 == "dw")
 {
   writeC--
 }
}
END {
 if(maxW > 1)
 {
   wTest = "FAIL"
 }
 print("maxr = " maxR ", maxw = " maxW)
 print("reader/writer test: " rTest)
 print("writer/writes test: " wTest)
}
