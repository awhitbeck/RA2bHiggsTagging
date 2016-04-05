#include "RA2bNtuple.cc"
#include "analyzer.cc"
#include "signalRegion.cc"
#include "selectBaseline.cc"
#include "selectBin.cc"
#include "skim.cc"
#include "weightProducer.cc"
#include "fillHisto.cc"

#include "TString.h"
#include "TChain.h"
#include "TFile.h"

#include <cstdio>
#include <string>
#include <iostream>

#include "helpers.h"

using namespace std;

/*  = = = = = = = = = = = = = = = = = =

    Things to develop:  

    - Need code that will split signals into different histograms 
      based on their masses 
    - Need histos that give the fraction of events that have a gen-level
      electron, muon, photon, di-muon, di-electron, e-mu, tau, di-tau 
    - Need to understand how often electrons are fakes
    - Need to understand how often photons are fake electrons
    
    = = = = = = = = = = = = = = = = = = */

typedef selectBin<RA2bNtuple> binCut;

int main(int argc, char** argv){

  // this code is setup specifically for analyzing one input file at a time.  The output histonames
  // are based on the sample key, from the fmap (see helper.h for details)
  TString fileTag = argv[1];
  fileMap fmap = parseInputs("inputFiles.txt");
  sampleMap rmap = reduceMap(fmap,fileTag);
  if( rmap.size() != 1 ){
    cout << "either no samples found or too many samples found..." << endl;
    return 1;
  }

  TString sampleTag = rmap.begin()->first;
  TChain* t = buildChain(rmap.begin()->second,"TreeMaker2/PreSelection");  
  RA2bNtuple *ntuple = new RA2bNtuple(t);

  // higgs tag
  binCut SRhiggsCut(ntuple,"SR_higgs");
  SRhiggsCut.minHiggsTags=1; SRhiggsCut.maxHiggsTags=1;
  signalRegion SR_higgs(ntuple,sampleTag,"SR_higgs");
  SR_higgs.addProcessor(&SRhiggsCut,1);

  // W/Z tag
  binCut SRVtagCut(ntuple,"SR_Vtag");
  SRVtagCut.minVTags=1; SRVtagCut.maxVTags=1;
  signalRegion SR_Vtag(ntuple,sampleTag,"SR_Vtag");
  SR_Vtag.addProcessor(&SRVtagCut,1);

  /*
  // >=2 btags
  binCut SRhighBTags(ntuple,"SR_highBTags");
  SRhighBTags.minBTags=2; SRhighBTags.maxBTags=2;
  signalRegion SR_highBTags(ntuple,sampleTag,"SR_highBTags");
  SR_highBTags.addProcessor(&SRhighBTags,1);

  // 2higgs tag
  binCut SR2higgsCut(ntuple,"SR_2higgs");
  SR2higgsCut.minHiggsTags=2; SR2higgsCut.maxHiggsTags=2;
  signalRegion SR_2higgs(ntuple,sampleTag,"SR_2higgs");
  SR_2higgs.addProcessor(&SR2higgsCut,1);
  */

  signalRegion SR(ntuple,sampleTag);


  for( int i = 0 ; i < t->GetEntries() ; i++ ){

    t->GetEntry(i);
    if( i % 10000 == 0 ) 
      cout << "event: " << i << endl;
    ntuple->patchJetID();

    SR.analyze();
    SR_higgs.analyze();
    SR_Vtag.analyze();
    /*
    SR_highBTags.analyze();
    SR_2higgs.analyze();
    SR_Vtag.analyze();
    */

  }

  cout << "save tree" << endl;

  TFile* outFile = new TFile("fullAnalysis_"+fileTag+".root","RECREATE");
  
  SR.postProcess();
  SR_higgs.postProcess();
  SR_Vtag.postProcess();
  /*
  SR_highBTags.postProcess();
  SRhiggsCut.postProcess();
  SR_2higgs.postProcess();
  SR_Vtag.postProcess();
  SRVtagCut.postProcess();
  */

  outFile->Close();
  
  delete ntuple;

}  

