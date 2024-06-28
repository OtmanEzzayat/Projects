# ProcessorCluster

## Description
Simulation of the activities of a multiprocessor system, in which each processor operates independently with its own memory and can handle multiple processes concurrently. The main program begins by setting up an initial cluster with no processes. Following this, it will create an empty waiting area and read an initial count of priorities n>0 along with the identifiers for these priorities. After these initial steps, a sequence of commands will be executed, concluding with the 'end' command which will stop the program.

An example of the program's input and output will be provided for clarification.

## Content
program/<br>
├── html/              # Folder that contains the files created with Doxygen to open the html which contains the project's inner workings and the command list<br>
├── Cluster            # Represents a cluster of processors stored in a binary tree format<br>
├── Espera            # Represents an area that stores processes waiting to be executed in the cluster<br>
├── Prioridad           # Represents a priority with the attributes identifier, accepted processes, and rejected processes. Additionally contains a list and a set to store processes<br>
├── Procesador          # Represents a processor with the attributes identifier, maximum memory, and contains various dictionaries to store and manage processes and spaces<br>
└── Proceso            # Represents a process with the attributes identifier, memory, and estimated execution time<br>
