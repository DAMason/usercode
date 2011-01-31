
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
// $Id: TreeMaker.h,v 1.1 2011/01/29 22:44:10 dmason Exp $
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


#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"

// Jet corrections
//#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
//#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
//#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"



using namespace edm;
using namespace std;


#include "DMason/TreeMaker/interface/TreeMakerBranchVars.h"


//
// class declaration
//
class TreeMaker : public edm::EDAnalyzer {
   public:
      explicit TreeMaker(const edm::ParameterSet&);
      ~TreeMaker();


   private:
      virtual void beginJob() ;
      virtual void beginRun(const edm::Run&, const edm::EventSetup&);
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void bookTree();
      virtual bool fillTreeCut();
      virtual void flushVectors();
      virtual void endJob() ;
      // ----------member data ---------------------------

      bool IsMonteCarlo;

      string CaloJetTag;
      string CaloJECL2Tag,CaloJECL3Tag,CaloJECResTag,CaloJECUncertTag;
      string CaloJECServiceName;
      string CaloJetIDTag,CaloJetExtenderTag;
      double CaloJetThresh;

      string PFJetTag;
      string PFJECL2Tag,PFJECL3Tag,PFJECResTag,PFJECUncertTag;
      string PFJECServiceName;
      double PFJetThresh;
      string JPTJetTag;

      string JPTJECL2Tag,JPTJECL3Tag,JPTJECResTag,JPTJECUncertTag;
      double JPTJetThresh;

      string GenJetTag;
      double GenJetThresh;

      string CaloMETTag,PFMETTag,TCMETTag;

      string TriggerProcessTag;
      vector<string> HLTTriggers;
      vector<string> L1Triggers;

      string PhotonTag;
      double PhotonThresh;
 
      string PFPhotonTag;
      double PFPhotonThresh;       

      string TreeName;

      Service<TFileService> fs;
      TTree *myTree;

      EventBranches  EventData;
      CaloJetBranches CaloJetData;

//      FactorizedJetCorrector *JEC,*PFJEC;
//      JetCorrectionUncertainty *JetCorUncert,*PFJetCorUncert;


      typedef struct {
        float corpt;
        float rawpt;
        float eta;
        float phi;
        float rawE;
        float corE;
        float y;
        float emf;
        float jecUnc;
        float fHPD;
        float fRBX;
        float EtaMoment;
        float PhiMoment;
        int nTrkVx;
        int nTrkCalo;
        int n90;
        int n90Hits;
      } caloJetStruct;

    caloJetStruct tcaloJets[CaloJetSize];


      typedef map<float,int> ptMapper;

};


//
// constants, enums and typedefs
//
//
// static data member definitions
//

