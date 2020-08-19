#!/usr/bin/awk -f

/^ptr/ {
    i = substr($3, 7)
    b = 0

    if($5 == "-1")
    {
        b = 0
    }
    else {
        b = 1
    }      
    print substr(i, 0, length(i) - 1) " " b
    
}
