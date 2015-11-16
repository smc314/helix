#
# This is the unix build version of the makefile
########################################################################################

all: setup_dirs
	cd server/c && make clean all
	cd qd/login && ./generate.py build	
	cd qd/admin && ./generate.py build	
	cd qd/dev && ./generate.py build	
	./createDist.sh


setup_dirs:
	mkdir -p qd/common/sqldo
	mkdir -p qd/admin/source/class/admin/sqldo
	mkdir -p qd/dev/source/class/dev/sqldo
	mkdir -p qd/welcome/source/class/welcome/layout
	
