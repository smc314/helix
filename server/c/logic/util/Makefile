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
	ExecuteGenericSQL.o \
	GetProfile.o \
	LogSettings.o \
	LogMessageFilter.o \
	FindLogMessage.o \
	LogSettings_test.o \
	CloseConnection.o \
	LogMessageFilter_test.o \
	SaveLogMsg.o \
	GetHitMap.o \
	SystemProperties.o \
	GetAllLRTasks.o \
	ConnectToServer.o \
	GetLogFiles.o \
	GetAllLayouts.o \
	SaveLayout.o \
	UserProperties.o \
	HitMap_test.o \
	LogOn.o \
	GetLogMessagesByRange.o \
	GetLogSettings.o \
	LRTask_test.o \
	GetLogMsgCount.o \
	LogObj.o \
	SchedItem.o \
	LogOn_test.o \
	GetLogMessages.o \
	Statics.o \
	UpdateLogSettings.o \
	SwitchServerConnection.o \
	LRTask.o \
	CleanoutLRTask.o \
	LogObj_test.o \
	GetOneLRTask.o \
	SQLStatement.o \
	HitMap.o \
	SchedItem_test.o \
	SQLStatement_test.o

all: $(DOTOH)
	g++ -shared -o ../../bin/libhelix.logic.util.so $(DOTOH) $(LFLAGS)
	cd test && $(GMAKE) -f Makefile all

clean:
	rm -f $(DOTOH) *.o *.obj core *.so
	touch -c *.sql.xml
	rm -f ../../bin/libhelix.logic.util.so
	cd test && $(GMAKE) -f Makefile clean

