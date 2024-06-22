Compile command

```
$ make
mkdir -p obj
gcc -g -Wall -c src/library.c -o obj/library.o
gcc -g -Wall -c src/main.c -o obj/main.o
gcc -g -Wall -c src/sll.c -o obj/sll.o
mkdir -p bin
gcc -g -Wall  obj/library.o  obj/main.o  obj/sll.o -o bin/app
```
