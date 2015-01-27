#
# This is a Lin64 Makefile generated for folder ../glob
# To adjust the settings in this makefile, please edit server/c/build/MakeMakefiles.cpp
######################################################################

3PL=../../../../3rdParty
GMAKE=make -j 8

CFLAGS=-g -Wall -D_REENTRANT -fPIC -O2 -rdynamic -I/usr/include -I/usr/include/libxml2 -I "$(3PL)/slib/include"  -I ../logic/util -I ../logic/admin -I. -I /Library/Java/Home/include -I /usr/lib/jvm/default/include -I/usr/lib/jvm/default/include/linux 

LFLAGS=

%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

%.o: %.c
	g++ $(CFLAGS) -c $< -o $@

DOTOH=\
	OdbcObj.o \
	ActionClass.o \
	IOAdapter.o \
	LongRunningTask.o \
	AdaptiveLogs.o \
	ThreadList.o \
	OdbcDrv.o \
	HttpIOAdapter.o \
	ActionHtml.o \
	TableActions.o \
	Authenticate.o \
	HttpConn.o \
	SessionSerializer.o \
	ConnectionPool.o \
	Scaler.o \
	TheMain.o \
	IOConn.o \
	mongoose.o \
	MsgProcessor.o \
	SessionList.o \
	SchedEntry.o \
	ActionLogic.o \
	Schedule.o \
	DataObjectTestMap.o \
	Jvm.o \
	SessionInfo.o \
	MsgProcScaler.o \
	DataObjectTestClass.o \
	MySqlDbInit.o \
	SchedConn.o \
	SqlDB.o \
	ActionMap.o \
	Threadable.o

all: $(DOTOH)
	g++ -shared -o ../bin/libhelix.glob.so $(DOTOH) $(LFLAGS)

clean:
	rm -f $(DOTOH) *.o *.obj core *.so
	rm -f ../bin/libhelix.glob.so

