# Minishell
This project is about creating a simple shell. Yes, My own little bash. I will learn a lot about processes and file descriptors.

# LAST CHANGES

i created a system file of our project which 
incld contain our header file
src	  contain our source files
utils contain our utils project like libft 

after that i created a new version of our makefile 
that compile our project with the new norms 


# WHAT SHOULD U DO

1. add ur libraries in incld/mini.h
2. add ur structs in incld/mini.h\
3. u are free to use main.c with any thing u waant
4. when i compile this project now i found some errors in ur builtin.c file but i know that u fix them in ur version
5. nothing to be done now clone this project and merge it or just replace this builtin.c whith the new version and every thing will be OK
6. good luck

# TO DO IN PARCING :

- [x] finishel the tokenizing
- [x] handling syntax error related to pipes and redirections and quotes
- [x] parce the linked list
- [x] create a new list to the executer
- [ ] handling edge cases
- [ ] parcing finished

# DONE

 - [x] space problems i scape all spaces but in some cases the spaces should be printed liked\
	- [x] "     heello" -> $     hello\
	- [x] echo "hello"     "world"  -> $hello world\
 - [x] spaces are counted always after single or double quote but i shoudl condsiderd them when they are between two words\
 - [x] the last space after double or single quote is counted\

# TO FIX :

2. - [] an error accure when a word is begin with & but the problem is that i take a word as echo not "&echo"\


# LAST UPDATE :

1. i created the double quotes and if there is redirection i creat a struct that contain information about the redirections
2. i opned the files for input , output , appand with


# AFTER TESTING :

1. echo -n 		
2. echo    		
3. echo -n-n 	
4. echo "-n     mdr"
5. echo - n
6. echo -n -n
7. /bin/echo " \  "


# TO BE DONE TODAY :
- [X] fix the bugs : 
	1. [X] echo "$$HOME"    ---->     $$HOME
	 ex : MY1. echo "$$HOME"  ---->     $HOME 
- if argc != 1 it shoudl out
- segflt when exiting from herdoc with ctrl c
- leaks in execution when entring words like koko or mama alone




/// i changed the check_existant value..