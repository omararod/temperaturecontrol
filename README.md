Summary
============
This project implements a system that controls the temperature of a room. To do so, it connects to a temperature sensor together with heating and cooling devices that implement the provided interfaces.

Build
===========
This project uses CMake
1. Generate the makefiles or project files for your target with 
    cmake <path_to_source_code>
2. Build with the default parameters. For instance on linux:
    make

Generate API documentation
==========================
API documentation can be generated with doxygen:
    doxygen <path_to_repo>/Doxyfile

The output is stored in a folder called "docs". Open the index.html file to view.

Build output
============
The build process generates:
1. A library for the temperature control system (libtemperaturecontrol)
2. An executable to the unit tests (tests)
3. An example application to demonstrate a typical implementation of the system (app)

Run tests
==========
Run the generated executable. For instance, on Linux:
    ./tests

Run example application
========================
Run the generated executable. For instance, on Linux:
    ./app