#
# This is a Lin64 Makefile generated for folder ../logic/test
# To adjust the settings in this makefile, please edit hub/src/build/MakeMakefiles.cpp
######################################################################

3PL=../../../../../../3rdParty
GMAKE=make -j 8

CFLAGS=-g -Wall -D_REENTRANT -O2 -rdynamic -I/usr/include -I/usr/include/libxml2 -I "$(3PL)/slib/include" -I ../../glob -I ../../client -I ../utils -I ../ascfg -I ../dash -I ../csa -I ../drvdep -I ../ia -I ../ldm -I ../test -I ../test/vsqdir 

%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

%.o: %.c
	g++ $(CFLAGS) -c $< -o $@

DOTOH=\

all: $(DOTOH)

clean:
	rm -f $(DOTOH) *.o *.obj core *.so
	touch -c *.sql.xml

