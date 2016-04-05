from ROOT import *

gROOT.ProcessLine(".L ~/tdrstyle.C")
gROOT.ProcessLine("setTDRStyle()")

file = TFile("testGeMET_SMS-T5Wg_mGl-1550_mNLSP-0to1500.root");
histos=[]
leg = TLegend(.6,.6,.9,.9)
leg.SetBorderSize(0)
leg.SetFillColor(0)

for i in range(15,0,-2) : 

    histos.append( file.Get("genMET_gluino1550GeV_NLSP{0}GeV".format(100+i*100)) )

    if histos[-1] == None : continue
    
    lineIndex = (i+1)/2

    histos[-1].SetLineWidth(2)
    histos[-1].SetLineColor(lineIndex%4+1)
    histos[-1].SetLineStyle(lineIndex/4+1)

    leg.AddEntry(histos[-1],"m_{NLSP}=%i GeV" % (100+i*100),"l")

    if i == 0 : 
        histos[-1].Draw()
    else : 
        histos[-1].Draw("SAME")

leg.Draw()
        
