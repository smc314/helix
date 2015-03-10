#
# This is a Lin64 Makefile generated for folder ../logic/dev
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
	DObject.o \
	Application_test.o \
	DOStmtOutput.o \
	GetProjectList.o \
	ProjectData_test.o \
	SaveProject.o \
	DOChild.o \
	DOStmt_test.o \
	DOStmtInput.o \
	Project.o \
	DOStmtInput_test.o \
	TableCol.o \
	ProjectData.o \
	DOStmt.o \
	Screen.o \
	Api.o \
	DOChild_test.o \
	Application.o \
	DObject_test.o \
	Project_test.o \
	TableCol_test.o \
	ProjectTable.o \
	ProjectTable_test.o \
	Api_test.o \
	GetProject.o \
	DOStmtOutput_test.o \
	Screen_test.o

all: $(DOTOH)
	g++ -shared -o ../../bin/libhelix.logic.dev.so $(DOTOH) $(LFLAGS)
	cd test && $(GMAKE) -f Makefile all

clean:
	rm -f $(DOTOH) *.o *.obj core *.so
	touch -c *.sql.xml
	rm -f ../../bin/libhelix.logic.dev.so
	cd test && $(GMAKE) -f Makefile clean

