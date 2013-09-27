#
# This is a Lin64 Makefile generated for folder ../logic/dev
# To adjust the settings in this makefile, please edit hub/src/build/MakeMakefiles.cpp
######################################################################

3PL=../../../../../3rdParty
GMAKE=make -j 8

CFLAGS=-g -Wall -D_REENTRANT -O2 -rdynamic -I/usr/include -I/usr/include/libxml2 -I "$(3PL)/slib/include" -I ../../glob -I ../../client -I ../util -I ../admin -I ../dev -I ../test 

%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

%.o: %.c
	g++ $(CFLAGS) -c $< -o $@

DOTOH=\
	Api.o \
	Api_test.o \
	Application.o \
	Application_test.o \
	DObject.o \
	DObject_test.o \
	DOChild.o \
	DOChild_test.o \
	DOStmt.o \
	DOStmt_test.o \
	DOStmtInput.o \
	DOStmtInput_test.o \
	DOStmtOutput.o \
	DOStmtOutput_test.o \
	GetProject.o \
	GetProjectList.o \
	Project.o \
	Project_test.o \
	ProjectData.o \
	ProjectData_test.o \
	ProjectTable.o \
	ProjectTable_test.o \
	SaveProject.o \
	Screen.o \
	Screen_test.o \
	TableCol.o \
	TableCol_test.o

all: $(DOTOH)
	cd test && $(GMAKE) -f Makefile all

clean:
	rm -f $(DOTOH) *.o *.obj core *.so
	touch -c *.sql.xml
	cd test && $(GMAKE) -f Makefile clean

