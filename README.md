IN THE LINUX SYSTEM SHOULD COMPILE THE FILE LIKE THIS
gcc receiver.c /usr/local/lib/libnanomsg.a  -o receiver3 -pthread -lanl

gcc -Wall -c sender.c /usr/local/lib/libnanomsg.so -I 
/usr/local/include/ -pthread -lanl


gcc testsender.c ./sender.o /usr/local/lib/libnanomsg.a -I 
/usr/local/include/ -o testsender -pthread -lanl


