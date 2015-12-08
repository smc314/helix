#
# This is a Lin64 Makefile generated for folder ../client
# To adjust the settings in this makefile, please edit server/c/build/MakeMakefiles.cpp
######################################################################

3PL=../../3rdParty
GMAKE=make -j 8
LINK=g++
UNAME := $(shell uname)

ifeq ($(UNAME),Linux)
	OPENSSLDIR=/usr
else
	OPENSSLDIR=/usr/local/opt/openssl
endif

CFLAGS=-g -Wall -D_REENTRANT -fPIC -O2 -rdynamic -I$(OPENSSLDIR)/include -I/usr/include -I/usr/include/libxml2 -I "$(3PL)/slib/include"  

ifeq ($(UNAME),Linux)
	LFLAGS=-L$(OPENSSLDIR)/lib -lssl -lcrypto -lpthread -lresolv -lxml2 -luuid -lz -lodbc -L$(3PL)/slib/lib -lSLib
else
	LFLAGS=-L$(OPENSSLDIR)/lib -lssl -lcrypto -lpthread -lresolv -lxml2 -lz -lodbc -L$(3PL)/slib/lib -lSLib
endif

%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

%.o: %.c
	g++ $(CFLAGS) -c $< -o $@

DOTOH=\
	TestCache.o \
	TestStats.o \
	TestLog.o \
	DynamicTest.o \
	ApiTest.o \
	HTest.o

all: $(DOTOH)
	$(LINK) -o htest $(DOTOH) $(LFLAGS)
	cp $(3PL)/slib/lib/libSlib.so .

clean:
	rm -f $(DOTOH) htest *.o *.obj core *.so

