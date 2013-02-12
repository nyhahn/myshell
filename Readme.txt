****************************************
	How to run the program
****************************************
run:
make && ./myshell

****************************************
	Language Specification
****************************************
The Shell written strictly follows the 
bash, so command like: ls > a.txt > b.txt
will result an empty file a.txt and with 
information written to b.txt

The /usr/bin/:/bin/ path is preloaded into
the path for convenience.


****************************************
	Some test cases
****************************************
HUs-MacBook-Air:submit oliverbs163$ make && ./myshell
gcc -c support.c
gcc -c shell.c
gcc -o myshell support.o shell.o
                Happy Chinese Lunar New Year!                                            
                    /^\/^\       Version 1.1     
                  _|__|  O|      Author Keqiu Hu
         \/     /~     \_/ \     UNI: kh2567
          \____|__________/  \   Date: 2/8/2013
                 \_______      \
                         `\     \                 \
                           |     |                  \
                          /      /                    \
                         /     /                      \\
                       /      /                         \ \
                      /     /                            \  \
                    /     /             _----_            \   \
                   /     /           _-~      ~-_         |   |
                  (      (        _-~    _--_    ~-_     _/   |
                   \      ~-____-~    _-~    ~-_    ~-_-~    /
                     ~-_           _-~          ~-_       _-~   
                        ~--______-~                ~-___-~

myshell$pwd
/Users/oliverbs163/Dropbox/osystem/submit
myshell$ls
Makefile	hw1.txt		shell.c		support.c	support.o
Readme.txt	myshell		shell.o		support.h
myshell$ls -l
total 152
-rw-r--r--@ 1 oliverbs163  staff    176 Feb  5 18:00 Makefile
-rw-r--r--@ 1 oliverbs163  staff   1994 Feb  5 19:32 Readme.txt
-rw-r--r--@ 1 oliverbs163  staff   7402 Feb 10 23:20 hw1.txt
-rwxr-xr-x  1 oliverbs163  staff  19108 Feb 10 23:25 myshell
-rw-r--r--  1 oliverbs163  staff   9853 Feb 10 21:27 shell.c
-rw-r--r--  1 oliverbs163  staff  10844 Feb 10 23:25 shell.o
-rw-r--r--  1 oliverbs163  staff   3929 Feb 10 19:15 support.c
-rw-r--r--  1 oliverbs163  staff    737 Feb 10 18:42 support.h
-rw-r--r--  1 oliverbs163  staff   4984 Feb 10 23:25 support.o
myshell$cd ..  
myshell$pwd
/Users/oliverbs163/Dropbox/osystem
myshell$cd submit
myshell$pwd
/Users/oliverbs163/Dropbox/osystem/submit
myshell$path
/bin/:/usr/bin/:
myshell$path + /test/
myshell$path
/bin/:/usr/bin/:/test/:
myshell$path - /testmo/
error: path /testmo/ not found
myshell$path - /test/
myshell$path
/bin/:/usr/bin/:
myshell$ls > 1.txt
myshell$cat 1.txt
1.txt
Makefile
Readme.txt
hw1.txt
myshell
shell.c
shell.o
support.c
support.h
support.o
myshell$ls > 2.txt
myshell$cat 2.txt
1.txt
2.txt
Makefile
Readme.txt
error.txt
hw1.txt
myshell
shell.c
shell.o
support.c
support.h
support.o
myshell$cat 1.txt | wc
      10      10      88
myshell$cat < 1.txt
1.txt
Makefile
Readme.txt
hw1.txt
myshell
shell.c
shell.o
support.c
support.h
support.o
myshell$ls | wc | wc
       1       3      25
myshell$ls | wc
      10      10      88
myshell$ls | wc | cat
      10      10      88
myshell$no
Command no not found.
myshell$cat notexist 2> error.txt
myshell$cat error.txt
cat: notexist: No such file or directory
myshell$ exit
Closing...
HUs-MacBook-