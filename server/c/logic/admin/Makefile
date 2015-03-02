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
	UpdateGroup.o \
	Session.o \
	Col_test.o \
	UpdateScheduleItem.o \
	SaveSQLWork.o \
	SQLTests.o \
	SchedItem.o \
	IAFile_test.o \
	Action_test.o \
	DeleteSQLWork.o \
	User.o \
	Group.o \
	Row_test.o \
	SQLWork_test.o \
	UpdateUser.o \
	SQLStmt.o \
	DeleteScheduleItem.o \
	DeleteUser.o \
	DeleteIAFile.o \
	Group_test.o \
	GetActions.o \
	IAFolder.o \
	Col.o \
	GetOneGroup.o \
	UserGroup_test.o \
	SQLTests_test.o \
	GetOneUser.o \
	Session_test.o \
	IAFile.o \
	IAFolder_test.o \
	LoadSQLTestMeta.o \
	GetGroups.o \
	GetOneScheduleItem.o \
	UserGroup.o \
	User_test.o \
	Row.o \
	GetUsers.o \
	GetIAFileList.o \
	SQLStmt_test.o \
	SaveIAFile.o \
	DeleteGroup.o \
	GetSQLTest.o \
	GetIAFileDetails.o \
	GetWorkFileList.o \
	GetScheduleItems.o \
	SaveSQLTest.o \
	GetSQLWork.o \
	SchedItem_test.o \
	Action.o

all: $(DOTOH)
	g++ -shared -o ../../bin/libhelix.logic.admin.so $(DOTOH) $(LFLAGS)
	cd test && $(GMAKE) -f Makefile all

clean:
	rm -f $(DOTOH) *.o *.obj core *.so
	touch -c *.sql.xml
	rm -f ../../bin/libhelix.logic.admin.so
	cd test && $(GMAKE) -f Makefile clean

