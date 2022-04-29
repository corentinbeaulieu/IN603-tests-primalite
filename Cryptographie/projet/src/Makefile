
.PHONY: run
run: primalite
	perf stat ./primalite -f test.txt

primalite: fonc.o main.o 
	gcc -Wall -o $@ $^ -lgmp -fopenmp

main.o: main.c fonc.h
	gcc -c -Wall main.c -lgmp -fopenmp

fonc.o: fonc.c fonc.h
	gcc -c -Wall fonc.c -lgmp -fopenmp


.PHONY: clean
clean: 
	rm -f fonc.o main.o
	rm -f primalite

.PHONY: memcheck
memcheck: primalite 
	valgrind --tool=memcheck --track-origins=yes --leak-check=full --show-leak-kinds=all ./$^ -f test.txt

.PHONY: debug
debug: primalite
	gdb $^


DIRNAME = BEAULIEU_CORENTIN_21906966
FILES = fonc.c fonc.h main.c Makefile

.PHONY: zip
zip:
	rm -rf $(DIRNAME) $(DIRNAME).zip
	mkdir $(DIRNAME)
	mkdir $(DIRNAME)/src
	cp ../README.md $(DIRNAME)
	cp $(FILES) $(DIRNAME)/src/
	zip $(DIRNAME).zip $(DIRNAME)
	rm -rf $(DIRNAME)


