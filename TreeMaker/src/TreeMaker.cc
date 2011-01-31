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
// $Id: TreeMaker.cc,v 1.2 2011/01/29 22:44:10 dmason Exp $
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
  CaloJECL2Tag      = iConfig.getUntrackedParameter<string>              ("CaloJECL2Tag","");
  CaloJECL3Tag      = iConfig.getUntrackedParameter<string>              ("CaloJECL3Tag","");
  CaloJECResTag      = iConfig.getUntrackedParameter<string>              ("CaloJECResTag","");
  CaloJECUncertTag      = iConfig.getUntrackedParameter<string>              ("CaloJECUncertTag","");
  CaloJECServiceName      = iConfig.getUntrackedParameter<string>              ("CaloJECServiceName","");

  CaloJetThresh      = iConfig.getUntrackedParameter<double>              ("CaloJetThresh",10.0);

  PFJetTag      = iConfig.getUntrackedParameter<string>              ("PFJetTag","");
  PFJECL2Tag      = iConfig.getUntrackedParameter<string>              ("PFJECL2Tag","");
  PFJECL3Tag      = iConfig.getUntrackedParameter<string>              ("PFJECL3Tag","");
  PFJECResTag      = iConfig.getUntrackedParameter<string>              ("PFJECResTag","");
  PFJECUncertTag      = iConfig.getUntrackedParameter<string>              ("PFJECUncertTag","");
  PFJECServiceName      = iConfig.getUntrackedParameter<string>              ("PFJECServiceName","");
  PFJetThresh      = iConfig.getUntrackedParameter<double>              ("PFJetThresh",10.0);

  JPTJetTag      = iConfig.getUntrackedParameter<string>              ("JPTJetTag","");
  JPTJECL2Tag      = iConfig.getUntrackedParameter<string>            ("JPTJECL2Tag","");
  JPTJECL3Tag      = iConfig.getUntrackedParameter<string>            ("JPTJECL3Tag","");
  JPTJECResTag      = iConfig.getUntrackedParameter<string>           ("JPTJECResTag","");
  JPTJECUncertTag      = iConfig.getUntrackedParameter<string>        ("JPTJECUncertTag","");
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


/*
  if (CaloJECL2Tag.length()>0 && CaloJECL3Tag.length()>0) {
    cout << "Setting up JEC's" << endl;
    string JEC_PATH("CondFormats/JetMETObjects/data/");
    edm::FileInPath fipL2(JEC_PATH+CaloJECL2Tag+".txt");
    edm::FileInPath fipL3(JEC_PATH+CaloJECL3Tag+".txt");
    edm::FileInPath fipRes(JEC_PATH+CaloJECResTag+".txt");
    edm::FileInPath fipUncert(JEC_PATH+CaloJECUncertTag+".txt");
    JetCorrectorParameters *L2JetCorPar = new JetCorrectorParameters(fipL2.fullPath());
    JetCorrectorParameters *L3JetCorPar = new JetCorrectorParameters(fipL3.fullPath());
    JetCorrectorParameters *ResJetCorPar = new JetCorrectorParameters(fipRes.fullPath());
    JetCorUncert = new JetCorrectionUncertainty(fipUncert.fullPath());
    cout<<fipL2.fullPath()<<endl;
    cout<<fipL3.fullPath()<<endl;
    if (!IsMonteCarlo) {
      cout<<fipRes.fullPath()<<endl;
      cout<<fipUncert.fullPath()<<endl;
    }

    vector<JetCorrectorParameters> vParam;
    vParam.push_back(*L2JetCorPar);
    vParam.push_back(*L3JetCorPar);
    if (!IsMonteCarlo) vParam.push_back(*ResJetCorPar);
    cout << vParam.size();
    JEC = new FactorizedJetCorrector(vParam);

  }

  if (PFJECL2Tag.length()>0 && PFJECL3Tag.length()>0) {
    cout << "Setting up PF JEC's" << endl;
    string JEC_PATH("CondFormats/JetMETObjects/data/");    
    edm::FileInPath fipPFL2(JEC_PATH+PFJECL2Tag+".txt");
    edm::FileInPath fipPFL3(JEC_PATH+PFJECL3Tag+".txt");    
    edm::FileInPath fipPFRes(JEC_PATH+PFJECResTag+".txt");
    edm::FileInPath fipPFUncert(JEC_PATH+PFJECUncertTag+".txt");
    JetCorrectorParameters *L2PFJetCorPar = new JetCorrectorParameters(fipPFL2.fullPath());
    JetCorrectorParameters *L3PFJetCorPar = new JetCorrectorParameters(fipPFL3.fullPath());
 JetCorrectorParameters *ResPFJetCorPar = new JetCorrectorParameters(fipPFRes.fullPath());
    PFJetCorUncert = new JetCorrectionUncertainty(fipPFUncert.fullPath());
    cout<<fipPFL2.fullPath()<<endl;
    cout<<fipPFL3.fullPath()<<endl;
    if (!IsMonteCarlo) {
      cout<<fipPFRes.fullPath()<<endl;
      cout<<fipPFUncert.fullPath()<<endl;
    }
    vector<JetCorrectorParameters> vParam;
    vParam.push_back(*L2PFJetCorPar);
    vParam.push_back(*L3PFJetCorPar);
    if (!IsMonteCarlo) vParam.push_back(*ResPFJetCorPar);
    PFJEC = new FactorizedJetCorrector(vParam);

  }
  cout << "Done setting up JEC's" << endl;
*/


  // Set up tree
//  myTree = fs->make<TTree>(TreeName,TreeName);
  myTree = fs->make<TTree>("Test","Test");
  bookTree();

}

void TreeMaker::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
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
   if ((*caloJets).size() >0)
     {
     // first loop through to get list of guys to keep
     vector<int> indexlist;
     vector<float> corpts,sortedcorpts;
     ptMapper calopttoindex;

     const JetCorrector* calocorrector = JetCorrector::getJetCorrector(CaloJECServiceName,iSetup);

     for (unsigned int ind=0;ind<(*caloJets).size();ind++)
       {
       //cout << "index is: "<< ind << endl; 
       float rawjetpt=(*caloJets)[ind].pt();

       double jecscale=calocorrector->correction((*caloJets)[ind].p4()); 
       float corjetpt=rawjetpt*jecscale;
//     correct here.
       if (rawjetpt>CaloJetThresh) {
           sortedcorpts.push_back(corjetpt);
           calopttoindex[rawjetpt]=ind;
         }
       } // jet loop
     sort(sortedcorpts.begin(),sortedcorpts.end());
     reverse(sortedcorpts.begin(),sortedcorpts.end());
     CaloJetData.nCaloJets=sortedcorpts.size();
     for (unsigned int localind=0;localind<sortedcorpts.size();localind++) {
        unsigned int jetind=calopttoindex[sortedcorpts[localind]];
        //cout << "now index is -- local: " << localind << " jet: " << jetind << endl;
        CaloJetData.rawpt[localind]=(*caloJets)[jetind].pt();
        double jecscale=calocorrector->correction((*caloJets)[jetind].p4());
        CaloJetData.corpt[localind]=(*caloJets)[jetind].pt()*jecscale;
        CaloJetData.eta[localind]=(*caloJets)[jetind].eta();
        cout << CaloJetData.rawpt[localind] << " cor: "  << CaloJetData.corpt[localind] << endl;
      } // passed jet loop
/*
       caloJetStruct thisJet;

       thisJet.rawpt=(*caloJets)[ind].pt();
       cout << "jet: " << ind << " pt: " << thisJet.rawpt << endl;
       thisJet.eta=(*caloJets)[ind].eta();
       thisJet.phi=(*caloJets)[ind].phi();
       thisJet.y=(*caloJets)[ind].y();
       thisJet.rawE=(*caloJets)[ind].energy();
       thisJet.n90=(*caloJets)[ind].n90();
       thisJet.emf=(*caloJets)[ind].emEnergyFraction();
       thisJet.EtaMoment=(*caloJets)[ind].etaetaMoment();
       thisJet.PhiMoment=(*caloJets)[ind].phiphiMoment();
       //if (thisJet.rawpt>CaloJetThresh) tcaloJets->push_back(thisJet);
       tcaloJets->push_back(thisJet);
*/

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
