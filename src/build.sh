#!/bin/sh

cd ../../
source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`

g++ -g `root-config --cflags --glibs` -I./AnalysisTools/src/ -I./RA2bHiggsTagging/src/ RA2bHiggsTagging/src/$1.cc -o RA2bHiggsTagging/src/$1.exe

