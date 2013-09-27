#
# This is a Lin64 Makefile generated for folder ../logic/util
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
	CleanoutLRTask.o \
	CloseConnection.o \
	ConnectToServer.o \
	ExecuteGenericSQL.o \
	FindLogMessage.o \
	GetAllLayouts.o \
	GetAllLRTasks.o \
	GetHitMap.o \
	GetLogFiles.o \
	GetLogMessages.o \
	GetLogMessagesByRange.o \
	GetLogMsgCount.o \
	GetLogSettings.o \
	GetOneLRTask.o \
	GetProfile.o \
	HitMap.o \
	HitMap_test.o \
	LogMessageFilter.o \
	LogMessageFilter_test.o \
	LogObj.o \
	LogObj_test.o \
	LogOn.o \
	LogOn_test.o \
	LogSettings.o \
	LogSettings_test.o \
	LRTask.o \
	LRTask_test.o \
	SaveLayout.o \
	SaveLogMsg.o \
	SchedItem.o \
	SchedItem_test.o \
	SQLStatement.o \
	SQLStatement_test.o \
	Statics.o \
	SwitchServerConnection.o \
	SystemProperties.o \
	UpdateLogSettings.o \
	UserProperties.o

all: $(DOTOH)
	cd test && $(GMAKE) -f Makefile all

clean:
	rm -f $(DOTOH) *.o *.obj core *.so
	touch -c *.sql.xml
	cd test && $(GMAKE) -f Makefile clean

