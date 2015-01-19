#
# This is a Lin64 Makefile generated for folder ../logic/util
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
	SystemProperties.o \
	GetLogMsgCount.o \
	HitMap.o \
	SchedItem.o \
	LogOn.o \
	CloseConnection.o \
	LRTask.o \
	LogMessageFilter.o \
	GetAllLayouts.o \
	GetLogSettings.o \
	GetLogMessagesByRange.o \
	SQLStatement.o \
	GetHitMap.o \
	CleanoutLRTask.o \
	ConnectToServer.o \
	GetAllLRTasks.o \
	SaveLogMsg.o \
	LogObj.o \
	LogObj_test.o \
	SQLStatement_test.o \
	Statics.o \
	FindLogMessage.o \
	LogSettings_test.o \
	UpdateLogSettings.o \
	GetProfile.o \
	GetOneLRTask.o \
	LRTask_test.o \
	UserProperties.o \
	SwitchServerConnection.o \
	LogMessageFilter_test.o \
	ExecuteGenericSQL.o \
	LogSettings.o \
	HitMap_test.o \
	GetLogMessages.o \
	SchedItem_test.o \
	SaveLayout.o \
	GetLogFiles.o \
	LogOn_test.o

all: $(DOTOH)
	g++ -shared -o ../../bin/libhelix.logic.util.so $(DOTOH) $(LFLAGS)
	cd test && $(GMAKE) -f Makefile all

clean:
	rm -f $(DOTOH) *.o *.obj core *.so
	touch -c *.sql.xml
	rm -f ../../bin/libhelix.logic.util.so
	cd test && $(GMAKE) -f Makefile clean

