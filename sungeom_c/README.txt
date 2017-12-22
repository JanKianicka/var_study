#  
#  Program to calculate solar geometry, particularly sunrise in global
#  scale for whole globe. The target is also to experiment with
#  multithread calculations, therefore we have scale factor as option.

#  1. Building the program
   gcc -c sungeom.c
   gcc -lm -lpthread sunrise_globe.c -o sunrise_globe sungeom.o

#  2. Running the program
   ./sunrise_globe

