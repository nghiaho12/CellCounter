INTRODUCTION
===============================================================================
CellCounter is a VERY domain specific cell counting tool aimed at assisting the 
user count cells faster. For an example of the type of images the software expects, 
please see my website (http://nghiaho.com) for some sample images. This program
was written primarily to help out a friend with their lab work. I don't plan to 
extend this program beyond that. I'm releasing this software on the off chance 
that someone else might find it useful.



USAGE
===============================================================================
The general work flow is

    1. Load an image
    2. Select a well
    3. Adjust the binary threshold
    4. Specify the range of colony sizes
    5. Click 'Count colonies'
    6. Click 'Save results'
    7. Repeat 1 until complete
    8. Copy text results into Excel for further processing

CellCounter makes a lot of use of the mouse and keyboard. These are

Mouse actions:
    Left button down + move - pan the image
    Left double click - centre the image
    Scroll wheel - zoom in/out
    Left click - select well
    Ctrl + left click - add colony
    Right click - remove colony

Keyboard actions:
    s - switch between binary and colour image

These instructions are also found in Help -> How to use



PRE-COMPILED BINARIES FOR WINDOWS
===============================================================================
A pre-compiled Windows version can be found in:

    http://nghiaho.com/?page_id=1011



HOW TO COMPILE
===============================================================================
CellCounter is cross platform and has been tested on Ubuntu 15.04 and Windows 7. 
The following external libraries are required for it to compile:

- wxWidgets 3.1 (or above)
- OpenCV 3.x (or above)

The Linux project can be compiled by opening the CellCounter.cbp project in 
CodeBlocks. The Windows Visual Studio 2010 project can be found in 
Win32/CellCounter. Please change the paths in the project settings to point to
the correct location of the external libraries.



LICENSE
===============================================================================
Please see the LICENSE file. In summary, it's a BSD license, which means you can
pretty do much whatever you want with the code. For educational or commercial.



FOUND A BUG?
===============================================================================
Email me at nghiaho12@yahoo.com
