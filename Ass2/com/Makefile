.phony all:
all: unique_lines string_list_tester

unique_lines: unique_lines.c string_list.c
	gcc -Wall -std=c99 -o unique_lines unique_lines.c string_list.c

string_list_tester: string_list_tester.c string_list.c
	 gcc -Wall -std=c99 -o string_list_tester string_list_tester.c string_list.c

.PHONY clean:
clean:
	-rm -rf *.o *.exe
