#!/usr/bin/awk -f

/^ptr/ {
    i = substr($3, 7)
    print substr(i, 0, length(i)-1)

}
