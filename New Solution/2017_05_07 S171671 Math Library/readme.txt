~~~~~~~~~~~~~~~~~~~~~~~~~~~~
S171671 MATH LIBRARY PROJECT
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Requirements
 * Installation
 * Configuration
 * Troubleshooting

INTRODUCTION
------------

Provided is a folder with the solution that the Math's Library was developed in, along with the unit test provided by AIE.
The Math's Library has the capability of exporting simultaneously as a .lib and a .dll, and the unit test has the functionality to run each
type of library based on its selected config. All classes used in the Math's Library are templated and require instances of the class to be
declared with a parameter list so the template can build the functionality from its blue-prints. E.g:

'Vector2<float> v2 = v2_b;'

Will create an operator from its blue-prints called:

'Vector2<float> operator = (float a_rhs);' 

Implementation of Math's Library is still WIP such as the functions for getting euler angles from a Transformation Matrix, but it has the functionality required to 
pass the given unit test.


 * For a timeline on development, visit the github page for this repository:
	https://github.com/DarthDementous/2017_03_27_SebStaticMathLib

REQUIREMENTS
------------
 * Visual Studo 2015 (at least Community Edition)

 * In order to run the DLL version of Unit Test the following needs to be included with the .exe:
	- 2017_05_06_SebMathLibrary_Fixed.dll

INSTALLATION
------------
 
 * Extract the .zip into a desired location and then double-click on the .sln file in the Solution folder or the .exes in the Release folder.


CONFIGURATION
-------------
 
 * Due to bugs with creating custom configurations for projects, the default 'Release' and 'Debug' have been converted to represent the following:
	- 2017_05_06_SebMathLibrary_Fixed DEBUG = Build .lib file.
	- 2017_05_06_SebMathLibrary_Fixed RELEASE = Build .dll file (also creates import .lib that must be loaded into the Linker Input in order to run in Visual Studio).
	- UnitTest_Fixed DEBUG = Run unit test using header files and Math Library .lib
	- UnitTest_Fixed RELEASE = Run unit test using header files and Math Library .dll

TROUBLESHOOTING
---------------

 * Due to limitations on filepath characters, the .zip may have to be extracted on to the C:\ drive in order to run properly.
