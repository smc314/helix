#!/bin/bash
########################################################################################
# This script is used to download and unpack the latest helix distribution from the
# website.  This will update all of our core helix binaries and projects that we build
# on top of.

#
# If we have a distribution file, remove it.
rm -f helixDist.tgz

#
# Download from the primary helix site:
wget http://www.helixsdk.org/helixDist.tgz

#
# Unpack the distribution
tar xvfz helixDist.tgz
