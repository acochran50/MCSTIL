# MCSTIL: Monte Carlo Simulation for Tissue Incident Light #

*Written by Alex Cochran, The Ohio State University Department of Materials Science & Engineering Undergraduate Program, 2016 - 2017*

## PROJECT ##
MCSTIL is a project written to assist with experimental design concerning optically-similar polymeric biological tissue models that can be used to test the efficacy of in-vivo biosensors. This software is designed to account for the layered nature of biological tissues, allowing layering of multiple tissue types defined by their known optical properties and thicknesses. The stochastic Monte Carlo model then makes use of random number generation to produce realistic results of photon propagation through the tissue layers. These results can be analyzed to influence the design and usage of particular optically sensitive biosensors without the need for extensive in vivo testing.

MCSTIL references the work of Lihong Wang, Ph. D., and Steven L. Jacques, Ph. D., *Monte Carlo Modeling of Light Transport in Multi-layered Tissues in Standard C*, University of Texas, M. D. Anderson Cancer Center, 1992.

This software is part of Alex Cochran's senior design project within the Department of Materials Science & Engineering at The Ohio State University, advised by John Lannutti, PhD. Other project members include Mallory Hutton, Maria Stang, and Elana Spiegler.

## DIRECTORY STRUCTURE AND FILE DESCRIPTIONS ##
- /include
	- MCSTIL.hpp :: project header file
- /src
	- MCSTIL.cpp :: main source file
	- MCSTIL_ERROR.cpp :: user defined error functions
	- MCSTIL_ERROR.hpp :: supporting header file for error functions
	- MCSTIL_TRIG.cpp :: user defined trigonometric functions
	- MCSTILRandom.cpp :: singleton class methods for random number generation
	- MCSTILRandom.hpp :: singleton class definition for random number generation
	- Photon.cpp :: class methods for photon properties/behaviors
	- Photon.hpp :: class definition for photons
	- TissueLayer.cpp :: class methods for tissue properties/behaviors
	- TissueLayer.hpp :: class definition for tissues
- /input
	- params.in :: simulation input file
	- tissue.in :: tissue properties input file
- /dev
	- algorithm.md :: describes the algorithm developed for photon propagation
	- dev_notes.md :: general notes taken during development
	- math.md :: describes equations used for development
	- todo.txt :: space for notes on things that should be done in the future

## LATEST VERSION ##
The latest version and version control details can be found on the project's GitHub page at https://github.com/acochran50/MCSTIL

## DOCUMENTATION ##
The documentation available as of now is included in the doc/manual directory. The most recent documentation is available on the project's GitHub page.

## INSTALLATION ##
Use the makefile to compile any changes made to the project source code. This software is compiled with C++ compiler g++ 5.4.0 and Python version 2.7.12. All necessary libraries are included in lib/. The input parameters can be edited using INPUT.txt in the project directory. The software can be executed using the bash executable MCSTIL also found in the project directory. Program output is written to OUTPUT.txt.

## LICENSING ##
__Once available__, licensing information can be found in the LICENSE file.
