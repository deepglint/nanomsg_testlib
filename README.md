THIS IS THE GALLERY OF BUILT LIBNANOMSG ON DIFFERENT PLATFORM

sender.o IS THE SIMPLE NANOMSG SEND-RECEIEVE LIBRARY

IN THE LINUX SYSTEM SHOULD COMPILE THE FILE LIKE THIS

gcc receiver.c /usr/local/lib/libnanomsg.a  -o receiver3 -pthread -lanl

gcc -Wall -c sender.c /usr/local/lib/libnanomsg.so -I 
/usr/local/include/ -pthread -lanl


gcc testsender.c ./sender.o /usr/local/lib/libnanomsg.a -I 
/usr/local/include/ -o testsender -pthread -lanl


IF IN THE LINUX SYSTEM YOU CANNOT FIND /libnanomsg.so.0 YOU SHOULD USE 
THE COMMAND LIKE THIS 
 export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/

REFERENCE:http://www.network-theory.co.uk/docs/gccintro/gccintro_25.html

HOW TO INSTALL LIBNANOMSG

ps: How to build Libnanomsg
1.Download nanomsg/nanomsg
2.install autoconf & libtool
3.run autogen.sh
4../configure
5.make
6.make install


to build the program depend on the nanomsg, you need to config the 
PKG_CONFIG path to the config libnanomsg.pc file

PKG_CONFIG_PATH=/usr/local/lib/pkgconfig/

If program cannot find the dlibe add the env

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/

