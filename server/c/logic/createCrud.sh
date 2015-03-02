#!/bin/bash
#############################################################################################
# This script makes it easy to create the GetAll, GetOne, Insert/Update, and Delete API
# requests that are required for every standard object that we expose to our UI.
# Pass in the object name, and we'll create the header/body files for each of these API
# requests.  You'll still have to tweak things, but as long as your queries are based
# on the standard patterns, this will get pretty close.

OBJNAME=$1

../createGetAll.sh ${OBJNAME}
../createGetOne.sh ${OBJNAME}
../createUpdate.sh ${OBJNAME}
../createDelete.sh ${OBJNAME}

