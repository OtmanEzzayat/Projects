OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Espera.o Cluster.o Prioridad.o Procesador.o Proceso.o
	g++ -o program.exe program.o Espera.o Cluster.o Prioridad.o Procesador.o Proceso.o

program.o: program.cc Espera.hh Cluster.hh Prioridad.hh Procesador.hh BinTree.hh Proceso.hh
	g++ -c program.cc $(OPCIONS)

Proceso.o: Proceso.cc Proceso.hh
	g++ -c Proceso.cc $(OPCIONS)

Procesador.o: Procesador.cc Procesador.hh Proceso.hh
	g++ -c Procesador.cc $(OPCIONS)

Cluster.o: Cluster.cc Cluster.hh Procesador.hh BinTree.hh Proceso.hh
	g++ -c Cluster.cc $(OPCIONS)

Prioridad.o: Prioridad.cc Prioridad.hh Proceso.hh
	g++ -c Prioridad.cc $(OPCIONS)

Espera.o: Espera.cc Espera.hh Cluster.hh Prioridad.hh Procesador.hh BinTree.hh Proceso.hh
	g++ -c Espera.cc $(OPCIONS)

clean:
	rm *.o
	rm *.exe
