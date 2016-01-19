#
# This is the unix build version of the makefile
# Use make -f Makefile to run this
###############################################################

CC=g++
LINK=g++
CP=cp
RM=rm -f
MKDIR=mkdir
MKDIRP=mkdir -p
PYTHON=python
DOXYGEN=doxygen
QDROOT=../../qd
# Tune this down if you don't have a multi-core system.  I have 8 cores and with this the build screams
GMAKE=make -j 8
UNAME := $(shell uname)
ARCH := $(shell uname -p)
DOJNI=false

3PL=../../../3rdParty

ifeq ($(UNAME),Linux)
	OPENSSLDIR=/usr
else
	OPENSSLDIR=/usr/local/opt/openssl
endif

CFLAGS=-g -Wall -D_REENTRANT -O2 -rdynamic -I$(OPENSSLDIR)/include -I/usr/include -I/usr/include/libxml2

ifeq ($(UNAME),Linux)
	LFLAGS=-L$(OPENSSLDIR)/lib -lssl -lcrypto -lpthread -lresolv -lxml2 -luuid -lodbc -lz -L./bin -lSLib
else
	LFLAGS=-L$(OPENSSLDIR)/lib -lssl -lcrypto -lpthread -lresolv -lxml2 -lodbc -lz -L./bin -lSLib
endif

%.o:	%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@

ALLOH=-L./bin \
	-lhelix.glob \
	-lhelix.client \
	-lhelix.logic.dev

all: install buildPrep subdirs HelixMain HelixDaemon install

buildPrep:
	cd build && $(GMAKE) -f Makefile.unix all
	-cd $(QDROOT)/common/sqldo && $(RM) *.js
	-cd $(QDROOT)/admin/source/class/admin/sqldo && $(RM) *.js
	-cd $(QDROOT)/dev/source/class/dev/sqldo && $(RM) *.js
	cd bin && ./GenerateSqlClasses
	cd bin && ./CopyCommon
	cd bin && ./AutoAsset
	cd bin && ./CopyIcons
	cd bin && ./MakeMakefiles -jni=$(DOJNI)

HelixMain:
	$(LINK) -o bin/HelixMain server/HelixMain.o $(ALLOH) $(LFLAGS)

# HelixDaemon should have none of our libraries required for it.  We don't want it dependent on
# SLib or anything else that can be upgraded.  It only depends on native linux libraries.
HelixDaemon:
	$(LINK) -o bin/HelixDaemon server/HelixDaemon.o 

subdirs: util_dir admin_dir glob_dir server_dir dev_dir client_dir

glob_dir:
	cd glob && $(GMAKE) -f Makefile all

server_dir:
	cd server && $(GMAKE) -f Makefile all

admin_dir:
	cd logic/admin && $(GMAKE) -f Makefile all

dev_dir:
	cd logic/dev && $(GMAKE) -f Makefile all

util_dir:
	cd logic/util && $(GMAKE) -f Makefile all

client_dir:
	cd client && $(GMAKE) -f Makefile all

clean: subdirs_clean 
	cd bin && $(RM) *.o core *.so HelixMain HelixDaemon

subdirs_clean: build_clean glob_clean server_clean admin_clean dev_clean util_clean client_clean 

build_clean:
	cd build && $(GMAKE) -f Makefile.unix clean

glob_clean:
	cd glob && $(GMAKE) -f Makefile clean

server_clean:
	cd server && $(GMAKE) -f Makefile clean

admin_clean:
	cd logic/admin && $(GMAKE) -f Makefile clean

dev_clean:
	cd logic/dev && $(GMAKE) -f Makefile clean

util_clean:
	cd logic/util && $(GMAKE) -f Makefile clean

client_clean:
	cd client && $(GMAKE) -f Makefile clean

install:
	-mkdir bin
	cp $(3PL)/x64/lib/libSLib.so bin/
	cp $(3PL)/x64/bin/LogDump bin/
	cp $(3PL)/x64/bin/SLogDump bin/
	cp $(3PL)/x64/bin/SqlShell bin/
	-cp logic/*.db.xml bin/

docs:
	-mkdir ../html/devdoc
	$(DOXYGEN) dev.doxy

qd: 
	cd ../qd && $(MAKE) -f Makefile.unix build

qd_source: 
	cd ../qd && $(MAKE) -f Makefile.unix source

qd_api: 
	cd ../qd && $(MAKE) -f Makefile.unix api

qd_test: 
	cd ../qd && $(MAKE) -f Makefile.unix test

# Create our distribution directory
dist:
	-cd .. && rm -rf dist
	mkdir ../dist
	cp -a bin ../dist/
	-cd ../dist/bin && rm -f *.exp *.lib *.log *.valgrind *.out *.rsa *.rsa_pub AutoAsset CopyCommon CopyIcons GenerateSqlClasses JvmTest1 MakeMakefiles RunGenericSql RunUnitTest 
	-cd ../dist/bin/logs && rm -rf *
	cd ../dist && find . -name .gitignore -exec rm {} \; -print
	cp -a ../html ../dist/
	-cd ../dist/html && rm -rf devdoc 
	cd ../qd && $(MAKE) -f Makefile.unix dist

# Remember to run dist before this command
deb:
	-cd .. && rm -rf helix_314.314.314.314*
	cd .. && mv dist helix_314.314.314.314
	cp Makefile.cust.linux ../helix_314.314.314.314/Makefile
	cd ../helix_314.314.314.314 && mkdir -p etc/init.d
	cp helix.linux.initd ../helix_314.314.314.314/etc/init.d/helix
	cd .. && tar cvfz helix_314.314.314.314.orig.tar.gz helix_314.314.314.314
	cp -a ../debian ../helix_314.314.314.314/
	cd ../helix_314.314.314.314 && debuild -us -uc

# Remember to run dist before this command
rpm:
	-cd /usr/src/redhat/RPMS/x86_64 && rm helix*.rpm
	-cd .. && rm -rf helix_314.314.314.314*
	cd .. && mv dist helix_314.314.314.314
	cp Makefile.cust.linux ../helix_314.314.314.314/Makefile
	cd ../helix_314.314.314.314 && mkdir -p etc/init.d
	cp helix.linux.initd ../helix_314.314.314.314/etc/init.d/helix
	cd ../helix_314.314.314.314 && make uninstall install DESTDIR=$(RPMPREFIX)
	cd .. && tar cvfz helix_314.314.314.314.orig.tar.gz helix_314.314.314.314
	cd ../redhat && rpmbuild -bb helix.spec

# this is a series of builds that I run every morning after updating from version control.
morning: clean all qd_source qd qd_api qd_test


