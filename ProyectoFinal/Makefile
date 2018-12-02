COMPILER=gcc
OUTPUT_FILE=main.out
FILES=main.c frontend.c backend.c TAD/airportADT.c TAD/movementsADT.c getnum.c
C_FLAGS=-pedantic -Wall -std=c99 -g -fsanitize=address
all:
	$(COMPILER) -o $(OUTPUT_FILE) $(FILES) $(C_FLAGS)
clean:
	rm -r $(OUTPUT_FILE)  