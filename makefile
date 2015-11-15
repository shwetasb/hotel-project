try:hotel.o
	cc hotel.o -o project
	clear
hotel.o: hotel.c
	cc hotel.c -c	
