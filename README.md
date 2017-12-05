# Battleship
Simple Battleship game using C++ and Qt in the Linux Ubuntu Environment

TODO:

Make AI strategically pick next spot (right now it is random)

Add Start Window and Game Over Window



To compile and run you need Qt installed. It was tested using Qt 5.5.1. Steps to compile and run:

Download the code from Github and navigate to the folder containing the code and execute the following commands:

$ qmake -project "QT+=widgets gui"

$ qmake Battleship.pro

$ make

$ ./Battleship
