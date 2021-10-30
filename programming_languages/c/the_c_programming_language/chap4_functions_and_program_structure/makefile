objects = 2_grep_multi_file.o 2_grep_multi_getline.o 2_grep_multi_strindex.o
cc = gcc

main: $(objects)
	cc -o main $(objects)

2_grep_multi_file.o : 2_grep_multi_file.c
	cc -c 2_grep_multi_file.c
2_grep_multi_getline.o : 2_grep_multi_getline.h
2_grep_multi_strindex.o : 2_grep_multi_strindex.h

clean :
	rm -f main *.o
