#!/bin/bash

cd $CMSSW_BASE/src
eval `scramv1 runtime -sh`
cd -

TAGS="TTJets WJets ZJets QCD GJets"
LIST=" "
for i in $TAGS 
do
    echo $i
    hadd -f fullAnalysis_${i}.root `xrdfsls -u /store/user/awhitbe1/RA2bHiggsTagging/fullAnalysis/${1}/ | grep ${i}`
    LIST=$LIST" fullAnalysis_${i}.root"
done

hadd -f fullAnalysis_all.root $LIST

