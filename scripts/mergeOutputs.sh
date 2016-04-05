#!/bin/bash

TAGS="TTJets WJets ZJets QCD GJets"
LIST=" "
for i in $TAGS
do
    echo $i
    hadd -f fullAnalysis_${i}.root `xrdfs root://cmseos.fnal.gov ls -u /store/user/awhitbe1/RA2bHiggsTagging/fullAnalysis/${1}/ | grep ${i}`
    LIST=$LIST" fullAnalysis_${i}.root"
done

hadd -f fullAnalysis_all.root $LIST
