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
	SQLWork_test.o \
	SQLTests.o \
	UserGroup.o \
	UserGroup_test.o \
	IAFile.o \
	GetIAFileDetails.o \
	GetOneUser.o \
	Session.o \
	SaveIAFile.o \
	Col_test.o \
	User.o \
	SQLTests_test.o \
	GetIAFileList.o \
	UpdateUser.o \
	Group.o \
	DeleteSQLWork.o \
	Col.o \
	SQLStmt_test.o \
	User_test.o \
	GetScheduleItems.o \
	SaveSQLWork.o \
	GetOneGroup.o \
	IAFolder.o \
	IAFolder_test.o \
	IAFile_test.o \
	SaveSQLTest.o \
	GetOneScheduleItem.o \
	LoadSQLTestMeta.o \
	UpdateScheduleItem.o \
	Group_test.o \
	SchedItem.o \
	GetWorkFileList.o \
	DeleteUser.o \
	Session_test.o \
	GetSQLWork.o \
	GetGroups.o \
	DeleteScheduleItem.o \
	DeleteIAFile.o \
	Action_test.o \
	GetUsers.o \
	SchedItem_test.o \
	SQLWork.o \
	Row_test.o \
	UpdateGroup.o \
	DeleteGroup.o \
	GetSQLTest.o \
	GetActions.o \
	Row.o \
	Action.o \
	SQLStmt.o

all: $(DOTOH)
	g++ -shared -o ../../bin/libhelix.logic.admin.so $(DOTOH) $(LFLAGS)
	cd test && $(GMAKE) -f Makefile all

clean:
	rm -f $(DOTOH) *.o *.obj core *.so
	touch -c *.sql.xml
	rm -f ../../bin/libhelix.logic.admin.so
	cd test && $(GMAKE) -f Makefile clean

