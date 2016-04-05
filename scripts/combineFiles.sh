#!/bin/bash

cd $CMSSW_BASE/src
eval `scramv1 runtime -sh`
cd -

TAGS="TTJets WJets ZJets QCD GJets"
LIST=" "
for i in $TAGS 
do
    echo $i
    hadd -f fullAnalysis_${i}.root `xrdfsls -u /store/user/awhitbe1/GMSBstudies/fullAnalysis/f71e60ce4d15f05794ac90b83a488bec88bfd529/ | grep ${i}`
    LIST=$LIST" fullAnalysis_${i}.root"
done

hadd -f fullAnalysis_all.root $LIST

