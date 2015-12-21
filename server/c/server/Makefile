#
# This is a Lin64 Makefile generated for folder ../server
# To adjust the settings in this makefile, please edit server/c/build/MakeMakefiles.cpp
######################################################################

3PL=../../../../3rdParty
GMAKE=make -j 8
LINK=g++
UNAME := $(shell uname)

ifeq ($(UNAME),Linux)
	OPENSSLDIR=/usr
else
	OPENSSLDIR=/usr/local/opt/openssl
endif

CFLAGS=-g -Wall -D_REENTRANT -O2 -rdynamic -I$(OPENSSLDIR)/include -I/usr/include -I/usr/include/libxml2 -I "$(3PL)/slib/include"  -I /Library/Java/Home/include -I /usr/lib/jvm/default/include -I/usr/lib/jvm/default/include/linux -I ../glob -I ../logic/admin -I ../logic/dev -I ../logic/test -I ../logic/util 

ifeq ($(UNAME),Linux)
	LFLAGS=-L$(OPENSSLDIR)/lib -lssl -lcrypto -lpthread -lresolv -lxml2 -luuid -lz -lodbc -L$(3PL)/slib/lib -lSLib
else
	LFLAGS=-L$(OPENSSLDIR)/lib -lssl -lcrypto -lpthread -lresolv -lxml2 -lz -L$(3PL)/slib/lib -lSLib
endif

%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

%.o: %.c
	g++ $(CFLAGS) -c $< -o $@

DOTOH=HelixMain.o HelixDaemon.o

all: $(DOTOH)

clean:
	rm -f $(DOTOH) *.o *.obj core *.so

