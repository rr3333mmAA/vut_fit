#------------------------------------------------------ MAKEFILE -----
#   Task: IJC-DU2
#   
#   File: Makefile
# 
#   Author: Abayev Amirkhan
#   Login: xabaye00
#   Faculty: Information Technology, Brno University of Technology
# 
#   Description: Building program 
#   Compiled: gcc 11.2.1
# 
#   Date: 18.4.2022
#----------------------------------------------------------------------

C_FLAGS = -std=c11 -pedantic -Wall -Wextra
CPP_FLAGS = -std=c++17 -pedantic -Wall
BIN = tail wordcount wordcount-dynamic
LIB = libhtab.a libhtab.so

all: tail wordcount wordcount-dynamic

tail: tail.c
	gcc $(C_FLAGS) -o $@ $<
wordcount: wordcount.c io.o libhtab.a
	gcc $(C_FLAGS) -static -o $@ $^
wordcount-dynamic: wordcount.c io.o libhtab.so
	gcc $(C_FLAGS) -L. -lhtab -o $@ wordcount.c io.o
wordcount-: wordcount-.cc
	g++ $(CPP_FLAGS) -O2 -o $@ 	
io.o: io.c io.h 
	gcc $(C_FLAGS) -c -o $@ $<
libhtab.a: htab_hash_function.o htab_init.o htab_free.o htab_clear.o htab_resize.o htab_size.o htab_bucket_count.o htab_lookup_add.o htab_for_each.o
	ar -rcs $@ $^
htab_hash_function.o: htab_hash_function.c htab_private.h
	gcc $(C_FLAGS) -c $<
htab_init.o: htab_init.c htab_private.h
	gcc $(C_FLAGS) -c $<
htab_free.o: htab_free.c htab_private.h
	gcc $(C_FLAGS) -c $<   
htab_clear.o: htab_clear.c htab_private.h
	gcc $(C_FLAGS) -c $<
htab_resize.o: htab_resize.c htab_private.h
	gcc $(C_FLAGS) -c $<
htab_size.o: htab_size.c htab_private.h
	gcc $(C_FLAGS) -c $<
htab_bucket_count.o: htab_bucket_count.c htab_private.h
	gcc $(C_FLAGS) -c $<
htab_lookup_add.o: htab_lookup_add.c htab_private.h
	gcc $(C_FLAGS) -c $<
htab_for_each.o: htab_for_each.c htab_private.h
	gcc $(C_FLAGS) -c $<
libhtab.so: htab_hash_function-dyn.o htab_init-dyn.o htab_free-dyn.o htab_clear-dyn.o htab_resize-dyn.o htab_size-dyn.o htab_bucket_count-dyn.o htab_lookup_add-dyn.o htab_for_each-dyn.o
	gcc $(C_FLAGS) -shared -o $@ $^
htab_hash_function-dyn.o: htab_hash_function.c htab_private.h
	gcc $(C_FLAGS) -c -fPIC $< -o $@
htab_init-dyn.o: htab_init.c htab_private.h
	gcc $(C_FLAGS) -c -fPIC $< -o $@
htab_free-dyn.o: htab_free.c htab_private.h
	gcc $(C_FLAGS) -c -fPIC $< -o $@  
htab_clear-dyn.o: htab_clear.c htab_private.h
	gcc $(C_FLAGS) -c -fPIC $< -o $@
htab_resize-dyn.o: htab_resize.c htab_private.h
	gcc $(C_FLAGS) -c -fPIC $< -o $@
htab_size-dyn.o: htab_size.c htab_private.h
	gcc $(C_FLAGS) -c -fPIC $< -o $@
htab_bucket_count-dyn.o: htab_bucket_count.c htab_private.h
	gcc $(C_FLAGS) -c -fPIC $< -o $@
htab_lookup_add-dyn.o: htab_lookup_add.c htab_private.h
	gcc $(C_FLAGS) -c -fPIC $< -o $@
htab_for_each-dyn.o: htab_for_each.c htab_private.h
	gcc $(C_FLAGS) -c -fPIC $< -o $@
clean:
	rm -f *.o $(BIN) $(LIB)
zip:
	zip xabaye00.zip *.c *.h Makefile
