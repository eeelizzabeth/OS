#!/usr/bin/awk -f
/^ptr/ {
    if($5 == "-1"){
        fail++
    }
    else{
        pass++
    }

}
END{
 print "num successes: " pass "; num failures: " fail

}
