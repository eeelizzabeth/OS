#!/usr/bin/awk -f

{
    flag = 1
    for(i=0; i <= NF; i++)
    {
        if(substr($i, 1, 2) == "sz")
        {
            printf substr($i, 4)
            
            flag = 0
        }

    }
    if(flag == 0)
    {
        print ""
    }
    
}
