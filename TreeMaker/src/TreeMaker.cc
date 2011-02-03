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
// $Id: TreeMaker.cc,v 1.6 2011/02/02 06:44:09 dmason Exp $
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
  CaloJetDetails      = iConfig.getUntrackedParameter<bool>              ("CaloJetDetails",false);
  CaloJetIDTag      = iConfig.getUntrackedParameter<string>              ("CaloJetIDTag","");
  CaloJetExtenderTag      = iConfig.getUntrackedParameter<string>              ("CaloJetExtenderTag","");
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
  PhotonDetails     = iConfig.getUntrackedParameter<bool>               ("PhotonDetails",false);
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


   Handle<View<reco::CaloJet> > caloJets;
   iEvent.getByLabel(CaloJetTag,"", caloJets);

   Handle<reco::JetExtendedAssociation::Container> jetExtender;
   iEvent.getByLabel(CaloJetExtenderTag,jetExtender);

   Handle<ValueMap<reco::JetID> > jetID;
   iEvent.getByLabel(CaloJetIDTag,jetID);

   float HT20=0,rawHT20=0;
   math::XYZTLorentzVector Jet20P4sum,rawJet20P4sum;
   Jet20P4sum.SetPxPyPzE(0,0,0,0);
   rawJet20P4sum.SetPxPyPzE(0,0,0,0);

   CaloJetData.nCaloJets=0;
   if (caloJets.isValid()&&(caloJets->size() >0))
     {
     //fetch corrections
     const JetCorrector* calocorrector = JetCorrector::getJetCorrector(CaloJECServiceName,iSetup);

     //have a class set up to hold both raw and corrected jets (and jet id) 
     //together so that they can all be sorted together
     vector<RawCorJetPair> keptJets;
     keptJets.clear();
     for(View<reco::CaloJet>::const_iterator jetit = caloJets->begin();jetit<caloJets->end();jetit++) {

       unsigned int ind= jetit-caloJets->begin();
       RefToBase<reco::CaloJet> jetRef = caloJets->refAt(ind);

       RawCorJetPair thisjet;
       thisjet.rawjet=*jetit;
       thisjet.corjet=*jetit;
       thisjet.fHPD=(*jetID)[jetRef].fHPD;
       thisjet.fRBX=(*jetID)[jetRef].fRBX;
       thisjet.n90hits=(*jetID)[jetRef].n90Hits;


       double jecscale=calocorrector->correction(thisjet.rawjet.p4()); 
       thisjet.corjet.scaleEnergy(jecscale);  // as of now its a corrected 
                                                  //jet -- scaled p4...
           //HT and MHT sums
           if (thisjet.corjet.pt()>20.0) {
            HT20+=thisjet.corjet.pt();
            Jet20P4sum+=thisjet.corjet.p4();
           }
           if (thisjet.rawjet.pt()>20.0) {
            rawHT20+=thisjet.rawjet.pt();
            rawJet20P4sum+=thisjet.rawjet.p4();
           }
           // store things here if its worthy
           if (thisjet.corjet.pt()>CaloJetThresh) keptJets.push_back(thisjet);
        } // jet loop

     // start filling in tree vars

     CaloJetData.HT20=HT20;
     CaloJetData.MHT20=Jet20P4sum.pt();
     CaloJetData.MHT20Phi=-Jet20P4sum.phi();
     CaloJetData.rawHT20=rawHT20;
     CaloJetData.rawMHT20=rawJet20P4sum.pt();
     CaloJetData.rawMHT20Phi=-rawJet20P4sum.phi();
     // this should sort by corrected jet pt.
     sort(keptJets.begin(),keptJets.end(),rawcorjetsorter);
     CaloJetData.nCaloJets=keptJets.size();
     for (unsigned int ijet=0;ijet<keptJets.size();ijet++) {
         CaloJetData.corpt[ijet]=keptJets[ijet].corjet.pt();
         CaloJetData.corE[ijet]=keptJets[ijet].corjet.energy();
         CaloJetData.corphi[ijet]=keptJets[ijet].corjet.phi();
         CaloJetData.coreta[ijet]=keptJets[ijet].corjet.eta();
         CaloJetData.rawpt[ijet]=keptJets[ijet].rawjet.pt();
         CaloJetData.rawE[ijet]=keptJets[ijet].rawjet.energy();
         CaloJetData.rawphi[ijet]=keptJets[ijet].rawjet.phi();
         CaloJetData.raweta[ijet]=keptJets[ijet].rawjet.eta();
         CaloJetData.emf[ijet]=keptJets[ijet].rawjet.emEnergyFraction();
         CaloJetData.n90[ijet]=keptJets[ijet].rawjet.n90();
         CaloJetData.HBE[ijet]=keptJets[ijet].rawjet.hadEnergyInHB();
         CaloJetData.HEE[ijet]=keptJets[ijet].rawjet.hadEnergyInHE();
         CaloJetData.HOE[ijet]=keptJets[ijet].rawjet.hadEnergyInHO();
         CaloJetData.HFE[ijet]=keptJets[ijet].rawjet.hadEnergyInHF();
         CaloJetData.EBE[ijet]=keptJets[ijet].rawjet.emEnergyInEB();
         CaloJetData.EEE[ijet]=keptJets[ijet].rawjet.emEnergyInEE();
         CaloJetData.EMHFE[ijet]=keptJets[ijet].rawjet.emEnergyInHF();

         CaloJetData.n90Hits[ijet]=keptJets[ijet].n90hits;
         CaloJetData.fHPD[ijet]=keptJets[ijet].fHPD;
         CaloJetData.fRBX[ijet]=keptJets[ijet].fRBX;
         //cout << "corpt: " << CaloJetData.corpt[ijet] << " rawpt: " << CaloJetData.rawpt[ijet] << " coreta: " << keptJets[ijet].corjet.eta() << " raweta: " << keptJets[ijet].rawjet.eta() << endl;

       }


     }

// CaloMET


// Photons

  Handle<reco::PhotonCollection> Photons;
  iEvent.getByLabel(PhotonTag, Photons);
//  View<reco::Photon> Photons=*PhotonHandle;
  
  vector<reco::Photon> keptPhotons;
     keptPhotons.clear();
  for(reco::PhotonCollection::const_iterator photonit = Photons->begin();photonit<Photons->end();photonit++) {
     //reco::Photon photon=*photonit;
     if ((*photonit).et()>PhotonThresh) keptPhotons.push_back(*photonit);


     }

     sort(keptPhotons.begin(),keptPhotons.end(),photonsorter);
     PhotonData.nPhotons=keptPhotons.size();
     for (unsigned int ip=0;ip<keptPhotons.size();ip++) {
       PhotonData.pt[ip]=keptPhotons[ip].et();  
       PhotonData.E[ip]=keptPhotons[ip].energy();  
       PhotonData.eta[ip]=keptPhotons[ip].eta();  
       PhotonData.phi[ip]=keptPhotons[ip].phi();  
       PhotonData.ScE[ip]=keptPhotons[ip].superCluster()->energy();  
       PhotonData.ScRawE[ip]=keptPhotons[ip].superCluster()->rawEnergy();  
       PhotonData.ScEta[ip]=keptPhotons[ip].superCluster()->position().eta();  
       PhotonData.ScPhi[ip]=keptPhotons[ip].superCluster()->position().phi();  
       PhotonData.HoverE[ip]=keptPhotons[ip].hadronicOverEm();  
       PhotonData.EcalIso[ip]=keptPhotons[ip].ecalRecHitSumEtConeDR04();  
       PhotonData.HcalIso[ip]=keptPhotons[ip].hcalTowerSumEtConeDR04();  
       PhotonData.TrackIsoPtHol[ip]=keptPhotons[ip].trkSumPtHollowConeDR04();  
       PhotonData.TrackIsoPtSol[ip]=keptPhotons[ip].trkSumPtSolidConeDR04();  
       PhotonData.nTrackHol[ip]=keptPhotons[ip].nTrkHollowConeDR04();  
       PhotonData.nTrackSol[ip]=keptPhotons[ip].nTrkSolidConeDR04();  
       PhotonData.EcalIsoDR03[ip]=keptPhotons[ip].ecalRecHitSumEtConeDR03();  
       PhotonData.HcalIsoDR03[ip]=keptPhotons[ip].hcalTowerSumEtConeDR03();  
       PhotonData.TrackIsoPtHolDR03[ip]=keptPhotons[ip].trkSumPtHollowConeDR03();  
       PhotonData.TrackIsoPtSolDR03[ip]=keptPhotons[ip].trkSumPtSolidConeDR03();  
       PhotonData.nTrackHolDR03[ip]=keptPhotons[ip].nTrkHollowConeDR03();  
       PhotonData.nTrackSolDR03[ip]=keptPhotons[ip].nTrkSolidConeDR03();  
       PhotonData.sigmaIetaIeta[ip]=keptPhotons[ip].sigmaIetaIeta();  
       PhotonData.r9[ip]=keptPhotons[ip].r9();  
       PhotonData.hasPixelSeed[ip]=keptPhotons[ip].hasPixelSeed();  
       //cout << "Photon: " << ip << "  " << keptPhotons[ip].et() << endl;

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


EventData.Run=0;
EventData.Lumi=0;
EventData.Event=0;
EventData.Bunch=0;
EventData.Register(myTree);

CaloJetData.nCaloJets=0; // effectively zero's out the arrays
CaloJetData.HT20=0;
CaloJetData.rawHT20=0;
CaloJetData.MHT20=0;
CaloJetData.rawMHT20=0;
CaloJetData.MHT20Phi=0;
CaloJetData.rawMHT20Phi=0;
CaloJetData.Register(myTree,CaloJetDetails);

PhotonData.nPhotons=0;
PhotonData.Register(myTree,PhotonDetails);

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
