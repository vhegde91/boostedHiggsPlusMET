#include "TString.h"
#include "TChain.h"
#include "TH1F.h"
#include "TROOT.h"
#include "THStack.h"
#include "TPad.h"

#include <vector>
#include <map>
#include <iostream>

#include "plotterUtils.cc"
#include "skimSamples.cc"
#include "definitions.cc"
#include "RA2bTree.cc"

using namespace std;

int main(int argc, char** argv){

  gROOT->ProcessLine(".L ~/tdrstyle.C");
  gROOT->ProcessLine("setTDRStyle()");
  
  skimSamples skims("singleMuCR");
  typedef plot<RA2bTree> plot;

  plot METplot(*fillMET<RA2bTree>,"MET_singleMuCR_singleHiggsTag","MET [GeV]",15,300.,1800.);
  plot HTplot(*fillHT<RA2bTree>,"HT_singleMuCR_singleHiggsTag","H_{T} [GeV]",15,300,2800.);
  plot NJetsplot(*fillNJets<RA2bTree>,"NJets_singleMuCR_singleHiggsTag","n_{j}",14,1.5,15.5);
  plot BTagsplot(*fillBTags<RA2bTree>,"BTags_singleMuCR_singleHiggsTag","n_{b}",6,-0.5,5.5);
  plot Binsplot(*fillAnalysisBins<RA2bTree>,"AnalysisBins_singleMuCR_singleHiggsTag","i^th Bin",8,0.5,8.5);
  plot J1pt_Massplot(*fillLeadingJetMass<RA2bTree>,"J1pt_Mass_singleMuCR_singleHiggsTag","m_{J} [GeV]",20,50.,200.);
  plot J2pt_Massplot(*fillSubLeadingJetMass<RA2bTree>,"J2pt_Mass_singleMuCR_singleHiggsTag","m_{J} [GeV]",20,50.,200.);
  plot J1bbtag_Massplot(*fillLeadingBBtagJetMass<RA2bTree>,"J1bbtag_Mass_singleMuCR_singleHiggsTag","m_{J} [GeV]",20,50.,200.);
  plot J2bbtag_Massplot(*fillSubLeadingBBtagJetMass<RA2bTree>,"J2bbtag_Mass_singleMuCR_singleHiggsTag","m_{J} [GeV]",20,50.,200.);

  plot J1pt_BBplot(*fillLeadingBBtag<RA2bTree>,"J1pt_BBtag_singleMuCR_singleHiggsTag","bb-tag",20,-1.,1.);
  plot J2pt_BBplot(*fillSubLeadingBBtag<RA2bTree>,"J2pt_BBtag_singleMuCR_singleHiggsTag","bb-tag",20,-1.,1.);
  plot J1bbtag_BBplot(*fillLeadingBBtagJetBBtag<RA2bTree>,"J1bbtag_BBtag_singleMuCR_singleHiggsTag","bb-tag",20,-1.,1.);
  plot J2bbtag_BBplot(*fillSubLeadingBBtagJetBBtag<RA2bTree>,"J2bbtag_BBtag_singleMuCR_singleHiggsTag","bb-tag",20,-1.,1.);

  plot J1pt_Tau21plot(*fillLeadingTau21<RA2bTree>,"J1pt_Tau21_singleMuCR_singleHiggsTag","#tau_{21}",20,0.,1.);
  plot J2pt_Tau21plot(*fillSubLeadingTau21<RA2bTree>,"J2pt_Tau21_singleMuCR_singleHiggsTag","#tau_{21}",20,0.,1.);
  plot J1bbtag_Tau21plot(*fillLeadingBBtagJetTau21<RA2bTree>,"J1bbtag_Tau21_singleMuCR_singleHiggsTag","#tau_{21}",20,0.,1.);
  plot J2bbtag_Tau21plot(*fillSubLeadingBBtagJetTau21<RA2bTree>,"J2bbtag_Tau21_singleMuCR_singleHiggsTag","#tau_{21}",20,0.,1.);

  plot J1pt_Ptplot(*fillLeadingJetPt<RA2bTree>,"J1pt_Pt_singleMuCR_singleHiggsTag","p_{T,J} [GeV]",40,300.,2300.);
  plot J2pt_Ptplot(*fillSubLeadingJetPt<RA2bTree>,"J2pt_Pt_singleMuCR_singleHiggsTag","p_{T,J} [GeV]",40,300.,2300.);
  plot J1bbtag_Ptplot(*fillLeadingBBtagJetPt<RA2bTree>,"J1bbtag_Pt_singleMuCR_singleHiggsTag","p_{T,J} [GeV]",40,300.,2300.);
  plot J2bbtag_Ptplot(*fillSubLeadingBBtagJetPt<RA2bTree>,"J2bbtag_Pt_singleMuCR_singleHiggsTag","p_{T,J} [GeV]",40,300.,2300.);

  plot J1pt_JetFlavorPlot(*fillLeadingJetFlavor<RA2bTree>,"J1pt_JetFlavorPlot","Jet Flavor",22,0.5,21.5);
  plot J2pt_JetFlavorPlot(*fillSubLeadingJetFlavor<RA2bTree>,"J2pt_JetFlavorPlot","Jet Flavor",22,0.5,21.5);

  vector<plot> plots;
  plots.push_back(METplot);
  plots.push_back(HTplot);
  plots.push_back(NJetsplot);
  plots.push_back(BTagsplot);
  plots.push_back(Binsplot);
  plots.push_back(J1pt_Massplot);
  plots.push_back(J2pt_Massplot);
  plots.push_back(J1bbtag_Massplot);
  plots.push_back(J2bbtag_Massplot);
  plots.push_back(J1pt_BBplot);
  plots.push_back(J2pt_BBplot);
  plots.push_back(J1bbtag_BBplot);
  plots.push_back(J2bbtag_BBplot);
  plots.push_back(J1pt_Tau21plot);
  plots.push_back(J2pt_Tau21plot);
  plots.push_back(J1bbtag_Tau21plot);
  plots.push_back(J2bbtag_Tau21plot);
  plots.push_back(J1pt_Ptplot);
  plots.push_back(J2pt_Ptplot);
  plots.push_back(J1bbtag_Ptplot);
  plots.push_back(J2bbtag_Ptplot);
  plots.push_back(J1pt_JetFlavorPlot);
  plots.push_back(J2pt_JetFlavorPlot);

  // background MC samples
  for( int iSample = 0 ; iSample < skims.ntuples.size() ; iSample++){

    RA2bTree* ntuple = skims.ntuples[iSample];

    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
      plots[iPlot].addNtuple(ntuple,skims.sampleName[iSample]);
      plots[iPlot].setFillColor(ntuple,skims.fillColor[iSample]);
    }

    int numEvents = ntuple->fChain->GetEntries();
    for( int iEvt = 0 ; iEvt < numEvents ; iEvt++ ){
      ntuple->GetEntry(iEvt);
      if( iEvt % 1000000 == 0 ) cout << skims.sampleName[iSample] << ": " << iEvt << "/" << numEvents << endl;
      //if( iEvt > 100000 ) break;
      if(! baselineCut(ntuple) ) continue;
      if(! antiTaggingCut(ntuple) ) continue;
      for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++ ){
	plots[iPlot].fill(ntuple);
      }
    }
  }

  /*
  // Signal samples
  for( int iSample = 0 ; iSample < skims.signalNtuples.size() ; iSample++){

    RA2bTree* ntuple = skims.signalNtuples[iSample];
    for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
      plots[iPlot].addSignalNtuple(ntuple,skims.signalSampleName[iSample]);
      plots[iPlot].setLineColor(ntuple,skims.lineColor[iSample]);
    }

    int numEvents = ntuple->fChain->GetEntries();
    for( int iEvt = 0 ; iEvt < numEvents ; iEvt++ ){
      ntuple->GetEntry(iEvt);
      if( iEvt % 1000000 == 0 ) cout << skims.signalSampleName[iSample] << ": " << iEvt << "/" << numEvents << endl;
      if(! baselineCut(ntuple) ) continue;
      if(! taggingCut(ntuple) ) continue;
      //if(ntuple->nGenHiggsBoson!=2) continue;
      for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
	plots[iPlot].fillSignal(ntuple);
      }
    }
  }
  */

  TCanvas* can = new TCanvas("can","can",500,500);
  for( int iPlot = 0 ; iPlot < plots.size() ; iPlot++){
    plots[iPlot].Draw(can,skims.ntuples,skims.signalNtuples,"plotObs_singleMuCR_antitag_plots");
  }
}
