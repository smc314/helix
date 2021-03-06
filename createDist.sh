#!/bin/bash
########################################################################################
# This script is used to create the distribution of precompiled components of the Helix
# project.  The distribution is used by projects that use helix as their foundation.

#
# Project folder is a temp folder right here
PROJECT_FOLDER=./helixDist

#
# Create the normal project folder structure
mkdir -p ${PROJECT_FOLDER}
mkdir -p ${PROJECT_FOLDER}/docs
mkdir -p ${PROJECT_FOLDER}/html
mkdir -p ${PROJECT_FOLDER}/html/admin
mkdir -p ${PROJECT_FOLDER}/html/dev
mkdir -p ${PROJECT_FOLDER}/html/HelixLogin
mkdir -p ${PROJECT_FOLDER}/qd
mkdir -p ${PROJECT_FOLDER}/server
mkdir -p ${PROJECT_FOLDER}/server/c/bin
mkdir -p ${PROJECT_FOLDER}/server/c/build
mkdir -p ${PROJECT_FOLDER}/server/c/client
mkdir -p ${PROJECT_FOLDER}/server/c/client/apitests
mkdir -p ${PROJECT_FOLDER}/server/c/glob
mkdir -p ${PROJECT_FOLDER}/server/c/logic
mkdir -p ${PROJECT_FOLDER}/server/c/logic/admin
mkdir -p ${PROJECT_FOLDER}/server/c/logic/dev
mkdir -p ${PROJECT_FOLDER}/server/c/logic/util


#
# Copy the precompiled binares required for the new project
cp server/c/bin/AutoAsset ${PROJECT_FOLDER}/server/c/bin/
cp server/c/bin/CopyCommon ${PROJECT_FOLDER}/server/c/bin/
cp server/c/bin/CopyIcons ${PROJECT_FOLDER}/server/c/bin/
cp server/c/bin/GenerateSqlClasses ${PROJECT_FOLDER}/server/c/bin/
cp server/c/bin/HelixDaemon ${PROJECT_FOLDER}/server/c/bin/
cp server/c/bin/HelixMain ${PROJECT_FOLDER}/server/c/bin/
cp server/c/bin/LogDump ${PROJECT_FOLDER}/server/c/bin/
cp server/c/bin/MakeMakefiles ${PROJECT_FOLDER}/server/c/bin/
cp server/c/bin/SLogDump ${PROJECT_FOLDER}/server/c/bin/
cp server/c/bin/SqlShell ${PROJECT_FOLDER}/server/c/bin/
cp server/c/bin/helix.db.xml ${PROJECT_FOLDER}/server/c/bin/
cp server/c/bin/helixdev.db.xml ${PROJECT_FOLDER}/server/c/bin/
cp server/c/bin/libSLib.so ${PROJECT_FOLDER}/server/c/bin/
cp server/c/bin/libhelix.client.so ${PROJECT_FOLDER}/server/c/bin/
cp server/c/bin/libhelix.glob.so ${PROJECT_FOLDER}/server/c/bin/
cp server/c/bin/libhelix.logic.admin.so ${PROJECT_FOLDER}/server/c/bin/
cp server/c/bin/libhelix.logic.dev.so ${PROJECT_FOLDER}/server/c/bin/
cp server/c/bin/libhelix.logic.util.so ${PROJECT_FOLDER}/server/c/bin/
cp server/c/build/*.tmpl ${PROJECT_FOLDER}/server/c/build/
cp server/c/glob/*.h ${PROJECT_FOLDER}/server/c/glob/
cp server/c/logic/admin/*.h ${PROJECT_FOLDER}/server/c/logic/admin/
grep LOGICCODEGEN server/c/logic/admin/*.cpp |sed -e "s/^.*://" > ${PROJECT_FOLDER}/server/c/logic/admin/LogicCodeGen.cpp
cp server/c/logic/dev/*.h ${PROJECT_FOLDER}/server/c/logic/dev/
grep LOGICCODEGEN server/c/logic/dev/*.cpp |sed -e "s/^.*://" > ${PROJECT_FOLDER}/server/c/logic/dev/LogicCodeGen.cpp
cp server/c/logic/util/*.h ${PROJECT_FOLDER}/server/c/logic/util/
grep LOGICCODEGEN server/c/logic/util/*.cpp |sed -e "s/^.*://" > ${PROJECT_FOLDER}/server/c/logic/util/LogicCodeGen.cpp
cp server/c/gmake.unix ${PROJECT_FOLDER}/server/c/
cp server/c/gmake.win ${PROJECT_FOLDER}/server/c/
cp server/c/logic/*.sh ${PROJECT_FOLDER}/server/c/logic/
cp server/c/client/HelixApi_Part1.cpp ${PROJECT_FOLDER}/server/c/client/

#
# Copy the precompiled web projects
# Don't include qd/login any more
#cp -a qd/login ${PROJECT_FOLDER}/qd/
# Don't include qd/common any more
#cp -a qd/common ${PROJECT_FOLDER}/qd/
cp -a qd/admin/build/* ${PROJECT_FOLDER}/html/admin/
cp -a qd/admin/source/layouts ${PROJECT_FOLDER}/html/admin/
cp -a qd/dev/build/* ${PROJECT_FOLDER}/html/dev/
cp -a qd/dev/source/layouts ${PROJECT_FOLDER}/html/dev/
cp -a qd/login/build/* ${PROJECT_FOLDER}/html/HelixLogin/
cp qd/*.sh ${PROJECT_FOLDER}/qd/

UNAME=`uname`
if [ "${UNAME}" = "Darwin" ]
then
	DISTNAME="helixOsxDist.tgz"
else
	DISTNAME="helixDist.tgz"
fi

#
# zip up the distribution folder
rm -f ${DISTNAME}
cd helixDist 
tar cvfz ../$(DISTNAME} *
cd ..
#
# Remove the distribution temp folder
rm -rf ${PROJECT_FOLDER}

#
# Copy the distribution over to the website - only works if we're on hericus4.hericus.com
scp ${DISTNAME} hericus4.hericus.com:/home/smc/websites/helixweb/publicweb/
