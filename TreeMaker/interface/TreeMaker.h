
// -*- C++ -*-
//
// Package:    TreeMaker
// Class:      TreeMaker
// 
/**\class TreeMaker TreeMaker.h DMason/TreeMaker/interface/TreeMaker.h

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  David_Mason
//         Created:  Sat Jan 29 15:42:27 CST 2011
// $Id: TreeMaker.h,v 1.6 2011/02/03 22:46:33 dmason Exp $
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

#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <TROOT.h>
#include <TMath.h>
#include <TTree.h>
#include <TLorentzVector.h>
#include "TH1.h"
#include "TH2.h"

#include <vector>
#include <algorithm>
#include <string>

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/Math/interface/LorentzVector.h"


#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/JetID.h"
#include "DataFormats/JetReco/interface/JetExtendedAssociation.h"

// Jet corrections
#include "JetMETCorrections/Objects/interface/JetCorrector.h"

// Photons
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterTools.h"

// GenParticles
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

// Triggers
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtUtils.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMap.h"



using namespace edm;
using namespace std;

// actually has a bit more than this but generally defines some useful things
#include "DMason/TreeMaker/interface/TreeMakerBranchVars.h"


//
// class declaration
//
class TreeMaker : public edm::EDAnalyzer {
   public:
      explicit TreeMaker(const edm::ParameterSet&);
      ~TreeMaker();
      virtual void beginJob() ;
      static bool rawcorjetsorter( const RawCorJetPair& jetA, const RawCorJetPair& jetB){
        return (jetA.corjet.pt() > jetB.corjet.pt());
        }
      static bool photonsorter( const reco::Photon& pA, const reco::Photon& pB) {
        return (pA.et() > pB.et());
        }

   private:
      virtual void beginRun(const edm::Run&, const edm::EventSetup&);
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void bookTree();
      virtual bool fillTreeCut();
      virtual void flushVectors();
      virtual void endJob() ;

      // ----------member data ---------------------------

      bool IsMonteCarlo;

      string CaloJetTag;
      string CaloJECServiceName;
      string CaloJetIDTag,CaloJetExtenderTag;
      bool CaloJetDetails;
      double CaloJetThresh;

      string PFJetTag;
      string PFJECServiceName;
      double PFJetThresh;

      string JPTJetTag;
      string JPTJECServiceName;
      double JPTJetThresh;

      string GenJetTag;
      double GenJetThresh;

   

      string CaloMETTag,PFMETTag,TCMETTag;

      string TriggerProcessTag;
      InputTag TriggerResultsTag;
      InputTag L1GTReadoutTag;
      InputTag L1GTObjectMapTag;
      vector<string> HLTTriggers;
      vector<string> L1Triggers;
      vector<unsigned int> TrigIndex;
      HLTConfigProvider HltConfig;   



      string PhotonTag;
      bool PhotonDetails;
      double PhotonThresh;
 
      string PFPhotonTag;
      double PFPhotonThresh;       

      string TreeName;

      Service<TFileService> fs;
      TTree *myTree;

      EventBranches  EventData;
      CaloJetBranches CaloJetData;
      PhotonBranches PhotonData;
      GenInfoBranches GenData;
      TrigBranches HLTData;
};


//
// constants, enums and typedefs
//
//
// static data member definitions
//

