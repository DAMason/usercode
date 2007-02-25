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
#include <map>
#include "RecoJets/JetPlots/interface/JetPlots.h"
using namespace edm;
using namespace reco;
using namespace std;

// Get the algorithm of the jet collections we will read from the .cfg file 
// which defines the value of the strings CaloJetAlgorithm and GenJetAlgorithm.
JetPlots::JetPlots( const ParameterSet & cfg ) :
  CaloJetAlgorithm( cfg.getParameter<string>( "CaloJetAlgorithm" ) ), 
  GenJetAlgorithm( cfg.getParameter<string>( "GenJetAlgorithm" ) )
  {
}

void JetPlots::beginJob( const EventSetup & ) {

// Hook into DQM interface...

dbe_=0;

//dbe_=edm::Service<DaqMonitorBEInterface>().operator->();
  dbe_ = Service<DaqMonitorBEInterface>().operator->();

  //We put this here for the moment since there is no better place 
  //edm::Service<MonitorDaemon> daemon;
  //daemon.operator->();





me_ptHatAll=0;
me_ptHatLow=0;

if (dbe_) {
    dbe_->setCurrentFolder("JetPlots");
    me_ptHatAll=dbe_->book1D( "ptHatAll",  "p_{T}hat for process", 80, 0, 8000 );
    me_ptHatLow = dbe_->book1D( "ptHatLow",  "p_{T}hat for process (Lower p_{T})", 200, 0, 1000 );
    me_ptGenAll=dbe_->book1D( "ptGenAll",  "p_{T} for leading genjets", 80, 0, 8000 );
    me_ptGenLow = dbe_->book1D( "ptGenLow",  "p_{T} for leading genjets (Lower p_{T})", 200, 0, 1000 );
    me_ptGenAllEtaB=dbe_->book1D( "ptGenAllEtaB",  "p_{T} for leadkng genjets #eta<1", 80, 0, 8000 );
    me_ptGenLowEtaB=dbe_->book1D( "ptGenLowEtaB",  "p_{T} for leading genjets #eta<1 (Lower p_{T})", 200, 0, 1000 );
    me_ptGenAllEtaBE=dbe_->book1D( "ptGenAllEtaBE",  "p_{T} for leading genjets 1<#eta<1.5", 80, 0, 8000 );
    me_ptGenLowEtaBE=dbe_->book1D( "ptGenLowEtaBE",  "p_{T} for leading genjets 1<#eta<1.5 (Lower p_{T})", 200, 0, 1000 );
    me_ptGenAllEtaE=dbe_->book1D( "ptGenAllEtaE",  "p_{T} for leading genjets 1.5<#eta<2.5", 80, 0, 8000 );
    me_ptGenLowEtaE=dbe_->book1D( "ptGenLowEtaE",  "p_{T} for leading genjets 1.5<#eta<2.5 (Lower p_{T})", 200, 0, 1000 );
    me_ptGenAllEtaEF=dbe_->book1D( "ptGenAllEtaEF",  "p_{T} for leading genjets 2.5<#eta<3", 80, 0, 8000 );
    me_ptGenLowEtaEF=dbe_->book1D( "ptGenLowEtaEF",  "p_{T} for leading genjets 2.5<#eta<3 (Lower p_{T})", 200, 0, 1000 );
    me_ptGenAllEtaF=dbe_->book1D( "ptGenAllEtaF",  "p_{T} for leading genjets 3<#eta<5", 80, 0, 8000 );
    me_ptGenLowEtaF=dbe_->book1D( "ptGenLowEtaF",  "p_{T} for leading genjets 3<#eta<5 (Lower p_{T})", 200, 0, 1000 );
    me_etaGen=dbe_->book1D( "etaGen", "#eta of leading GenJets", 100, -5, 5 );
    me_etaGenLowpt=dbe_->book1D( "etaGenLowpt", "#eta of Low p_{T} leading GenJets", 100, -5, 5 );
    me_phiGen=dbe_->book1D( "phiGen", "#phi of leading GenJets", 60, -M_PI, M_PI );
  }
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


  if (me_ptHatAll) me_ptHatAll->Fill(evtscale,BinWt);
  if (me_ptHatLow) me_ptHatLow->Fill(evtscale,BinWt);




  //Get the CaloJet collection
  Handle<CaloJetCollection> caloJets;
  evt.getByLabel( CaloJetAlgorithm, caloJets );

  //Loop over the two leading CaloJets and fill some histograms
  int jetInd = 0;
  for( CaloJetCollection::const_iterator cal = caloJets->begin(); cal != caloJets->end() && jetInd<2; ++ cal ) {
//    h_ptCal.Fill( cal->pt() );   
//    h_etaCal.Fill( cal->eta() );
//    h_phiCal.Fill( cal->phi() );
    jetInd++;
  }

  //Get the GenJet collection
  Handle<GenJetCollection> genJets;
  evt.getByLabel( GenJetAlgorithm, genJets );

  //Loop over the two leading GenJets and fill some histograms
  jetInd = 0;
  for( GenJetCollection::const_iterator gen = genJets->begin(); gen != genJets->end() && jetInd<2; ++ gen ) {
    if (me_ptGenAll) me_ptGenAll->Fill( gen->pt(),BinWt );  
    if (me_ptGenLow) me_ptGenLow->Fill( gen->pt(),BinWt ); 
    if (abs(gen->eta())<1) {
           if (me_ptGenAllEtaB) me_ptGenAllEtaB->Fill( gen->pt(),BinWt );  
           if (me_ptGenLowEtaB) me_ptGenLowEtaB->Fill( gen->pt(),BinWt ); 
    }
    if (abs(gen->eta())>=1&&abs(gen->eta())<1.5) {
           if (me_ptGenAllEtaBE) me_ptGenAllEtaBE->Fill( gen->pt(),BinWt );  
           if (me_ptGenLowEtaBE) me_ptGenLowEtaBE->Fill( gen->pt(),BinWt ); 
    }
    if (abs(gen->eta())>=1.5&&abs(gen->eta())<2.5) {
           if (me_ptGenAllEtaE) me_ptGenAllEtaE->Fill( gen->pt(),BinWt );  
           if (me_ptGenLowEtaE) me_ptGenLowEtaE->Fill( gen->pt(),BinWt ); 
    }
    if (abs(gen->eta())>=2.5&&abs(gen->eta())<3) {
           if (me_ptGenAllEtaEF) me_ptGenAllEtaEF->Fill( gen->pt(),BinWt );  
           if (me_ptGenAllEtaEF) me_ptGenLowEtaEF->Fill( gen->pt(),BinWt ); 
    }
    if (abs(gen->eta())>=3&&abs(gen->eta())<5) {
           if (me_ptGenAllEtaF) me_ptGenAllEtaF->Fill( gen->pt(),BinWt );  
           if (me_ptGenLowEtaF) me_ptGenLowEtaF->Fill( gen->pt(),BinWt ); 
    }

    if (me_etaGen) me_etaGen->Fill( gen->eta(),BinWt );
    if (gen->pt()<1000) {
      if (me_etaGenLowpt) me_etaGenLowpt->Fill(gen->eta(),BinWt);
    }
    if (me_phiGen) me_phiGen->Fill( gen->phi(),BinWt );
    jetInd++;
  }

usleep(100000);

}

void JetPlots::endJob() {

  //Write out the histogram file.
  //m_file->Write(); 

  dbe_->save("JetPlots.root");

}
