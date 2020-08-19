
# the include file in cache_sim.c must be set to select cache implementation

rand:
	sed 's/\#include.*cache\.h/\#include \"random_cache\.h/' cache_sim.c > temp.c
	gcc -o cache_sim_rand temp.c random_cache.c
	./cache_sim_rand

tarball:
	tar cvf cache.tar *.c *.h Makefile

clean:
	rm -f cache_sim_rand temp.c cache.tar *~ 

