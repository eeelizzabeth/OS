#!/usr/bin/awk -f

/^Free / { printf("%s\n", $5) }
