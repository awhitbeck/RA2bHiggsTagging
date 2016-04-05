#include "RA2bNtuple.cc"
#include "analyzer.cc"
#include "selectBaseline.cc"
#include "skim.cc"
#include "weightProducer.cc"
#include "fillHisto.cc"
#include "fillLeptonTruth.cc"
#include "fillRA2bHisto.cc"

#include "TString.h"
#include "TChain.h"
#include "TFile.h"

#include <cstdio>
#include <string>
#include <iostream>

#include "helpers.h"

using namespace std; 

/* 

   analyzer for plotting distributions in the full phase space of the
   signal region ...

 */

typedef fillHisto<RA2bNtuple> histo;

class signalRegion : public analyzer<RA2bNtuple> {

public :

  RA2bNtuple* ntuple;
  selectBaseline<RA2bNtuple> *selectBase;
  histo *HThisto;
  histo *MHThisto;
  histo *NJetshisto;
  histo *BTagshisto; 
  histo *DeltaPhi1histo;
  histo *DeltaPhi2histo;
  histo *DeltaPhi3histo;
  histo *DeltaPhi4histo;
  fillRA2bHisto<RA2bNtuple>* ra2bHisto;
  TString sampleTag, regionTag;

  signalRegion( RA2bNtuple* ntuple_ , TString sampleTag_ , TString regionTag_ = "SR" , 
		vector<processor<RA2bNtuple>* > *addSelectors = 0 )
    : analyzer<RA2bNtuple>(ntuple_,8){
    ntuple = ntuple_ ; 
    sampleTag = sampleTag_;
    regionTag = regionTag_;

    selectBase = new selectBaseline<RA2bNtuple>(ntuple,regionTag);

    HThisto = new histo(ntuple,40,500,4000,regionTag+"_"+sampleTag,"HT","Weight") ; 
    MHThisto = new histo(ntuple,40,000,1000,regionTag+"_"+sampleTag,"MHT","Weight")   ; 
    NJetshisto = new histo(ntuple,12,3.5,15.5,regionTag+"_"+sampleTag,"NJets","Weight") ;
    BTagshisto = new histo(ntuple,7,-0.5,6.5,regionTag+"_"+sampleTag,"BTags","Weight") ; 
    DeltaPhi1histo = new histo(ntuple,40,0.,3.2,regionTag+"_"+sampleTag,"DeltaPhi1","Weight");
    DeltaPhi2histo = new histo(ntuple,40,0.,3.2,regionTag+"_"+sampleTag,"DeltaPhi2","Weight");
    DeltaPhi3histo = new histo(ntuple,40,0.,3.2,regionTag+"_"+sampleTag,"DeltaPhi3","Weight");
    DeltaPhi4histo = new histo(ntuple,40,0.,3.2,regionTag+"_"+sampleTag,"DeltaPhi4","Weight");
    ra2bHisto = new fillRA2bHisto<RA2bNtuple>(ntuple,regionTag+"_"+sampleTag,"Weight");

    addProcessor(selectBase);

    if( addSelectors && addSelectors->size()>0){
      for( unsigned int s=0 ; s < addSelectors->size() ; s++ ){
	addProcessor(addSelectors->at(s));
      }
    }

    addProcessor(HThisto);
    addProcessor(MHThisto);
    addProcessor(NJetshisto);
    addProcessor(BTagshisto);
    addProcessor(DeltaPhi1histo);
    addProcessor(DeltaPhi2histo);
    addProcessor(DeltaPhi3histo);
    addProcessor(DeltaPhi4histo);
    addProcessor(ra2bHisto);

  };

  ~signalRegion(){

    delete selectBase;
    delete HThisto;
    delete MHThisto;
    delete NJetshisto;
    delete BTagshisto; 
    delete DeltaPhi1histo;
    delete DeltaPhi2histo;
    delete DeltaPhi3histo;
    delete DeltaPhi4histo;
    delete ra2bHisto;

  };

  void analyze(){
    
    for( unsigned int iProc = 0 ; iProc < processorList->size() ; iProc++){
      //cout << "SR proc: " << iProc << " " << processorList->at(iProc)->moduleName << endl;
      if( ! processorList->at(iProc)->process() ) break;
    }

  };

  void postProcess(){

    selectBase->histo->Write("signalRegionYields_"+sampleTag);

    HThisto->histo->Write();
    MHThisto->histo->Write();
    NJetshisto->histo->Write();
    BTagshisto->histo->Write();
    DeltaPhi1histo->histo->Write();
    DeltaPhi2histo->histo->Write();
    DeltaPhi3histo->histo->Write();
    DeltaPhi4histo->histo->Write();
    ra2bHisto->histo->Write();

  };

};
