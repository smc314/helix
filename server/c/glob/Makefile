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
	IOConn.o \
	TheMain.o \
	Scaler.o \
	IOAdapter.o \
	DataObjectTestMap.o \
	MsgProcScaler.o \
	Authenticate.o \
	AdaptiveLogs.o \
	HttpIOAdapter.o \
	DataObjectTestClass.o \
	SessionSerializer.o \
	ActionClass.o \
	LongRunningTask.o \
	mongoose.o \
	OdbcDrv.o \
	SessionInfo.o \
	SqlDB.o \
	ConnectionPool.o \
	SchedConn.o \
	MsgProcessor.o \
	Schedule.o \
	OdbcObj.o \
	ActionMap.o \
	ThreadList.o \
	ActionLogic.o \
	HttpConn.o \
	SchedEntry.o \
	TableActions.o \
	SessionList.o \
	Threadable.o \
	MySqlDbInit.o \
	ActionHtml.o

all: $(DOTOH)
	g++ -shared -o ../bin/libhelix.glob.so $(DOTOH) $(LFLAGS)

clean:
	rm -f $(DOTOH) *.o *.obj core *.so
	rm -f ../bin/libhelix.glob.so

