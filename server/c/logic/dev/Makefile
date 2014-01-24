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
	BusinessUnit.o \
	DObject.o \
	DOStmt.o \
	Screen_test.o \
	FunctionalRole.o \
	Person_test.o \
	Project_test.o \
	ProjectData_test.o \
	Application_test.o \
	Api_test.o \
	Email.o \
	BusinessUnit_test.o \
	Screen.o \
	GetProject.o \
	DOStmtInput_test.o \
	Project.o \
	DOChild_test.o \
	DOStmtOutput_test.o \
	Phone.o \
	TableCol_test.o \
	DOStmt_test.o \
	ProjectTable.o \
	Phone_test.o \
	Address.o \
	DOStmtInput.o \
	ProjectData.o \
	Api.o \
	DObject_test.o \
	Address_test.o \
	Application.o \
	SaveProject.o \
	GetProjectList.o \
	DOChild.o \
	ProjectTable_test.o \
	Person.o \
	Prospect_test.o \
	FunctionalRole_test.o \
	TableCol.o \
	DOStmtOutput.o \
	Prospect.o \
	Email_test.o

all: $(DOTOH)
	cd test && $(GMAKE) -f Makefile all

clean:
	rm -f $(DOTOH) *.o *.obj core *.so
	touch -c *.sql.xml
	cd test && $(GMAKE) -f Makefile clean

