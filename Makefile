build: task1 pacman

task1: task1.c 
	gcc -Wall -std=c99 task1.c -o task1

pacman: pacman.c
	gcc -Wall -std=c99 pacman.c -o pacman

clean:
	rm -f task1 pacman
	

	
