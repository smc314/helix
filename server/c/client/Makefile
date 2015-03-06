#
# This is a Lin64 Makefile generated for folder ../client
# To adjust the settings in this makefile, please edit server/c/build/MakeMakefiles.cpp
######################################################################

3PL=../../../../3rdParty
GMAKE=make -j 8
LINK=g++
UNAME := $(shell uname)

CFLAGS=-g -Wall -D_REENTRANT -fPIC -O2 -rdynamic -I/usr/include -I/usr/include/libxml2 -I "$(3PL)/slib/include"  -I /Library/Java/Home/include -I /usr/lib/jvm/default/include -I/usr/lib/jvm/default/include/linux -I ../glob -I ../logic/admin -I ../logic/dev -I ../logic/test -I ../logic/util 

ifeq ($(UNAME),Linux)
	LFLAGS=-lssl -lcrypto -lpthread -lresolv -lxml2 -luuid -lz -lodbc -L$(3PL)/slib/lib -lSLib
else
	LFLAGS=-lssl -lcrypto -lpthread -lresolv -lxml2 -lz -L$(3PL)/slib/lib -lSLib
endif

GLOBOBJS=-L../bin -lhelix.glob
LOGICOBJS=-L../bin \
	-lhelix.logic.admin \
	-lhelix.logic.dev \
	-lhelix.logic.util 

%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

%.o: %.c
	g++ $(CFLAGS) -c $< -o $@

DOTOH=\
	HelixApiTest.o

APIOH=HelixApi_Part1.o HelixApi_Part2.o
LINKOBJ=-L../bin -lhelix.client $(GLOBOBJS) $(LOGICOBJS) $(LLIBS)

all: $(DOTOH) $(APIOH)
	g++ -shared -o ../bin/libhelix.client.so $(APIOH)
	$(LINK) -o ../bin/HelixApiTest HelixApiTest.o $(LINKOBJ) $(LFLAGS)

clean:
	rm -f $(DOTOH) *.o *.obj core *.so
	rm -f ../bin/libhelix.client.so

