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
#include "DataFormats/JetReco/interface/JetExtendedAssociation.h"
#include "RecoJets/JetAlgorithms/interface/JetIDHelper.h"

#include "DataFormats/Common/interface/RefToBase.h"

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


#include "DMason/Crafty/interface/DefineHists.h"

      edm::ParameterSet parameters;

      typedef std::map<int,int> ThingCounter;
      ThingCounter eventsPerRunCounter;

       
      int currentRun;
      int  calometerrcount;

      TTree* mTree;

      edm::Service<TFileService> fs;


      reco::helper::JetIDHelper *jetID;

      InputTag triggerResultsTag;
      InputTag alternateTriggerResultsTag;

      typedef std::map< char *,int> StringCounter;

      StringCounter NamedTrigCounter;
    
      float tpx[2],tpy[2],tpz[2],tpt[2],tE[2],tEmf[2];
      float teta[2],tphi[2];
      float tMET,tSumET,tPtHat; 
      unsigned int tHLTBits[6],trun,tlumi,tevent;
      unsigned int tBx;
      unsigned int tNJets6,tNJets15,tNJets30;
      unsigned int tNtrkVx[2],tNtrkCalo[2];
      float tCHFVx[2],tCHFCalo[2];
      float tfHPD[2],tfRBX[2];
      unsigned int tn90Hits[2];
};

//
// constants, enums and typedefs
//


//
// static data member definitions
//

// That's All Folks
