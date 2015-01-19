#
# This is a Lin64 Makefile generated for folder ../logic/admin
# To adjust the settings in this makefile, please edit hub/src/build/MakeMakefiles.cpp
######################################################################

3PL=../../../../../3rdParty
GMAKE=make -j 8

CFLAGS=-g -Wall -D_REENTRANT -fPIC -O2 -rdynamic -I/usr/include -I/usr/include/libxml2 -I "$(3PL)/slib/include" -I ../../glob -I ../../client -I ../util -I ../admin -I ../dev -I ../test 

LFLAGS=

%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

%.o: %.c
	g++ $(CFLAGS) -c $< -o $@

DOTOH=\
	SQLWork.o \
	Col_test.o \
	UpdateScheduleItem.o \
	SaveSQLWork.o \
	SQLTests.o \
	SchedItem.o \
	IAFile_test.o \
	DeleteSQLWork.o \
	Row_test.o \
	SQLWork_test.o \
	SQLStmt.o \
	DeleteScheduleItem.o \
	DeleteIAFile.o \
	IAFolder.o \
	Col.o \
	SQLTests_test.o \
	IAFile.o \
	IAFolder_test.o \
	LoadSQLTestMeta.o \
	GetOneScheduleItem.o \
	Row.o \
	GetIAFileList.o \
	SQLStmt_test.o \
	SaveIAFile.o \
	GetSQLTest.o \
	GetIAFileDetails.o \
	GetWorkFileList.o \
	GetScheduleItems.o \
	SaveSQLTest.o \
	GetSQLWork.o \
	SchedItem_test.o

all: $(DOTOH)
	g++ -shared -o ../../bin/libhelix.logic.admin.so $(DOTOH) $(LFLAGS)
	cd test && $(GMAKE) -f Makefile all

clean:
	rm -f $(DOTOH) *.o *.obj core *.so
	touch -c *.sql.xml
	rm -f ../../bin/libhelix.logic.admin.so
	cd test && $(GMAKE) -f Makefile clean

