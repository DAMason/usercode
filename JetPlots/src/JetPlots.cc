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
#include <TROOT.h>
#include <TSystem.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1.h>
#include <cmath>
#include <iostream>
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

  // Open the histogram file and book some associated histograms
  m_file=new TFile("histo.root","RECREATE"); 
  h_ptCal =  TH1F( "ptCal",  "p_{T} of leading CaloJets", 50, 0, 1000 );
  h_etaCal = TH1F( "etaCal", "#eta of leading CaloJets", 50, -3, 3 );
  h_phiCal = TH1F( "phiCal", "#phi of leading CaloJets", 50, -M_PI, M_PI );
  h_ptGenAll =  TH1F( "ptGenAll",  "p_{T} of leading GenJets", 80, 0, 8000 );
  h_ptGenLow =  TH1F( "ptGenLow",  "p_{T} of leading GenJets (Lower p_{T})", 200, 0, 1000 );
  h_ptGenAllEtaB = TH1F( "ptGenAllEtaB",  "p_{T} of All leading GenJets, #eta<1", 80, 0, 8000 );
  h_ptGenLowEtaB = TH1F( "ptGenLowEtaB",  "p_{T} of Low p_{T} leading GenJets, #eta<1", 200, 0, 1000 );
  
  h_ptGenAllEtaBE = TH1F( "ptGenAllEtaBE",  "p_{T} of All leading GenJets, 1<#eta<1.5", 80, 0, 8000 );
  h_ptGenLowEtaBE = TH1F( "ptGenLowEtaBE",  "p_{T} of Low p_{T} leading GenJets, 1<#eta<1.5", 200, 0, 1000 );

  h_ptGenAllEtaE = TH1F( "ptGenAllEtaE",  "p_{T} of All leading GenJets, 1.5<#eta<2.5", 80, 0, 8000 );
  h_ptGenLowEtaE = TH1F( "ptGenLowEtaE",  "p_{T} of Low p_{T} leading GenJets, 1.5<#eta<2.5", 200, 0, 1000 );

  h_ptGenAllEtaEF = TH1F( "ptGenAllEtaEF",  "p_{T} of All leading GenJets, 2.5<#eta<3", 80, 0, 8000 );
  h_ptGenLowEtaEF = TH1F( "ptGenLowEtaEF",  "p_{T} of Low p_{T} leading GenJets, 2.5<#eta<3", 200, 0, 1000 );

  h_ptGenAllEtaF = TH1F( "ptGenAllEtaF",  "p_{T} of All leading GenJets, 3<#eta<5", 80, 0, 8000 );
  h_ptGenLowEtaF = TH1F( "ptGenLowEtaF",  "p_{T} of Low p_{T} leading GenJets, 3<#eta<5", 200, 0, 1000 );


  h_ptHatAll = TH1F( "ptHatAll",  "p_{T}hat for process", 80, 0, 8000 );
  h_ptHatLow = TH1F( "ptHatLow",  "p_{T}hat for process (Lower p_{T})", 200, 0, 1000 );

  h_etaGen = TH1F( "etaGen", "#eta of leading GenJets", 100, -5, 5 );
  h_etaGenLowpt = TH1F( "etaGenLowpt", "#eta of Low p_{T} leading GenJets", 100, -5, 5 );
  h_phiGen = TH1F( "phiGen", "#phi of leading GenJets", 60, -M_PI, M_PI );

// Hook into DQM interface...

dbe_=0;

//dbe_=edm::Service<DaqMonitorBEInterface>().operator->();
  dbe_ = Service<DaqMonitorBEInterface>().operator->();

  //We put this here for the moment since there is no better place 
  edm::Service<MonitorDaemon> daemon;
  daemon.operator->();


me_ptHatAll=0;
me_ptHatLow=0;

if (dbe_) {
    dbe_->setCurrentFolder("JetPlots");
    me_ptHatAll=dbe_->book1D( "ptHatAll",  "p_{T}hat for process", 80, 0, 8000 );
    me_ptHatLow = dbe_->book1D( "ptHatLow",  "p_{T}hat for process (Lower p_{T})", 200, 0, 1000 );
  }
}

void JetPlots::analyze( const Event& evt, const EventSetup& es) {


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

  h_ptHatAll.Fill(evtscale);
  if (me_ptHatAll) me_ptHatAll->Fill(evtscale);
  h_ptHatLow.Fill(evtscale);
  if (me_ptHatLow) me_ptHatLow->Fill(evtscale);




  //Get the CaloJet collection
  Handle<CaloJetCollection> caloJets;
  evt.getByLabel( CaloJetAlgorithm, caloJets );

  //Loop over the two leading CaloJets and fill some histograms
  int jetInd = 0;
  for( CaloJetCollection::const_iterator cal = caloJets->begin(); cal != caloJets->end() && jetInd<2; ++ cal ) {
    h_ptCal.Fill( cal->pt() );   
    h_etaCal.Fill( cal->eta() );
    h_phiCal.Fill( cal->phi() );
    jetInd++;
  }

  //Get the GenJet collection
  Handle<GenJetCollection> genJets;
  evt.getByLabel( GenJetAlgorithm, genJets );

  //Loop over the two leading GenJets and fill some histograms
  jetInd = 0;
  for( GenJetCollection::const_iterator gen = genJets->begin(); gen != genJets->end() && jetInd<2; ++ gen ) {
    h_ptGenAll.Fill( gen->pt() );  
    h_ptGenLow.Fill( gen->pt() ); 
    if (abs(gen->eta())<1) {
           h_ptGenAllEtaB.Fill( gen->pt() );  
           h_ptGenLowEtaB.Fill( gen->pt() ); 
    }
    if (abs(gen->eta())>=1&&abs(gen->eta())<1.5) {
           h_ptGenAllEtaBE.Fill( gen->pt() );  
           h_ptGenLowEtaBE.Fill( gen->pt() ); 
    }
    if (abs(gen->eta())>=1.5&&abs(gen->eta())<2.5) {
           h_ptGenAllEtaE.Fill( gen->pt() );  
           h_ptGenLowEtaE.Fill( gen->pt() ); 
    }
    if (abs(gen->eta())>=2.5&&abs(gen->eta())<3) {
           h_ptGenAllEtaEF.Fill( gen->pt() );  
           h_ptGenLowEtaEF.Fill( gen->pt() ); 
    }
    if (abs(gen->eta())>=3&&abs(gen->eta())<5) {
           h_ptGenAllEtaF.Fill( gen->pt() );  
           h_ptGenLowEtaF.Fill( gen->pt() ); 
    }

    h_etaGen.Fill( gen->eta() );
    if (gen->pt()<1000) {
      h_etaGenLowpt.Fill(gen->eta());
    }
    h_phiGen.Fill( gen->phi() );
    jetInd++;
  }

}

void JetPlots::endJob() {

  //Write out the histogram file.
  m_file->Write(); 

}
