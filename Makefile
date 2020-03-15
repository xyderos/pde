CC = g++
LIBS =
CFLAGS = -std=c++11 -fopenmp
JS = Jacobi/seq
JC = Jacobi/conc
MS = Multigrid/seq
MC = Multigrid/conc
EXECUTABLES = executables
RESULT = res
TARGETS = js jc ms mc
BENCHMARKS = benchmark-js benchmark-jc benchmark-ms benchmark-mc
DEFINES = NONE

all: $(TARGETS) $(BENCHMARKS) clean

.PHONY: all

js: $(JS)/js.cpp
	@mkdir -p $(EXECUTABLES)
	$(CC) $(CFLAGS) -o $(EXECUTABLES)/$@ $(JS)/$@.cpp $(LIBS)

jc: $(JC)/jc.cpp
	@mkdir -p $(EXECUTABLES)
	$(CC) $(CFLAGS) -o $(EXECUTABLES)/$@ $(JC)/$@.cpp $(LIBS)

ms: $(MS)/ms.cpp
	@mkdir -p $(EXECUTABLES)
	$(CC) $(CFLAGS) -o $(EXECUTABLES)/$@ $(MS)/$@.cpp $(LIBS)

mc: $(MC)/mc.cpp
	@mkdir -p $(EXECUTABLES)
	$(CC) $(CFLAGS) -o $(EXECUTABLES)/$@ $(MC)/$@.cpp $(LIBS)

benchmark-js:
	
	@mkdir -p $(RESULT)
	
	@rm -f $(RESULT)/$@-result.txt

	@echo "Gridsize 100 with 20 iterations" >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/js 100 20 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/js 100 20 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/js 100 20>> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/js 100 20 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/js 100 20 >> $(RESULT)/$@-result.txt

	@echo "Gridsize 200 with 20 iterations" >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/js 200 20 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/js 200 20 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/js 200 20 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/js 200 20 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/js 200 20 >> $(RESULT)/$@-result.txt

benchmark-jc:
	
	@mkdir -p $(RESULT)
	
	@rm -f $(RESULT)/$@-result.txt

	@echo "Gridsize 100 with 20 iterations and 1 worker" >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 100 20 1 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 100 20 1 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 100 20 1 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 100 20 1 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 100 20 1 >> $(RESULT)/$@-result.txt

	@echo "Gridsize 100 with 20 iterations and 2 workers" >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 100 20 2 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 100 20 2 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 100 20 2 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 100 20 2 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 100 20 2 >> $(RESULT)/$@-result.txt

	@echo "Gridsize 100 with 20 iterations and 3 workers" >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 100 20 3 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 100 20 3 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 100 20 3 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 100 20 3 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 100 20 3 >> $(RESULT)/$@-result.txt

	@echo "Gridsize 100 with 20 iterations and 4 workers" >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 100 20 4 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 100 20 4 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 100 20 4 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 100 20 4 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 100 20 4 >> $(RESULT)/$@-result.txt

	@echo "Gridsize 200 with 20 iterations and 1 worker" >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 200 20 1 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 200 20 1 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 200 20 1 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 200 20 1 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 200 20 1 >> $(RESULT)/$@-result.txt

	@echo "Gridsize 200 with 20 iterations and 2 workers" >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 200 20 2 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 200 20 2 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 200 20 2 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 200 20 2 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 200 20 2 >> $(RESULT)/$@-result.txt

	@echo "Gridsize 200 with 20 iterations and 3 workers" >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 200 20 3 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 200 20 3 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 200 20 3 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 200 20 3 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 200 20 3 >> $(RESULT)/$@-result.txt

	@echo "Gridsize 200 with 20 iterations and 4 workers" >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 200 20 4 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 200 20 4 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 200 20 4 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 200 20 4 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/jc 200 20 4 >> $(RESULT)/$@-result.txt

benchmark-ms:
	
	@mkdir -p $(RESULT)
	
	@rm -f $(RESULT)/$@-result.txt

	@echo "Gridsize 29 with 20 iterations" >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/ms 29 20 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/ms 29 20 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/ms 29 20 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/ms 29 20 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/ms 29 20 >> $(RESULT)/$@-result.txt

	@echo "Gridsize 69 with 20 iterations" >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/ms 69 20 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/ms 69 20 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/ms 69 20 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/ms 69 20 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/ms 69 20 >> $(RESULT)/$@-result.txt

benchmark-mc:
	
	@mkdir -p $(RESULT)
	
	@rm -f $(RESULT)/$@-result.txt

	@echo "Gridsize 29 with 20 iterations and 1 worker" >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 29 20 1 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 29 20 1 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 29 20 1 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 29 20 1 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 29 20 1 >> $(RESULT)/$@-result.txt

	@echo "Gridsize 29 with 20 iterations and 2 workers" >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 29 20 2 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 29 20 2 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 29 20 2 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 29 20 2 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 29 20 2 >> $(RESULT)/$@-result.txt

	@echo "Gridsize 29 with 20 iterations and 3 workers" >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 29 20 3 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 29 20 3 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 29 20 3 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 29 20 3 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 29 20 3 >> $(RESULT)/$@-result.txt

	@echo "Gridsize 29 with 20 iterations and 4 workers" >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 29 20 4 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 29 20 4 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 29 20 4 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 29 20 4 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 29 20 4 >> $(RESULT)/$@-result.txt

	@echo "Gridsize 69 with 20 iterations and 1 worker" >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 69 20 1 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 69 20 1 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 69 20 1 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 69 20 1 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 69 20 1 >> $(RESULT)/$@-result.txt

	@echo "Gridsize 69 with 20 iterations and 2 workers" >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 69 20 2 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 69 20 2 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 69 20 2 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 69 20 2 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 69 20 2 >> $(RESULT)/$@-result.txt

	@echo "Gridsize 69 with 20 iterations and 3 workers" >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 69 20 3 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 69 20 3 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 69 20 3 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 69 20 3 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 69 20 3 >> $(RESULT)/$@-result.txt

	@echo "Gridsize 69 with 20 iterations and 4 workers" >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 69 20 4 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 69 20 4 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 69 20 4 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 69 20 4 >> $(RESULT)/$@-result.txt

	./$(EXECUTABLES)/mc 69 20 4 >> $(RESULT)/$@-result.txt


clean: 
	rm -f *.o *.exe *.out $(TARGETS)
