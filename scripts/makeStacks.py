from ROOT import *
import stackPlots 
gROOT.SetBatch(True)

vars = ["HT","MHT","NJets","BTags","DeltaPhi1","DeltaPhi2","DeltaPhi3","DeltaPhi4"]
regions = ["SR",
          "SR_higgs",
           "SR_Vtag"
          ]

inputFile = TFile("fullAnalysis_all.root","READ")

for var in vars :
    for reg in regions : 
        stackPlots.plot(var+"_"+reg,inputFile)
    
