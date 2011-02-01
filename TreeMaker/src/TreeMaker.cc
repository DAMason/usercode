// -*- C++ -*-
//
// Package:    TreeMaker
// Class:      TreeMaker
// 
/**\class TreeMaker TreeMaker.cc DMason/TreeMaker/src/TreeMaker.cc

 Description: [one line class summary]

 Implementation:
     lots of bits generally stolen from 
     QCDAnalysis/HighPTJetAnalysis/InclusiveTreeProducer
     and GMSB-DIPHOTON-2010/GMSBTuple/GMSBTuple
*/
//
// Original Author:  David_Mason
//         Created:  Sat Jan 29 15:42:27 CST 2011
// $Id: TreeMaker.cc,v 1.3 2011/01/31 01:25:38 dmason Exp $
//
//

#include "DMason/TreeMaker/interface/TreeMaker.h" 
//
// constructors and destructor
//
TreeMaker::TreeMaker(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
  CaloJetTag      = iConfig.getUntrackedParameter<string>              ("CaloJetTag");
  CaloJECServiceName      = iConfig.getUntrackedParameter<string>              ("CaloJECServiceName","");

  CaloJetThresh      = iConfig.getUntrackedParameter<double>              ("CaloJetThresh",10.0);

  PFJetTag      = iConfig.getUntrackedParameter<string>              ("PFJetTag","");
  PFJECServiceName      = iConfig.getUntrackedParameter<string>              ("PFJECServiceName","");
  PFJetThresh      = iConfig.getUntrackedParameter<double>              ("PFJetThresh",10.0);

  JPTJetTag      = iConfig.getUntrackedParameter<string>              ("JPTJetTag","");
  JPTJECServiceName      = iConfig.getUntrackedParameter<string>        ("JPTJECServiceName","");
  JPTJetThresh      = iConfig.getUntrackedParameter<double>           ("JPTJetThresh",10.0);

  CaloMETTag      = iConfig.getUntrackedParameter<string>              ("CaloMETTag","");
  PFMETTag      = iConfig.getUntrackedParameter<string>                ("PFMETTag","");
  TCMETTag      = iConfig.getUntrackedParameter<string>                ("TCMETTag","");

  PhotonTag     = iConfig.getUntrackedParameter<string>               ("PhotonTag","");
  PhotonThresh  = iConfig.getUntrackedParameter<double>               ("PhotonThresh",5.0);


  PFPhotonTag     = iConfig.getUntrackedParameter<string>               ("PFPhotonTag","");
  PFPhotonThresh  = iConfig.getUntrackedParameter<double>               ("PFPhotonThresh",5.0);
 
  TriggerProcessTag = iConfig.getUntrackedParameter<string>            ("TriggerProcessTag","HLT");
  HLTTriggers   = iConfig.getUntrackedParameter<vector<string> >        ("HLTTriggers");
  L1Triggers   = iConfig.getUntrackedParameter<vector<string> >        ("L1Triggers");
 
  IsMonteCarlo = iConfig.getUntrackedParameter<bool>                 ("IsMonteCarlo",false);

  TreeName = iConfig.getUntrackedParameter<string>                   ("TreeName","TheTree");
}


TreeMaker::~TreeMaker()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//


// ------------ method called once each job just before starting event loop  ------------
void 
TreeMaker::beginJob()
{

  // Set up tree
//  myTree = fs->make<TTree>(TreeName,TreeName);
  myTree = fs->make<TTree>("Test","Test");
  bookTree();

}


void 
TreeMaker::beginRun(const edm::Run&, const edm::EventSetup&) 
{

}


// ------------ method called to for each event  ------------
void
TreeMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;


   flushVectors();


// General event things
   EventData.Run=iEvent.id().run();
   EventData.Lumi=iEvent.luminosityBlock();
   EventData.Event=iEvent.id().event();
   EventData.Bunch=iEvent.bunchCrossing();




// CaloJets

   Handle<reco::CaloJetCollection> caloJets;
   iEvent.getByLabel(CaloJetTag,caloJets);

   CaloJetData.nCaloJets=0;
   if (caloJets.isValid()&&((*caloJets).size() >0))
     {
     const JetCorrector* calocorrector = JetCorrector::getJetCorrector(CaloJECServiceName,iSetup);
     vector<RawCorJetPair> keptJets;
     for(reco::CaloJetCollection::const_iterator jetit = caloJets->begin();jetit<caloJets->end();jetit++) {
           RawCorJetPair thisjet;
           thisjet.rawjet=*jetit;
           thisjet.corjet=*jetit;
           double jecscale=calocorrector->correction(thisjet.rawjet.p4()); 
           thisjet.corjet.scaleEnergy(jecscale);  // as of now its a corrected jet...
           if (thisjet.corjet.pt()>CaloJetThresh) keptJets.push_back(thisjet);
        } // jet loop
     // this should sort by corrected jet pt.
     sort(keptJets.begin(),keptJets.end(),rawcorjetsorter);
     CaloJetData.nCaloJets=keptJets.size();
     for (unsigned int ijet=0;ijet<keptJets.size();ijet++) {
     // want to keep 4 vectors of each raw and corrected.
         CaloJetData.corpt[ijet]=keptJets[ijet].corjet.pt();
         CaloJetData.corE[ijet]=keptJets[ijet].corjet.energy();
         CaloJetData.corphi[ijet]=keptJets[ijet].corjet.phi();
         CaloJetData.coreta[ijet]=keptJets[ijet].corjet.eta();
         CaloJetData.rawpt[ijet]=keptJets[ijet].rawjet.pt();
         CaloJetData.rawE[ijet]=keptJets[ijet].rawjet.energy();
         CaloJetData.rawphi[ijet]=keptJets[ijet].rawjet.phi();
         CaloJetData.raweta[ijet]=keptJets[ijet].rawjet.eta();
         CaloJetData.emf[ijet]=keptJets[ijet].rawjet.emEnergyFraction();

         //cout << "corpt: " << CaloJetData.corpt[ijet] << " rawpt: " << CaloJetData.rawpt[ijet] << " coreta: " << keptJets[ijet].corjet.eta() << " raweta: " << keptJets[ijet].rawjet.eta() << endl;

       }


     }

    

#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif


   if (fillTreeCut()) myTree->Fill();


}


// ------------ called at the beginning to set up the tree

void 
TreeMaker::bookTree() {

EventData.Register(myTree);
CaloJetData.Register(myTree);
}

void 
TreeMaker::flushVectors() {

//tcaloJets->clear();

}

// ------------ determines what events fill the tree

bool
TreeMaker::fillTreeCut() {



return true;
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TreeMaker::endJob() {
}


//define this as a plug-in
DEFINE_FWK_MODULE(TreeMaker);
