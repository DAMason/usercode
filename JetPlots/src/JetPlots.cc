// JetPlots.cc
// Description: Making some simple plots 
// Based on JetPlotsExample.cc
// by Robert M. Harris
// Date:  28 - August - 2006
// 

// D. Mason tweaks starting in Feb '07

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Handle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DQMServices/Core/interface/DaqMonitorBEInterface.h"
#include "DQMServices/Daemon/interface/MonitorDaemon.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "SimDataFormats/HepMCProduct/interface/HepMCProduct.h"

#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <map>
#include "RecoJets/JetPlots/interface/JetPlots.h"
using namespace edm;
using namespace reco;
using namespace std;

// Get the algorithm of the jet collections we will read from the .cfg file 
// which defines the value of the strings CaloJetAlgorithm and GenJetAlgorithm.
JetPlots::JetPlots( const ParameterSet & cfg ) :
  CaloJetAlgorithm( cfg.getParameter<string>( "CaloJetAlgorithm" ) ), 
  GenJetAlgorithm( cfg.getParameter<string>( "GenJetAlgorithm" ) ),
  CorJetAlgorithm( cfg.getParameter<string>( "CorJetAlgorithm") )
  {
  }

void JetPlots::beginJob( const EventSetup & ) {

for (int ii=0;ii<21;ii++) {
     BinIsBooked[ii]=false;
}


// Hook into DQM interface...

dbe_=0;

//dbe_=edm::Service<DaqMonitorBEInterface>().operator->();
  dbe_ = Service<DaqMonitorBEInterface>().operator->();

  //We put this here for the moment since there is no better place 
  //edm::Service<MonitorDaemon> daemon;
  //daemon.operator->();


if (dbe_) {
    dbe_->setCurrentFolder("JetPlots");

    //    for (int i=1;i<21;i++) {
    // sprintf (histoname,"ptHatAllBinned%i",i);
    // me_binned_ptHatAll[i]=dbe_->book1D( histoname,  "p_{T}hat for process", 80, 0, 8000 );
    //}

    // if (me_binned_ptHatAll.count(3)==0) {
    //  cout << "me_binned_ptHatAll[3] is being booked" << endl;
    //  bookBinnedMEs(3);
    // } else if (me_binned_ptHatAll.count(3)>1) {
    //   cout << "me_binned_ptHatAll[3] has more than one key" << endl;
    // }


  }
}

void JetPlots::bookBinnedMEs(int binNum) {
  
 char histoname[37] = "";

 sprintf (histoname,"ptHatAllBin%i",binNum);
 me_ptHatAll[binNum]=dbe_->book1D( histoname,  "p_{T}hat for process", 100, 0, 5000 );

 sprintf (histoname,"ptHatLowBin%i",binNum);
 me_ptHatLow[binNum]=dbe_->book1D( histoname,  "p_{T}hat for process (Lower p_{T}", 200, 0, 1000 );


 sprintf (histoname,"ptGenAllBin%i",binNum);
 me_ptGenAll[binNum]=dbe_->book1D( histoname,  "p_{T} for leading genjets", 100, 0, 5000 );


 sprintf (histoname,"ptGenLowBin%i",binNum);
 me_ptGenLow[binNum] = dbe_->book1D( histoname,  "p_{T} for leading genjets (Lower p_{T})", 200, 0, 1000 );


 sprintf (histoname,"etaGenBin%i",binNum);
 me_etaGen[binNum]=dbe_->book1D(histoname, "#eta of leading GenJets", 100, -5, 5 );
 
 sprintf (histoname,"etaGenLowptBin%i",binNum);
 me_etaGenLowpt[binNum]=dbe_->book1D( histoname, "#eta of Low p_{T} leading GenJets", 100, -5, 5 );

 
 sprintf (histoname,"phiGenBin%i",binNum);
 me_phiGen[binNum]=dbe_->book1D( histoname, "#phi of leading GenJets", 60, -M_PI, M_PI );


 sprintf (histoname,"ptGenAllEtaBBin%i",binNum);
 me_ptGenAllEtaB[binNum]=dbe_->book1D( histoname,  "p_{T} for leading genjets #eta<1", 100, 0, 5000 );


 sprintf (histoname,"ptGenLowEtaBBin%i",binNum);
 me_ptGenLowEtaB[binNum]=dbe_->book1D( histoname,  "p_{T} for leading genjets #eta<1 (Lower p_{T})", 200, 0, 1000 );
 

 sprintf (histoname,"ptGenAllEtaBEBin%i",binNum);
 me_ptGenAllEtaBE[binNum]=dbe_->book1D( histoname,  "p_{T} for leading genjets 1<#eta<1.5", 100, 0, 5000 );


 sprintf (histoname,"ptGenLowEtaBEBin%i",binNum);
 me_ptGenLowEtaBE[binNum]=dbe_->book1D( histoname,  "p_{T} for leading genjets 1<#eta<1.5 (Lower p_{T})", 200, 0, 1000 );

 sprintf (histoname,"ptGenAllEtaEBin%i",binNum);
 me_ptGenAllEtaE[binNum]=dbe_->book1D( histoname,  "p_{T} for leading genjets 1.5<#eta<2.5", 100, 0, 5000 );

 sprintf (histoname,"ptGenLowEtaEBin%i",binNum);
 me_ptGenLowEtaE[binNum]=dbe_->book1D( histoname,  "p_{T} for leading genjets 1.5<#eta<2.5 (Lower p_{T})", 200, 0, 1000 );

 sprintf (histoname,"ptGenAllEtaEFBin%i",binNum);
 me_ptGenAllEtaEF[binNum]=dbe_->book1D( histoname,  "p_{T} for leading genjets 2.5<#eta<3", 100, 0, 5000 );

 sprintf (histoname,"ptGenLowEtaEFBin%i",binNum);
 me_ptGenLowEtaEF[binNum]=dbe_->book1D( histoname,  "p_{T} for leading genjets 2.5<#eta<3 (Lower p_{T})", 200, 0, 1000 );

 sprintf (histoname,"ptGenAllEtaFBin%i",binNum);
 me_ptGenAllEtaF[binNum]=dbe_->book1D( histoname,  "p_{T} for leading genjets 3<#eta<5", 100, 0, 5000 );

 sprintf (histoname,"ptGenLowEtaFBin%i",binNum);
 me_ptGenLowEtaF[binNum]=dbe_->book1D( histoname,  "p_{T} for leading genjets 3<#eta<5 (Lower p_{T})", 200, 0, 1000 );

 sprintf (histoname,"GenDjMBin%i",binNum);
 me_GenDjM[binNum]=dbe_->book1D( histoname,  "Dijet Mass for leading genjets", 160, 0, 8000 );

 sprintf (histoname,"GenDjMEtaBBBin%i",binNum);
 me_GenDjMEtaBB[binNum]=dbe_->book1D( histoname,  "Dijet Mass for leading barrel genjets", 160, 0, 8000 );

 sprintf (histoname,"2DGenEtaEtaBBBin%i",binNum);
 me_GenEtaEtaBB[binNum]=dbe_->book2D( histoname, "#eta vs #eta for leading barrel jets",200,-1.0,1.0,200,-1.0,1.0);

 sprintf (histoname,"2DGenEtaEtaBin%i",binNum);
 me_GenEtaEta[binNum]=dbe_->book2D( histoname, "#eta vs #eta for leading jets",200,-5.0,5.0,200,-5.0,5.0);

 sprintf (histoname,"2DGenPtPtBin%i",binNum);
 me_GenPtPt[binNum]=dbe_->book2D( histoname, "p_{T} vs p_{T} for leading jets",100,0,5000,100,0,5000);

 sprintf (histoname,"2DGenPtPtBBBin%i",binNum);
 me_GenPtPtBB[binNum]=dbe_->book2D( histoname, "p_{T} vs p_{T} for leading barrel jets",100,0,5000,100,0,5000);


// sprintf (histoname,"nGenJetsBin%i",binNum);
// me_nGenJets[binNum]=dbe_->book1D( histoname,  "Number of genJets", 20, 0, 20 );

 sprintf (histoname,"ptCalAllBin%i",binNum);
 me_ptCalAll[binNum]=dbe_->book1D( histoname,  "p_{T} for leading calojets", 100, 0, 5000 );

 sprintf (histoname,"ptCalLowBin%i",binNum);
 me_ptCalLow[binNum]=dbe_->book1D( histoname,  "p_{T} for leading calojets", 200, 0, 1000 );


 sprintf (histoname,"ptCalAllEtaBBin%i",binNum);
 me_ptCalAllEtaB[binNum]=dbe_->book1D( histoname,  "p_{T} for leading calojets #eta<1", 100, 0, 5000 );

 sprintf (histoname,"ptCalLowEtaBBin%i",binNum);
 me_ptCalLowEtaB[binNum]=dbe_->book1D( histoname,  "p_{T} for leading calojets #eta<1 (Lower p_{T})", 200, 0, 1000 );

 sprintf (histoname,"ptCalAllEtaBEBin%i",binNum);
 me_ptCalAllEtaBE[binNum]=dbe_->book1D( histoname,  "p_{T} for leading calojets 1<#eta<1.5", 100, 0, 5000 );

 sprintf (histoname,"ptCalLowEtaBEBin%i",binNum);
 me_ptCalLowEtaBE[binNum]=dbe_->book1D( histoname,  "p_{T} for leading calojets 1<#eta<1.5 (Lower p_{T})", 200, 0, 1000 );

 sprintf (histoname,"ptCalAllEtaEBin%i",binNum);
 me_ptCalAllEtaE[binNum]=dbe_->book1D( histoname,  "p_{T} for leading calojets 1.5<#eta<2.5", 100, 0, 5000 );

 sprintf (histoname,"ptCalLowEtaEBin%i",binNum);
 me_ptCalLowEtaE[binNum]=dbe_->book1D( histoname,  "p_{T} for leading calojets 1.5<#eta<2.5 (Lower p_{T})", 200, 0, 1000 );

 sprintf (histoname,"ptCalAllEtaEFBin%i",binNum);
 me_ptCalAllEtaEF[binNum]=dbe_->book1D( histoname,  "p_{T} for leading calojets 2.5<#eta<3", 100, 0, 5000 );

 sprintf (histoname,"ptCalLowEtaEFBin%i",binNum);
 me_ptCalLowEtaEF[binNum]=dbe_->book1D( histoname,  "p_{T} for leading calojets 2.5<#eta<3 (Lower p_{T})", 200, 0, 1000 );

 sprintf (histoname,"ptCalAllEtaFBin%i",binNum);
 me_ptCalAllEtaF[binNum]=dbe_->book1D( histoname,  "p_{T} for leading calojets 3<#eta<5", 100, 0, 5000 );

 sprintf (histoname,"ptCalLowEtaFBin%i",binNum);
 me_ptCalLowEtaF[binNum]=dbe_->book1D( histoname,  "p_{T} for leading calojets 3<#eta<5 (Lower p_{T})", 200, 0, 1000 );

 sprintf (histoname,"CalDjMBin%i",binNum);
 me_CalDjM[binNum]=dbe_->book1D( histoname,  "Dijet Mass for leading calojets", 160, 0, 8000 );

 sprintf (histoname,"CalDjMEtaBBBin%i",binNum);
 me_CalDjMEtaBB[binNum]=dbe_->book1D( histoname,  "Dijet Mass for leading barrel calojets", 160, 0, 8000 );

 sprintf (histoname,"2DCalEtaEtaBBBin%i",binNum);
 me_CalEtaEtaBB[binNum]=dbe_->book2D( histoname, "#eta vs #eta for leading barrel calojets",200,-1.0,1.0,200,-1.0,1.0);

 sprintf (histoname,"2DCalEtaEtaBin%i",binNum);
 me_CalEtaEta[binNum]=dbe_->book2D( histoname, "#eta vs #eta for leading calojets",200,-5.0,5.0,200,-5.0,5.0);

 sprintf (histoname,"2DCalPtPtBin%i",binNum);
 me_CalPtPt[binNum]=dbe_->book2D( histoname, "p_{T} vs p_{T} for leading calojets",100 ,0,5000,100,0,5000);

 sprintf (histoname,"2DCalPtPtBBBin%i",binNum);
 me_CalPtPtBB[binNum]=dbe_->book2D( histoname, "p_{T} vs p_{T} for leading barrel calojets",100,0,5000,100,0,5000);


 sprintf (histoname,"ptCorAllBin%i",binNum);
 me_ptCorAll[binNum]=dbe_->book1D( histoname,  "p_{T} for corrected leading calojets", 100, 0, 5000 );

 sprintf (histoname,"ptCorLowBin%i",binNum);
 me_ptCorLow[binNum]=dbe_->book1D( histoname,  "p_{T} for corrected leading calojets", 200, 0, 1000 );


 sprintf (histoname,"ptCorAllEtaBBin%i",binNum);
 me_ptCorAllEtaB[binNum]=dbe_->book1D( histoname,  "p_{T} for corrected leading calojets #eta<1", 100, 0, 5000 );

 sprintf (histoname,"ptCorLowEtaBBin%i",binNum);
 me_ptCorLowEtaB[binNum]=dbe_->book1D( histoname,  "p_{T} for corrected leading calojets #eta<1 (Lower p_{T})", 200, 0, 1000 );

 sprintf (histoname,"ptCorAllEtaBEBin%i",binNum);
 me_ptCorAllEtaBE[binNum]=dbe_->book1D( histoname,  "p_{T} for corrected leading calojets 1<#eta<1.5", 100, 0, 5000 );

 sprintf (histoname,"ptCorLowEtaBEBin%i",binNum);
 me_ptCorLowEtaBE[binNum]=dbe_->book1D( histoname,  "p_{T} for corrected leading calojets 1<#eta<1.5 (Lower p_{T})", 200, 0, 1000 );

 sprintf (histoname,"ptCorAllEtaEBin%i",binNum);
 me_ptCorAllEtaE[binNum]=dbe_->book1D( histoname,  "p_{T} for corrected leading calojets 1.5<#eta<2.5", 100, 0, 5000 );

 sprintf (histoname,"ptCorLowEtaEBin%i",binNum);
 me_ptCorLowEtaE[binNum]=dbe_->book1D( histoname,  "p_{T} for corrected leading calojets 1.5<#eta<2.5 (Lower p_{T})", 200, 0, 1000 );

 sprintf (histoname,"ptCorAllEtaEFBin%i",binNum);
 me_ptCorAllEtaEF[binNum]=dbe_->book1D( histoname,  "p_{T} for corrected leading calojets 2.5<#eta<3", 100, 0, 5000 );

 sprintf (histoname,"ptCorLowEtaEFBin%i",binNum);
 me_ptCorLowEtaEF[binNum]=dbe_->book1D( histoname,  "p_{T} for corrected leading calojets 2.5<#eta<3 (Lower p_{T})", 200, 0, 1000 );

 sprintf (histoname,"ptCorAllEtaFBin%i",binNum);
 me_ptCorAllEtaF[binNum]=dbe_->book1D( histoname,  "p_{T} for corrected leading calojets 3<#eta<5", 100, 0, 5000 );

 sprintf (histoname,"ptCorLowEtaFBin%i",binNum);
 me_ptCorLowEtaF[binNum]=dbe_->book1D( histoname,  "p_{T} for corrected leading calojets 3<#eta<5 (Lower p_{T})", 200, 0, 1000 );

 sprintf (histoname,"CorDjMBin%i",binNum);
 me_CorDjM[binNum]=dbe_->book1D( histoname,  "Dijet Mass for leading corrected calojets", 160, 0, 8000 );

 sprintf (histoname,"CorDjMEtaBBBin%i",binNum);
 me_CorDjMEtaBB[binNum]=dbe_->book1D( histoname,  "Dijet Mass for leading corrected barrel calojets", 160, 0, 8000 );

 sprintf (histoname,"2DCorEtaEtaBBBin%i",binNum);
 me_CorEtaEtaBB[binNum]=dbe_->book2D( histoname, "#eta vs #eta for leading corrected barrel calojets",200,-1.0,1.0,200,-1.0,1.0);
 
 sprintf (histoname,"2DCorEtaEtaBin%i",binNum);
 me_CorEtaEta[binNum]=dbe_->book2D( histoname, "#eta vs #eta for leading corrected calojets",200,-5.0,5.0,200,-5.0,5.0);
 
 sprintf (histoname,"2DCorPtPtBin%i",binNum);
 me_CorPtPt[binNum]=dbe_->book2D( histoname, "p_{T} vs p_{T} for leading corrected calojets",100 ,0,5000,100,0,5000);
 
 sprintf (histoname,"2DCorPtPtBBBin%i",binNum);
 me_CorPtPtBB[binNum]=dbe_->book2D( histoname, "p_{T} vs p_{T} for leading corrected barrel calojets",100,0,5000,100,0,5000);


// sprintf (histoname,"nCoroJetsBin%i",binNum);
// me_nCoroJets[binNum]=dbe_->book1D( histoname,  "Number of caloJets", 20, 0, 20 );
}


void JetPlots::analyze( const Event& evt, const EventSetup& es) {


  float PtLowEdge[21]={0,15,20,30,50,80,120,170,230,300,380,470,600,800,1000,1400,1800,2200,2600,3000,3500};
  float PtHiEdge[21]={15,20,30,50,80,120,170,230,300,380,470,600,800,1000,1400,1800,2200,2600,3000,3500,14000};
  float BinXsec[21]={5.52E+01,1.46E+00,6.32E-01,1.63E-01,2.16E-02,3.08E-03,4.94E-04,1.01E-04,2.45E-05,6.24E-06,1.78E-06,6.83E-07,2.04E-07,3.51E-08,1.09E-08,1.06E-09,1.45E-10,2.38E-11,4.29E-12,8.44E-13,1.08E-13};

  int CurrPtBin=0;
  float BinWt=0.;



  //Get HepMC stuff

    Handle<HepMCProduct> mcTruth;
    // VtxSmeared is the case for the 120 onsel datasets -- found by browsing in root and seeing
    // edmHepMCProduct_VtxSmeared  where VtxSmeared appears to have been the source name, edmHepMCProduct
    // the type

    evt.getByLabel("VtxSmeared" ,mcTruth);

  HepMC::GenEvent * myGenEvent = new HepMC::GenEvent(*(mcTruth->GetEvent()));

  //int procid= myGenEvent->signal_process_id();
  double evtscale = myGenEvent->event_scale();

  //std::cout<<"ProcessID was "<<procid<<" and scale was "<<evtscale<<" GeV "<<endl;


  for (int j=0;j<21;j++) {
    if (evtscale>PtLowEdge[j]&&evtscale<=PtHiEdge[j]) {
      CurrPtBin=j;
      BinWt=BinXsec[j];
    }
  }

  if (!BinIsBooked[CurrPtBin]){
    bookBinnedMEs(CurrPtBin);
    BinIsBooked[CurrPtBin]=true;
      }

  if (me_ptHatAll[CurrPtBin]) me_ptHatAll[CurrPtBin]->Fill(evtscale,BinWt);   
  if (me_ptHatLow[CurrPtBin]) me_ptHatLow[CurrPtBin]->Fill(evtscale,BinWt);   







  //Get the GenJet collection
  Handle<GenJetCollection> genJets;
  evt.getByLabel( GenJetAlgorithm, genJets );

  //Loop over the two leading GenJets and fill some histograms
  int jetInd = 0;
  math::XYZTLorentzVector p4gen[2];
  for( GenJetCollection::const_iterator gen = genJets->begin(); gen != genJets->end() && jetInd<2; ++ gen ) {

    p4gen[jetInd]=gen->p4();

    if (me_ptGenAll[CurrPtBin]) me_ptGenAll[CurrPtBin]->Fill( gen->pt(),BinWt );  
    if (me_ptGenLow[CurrPtBin]) me_ptGenLow[CurrPtBin]->Fill( gen->pt(),BinWt ); 

    
    if (abs(gen->eta())<1) {
           if (me_ptGenAllEtaB[CurrPtBin]) me_ptGenAllEtaB[CurrPtBin]->Fill( gen->pt(),BinWt );  
           if (me_ptGenLowEtaB[CurrPtBin]) me_ptGenLowEtaB[CurrPtBin]->Fill( gen->pt(),BinWt ); 
    }
    if (abs(gen->eta())>=1&&abs(gen->eta())<1.5) {
           if (me_ptGenAllEtaBE[CurrPtBin]) me_ptGenAllEtaBE[CurrPtBin]->Fill( gen->pt(),BinWt );  
           if (me_ptGenLowEtaBE[CurrPtBin]) me_ptGenLowEtaBE[CurrPtBin]->Fill( gen->pt(),BinWt ); 
    }
    if (abs(gen->eta())>=1.5&&abs(gen->eta())<2.5) {
           if (me_ptGenAllEtaE[CurrPtBin]) me_ptGenAllEtaE[CurrPtBin]->Fill( gen->pt(),BinWt );  
           if (me_ptGenLowEtaE[CurrPtBin]) me_ptGenLowEtaE[CurrPtBin]->Fill( gen->pt(),BinWt ); 
    }
    if (abs(gen->eta())>=2.5&&abs(gen->eta())<3) {
           if (me_ptGenAllEtaEF[CurrPtBin]) me_ptGenAllEtaEF[CurrPtBin]->Fill( gen->pt(),BinWt );  
           if (me_ptGenAllEtaEF[CurrPtBin]) me_ptGenLowEtaEF[CurrPtBin]->Fill( gen->pt(),BinWt ); 
    }
    if (abs(gen->eta())>=3&&abs(gen->eta())<5) {
           if (me_ptGenAllEtaF[CurrPtBin]) me_ptGenAllEtaF[CurrPtBin]->Fill( gen->pt(),BinWt );  
           if (me_ptGenLowEtaF[CurrPtBin]) me_ptGenLowEtaF[CurrPtBin]->Fill( gen->pt(),BinWt ); 
    }

    

    if (me_etaGen[CurrPtBin]) me_etaGen[CurrPtBin]->Fill( gen->eta(),BinWt );
    if (gen->pt()<1000) {
      if (me_etaGenLowpt[CurrPtBin]) me_etaGenLowpt[CurrPtBin]->Fill(gen->eta(),BinWt);
    }
    if (me_phiGen[CurrPtBin]) me_phiGen[CurrPtBin]->Fill( gen->phi(),BinWt );
    jetInd++;
  }

  if (me_GenDjM[CurrPtBin]) me_GenDjM[CurrPtBin]->Fill((p4gen[0]+p4gen[1]).mass(),BinWt);

  if (me_GenEtaEta[CurrPtBin]) me_GenEtaEta[CurrPtBin]->Fill(p4gen[0].eta(),p4gen[1].eta());

  if (me_GenPtPt[CurrPtBin]) me_GenPtPt[CurrPtBin]->Fill(p4gen[0].pt(),p4gen[1].pt());

  if (abs(p4gen[1].eta())<=1.0 && abs(p4gen[2].eta())<1.0) {

    if (me_GenDjMEtaBB[CurrPtBin]) me_GenDjMEtaBB[CurrPtBin]->Fill((p4gen[0]+p4gen[1]).mass(),BinWt);

    if (me_GenEtaEtaBB[CurrPtBin]) me_GenEtaEtaBB[CurrPtBin]->Fill(p4gen[0].eta(),p4gen[1].eta());

    if (me_GenPtPtBB[CurrPtBin]) me_GenPtPtBB[CurrPtBin]->Fill(p4gen[0].pt(),p4gen[1].pt());

   }

  //Get the CaloJet collection
  Handle<CaloJetCollection> caloJets;
  math::XYZTLorentzVector p4cal[2];
  evt.getByLabel( CaloJetAlgorithm, caloJets );

  //Loop over the two leading CaloJets and fill some histograms
  jetInd = 0;
  for( CaloJetCollection::const_iterator cal = caloJets->begin(); cal != caloJets->end() && jetInd<2; ++ cal ) {

    p4cal[jetInd]=cal->p4();

    if (me_ptCalAll[CurrPtBin]) me_ptCalAll[CurrPtBin]->Fill( cal->pt(),BinWt );   
    if (me_ptCalLow[CurrPtBin]) me_ptCalLow[CurrPtBin]->Fill( cal->pt(),BinWt );

    if (abs(cal->eta())<1) {
           if (me_ptCalAllEtaB[CurrPtBin]) me_ptCalAllEtaB[CurrPtBin]->Fill( cal->pt(),BinWt );  
           if (me_ptCalLowEtaB[CurrPtBin]) me_ptCalLowEtaB[CurrPtBin]->Fill( cal->pt(),BinWt ); 
    }
    if (abs(cal->eta())>=1&&abs(cal->eta())<1.5) {
           if (me_ptCalAllEtaBE[CurrPtBin]) me_ptCalAllEtaBE[CurrPtBin]->Fill( cal->pt(),BinWt );  
           if (me_ptCalLowEtaBE[CurrPtBin]) me_ptCalLowEtaBE[CurrPtBin]->Fill( cal->pt(),BinWt ); 
    }
    if (abs(cal->eta())>=1.5&&abs(cal->eta())<2.5) {
           if (me_ptCalAllEtaE[CurrPtBin]) me_ptCalAllEtaE[CurrPtBin]->Fill( cal->pt(),BinWt );  
           if (me_ptCalLowEtaE[CurrPtBin]) me_ptCalLowEtaE[CurrPtBin]->Fill( cal->pt(),BinWt ); 
    }
    if (abs(cal->eta())>=2.5&&abs(cal->eta())<3) {
           if (me_ptCalAllEtaEF[CurrPtBin]) me_ptCalAllEtaEF[CurrPtBin]->Fill( cal->pt(),BinWt );  
           if (me_ptCalAllEtaEF[CurrPtBin]) me_ptCalLowEtaEF[CurrPtBin]->Fill( cal->pt(),BinWt ); 
    }
    if (abs(cal->eta())>=3&&abs(cal->eta())<5) {
           if (me_ptCalAllEtaF[CurrPtBin]) me_ptCalAllEtaF[CurrPtBin]->Fill( cal->pt(),BinWt );  
           if (me_ptCalLowEtaF[CurrPtBin]) me_ptCalLowEtaF[CurrPtBin]->Fill( cal->pt(),BinWt ); 
    }

    jetInd++;
  }


  if (me_CalDjM[CurrPtBin]) me_CalDjM[CurrPtBin]->Fill((p4cal[0]+p4cal[1]).mass(),BinWt);

  if (me_CalEtaEta[CurrPtBin]) me_CalEtaEta[CurrPtBin]->Fill(p4cal[0].eta(),p4cal[1].eta());

  if (me_CalPtPt[CurrPtBin]) me_CalPtPt[CurrPtBin]->Fill(p4cal[0].pt(),p4cal[1].pt());

  if (abs(p4cal[1].eta())<=1.0 && abs(p4cal[2].eta())<=1.0) {

    if (me_CalDjMEtaBB[CurrPtBin]) me_CalDjMEtaBB[CurrPtBin]->Fill((p4cal[0]+p4cal[1]).mass(),BinWt);

    if (me_CalEtaEtaBB[CurrPtBin]) me_CalEtaEtaBB[CurrPtBin]->Fill(p4cal[0].eta(),p4cal[1].eta());

    if (me_CalPtPtBB[CurrPtBin]) me_CalPtPtBB[CurrPtBin]->Fill(p4cal[0].pt(),p4cal[1].pt());

   }



  //Get the CaloJet collection
  Handle<CaloJetCollection> corJets;
  math::XYZTLorentzVector p4cor[2];
  evt.getByLabel( CorJetAlgorithm, corJets );


  //Loop over the two leading CorJets and fill a histogram
  jetInd = 0;
  for( CaloJetCollection::const_iterator cor = corJets->begin(); cor != corJets->end() && jetInd<2; ++ cor ) {
    
    p4cor[jetInd]=cor->p4();
    if (me_ptCorAll[CurrPtBin]) me_ptCorAll[CurrPtBin]->Fill( cor->pt(),BinWt );   
    if (me_ptCorLow[CurrPtBin]) me_ptCorLow[CurrPtBin]->Fill( cor->pt(),BinWt );

    if (abs(cor->eta())<1) {
           if (me_ptCorAllEtaB[CurrPtBin]) me_ptCorAllEtaB[CurrPtBin]->Fill( cor->pt(),BinWt );  
           if (me_ptCorLowEtaB[CurrPtBin]) me_ptCorLowEtaB[CurrPtBin]->Fill( cor->pt(),BinWt ); 
    }
    if (abs(cor->eta())>=1&&abs(cor->eta())<1.5) {
           if (me_ptCorAllEtaBE[CurrPtBin]) me_ptCorAllEtaBE[CurrPtBin]->Fill( cor->pt(),BinWt );  
           if (me_ptCorLowEtaBE[CurrPtBin]) me_ptCorLowEtaBE[CurrPtBin]->Fill( cor->pt(),BinWt ); 
    }
    if (abs(cor->eta())>=1.5&&abs(cor->eta())<2.5) {
           if (me_ptCorAllEtaE[CurrPtBin]) me_ptCorAllEtaE[CurrPtBin]->Fill( cor->pt(),BinWt );  
           if (me_ptCorLowEtaE[CurrPtBin]) me_ptCorLowEtaE[CurrPtBin]->Fill( cor->pt(),BinWt ); 
    }
    if (abs(cor->eta())>=2.5&&abs(cor->eta())<3) {
           if (me_ptCorAllEtaEF[CurrPtBin]) me_ptCorAllEtaEF[CurrPtBin]->Fill( cor->pt(),BinWt );  
           if (me_ptCorAllEtaEF[CurrPtBin]) me_ptCorLowEtaEF[CurrPtBin]->Fill( cor->pt(),BinWt ); 
    }
    if (abs(cor->eta())>=3&&abs(cor->eta())<5) {
           if (me_ptCorAllEtaF[CurrPtBin]) me_ptCorAllEtaF[CurrPtBin]->Fill( cor->pt(),BinWt );  
           if (me_ptCorLowEtaF[CurrPtBin]) me_ptCorLowEtaF[CurrPtBin]->Fill( cor->pt(),BinWt ); 
    }
   
    jetInd++;
  }



if (me_CorDjM[CurrPtBin]) me_CorDjM[CurrPtBin]->Fill((p4cor[0]+p4cor[1]).mass(),BinWt);

  if (me_CorEtaEta[CurrPtBin]) me_CorEtaEta[CurrPtBin]->Fill(p4cor[0].eta(),p4cor[1].eta());
 
  if (me_CorPtPt[CurrPtBin]) me_CorPtPt[CurrPtBin]->Fill(p4cor[0].pt(),p4cor[1].pt());

  if (abs(p4cor[1].eta())<=1.0 && abs(p4cor[2].eta())<=1.0) {

    if (me_CorDjMEtaBB[CurrPtBin]) me_CorDjMEtaBB[CurrPtBin]->Fill((p4cor[0]+p4cor[1]).mass(),BinWt);

    if (me_CorEtaEtaBB[CurrPtBin]) me_CorEtaEtaBB[CurrPtBin]->Fill(p4cor[0].eta(),p4cor[1].eta());

    if (me_CorPtPtBB[CurrPtBin]) me_CorPtPtBB[CurrPtBin]->Fill(p4cor[0].pt(),p4cor[1].pt());

   } 

usleep(100000);

}

void JetPlots::endJob() {

  //Write out the histogram file.
  //m_file->Write(); 

  dbe_->save("JetPlots.root");

}
