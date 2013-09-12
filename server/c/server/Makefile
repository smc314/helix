#
# This is a Lin64 Makefile generated for folder ../glob
# To adjust the settings in this makefile, please edit hub/src/build/MakeMakefiles.cpp
######################################################################

3PL=../../../../../3rdParty
GMAKE=make -j 8

CFLAGS=-g -Wall -D_REENTRANT -O2 -rdynamic -I/usr/include -I/usr/include/libxml2 -I "$(3PL)/slib/include"  -I ../logic/utils -I. -I /Library/Java/Home/include -I /usr/lib/jvm/default/include -I/usr/lib/jvm/default/include/linux 


%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

%.o: %.c
	g++ $(CFLAGS) -c $< -o $@

DOTOH=\

all: $(DOTOH)

clean:
	rm -f $(DOTOH) *.o *.obj core *.so

