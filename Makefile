# Makefile for Building C++ Application

# Detect the operating system and set the appropriate compiler

# If the operating system is Windows, use the Microsoft Visual C++ compiler
ifeq ($(OS),Windows_NT)
	CC=cl
# If the operating system is macOS, use the clang++ compiler
else ifeq ($(shell uname),Darwin)
	CC=clang++
# For other operating systems (assumed to be Linux), use the g++ compiler
else
	CC=g++
endif

# Compiler flags
CPPFlags=-std=c++11 -Wall -pedantic

# Directory where the source code files are located
SRCDIR=src

# Target: 'output'
# This target links the object files together to create the final application.
output: $(SRCDIR)/Application.o $(SRCDIR)/CycleVector.o $(SRCDIR)/Dictionary.o $(SRCDIR)/InteractiveDictionary.o 
	$(CC) $(SRCDIR)/Application.o $(SRCDIR)/CycleVector.o $(SRCDIR)/Dictionary.o $(SRCDIR)/InteractiveDictionary.o -o Application

# The following targets compile each of the source code files into object files.
# These object files are intermediate files created from compiling the source code.
# They contain machine code and can be linked together to create the final application.
$(SRCDIR)/Application.o: $(SRCDIR)/Application.cpp
	$(CC) $(CPPFlags) -c $(SRCDIR)/Application.cpp -o $(SRCDIR)/Application.o

$(SRCDIR)/CycleVector.o: $(SRCDIR)/CycleVector.cpp
	$(CC) $(CPPFlags) -c $(SRCDIR)/CycleVector.cpp -o $(SRCDIR)/CycleVector.o

$(SRCDIR)/Dictionary.o: $(SRCDIR)/Dictionary.cpp
	$(CC) $(CPPFlags) -c $(SRCDIR)/Dictionary.cpp -o $(SRCDIR)/Dictionary.o

$(SRCDIR)/InteractiveDictionary.o: $(SRCDIR)/InteractiveDictionary.cpp
	$(CC) $(CPPFlags) -c $(SRCDIR)/InteractiveDictionary.cpp -o $(SRCDIR)/InteractiveDictionary.o

# Target: 'clean'
# This target deletes all the object files and the final application.
clean:
	rm $(SRCDIR)/*.o Application

# Target: 'cleano'
# This target deletes only the object files, not the final application.
cleano:
	rm $(SRCDIR)/*.o

# Target: 'lldb'
# This target compiles the source files with debugging information included.
# It enables debugging using a debugger like lldb.
lldb:
	$(CC) $(CPPFlags) -g $(SRCDIR)/Application.cpp $(SRCDIR)/CycleVector.cpp $(SRCDIR)/Dictionary.cpp $(SRCDIR)/InteractiveDictionary.cpp -o Application

# Target: 'run'
# This target executes the final application.
run:
	./Application
