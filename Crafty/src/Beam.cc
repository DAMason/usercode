// -*- C++ -*-
//
// Package:    Beam
// Class:      Beam
// 
/**\class Beam Beam.cc QCDAnalysis/Craft/src/Beam.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  David_Mason
//         Created:  Mon May 12 11:02:06 CDT 2008
// $Id: Beam.cc,v 1.3 2009/11/29 07:51:30 dmason Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/METReco/interface/CaloMETCollection.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/CaloJet.h"

#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include <FWCore/Framework/interface/TriggerNames.h>
#include <DataFormats/HLTReco/interface/TriggerEvent.h>
#include <DataFormats/HLTReco/interface/TriggerFilterObjectWithRefs.h>

#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <TROOT.h>
#include <TMath.h>
#include <TTree.h>
//#include <TFile.h>
#include <TLorentzVector.h>
#include "TH1.h"
#include "TH2.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

   using namespace edm;
   using namespace std;


//
// class declaration
//

class Beam : public edm::EDAnalyzer {
   public:
      explicit Beam(const edm::ParameterSet&);
      ~Beam();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      void bookHistsForRun(int);
      virtual void endJob() ;

      // ----------member data ---------------------------

      typedef std::map<int,int> ThingCounter;
      ThingCounter eventsPerRunCounter;


      typedef std::map<int, TH1D*> BinnedHSet; 
      BinnedHSet h_EventCounter;

      BinnedHSet h_CaloMET;
      BinnedHSet h_CaloSumET;
      BinnedHSet h_CaloMETRatio;

      BinnedHSet h_LBarrelCaloJetPt;
      BinnedHSet h_CaloJetPt;
      BinnedHSet h_LCaloJetPt;
      BinnedHSet h_LCaloJetPtJet30trig;
      BinnedHSet h_CaloJetPtJet30trig;
      BinnedHSet h_LCaloJetPtJet50trig;
      BinnedHSet h_CaloJetPtJet50trig;
      BinnedHSet h_BarrelCaloJetPt;

      BinnedHSet h_CaloMETRatioJet5;
      BinnedHSet h_CaloMETRatioJet10;
      BinnedHSet h_CaloMETRatioJet15;
      BinnedHSet h_CaloMETRatioJet30;
      BinnedHSet h_CaloMETRatioJet50;
      BinnedHSet h_CaloMETRatioJet80;
      BinnedHSet h_CaloMETRatioJet110;


      BinnedHSet h_TowerMETRatio;
      BinnedHSet h_CaloTowerEt;
      BinnedHSet h_AcceptedCaloTowerEt;


      BinnedHSet h_TowerMETRatioJet30trig;
      BinnedHSet h_TowerMETRatioJet50trig;

      BinnedHSet h_LBarrelCaloWideJetPt;
      BinnedHSet h_BarrelCaloWideJetPt;


      BinnedHSet h_CaloMETRatioJet5Jet30trig;
      BinnedHSet h_CaloMETRatioJet10Jet30trig;
      BinnedHSet h_CaloMETRatioJet15Jet30trig;
      BinnedHSet h_CaloMETRatioJet30Jet30trig;
      BinnedHSet h_CaloMETRatioJet50Jet30trig;
      BinnedHSet h_CaloMETRatioJet80Jet30trig;
      BinnedHSet h_CaloMETRatioJet110Jet30trig;


      BinnedHSet h_CaloMETRatioJet5Jet50trig;
      BinnedHSet h_CaloMETRatioJet10Jet50trig;
      BinnedHSet h_CaloMETRatioJet15Jet50trig;
      BinnedHSet h_CaloMETRatioJet30Jet50trig;
      BinnedHSet h_CaloMETRatioJet50Jet50trig;
      BinnedHSet h_CaloMETRatioJet80Jet50trig;
      BinnedHSet h_CaloMETRatioJet110Jet50trig;

      BinnedHSet h_TriggerMonitor;

      typedef std::map<int, TH2D*> Binned2DHSet;
      Binned2DHSet h_CaloJetEtaPhi;  
      Binned2DHSet h_EtaPhiAcceptedTowers;
      Binned2DHSet h_CaloJetEtaPhiJet30trig;
      Binned2DHSet h_CaloJetEtaPhiJet50trig;
      Binned2DHSet h_CaloJetEtaPhiJetsGreater110;
    
      Binned2DHSet h_CaloJetPtCaloMETRatio;
      Binned2DHSet h_LCaloJetPtCaloMETRatio;
      Binned2DHSet h_MaxCaloJetPtCaloMETRatio;
      Binned2DHSet h_First100LumisTriggerMonitor;
      Binned2DHSet h_First1000LumisTriggerMonitor;
      Binned2DHSet h_First100LumisL1TechTriggerMonitor;

      int currentRun;
      int  calometerrcount;

      TTree* mTree;

      edm::Service<TFileService> fs;


      InputTag triggerResultsTag;
      InputTag alternateTriggerResultsTag;

      typedef std::map< char *,int> StringCounter;

      StringCounter NamedTrigCounter;
    
      float tpx[2],tpy[2],tpz[2],tpt[2],tE[2],tEmf[2],tNtrkVx[2],tNtrkCalo[2];
      float teta[2],tphi[2];
      float tMET,tSumET,tPtHat; 
      int tHLTBits[6],trun,tlumi,tevent;
      int tNJets6,tNJets15,tNJets30;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
Beam::Beam(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

  triggerResultsTag=iConfig.getParameter<InputTag>("triggerResults");
  alternateTriggerResultsTag=iConfig.getParameter<InputTag>("alternateTriggerResults");
}


Beam::~Beam()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
Beam::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{


   currentRun=iEvent.id().run();
   trun=currentRun;
   tevent=iEvent.id().event();
   tlumi=iEvent.luminosityBlock();

   /*
   this is actually overkill ... Really just need to see if the thing is 1...
   map<string,int>::iterator iter = eventsPerRunCounter.find(currentRun);
   if( iter == eventsPerRunCounter.end() ) {
     cout << "Run Number: " << currentRun << " is New! Booking new Histos..."<< endl;
   } 
   */

  eventsPerRunCounter[currentRun]++;

  if(eventsPerRunCounter[currentRun]==1) {
     cout << "Run Number: " << currentRun << " is New! Booking new Histos..."<< endl;
     bookHistsForRun(currentRun);
  }
  h_EventCounter[currentRun]->Fill(1.0,1.0); 


//  Attempt to look at L1 bits...
//  For the first collisions the technical trigger bits were interesting
//  specifically bits 40 & 41...

  bool BSCAnything = false;
  bool RPCAnything = false;
  bool BSCBit4041 = false;
  
  Handle< L1GlobalTriggerReadoutRecord > gtRecord;
  iEvent.getByLabel( "gtDigis", gtRecord);

  const TechnicalTriggerWord tWord = gtRecord->technicalTriggerWord();
  const DecisionWord         dWord = gtRecord->decisionWord();

  unsigned int nL1Paths=tWord.size();
  //cout << "got " <<nL1Paths << " L1 technical bits " << endl;

  for (unsigned int itrig=0;itrig < nL1Paths; ++itrig) {
     //if (tWord.at(itrig)) cout << "Bit: " << itrig << " Passed! " << endl;
     if (tWord.at(itrig)) {
       h_First100LumisL1TechTriggerMonitor[currentRun]->Fill(double(tlumi),double(itrig),1.0);
       if (itrig==40 || itrig==41) BSCBit4041=true;
       if (itrig>=32 && itrig <= 43 ) BSCAnything = true;
       if (itrig>=24 && itrig <= 30 ) RPCAnything = true;
       }
   }

      tHLTBits[0]=0;
      tHLTBits[1]=0;
      tHLTBits[2]=0;


       if (BSCAnything) tHLTBits[0]=1;
       if (BSCBit4041) tHLTBits[1]=1;
       if (RPCAnything) tHLTBits[2]=1;


  //Trigger bits...


  TriggerNames triggerNames;
  std::vector<std::string> selectedHLTBits;  

  edm::Handle<TriggerResults> trigResults;

  iEvent.getByLabel(triggerResultsTag,trigResults);

  bool Jet15Accept = false;
  bool Jet30Accept = false;
  bool Jet50Accept = false;
  bool L1Jet6Accept = false;



//  if (trigResults) iEvent.getByLabel(alternateTriggerResultsTag,trigResults);


    triggerNames.init (*(trigResults.product()));

    if (trigResults.product()->wasrun()) {

      unsigned int nPaths = trigResults.product()->size();
      //cout << "got "<< nPaths << " trig paths" << endl; 

      for (unsigned int itrig=0;itrig < nPaths; ++itrig) {
        if(eventsPerRunCounter[currentRun]==1) {
          cout << "Bit: " << itrig << "path: " << triggerNames.triggerName( itrig ) << " state: " << trigResults.product()->state( itrig ) << " accept? " << trigResults.product()->accept( itrig ) << endl;
        }
        if (trigResults.product()->accept(itrig)) {
            h_TriggerMonitor[currentRun]->Fill(double(itrig),1.0);
            h_First100LumisTriggerMonitor[currentRun]->Fill(double(tlumi),double(itrig),1.0);
            h_First1000LumisTriggerMonitor[currentRun]->Fill(double(tlumi),double(itrig),1.0);
        }
//        if (triggerNames.triggerName(itrig)=="HLT_Jet30") {
        if (triggerNames.triggerName(itrig)=="HLT_L1Jet6U") {
           if (trigResults.product()->accept(itrig)) L1Jet6Accept=true;
        }
        if (triggerNames.triggerName(itrig)=="HLT_Jet15U") {
           if (trigResults.product()->accept(itrig)) Jet15Accept=true;
        }
        if (triggerNames.triggerName(itrig)=="HLT_Jet30U") {
           if (trigResults.product()->accept(itrig)) Jet30Accept=true;
        }
        if (triggerNames.triggerName(itrig)=="HLT_Jet50U") {
           if (trigResults.product()->accept(itrig)) Jet50Accept=true;
        }
        
      tHLTBits[3]=0;
      tHLTBits[4]=0;
      tHLTBits[5]=0;


//       if (Jet15Accept) tHLTBits[3]=1;
//       if (Jet30Accept) tHLTBits[4]=1;
//       if (Jet50Accept) tHLTBits[5]=1;
       if (L1Jet6Accept) tHLTBits[3]=1;
       if (Jet15Accept)   tHLTBits[4]=1;
       if (Jet30Accept)   tHLTBits[5]=1;

      }
    }


    //CALOMET


  Double_t CaloMETRatio = 0;
  Double_t MaskedTowerMETRatio = 0;

  //Get the calo MET collection
  Handle<CaloMETCollection> caloMETs;
  //math::XYZTLorentzVector p4cor[2];
  try {
  iEvent.getByLabel( "met", caloMETs );
  //const CaloMETCollection *metCol = caloMETs.product();


   Int_t metInd=0;
   for( CaloMETCollection::const_iterator met = caloMETs->begin(); met != caloMETs->end(); ++ met ) {

   metInd++;

//   cout << "MET: " <<metInd << " sumEt: " << met->et() << " MEt: " << met->sumEt();
   if (met->sumEt() > 0) {
      CaloMETRatio=met->et()/met->sumEt();
      if (h_CaloMETRatio[currentRun]) h_CaloMETRatio[currentRun]->Fill(CaloMETRatio,1.0);
        tSumET=met->sumEt();
        tMET=met->et();
//      cout << " Ratio: " << met->et()/met->sumEt();
//      cout << endl;
   }

   if (h_CaloMET[currentRun])  h_CaloMET[currentRun]->Fill(met->et(),1.0);
   if (h_CaloSumET[currentRun]) h_CaloSumET[currentRun]->Fill(met->sumEt(),1.0);

   }
  }    catch (...) {
   calometerrcount++;
   if (calometerrcount<10) cout << "no CaloMET! " << endl;
  }


  //CALOTOWERS -- old masking code...



  Double_t et,eta,phi,ieta,iphi;
  math::XYZTLorentzVector p4towerall,p4towermasked;
  Double_t sumtower,sumtowermasked;

  sumtower=0;
  sumtowermasked=0;
  


  Handle<CaloTowerCollection> caloTowers;
  iEvent.getByLabel("towerMaker",caloTowers);



  for( CaloTowerCollection::const_iterator cal = caloTowers->begin(); cal != caloTowers->end(); ++ cal ) {
    et=cal->et();
    eta=cal->eta();
    phi=cal->phi();
    ieta=cal->ieta();
    iphi=cal->iphi();
//    cout << "Tower: " <<ieta << " " << iphi << " "<< et << " "<< eta << " "<< phi << endl;
    if (h_CaloTowerEt[currentRun]) h_CaloTowerEt[currentRun]->Fill(et,1.0);
    if (et>0.5) {
     if (h_AcceptedCaloTowerEt[currentRun]) h_AcceptedCaloTowerEt[currentRun]->Fill(et,1.0);
     if (h_EtaPhiAcceptedTowers[currentRun]) h_EtaPhiAcceptedTowers[currentRun]->Fill(eta,phi,1.0);
     p4towerall+=cal->p4();
     sumtower+=et;
     if (ieta!=-32 and iphi!=45) {
       p4towermasked+=cal->p4();
       sumtowermasked+=et;
     }
    }
  }

  MaskedTowerMETRatio = p4towermasked.pt()/sumtowermasked;


  //CALOJETS


//  cout <<  " TowerJetsumEt: " << sumtower << " Et: " << p4towerall.pt();
//  if (sumtower > 0) cout << " Ratio: " << p4towerall.pt()/sumtower;
//  cout << endl;
//  cout <<  " TowerJetsumMaskedEt: " << sumtowermasked << " Et: " << p4towermasked.pt();
//  if (sumtowermasked > 0) cout << " Ratio: " << MaskedTowerMETRatio;
//  cout << endl;

  if (h_TowerMETRatio[currentRun]) h_TowerMETRatio[currentRun]->Fill(p4towerall.pt()/sumtower,1.0);
  if (Jet30Accept) {
    if (h_TowerMETRatioJet30trig[currentRun]) h_TowerMETRatioJet30trig[currentRun]->Fill(p4towerall.pt()/sumtower,1.0);
    if (h_TowerMETRatioJet50trig[currentRun]) h_TowerMETRatioJet50trig[currentRun]->Fill(p4towerall.pt()/sumtower,1.0);
  }

  Handle<CaloJetCollection> caloJets;
  iEvent.getByLabel("sisCone5CaloJets",caloJets);

  int jetInd = 0;
  Double_t MaxJet = 0.;

  math::XYZTLorentzVector p4Calo;
  Double_t CaloSumEt;

  tNJets6=0;
  tNJets15=0;
  tNJets30=0;

  for (CaloJetCollection::const_iterator cal = caloJets->begin(); cal != caloJets->end(); ++cal) {

    if (h_CaloJetPt[currentRun]) h_CaloJetPt[currentRun]->Fill(cal->et(),1.0);

    if (h_CaloJetEtaPhi[currentRun]) h_CaloJetEtaPhi[currentRun]->Fill(cal->eta(),cal->phi(),1.0);

    if (Jet30Accept && h_CaloJetPtJet30trig[currentRun]) h_CaloJetPtJet30trig[currentRun]->Fill(cal->et(),1.0);
    if (Jet50Accept && h_CaloJetPtJet50trig[currentRun]) h_CaloJetPtJet50trig[currentRun]->Fill(cal->et(),1.0);

    if (Jet30Accept && h_CaloJetEtaPhiJet30trig[currentRun]) h_CaloJetEtaPhiJet30trig[currentRun]->Fill(cal->eta(),cal->phi(),1.0);
    if (Jet50Accept && h_CaloJetEtaPhiJet50trig[currentRun]) h_CaloJetEtaPhiJet50trig[currentRun]->Fill(cal->eta(),cal->phi(),1.0);

    if (cal->et()>110.0 && h_CaloJetEtaPhiJetsGreater110[currentRun]) h_CaloJetEtaPhiJetsGreater110[currentRun]->Fill(cal->eta(),cal->phi(),1.0);

    if (h_CaloJetPtCaloMETRatio[currentRun]) h_CaloJetPtCaloMETRatio[currentRun]->Fill(cal->et(),CaloMETRatio,1.0);


    if (cal->et()>6.0) tNJets6++;
    if (cal->et()>15.0) tNJets15++;
    if (cal->et()>30.0) tNJets30++;

    if (jetInd<2) {

      tpt[jetInd]=cal->et();
      tpx[jetInd]=cal->px();
      tpy[jetInd]=cal->py();
      tpz[jetInd]=cal->pz();
      tE[jetInd]=cal->energy();
      teta[jetInd]=cal->eta();
      tphi[jetInd]=cal->phi();
      tEmf[jetInd]=cal->emEnergyFraction();

      if (h_LCaloJetPt[currentRun]) h_LCaloJetPt[currentRun]->Fill(cal->et(),1.0);
      if (Jet30Accept && h_LCaloJetPtJet30trig[currentRun]) h_LCaloJetPtJet30trig[currentRun]->Fill(cal->et(),1.0);
      if (Jet50Accept && h_LCaloJetPtJet50trig[currentRun]) h_LCaloJetPtJet50trig[currentRun]->Fill(cal->et(),1.0);
      if (h_LCaloJetPtCaloMETRatio[currentRun]) h_LCaloJetPtCaloMETRatio[currentRun]->Fill(cal->et(),CaloMETRatio,1.0);
    }

    if (jetInd==0) {
       MaxJet=cal->et();
       if (h_MaxCaloJetPtCaloMETRatio[currentRun]) h_MaxCaloJetPtCaloMETRatio[currentRun]->Fill(cal->et(),CaloMETRatio,1.0);
       }

    if (abs(cal->eta())<1.3) {
      if (jetInd<2) {
         if (h_LBarrelCaloJetPt[currentRun]) h_LBarrelCaloJetPt[currentRun]->Fill(cal->et(),1.0);
         if (h_LBarrelCaloWideJetPt[currentRun]) h_LBarrelCaloWideJetPt[currentRun]->Fill(cal->et(),1.0);
      }
    if (h_BarrelCaloJetPt[currentRun]) h_BarrelCaloJetPt[currentRun]->Fill(cal->et(),1.0);
    if (h_BarrelCaloWideJetPt[currentRun]) h_BarrelCaloWideJetPt[currentRun]->Fill(cal->et(),1.0);
    }
    jetInd++;


  } 

  if (MaxJet>5.0 ) {
      if (h_CaloMETRatioJet5[currentRun]) h_CaloMETRatioJet5[currentRun]->Fill(CaloMETRatio,1.0);
      if (Jet30Accept) {
              if (h_CaloMETRatioJet5Jet30trig[currentRun]) h_CaloMETRatioJet5Jet30trig[currentRun]->Fill(CaloMETRatio,1.0);
      }
      if (Jet50Accept) {
              if (h_CaloMETRatioJet5Jet50trig[currentRun]) h_CaloMETRatioJet5Jet50trig[currentRun]->Fill(CaloMETRatio,1.0);
      }
  }



   if (MaxJet>10.0 ) {
      if (h_CaloMETRatioJet10[currentRun]) h_CaloMETRatioJet10[currentRun]->Fill(CaloMETRatio,1.0);
      if (Jet30Accept) {
              if (h_CaloMETRatioJet10Jet30trig[currentRun]) h_CaloMETRatioJet10Jet30trig[currentRun]->Fill(CaloMETRatio,1.0);
      }
      if (Jet50Accept) {
              if (h_CaloMETRatioJet10Jet50trig[currentRun]) h_CaloMETRatioJet10Jet50trig[currentRun]->Fill(CaloMETRatio,1.0);
      }
  }

  if (MaxJet>15.0 ) {
      if (h_CaloMETRatioJet15[currentRun]) h_CaloMETRatioJet15[currentRun]->Fill(CaloMETRatio,1.0);
      if (Jet30Accept) {
              if (h_CaloMETRatioJet15Jet30trig[currentRun]) h_CaloMETRatioJet15Jet30trig[currentRun]->Fill(CaloMETRatio,1.0);
      }
      if (Jet50Accept) {
              if (h_CaloMETRatioJet15Jet50trig[currentRun]) h_CaloMETRatioJet15Jet50trig[currentRun]->Fill(CaloMETRatio,1.0);
      }
  }

  if (MaxJet>30.0 ) {
      if (h_CaloMETRatioJet30[currentRun]) h_CaloMETRatioJet30[currentRun]->Fill(CaloMETRatio,1.0);
      if (Jet30Accept) {
              if (h_CaloMETRatioJet30Jet30trig[currentRun]) h_CaloMETRatioJet30Jet30trig[currentRun]->Fill(CaloMETRatio,1.0);
      }
      if (Jet50Accept) {
              if (h_CaloMETRatioJet30Jet50trig[currentRun]) h_CaloMETRatioJet30Jet50trig[currentRun]->Fill(CaloMETRatio,1.0);
      }
  }

  if (MaxJet>50.0 ) {
      if (h_CaloMETRatioJet50[currentRun]) h_CaloMETRatioJet50[currentRun]->Fill(CaloMETRatio,1.0);
      if (Jet30Accept) {
              if (h_CaloMETRatioJet50Jet30trig[currentRun]) h_CaloMETRatioJet50Jet30trig[currentRun]->Fill(CaloMETRatio,1.0);
      }
      if (Jet50Accept) {
              if (h_CaloMETRatioJet50Jet50trig[currentRun]) h_CaloMETRatioJet50Jet50trig[currentRun]->Fill(CaloMETRatio,1.0);
      }
  }

  if (MaxJet>80.0 ) {
      if (h_CaloMETRatioJet80[currentRun]) h_CaloMETRatioJet80[currentRun]->Fill(CaloMETRatio,1.0);
      if (Jet30Accept) {
              if (h_CaloMETRatioJet80Jet30trig[currentRun]) h_CaloMETRatioJet80Jet30trig[currentRun]->Fill(CaloMETRatio,1.0);
      }
      if (Jet50Accept) {
              if (h_CaloMETRatioJet80Jet50trig[currentRun]) h_CaloMETRatioJet80Jet50trig[currentRun]->Fill(CaloMETRatio,1.0);
      }
  }

  if (MaxJet>110.0 ) {
      if (h_CaloMETRatioJet110[currentRun]) h_CaloMETRatioJet110[currentRun]->Fill(CaloMETRatio,1.0);
      if (Jet30Accept) {
              if (h_CaloMETRatioJet110Jet30trig[currentRun]) h_CaloMETRatioJet110Jet30trig[currentRun]->Fill(CaloMETRatio,1.0);
      }
      if (Jet50Accept) {
              if (h_CaloMETRatioJet110Jet50trig[currentRun]) h_CaloMETRatioJet110Jet50trig[currentRun]->Fill(CaloMETRatio,1.0);
      }
  }



// if (Jet15Accept) mTree->Fill(); 
 if (BSCAnything||L1Jet6Accept) mTree->Fill(); 


}


void Beam::bookHistsForRun(int runNum) {

  char histoname[37] = "";
  cout <<"'Booking hist for run " << runNum;
  sprintf (histoname,"EventCounterRun%i",runNum);
  h_EventCounter[runNum]=fs->make<TH1D>(histoname, "Event Counter", 1, 0., 2.);

  sprintf (histoname,"CaloMETRun%i",runNum);
  h_CaloMET[runNum]=fs->make<TH1D>(histoname, "CaloMET", 100, 0., 100.);
  sprintf (histoname,"CaloSumETRun%i",runNum);
  h_CaloSumET[runNum]=fs->make<TH1D>(histoname, "Calo Sum ET",100,0.,100.);
  sprintf (histoname,"CaloMETRatioRun%i",runNum);
  h_CaloMETRatio[runNum]=fs->make<TH1D>(histoname, "Calo MET/SumET ratio",100,0.,1.);
  sprintf (histoname,"CaloJetPTRun%i",runNum);
  h_CaloJetPt[runNum]=fs->make<TH1D>(histoname, "CaloJet PT", 1000, 0., 1000.);
  sprintf (histoname,"LCaloJetPTRun%i",runNum);
  h_LCaloJetPt[runNum]=fs->make<TH1D>(histoname, "Leading CaloJet PT", 1000, 0., 1000.);
  sprintf (histoname,"LCaloJetPTJet30trigRun%i",runNum); 
  h_LCaloJetPtJet30trig[runNum]=fs->make<TH1D>(histoname, "Leading CaloJet PT Jet 30 trigger", 1000, 0., 1000.);
  sprintf (histoname,"LCaloJetPTJet50trigRun%i",runNum); 
  h_LCaloJetPtJet50trig[runNum]=fs->make<TH1D>(histoname, "Leading CaloJet PT Jet 50 trigger", 1000, 0., 1000.);
  sprintf (histoname,"CaloJetPTJet30trigRun%i",runNum);
  h_CaloJetPtJet30trig[runNum]=fs->make<TH1D>(histoname, "CaloJet PT Jet30 Trigger", 1000, 0., 1000.);
  sprintf (histoname,"CaloJetPTJet50trigRun%i",runNum);
  h_CaloJetPtJet50trig[runNum]=fs->make<TH1D>(histoname, "CaloJet PT Jet50 Trigger", 1000, 0., 1000.);
  sprintf (histoname,"LBarrelCaloJetPTRun%i",runNum);
  h_LBarrelCaloJetPt[runNum]=fs->make<TH1D>(histoname, "Barrel Leading CaloJet PT #eta<1.3", 100, 0., 100.);
  sprintf (histoname,"BarrelCaloJetPTRun%i",runNum);
  h_BarrelCaloJetPt[runNum]=fs->make<TH1D>(histoname, "Barrel CaloJet PT #eta<1.3", 100, 0., 100.);

  sprintf (histoname,"LBarrelCaloJetPTWideRun%i",runNum);
  h_LBarrelCaloWideJetPt[runNum]=fs->make<TH1D>(histoname, "Barrel Leading CaloJet PT #eta<1.3", 2000, 0., 2000.);
  sprintf (histoname,"BarrelCaloJetWidePTRun%i",runNum);
  h_BarrelCaloWideJetPt[runNum]=fs->make<TH1D>(histoname, "Barrel CaloJet PT #eta<1.3", 2000, 0., 2000.);

  sprintf(histoname,"h_CaloJetEtaPhiRun%i",runNum);
  h_CaloJetEtaPhi[runNum]=fs->make<TH2D>(histoname, "CaloJet Eta vs Phi",100,-5,5,60,-3.14,3.14);
  
  sprintf(histoname,"h_CaloJetEtaPhiJet30trigRun%i",runNum);
  h_CaloJetEtaPhiJet30trig[runNum]=fs->make<TH2D>(histoname, "CaloJet Eta vs Phi Jet30 triggered",100,-5,5,60,-3.14,3.14);

  sprintf(histoname,"h_CaloJetEtaPhiJet50trigRun%i",runNum);
  h_CaloJetEtaPhiJet50trig[runNum]=fs->make<TH2D>(histoname, "CaloJet Eta vs Phi Jet50 triggered",100,-5,5,60,-3.14,3.14);

  sprintf(histoname,"h_CaloJetEtaPhiJetsGreater110Run%i",runNum);
  h_CaloJetEtaPhiJetsGreater110[runNum]=fs->make<TH2D>(histoname, "CaloJet Eta vs Phi Jets > 110 GeV",100,-5,5,60,-3.14,3.14); 


  sprintf(histoname,"h_EtaPhiAcceptedTowersRun%i",runNum);
  h_EtaPhiAcceptedTowers[runNum]=fs->make<TH2D>(histoname, "Eta vs Phi of MET Accepted Calo Towers",100,-5,5,60,-3.14,3.14); 
   
  sprintf(histoname,"h_CaloJetPtCaloMETRatioRun%i",runNum);
  h_CaloJetPtCaloMETRatio[runNum]=fs->make<TH2D>(histoname, "CaloMET ratio vs CaloJet pT",200,0,2000,25,0,1);
  sprintf(histoname,"h_LCaloJetPtCaloMETRatioRun%i",runNum);
  h_LCaloJetPtCaloMETRatio[runNum]=fs->make<TH2D>(histoname, "2 Leading Jet CaloMET ratio vs CaloJet pT",200,0,2000,25,0,1);
  sprintf(histoname,"h_MaxCaloJetPtCaloMETRatioRun%i",runNum);
  h_MaxCaloJetPtCaloMETRatio[runNum]=fs->make<TH2D>(histoname, "CaloMET ratio vs Max CaloJet pT",200,0,2000,25,0,1);



  sprintf(histoname,"h_CaloMETRatioJet5Run%i",runNum);
  h_CaloMETRatioJet5[runNum]=fs->make<TH1D>(histoname, "Calo MET/SumET ratio, Jet pT>5",100,0.,1.);  

  sprintf(histoname,"h_CaloMETRatioJet10Run%i",runNum);
  h_CaloMETRatioJet10[runNum]=fs->make<TH1D>(histoname, "Calo MET/SumET ratio, Jet pT>10",100,0.,1.);

  sprintf(histoname,"h_CaloMETRatioJet15Run%i",runNum);
  h_CaloMETRatioJet15[runNum]=fs->make<TH1D>(histoname, "Calo MET/SumET ratio, Jet pT>15",100,0.,1.);

  sprintf(histoname,"h_CaloMETRatioJet30Run%i",runNum);
  h_CaloMETRatioJet30[runNum]=fs->make<TH1D>(histoname, "Calo MET/SumET ratio, Jet pT>30",100,0.,1.);

  sprintf(histoname,"h_CaloMETRatioJet50Run%i",runNum);
  h_CaloMETRatioJet50[runNum]=fs->make<TH1D>(histoname, "Calo MET/SumET ratio, Jet pT>50",100,0.,1.);

  sprintf(histoname,"h_CaloMETRatioJet80Run%i",runNum);
  h_CaloMETRatioJet80[runNum]=fs->make<TH1D>(histoname, "Calo MET/SumET ratio, Jet pT>80",100,0.,1.);

  sprintf(histoname,"h_CaloMETRatioJet110Run%i",runNum);
  h_CaloMETRatioJet110[runNum]=fs->make<TH1D>(histoname, "Calo MET/SumET ratio, Jet pT>110",100,0.,1.);


  sprintf(histoname,"h_TowerMETRatioRun%i",runNum);
  h_TowerMETRatio[runNum]=fs->make<TH1D>(histoname, "Summed Tower MET/SumET ratio, ",100,0.,1.);



  sprintf(histoname,"h_TowerMETRatioJet30trigRun%i",runNum);
  h_TowerMETRatioJet30trig[runNum]=fs->make<TH1D>(histoname, "Summed Tower MET/SumET ratio, Jet30 trigger",100,0.,1.); 

  sprintf(histoname,"h_CaloMETRatioJet5Jet30trigRun%i",runNum);
  h_CaloMETRatioJet5Jet30trig[runNum]=fs->make<TH1D>(histoname, "Calo MET/SumET ratio, Jet pT>5 Jet30 trigger",100,0.,1.); 
  sprintf(histoname,"h_CaloMETRatioJet10Jet30trigRun%i",runNum);
  h_CaloMETRatioJet10Jet30trig[runNum]=fs->make<TH1D>(histoname, "Calo MET/SumET ratio, Jet pT>10 Jet30 trigger",100,0.,1.);
  sprintf(histoname,"h_CaloMETRatioJet15Jet30trigRun%i",runNum);
  h_CaloMETRatioJet15Jet30trig[runNum]=fs->make<TH1D>(histoname, "Calo MET/SumET ratio, Jet pT>15 Jet30 trigger",100,0.,1.);
  sprintf(histoname,"h_CaloMETRatioJet30Jet30trigRun%i",runNum);
  h_CaloMETRatioJet30Jet30trig[runNum]=fs->make<TH1D>(histoname, "Calo MET/SumET ratio, Jet pT>30 Jet30 trigger",100,0.,1.);
  sprintf(histoname,"h_CaloMETRatioJet50Jet30trigRun%i",runNum);
  h_CaloMETRatioJet50Jet30trig[runNum]=fs->make<TH1D>(histoname, "Calo MET/SumET ratio, Jet pT>50 Jet30 trigger",100,0.,1.);
  sprintf(histoname,"h_CaloMETRatioJet80Jet30trigRun%i",runNum);
  h_CaloMETRatioJet80Jet30trig[runNum]=fs->make<TH1D>(histoname, "Calo MET/SumET ratio, Jet pT>80 Jet30 trigger",100,0.,1.);
  sprintf(histoname,"h_CaloMETRatioJet110Jet30trigRun%i",runNum);
  h_CaloMETRatioJet110Jet30trig[runNum]=fs->make<TH1D>(histoname, "Calo MET/SumET ratio, Jet pT>110 Jet30 trigger",100,0.,1.);



  sprintf(histoname,"h_TowerMETRatioJet50trigRun%i",runNum);
  h_TowerMETRatioJet50trig[runNum]=fs->make<TH1D>(histoname, "Summed Tower MET/SumET ratio, Jet50 trigger",100,0.,1.); 

  sprintf(histoname,"h_CaloMETRatioJet5Jet50trigRun%i",runNum);
  h_CaloMETRatioJet5Jet50trig[runNum]=fs->make<TH1D>(histoname, "Calo MET/SumET ratio, Jet pT>5 Jet50 trigger",100,0.,1.); 
  sprintf(histoname,"h_CaloMETRatioJet10Jet50trigRun%i",runNum);
  h_CaloMETRatioJet10Jet50trig[runNum]=fs->make<TH1D>(histoname, "Calo MET/SumET ratio, Jet pT>10 Jet50 trigger",100,0.,1.);
  sprintf(histoname,"h_CaloMETRatioJet15Jet50trigRun%i",runNum);
  h_CaloMETRatioJet15Jet50trig[runNum]=fs->make<TH1D>(histoname, "Calo MET/SumET ratio, Jet pT>15 Jet50 trigger",100,0.,1.);
  sprintf(histoname,"h_CaloMETRatioJet30Jet50trigRun%i",runNum);
  h_CaloMETRatioJet30Jet50trig[runNum]=fs->make<TH1D>(histoname, "Calo MET/SumET ratio, Jet pT>30 Jet50 trigger",100,0.,1.);
  sprintf(histoname,"h_CaloMETRatioJet50Jet50trigRun%i",runNum);
  h_CaloMETRatioJet50Jet50trig[runNum]=fs->make<TH1D>(histoname, "Calo MET/SumET ratio, Jet pT>50 Jet50 trigger",100,0.,1.);
  sprintf(histoname,"h_CaloMETRatioJet80Jet50trigRun%i",runNum);
  h_CaloMETRatioJet80Jet50trig[runNum]=fs->make<TH1D>(histoname, "Calo MET/SumET ratio, Jet pT>80 Jet50 trigger",100,0.,1.);
  sprintf(histoname,"h_CaloMETRatioJet110Jet50trigRun%i",runNum);
  h_CaloMETRatioJet110Jet50trig[runNum]=fs->make<TH1D>(histoname, "Calo MET/SumET ratio, Jet pT>110 Jet50 trigger",100,0.,1.);


  sprintf(histoname,"h_CaloTowerEtRun%i",runNum);
  h_CaloTowerEt[runNum]=fs->make<TH1D>(histoname, "CaloTower Et",500,0.,500.);

    
  sprintf(histoname,"h_AcceptedCaloTowerEtRun%i",runNum);
  h_AcceptedCaloTowerEt[runNum]=fs->make<TH1D>(histoname, "Accepted CaloTower Et",500,0.,500.);


  sprintf(histoname,"h_TriggerMonitorRun%i",runNum);
  h_TriggerMonitor[runNum]=fs->make<TH1D>(histoname,"Trigger Counts",200,0.,200.);
  sprintf(histoname,"h_First100LumisTriggerMonitorRun%i",runNum);
  h_First100LumisTriggerMonitor[runNum]=fs->make<TH2D>(histoname, "Trigger counts per first 100 lumis",100,0,100,200,0,200);
  sprintf(histoname,"h_First100LumisL1TechTriggerMonitorRun%i",runNum);
  h_First100LumisL1TechTriggerMonitor[runNum]=fs->make<TH2D>(histoname, "L1 Tech Trigger counts per first 100 lumis",100,0,100,64,-0.5,63.5);
  sprintf(histoname,"h_First1000LumisTriggerMonitorRun%i",runNum);
  h_First1000LumisTriggerMonitor[runNum]=fs->make<TH2D>(histoname, "Trigger counts per first 1000 lumis",100,0,1000,200,0,200);


}






// ------------ method called once each job just before starting event loop  ------------
void 
Beam::beginJob(const edm::EventSetup&)
{

 mTree = fs->make<TTree>("analTree","analTree");
 mTree->Branch("run"      ,&trun     ,"run/I");
 mTree->Branch("lumi"     ,&tlumi    ,"lumi/I");
 mTree->Branch("event"    ,&tevent   ,"event/I");
 mTree->Branch("px"       ,tpx       ,"px[2]/F");
 mTree->Branch("py"       ,tpy       ,"py[2]/F");
 mTree->Branch("pz"       ,tpz       ,"pz[2]/F");
 mTree->Branch("pt"       ,tpt       ,"pt[2]/F");
 mTree->Branch("e"        ,tE        ,"E[2]/F");
 mTree->Branch("eta"      ,teta      ,"eta[2]/F");
 mTree->Branch("phi"      ,tphi      ,"phi[2]/F");
 mTree->Branch("emf"      ,tEmf      ,"emf[2]/F");
// mTree->Branch("nTrkVx"   ,tntrkVx   ,"NtrkVx[2]/F");
// mTree->Branch("nTrkCalo" ,tntrkCalo ,"NtrkCalo[2]/F");
 mTree->Branch("met"      ,&tMET     ,"MET/F");
 mTree->Branch("sumet"    ,&tSumET   ,"SumET/F");
 mTree->Branch("nJets6"   ,&tNJets6  ,"Njets6/I");
 mTree->Branch("nJets15"   ,&tNJets15  ,"Njets15/I");
 mTree->Branch("nJets30"   ,&tNJets30  ,"Njets30/I");
 mTree->Branch("HLTBits"  ,tHLTBits  ,"HLTBits[6]/I");


 calometerrcount=0;


}

// ------------ method called once each job just after ending the event loop  ------------
void 
Beam::endJob() {

}

//define this as a plug-in
DEFINE_FWK_MODULE(Beam);
