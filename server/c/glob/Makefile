#
# This is a Lin64 Makefile generated for folder ../glob
# To adjust the settings in this makefile, please edit server/c/build/MakeMakefiles.cpp
######################################################################

3PL=../../../../3rdParty
GMAKE=make -j 8

CFLAGS=-g -Wall -D_REENTRANT -O2 -rdynamic -I/usr/include -I/usr/include/libxml2 -I "$(3PL)/slib/include"  -I ../logic/util -I. -I /Library/Java/Home/include -I /usr/lib/jvm/default/include -I/usr/lib/jvm/default/include/linux 


%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

%.o: %.c
	g++ $(CFLAGS) -c $< -o $@

DOTOH=\
	ActionClass.o \
	ActionHtml.o \
	ActionLogic.o \
	ActionMap.o \
	AdaptiveLogs.o \
	ConnectionPool.o \
	DataObjectTestClass.o \
	DataObjectTestMap.o \
	HttpConn.o \
	HttpIOAdapter.o \
	IOAdapter.o \
	IOConn.o \
	Jvm.o \
	LongRunningTask.o \
	mongoose.o \
	MsgProcessor.o \
	MsgProcScaler.o \
	OdbcDrv.o \
	OdbcObj.o \
	Scaler.o \
	SchedConn.o \
	SchedEntry.o \
	Schedule.o \
	SessionInfo.o \
	SessionList.o \
	SessionSerializer.o \
	SqlDB.o \
	TheMain.o \
	Threadable.o \
	ThreadList.o

all: $(DOTOH)

clean:
	rm -f $(DOTOH) *.o *.obj core *.so

