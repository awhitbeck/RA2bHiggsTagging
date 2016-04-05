#!/bin/sh

executable=$1
inputFileTag=$2
outputFileTag=$3
commitHash=$4
workingDir=$PWD

######################################
# SETUP CMSSW STUFF...
######################################
source /cvmfs/cms.cern.ch/cmsset_default.sh
scram p CMSSW CMSSW_7_4_2
cd CMSSW_7_4_2/src
eval `scramv1 runtime -sh`
pwd

######################################
# SETUP PRIVATE STUFF...
######################################
echo "ls"
ls
cp ../../*.tar .
mkdir RA2bHiggsTagging
tar -xf RA2bHiggsTagging.tar -C RA2bHiggsTagging
mkdir AnalysisTools
tar -xf AnalysisTools.tar -C AnalysisTools

echo "ls"
ls
echo "ls RA2bHiggsTagging"
ls RA2bHiggsTagging
echo "ls AnalysisTools"
ls AnalysisTools

echo $commitHash

g++ `root-config --cflags --glibs` -I./AnalysisTools/src/ -I./RA2bHiggsTagging/src/ RA2bHiggsTagging/src/$executable.cc -o RA2bHiggsTagging/src/$executable.exe
ls
echo "RUNNING ANALYSIS"

cd RA2bHiggsTagging/src/
./$executable.exe $inputFileTag
ls
echo "COPYING OUTPUT"

for i in $( ls | grep root ) ; do 
    xrdcp $i root://cmseos.fnal.gov//store/user/awhitbe1/RA2bHiggsTagging/${executable}/${commitHash}/$i
done