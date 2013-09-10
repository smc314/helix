#
# This is a Lin64 Makefile generated for folder ../client
# To adjust the settings in this makefile, please edit hub/src/build/MakeMakefiles.cpp
######################################################################

3PL=../../../../../3rdParty
GMAKE=make -j 8
LINK=g++
UNAME := $(shell uname)

CFLAGS=-g -Wall -D_REENTRANT -O2 -rdynamic -I/usr/include -I/usr/include/libxml2 -I "$(3PL)/slib/include"  -I /Library/Java/Home/include -I /usr/lib/jvm/default/include -I/usr/lib/jvm/default/include/linux -I ../glob -I ../logic/ascfg -I ../logic/dash -I ../logic/csa -I ../logic/drvdep -I ../logic/ia -I ../logic/ldm -I ../logic/test -I ../logic/test/vsqdir -I ../logic/utils 

ifeq ($(UNAME),Linux)
	LFLAGS=-lssl -lcrypto -lpthread -lresolv -lxml2 -luuid -lz -lodbc -L$(3PL)/slib/lib -lSLib
else
	LFLAGS=-lssl -lcrypto -lpthread -lresolv -lxml2 -lz -L$(3PL)/slib/lib -lSLib
endif

GLOBOBJS=../glob/*.o
LOGICOBJS=../logic/ascfg/*.o \
	../logic/dash/*.o \
	../logic/csa/*.o \
	../logic/drvdep/*.o \
	../logic/ia/*.o \
	../logic/ldm/*.o \
	../logic/test/*.o \
	../logic/test/vsqdir/*.o \
	../logic/utils/*.o 

%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

%.o: %.c
	g++ $(CFLAGS) -c $< -o $@

DOTOH=\

APIOH=HubApi_Part1.o HubApi_Part2.o
LINKOBJ=$(APIOH) $(GLOBOBJS) $(LOGICOBJS) $(LLIBS)

all: $(DOTOH) $(APIOH)

clean:
	rm -f $(DOTOH) *.o *.obj core *.so

