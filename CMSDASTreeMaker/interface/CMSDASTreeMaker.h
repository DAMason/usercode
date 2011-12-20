
// -*- C++ -*-
//
// Package:    CMSDASTreeMaker
// Class:      CMSDASTreeMaker
// 
/**\class CMSDASTreeMaker CMSDASTreeMaker.h DMason/CMSDASTreeMaker/interface/CMSDASTreeMaker.h

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  David_Mason
//         Created:  Sat Jan 29 15:42:27 CST 2011
// $Id: CMSDASTreeMaker.h,v 1.8 2011/03/05 16:52:59 dmason Exp $
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
// Vertices

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"


// Photons
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterTools.h"

// GenParticles
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
//#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

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

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"

using namespace edm;
using namespace std;

// actually has a bit more than this but generally defines some useful things
#include "DMason/CMSDASTreeMaker/interface/CMSDASTreeMakerBranchVars.h"


//
// class declaration
//
class CMSDASTreeMaker : public edm::EDAnalyzer {
   public:
      explicit CMSDASTreeMaker(const edm::ParameterSet&);
      ~CMSDASTreeMaker();
      virtual void beginJob() ;
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

      string PFCandidateTag;
      double PFCandidateThresh;

      string TriggerProcessTag;
      InputTag TriggerResultsTag;
      InputTag L1GTReadoutTag;
      InputTag L1GTObjectMapTag;
      vector<string> HLTTriggers;
      vector<string> L1Triggers;
      vector<unsigned int> TrigIndex;
      HLTConfigProvider HltConfig;   

      vector<string> FullHLTTriggerNames;
      vector<int> HLTVersions;

      string VertexTag;

      string PhotonTag;
      bool PhotonDetails;
      double PhotonThresh;
 
      string PFPhotonTag;
      double PFPhotonThresh;       

      string TreeName;

      Service<TFileService> fs;
      TTree *myTree;

      EventBranches  EventData;
      TrigBranches HLTData;
      VertexBranches VertexData;
      PhotonBranches PhotonData;
      GenInfoBranches GenData;
      PFCandidateBranches PFData;
};


//
// constants, enums and typedefs
//
//
// static data member definitions
//

