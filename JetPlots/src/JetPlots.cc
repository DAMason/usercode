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
  GenJetAlgorithm( cfg.getParameter<string>( "GenJetAlgorithm" ) )
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
 me_ptHatAll[binNum]=dbe_->book1D( histoname,  "p_{T}hat for process", 80, 0, 8000 );

 sprintf (histoname,"ptHatLowBin%i",binNum);
 me_ptHatLow[binNum]=dbe_->book1D( histoname,  "p_{T}hat for process (Lower p_{T}", 200, 0, 1000 );

 sprintf (histoname,"ptGenAllBin%i",binNum);
 me_ptGenAll[binNum]=dbe_->book1D( histoname,  "p_{T} for leading genjets", 80, 0, 8000 );
 
 sprintf (histoname,"ptGenLowBin%i",binNum);
 me_ptGenLow[binNum] = dbe_->book1D( histoname,  "p_{T} for leading genjets (Lower p_{T})", 200, 0, 1000 );
  
 sprintf (histoname,"etaGen%i",binNum);
 me_etaGen[binNum]=dbe_->book1D(histoname, "#eta of leading GenJets", 100, -5, 5 );
 
 sprintf (histoname,"etaGenLowpt%i",binNum);
 me_etaGenLowpt[binNum]=dbe_->book1D( histoname, "#eta of Low p_{T} leading GenJets", 100, -5, 5 );
 
 sprintf (histoname,"phiGen%i",binNum);
 me_phiGen[binNum]=dbe_->book1D( histoname, "#phi of leading GenJets", 60, -M_PI, M_PI );


 sprintf (histoname,"ptGenAllEtaB%i",binNum);
 me_ptGenAllEtaB[binNum]=dbe_->book1D( histoname,  "p_{T} for leadkng genjets #eta<1", 80, 0, 8000 );

 sprintf (histoname,"ptGenLowEtaB%i",binNum);
 me_ptGenLowEtaB[binNum]=dbe_->book1D( histoname,  "p_{T} for leading genjets #eta<1 (Lower p_{T})", 200, 0, 1000 );

 sprintf (histoname,"ptGenAllEtaBE%i",binNum);
 me_ptGenAllEtaBE[binNum]=dbe_->book1D( histoname,  "p_{T} for leading genjets 1<#eta<1.5", 80, 0, 8000 );

 sprintf (histoname,"ptGenLowEtaBE%i",binNum);
 me_ptGenLowEtaBE[binNum]=dbe_->book1D( histoname,  "p_{T} for leading genjets 1<#eta<1.5 (Lower p_{T})", 200, 0, 1000 );

 sprintf (histoname,"ptGenAllEtaE%i",binNum);
 me_ptGenAllEtaE[binNum]=dbe_->book1D( "ptGenAllEtaE",  "p_{T} for leading genjets 1.5<#eta<2.5", 80, 0, 8000 );

 sprintf (histoname,"ptGenLowEtaE%i",binNum);
 me_ptGenLowEtaE[binNum]=dbe_->book1D( histoname,  "p_{T} for leading genjets 1.5<#eta<2.5 (Lower p_{T})", 200, 0, 1000 );

 sprintf (histoname,"ptGenAllEtaEF%i",binNum);
 me_ptGenAllEtaEF[binNum]=dbe_->book1D( histoname,  "p_{T} for leading genjets 2.5<#eta<3", 80, 0, 8000 );

 sprintf (histoname,"ptGenLowEtaEF%i",binNum);
 me_ptGenLowEtaEF[binNum]=dbe_->book1D( histoname,  "p_{T} for leading genjets 2.5<#eta<3 (Lower p_{T})", 200, 0, 1000 );

 sprintf (histoname,"ptGenAllEtaF%i",binNum);
 me_ptGenAllEtaF[binNum]=dbe_->book1D( histoname,  "p_{T} for leading genjets 3<#eta<5", 80, 0, 8000 );

 sprintf (histoname,"ptGenLowEtaF%i",binNum);
 me_ptGenLowEtaF[binNum]=dbe_->book1D( histoname,  "p_{T} for leading genjets 3<#eta<5 (Lower p_{T})", 200, 0, 1000 );


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

usleep(100000);

}

void JetPlots::endJob() {

  //Write out the histogram file.
  //m_file->Write(); 

  dbe_->save("JetPlots.root");

}
