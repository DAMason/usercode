// -*- C++ -*-
//
// Package:    CMSDASTreeMaker
// Class:      CMSDASTreeMaker
// 
/**\class CMSDASTreeMaker CMSDASTreeMaker.cc DMason/CMSDASTreeMaker/src/CMSDASTreeMaker.cc

 Description: [one line class summary]

 Implementation:
     lots of bits generally stolen from 
       QCDAnalysis/HighPTJetAnalysis/InclusiveTreeProducer
       UserCode/GMSB-DIPHOTON-2010/GMSBTuple/GMSBTuple
       UserCode/LPCPJM/SusyAnalysis/SusyNtuplizer
       Some HLT bits from Vasu
*/
//
// Original Author:  David_Mason
//         Created:  Sat Jan 29 15:42:27 CST 2011
// $Id: CMSDASTreeMaker.cc,v 1.9 2011/03/05 16:54:31 dmason Exp $
//
//

#include "DMason/CMSDASTreeMaker/interface/CMSDASTreeMaker.h" 
//
// constructors and destructor
//
CMSDASTreeMaker::CMSDASTreeMaker(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed


  PhotonTag     = iConfig.getUntrackedParameter<string>               ("PhotonTag","");
  PhotonDetails     = iConfig.getUntrackedParameter<bool>               ("PhotonDetails",false);
  PhotonThresh  = iConfig.getUntrackedParameter<double>               ("PhotonThresh",5.0);

  PFCandidateTag = iConfig.getUntrackedParameter<string>               ("PFCandidateTag","");  
  PFCandidateThresh  = iConfig.getUntrackedParameter<double>               ("PFCandidateThresh",1.0);

  VertexTag     = iConfig.getUntrackedParameter<string>               ("VertexTag","");
 
//  TriggerProcessTag = iConfig.getUntrackedParameter<string>            ("TriggerProcessTag","HLT");
  TriggerResultsTag = iConfig.getUntrackedParameter<InputTag>            ("TriggerResultsTag");
  L1GTReadoutTag = iConfig.getUntrackedParameter<InputTag>            ("L1GTObjectMapTag");
  L1GTObjectMapTag = iConfig.getUntrackedParameter<InputTag>            ("L1GTObjectMapTag");
  HLTTriggers   = iConfig.getUntrackedParameter<vector<string> >        ("HLTTriggers");
  L1Triggers   = iConfig.getUntrackedParameter<vector<string> >        ("L1Triggers");
 
  IsMonteCarlo = iConfig.getUntrackedParameter<bool>                 ("IsMonteCarlo",false);

  TreeName = iConfig.getUntrackedParameter<string>                   ("TreeName","TheTree");
}


CMSDASTreeMaker::~CMSDASTreeMaker()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//


// ------------ method called once each job just before starting event loop  ------------
void 
CMSDASTreeMaker::beginJob()
{

  // Set up tree
//  myTree = fs->make<TTree>(TreeName,TreeName);
  myTree = fs->make<TTree>("Test","Test");
  bookTree();

}


void 
CMSDASTreeMaker::beginRun(const edm::Run& iRun, const edm::EventSetup& iSetup) 
{

   if (HLTTriggers.size()>0)
     {
       bool changed(true);
       if (HltConfig.init(iRun,iSetup,TriggerResultsTag.process(),changed)) 
         {
            // if init returns TRUE, initialisation has succeeded!
            TrigIndex.clear();
            for(unsigned int i=0;i<HLTTriggers.size();i++)
              {
              // find the full name with version number in this particular menu...
              FullHLTTriggerNames.push_back(HLTTriggers[i]);
              HLTVersions.push_back(0);
              for (unsigned int iv=1;iv<10;iv++) {
                std::stringstream trigstream;
                trigstream << HLTTriggers[i] << "_v" << iv;
                if (HltConfig.triggerIndex(trigstream.str())<HltConfig.size()) {
                  FullHLTTriggerNames[i]=trigstream.str();
                  HLTVersions[i]=iv;
                }
              }
              cout<<FullHLTTriggerNames[i]<<" "<<HltConfig.triggerIndex(FullHLTTriggerNames[i])<<endl;
              TrigIndex.push_back(HltConfig.triggerIndex(FullHLTTriggerNames[i]));
              if (TrigIndex[i] == HltConfig.size())
                {
                  string errorMessage="Requested TriggerName does not exist! -- "+HLTTriggers[i]+"\n";
                }
              }
            if (changed) 
              {
                std::cout<<"Run: "<<iRun.run()<<".....Changed HLTConfig"<<std::endl;
              }
         } 
       else 
         {
           cout << " HLT config extraction failure with process name " << TriggerResultsTag.process()<<std::endl;
         }
     }



}


// ------------ method called to for each event  ------------
void
CMSDASTreeMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;


   flushVectors();


// General event things
   EventData.Run=iEvent.id().run();
   EventData.Lumi=iEvent.luminosityBlock();
   EventData.Event=iEvent.id().event();
   EventData.Bunch=iEvent.bunchCrossing();


 if (IsMonteCarlo) {
  // get genParticles for MC
  edm::Handle<reco::GenParticleCollection> genHandle;
  iEvent.getByLabel("genParticles", genHandle);


  ////////////////////////////////////////////////
  // start to fill genParticles Info for MC
  ////////////////////////////////////////////////
  memset(&GenData,0x00,sizeof(GenData));

if(!iEvent.isRealData()){

  std::vector<reco::GenParticle> PreselGens;
  for(std::vector <reco::GenParticle>::const_iterator it_gen = genHandle->begin();
        it_gen != genHandle->end(); it_gen++ ) {
                    PreselGens.push_back(*it_gen);
  }

  for(std::vector <reco::GenParticle>::const_iterator it_gen = genHandle->begin();
        it_gen != genHandle->end(); it_gen++ ) {

        if (GenData.Size>=GenParticles) break;

        GenData.Index           [GenData.Size] = GenData.Size;
        GenData.Status          [GenData.Size] = it_gen->status();
        GenData.pdgId           [GenData.Size] = it_gen->pdgId();
        GenData.Pt           	[GenData.Size] = it_gen->pt();
        GenData.E           	[GenData.Size] = it_gen->energy();
        GenData.Phi           	[GenData.Size] = it_gen->phi();
        GenData.Eta           	[GenData.Size] = it_gen->eta();
        GenData.Vx           	[GenData.Size] = it_gen->vx();
        GenData.Vy           	[GenData.Size] = it_gen->vy();
        GenData.Vz           	[GenData.Size] = it_gen->vz();

        int NofDaughters   = it_gen->numberOfDaughters();
        int NofMothers     = it_gen->numberOfMothers();
        GenData.nDaughters    	[GenData.Size] = NofDaughters;
        GenData.nMothers       	[GenData.Size] = NofMothers;
        // fill mother index
        GenData.momIndex        [GenData.Size] = -999;
        if(NofMothers>0){
	  for (int i=0;i<int(PreselGens.size());++i){
		if(it_gen->mother(0)->pdgId()	==PreselGens[i].pdgId() &&
		   it_gen->mother(0)->pt()	==PreselGens[i].pt() &&
		   it_gen->mother(0)->pz()	==PreselGens[i].pz() &&
		   it_gen->mother(0)->phi()	==PreselGens[i].phi() &&
		   it_gen->mother(0)->vx()	==PreselGens[i].vx() &&
                   it_gen->mother(0)->vy()	==PreselGens[i].vy() &&
                   it_gen->mother(0)->vz()	==PreselGens[i].vz()) 
			GenData.momIndex[GenData.Size] = (i<GenParticles)?i:-999;
          }
	}
        GenData.Size++;
    } //Fill the GenParticle TTree
  }
 }// if IsMonteCarlo


  Handle<TriggerResults> triggerResultsHandle;
  //TriggerNames triggerNames;
  if (HLTTriggers.size()>0)
    {
      int ErrFlag=0;
      iEvent.getByLabel(TriggerResultsTag,triggerResultsHandle); 
      if (!triggerResultsHandle.isValid())
        {
          edm::LogError("CMSDASTreeMaker") << "TriggerResults " << TriggerResultsTag << " not available!";
          ErrFlag=-1;
        }

      for(unsigned int i=0;i<HLTTriggers.size();i++) 
        {
          HLTData.trigState[i].version=HLTVersions[i];
          HLTData.trigState[i].fired=ErrFlag;
          HLTData.trigState[i].L1prescale=-1;
          HLTData.trigState[i].HLTprescale=-1;
          bool accept=false;

          if (ErrFlag>-1) {

          // here we play this game of adding "v..." to the requested trigger
          // and hunt for the version number of the thing...
          // and there are a lot of try and open catches here because HLT code
          // seems to want to segfault at the slightest provocation

          bool waslegal=false;
          string therealtriggername;

          //for (int iv=1;iv<10;iv++) {
          //  std::stringstream trigstream;
          //  trigstream << HLTTriggers[i] << "_v" << iv;
          //  string fulltrigname=trigstream.str();
          //  bool waslegal=false;
            //cout << fulltrigname << endl; 
            try {
               //unsigned int trIndex=HltConfig.triggerIndex(HLTTriggers[i]);
               unsigned int trIndex=HltConfig.triggerIndex(FullHLTTriggerNames[i]);
                if (HltConfig.size()!=trIndex) {
                  accept = triggerResultsHandle->accept(trIndex);
                }
                else {
                  accept=false;
                  HLTData.trigState[i].fired=-1;
                }
              }
              catch (...) {
                accept=false;
                HLTData.trigState[i].fired=-1;
              }

              if (accept) {
                HLTData.trigState[i].fired=1;
              }
          //}
          //cout << "the real trigger name was: " << FullHLTTriggerNames[i] << "version: "<< HLTVersions[i] << endl;
          std::pair<int,int> prescalepair;
          try {
            //prescalepair=HltConfig.prescaleValues(iEvent,iSetup,HLTTriggers[i]);
            prescalepair=HltConfig.prescaleValues(iEvent,iSetup,FullHLTTriggerNames[i]);
            //cout << "prescale for " << mTriggerNames[i] << " is " << prescalepair.first << " and " << prescalepair.second << endl;
            HLTData.trigState[i].L1prescale=prescalepair.first;
            HLTData.trigState[i].HLTprescale=prescalepair.second;
            }
          catch (...) {
            HLTData.trigState[i].L1prescale=-1;
            HLTData.trigState[i].HLTprescale=-1;
          }


          }//ErrFlag
        }
    }
    

// Vertex

   Handle<reco::VertexCollection> Vertices;
   vector<reco::Vertex> keptVertices;
   keptVertices.clear();
   try {
       iEvent.getByLabel(VertexTag,Vertices);
       for (reco::VertexCollection::const_iterator vertit = Vertices->begin();vertit<Vertices->end();vertit++) {
         // could apply a cut here...
         keptVertices.push_back(*vertit);
       }
       VertexData.nVertices=keptVertices.size();
       for (unsigned int iv=0;iv<keptVertices.size();iv++){
         if (VertexData.nVertices>=NVertices) break;
         VertexData.chi2[iv]=keptVertices[iv].chi2();
         VertexData.ndof[iv]=keptVertices[iv].ndof();
         VertexData.x[iv]=keptVertices[iv].x();
         VertexData.y[iv]=keptVertices[iv].y();
         VertexData.z[iv]=keptVertices[iv].z();
       }

   } catch(cms::Exception& e) {
     edm::LogError("CMSDASTreeMaker") << "VertexCollection " << VertexTag << " not available!" << e.what();
   }



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

// PFCandidates

Handle<reco::PFCandidateCollection> Candidates;
vector<reco::PFCandidate> keptPFCandidates;
keptPFCandidates.clear();

try{
   iEvent.getByLabel(PFCandidateTag,Candidates);
   for (reco::PFCandidateCollection::const_iterator iPF=Candidates->begin();iPF !=Candidates->end();iPF++) {
     if ((*iPF).pt() >= PFCandidateThresh) {
        keptPFCandidates.push_back(*iPF); 
       }
   }

   PFData.Size=keptPFCandidates.size();
   for (unsigned int ic=0;ic<keptPFCandidates.size();ic++) {
     PFData.pdgId[ic]=keptPFCandidates[ic].translateTypeToPdgId(keptPFCandidates[ic].particleId());
     PFData.charge[ic]=keptPFCandidates[ic].charge();
     PFData.pt[ic]=keptPFCandidates[ic].pt();
     PFData.eta[ic]=keptPFCandidates[ic].eta();
     PFData.phi[ic]=keptPFCandidates[ic].phi();
     PFData.E[ic]=keptPFCandidates[ic].energy();
     PFData.vx[ic]=keptPFCandidates[ic].vx();
     PFData.vy[ic]=keptPFCandidates[ic].vy();
     PFData.vz[ic]=keptPFCandidates[ic].vz();
     PFData.Ecalx[ic]=keptPFCandidates[ic].positionAtECALEntrance().x();
     PFData.Ecaly[ic]=keptPFCandidates[ic].positionAtECALEntrance().y();
     PFData.Ecalz[ic]=keptPFCandidates[ic].positionAtECALEntrance().z();
     PFData.ecalEnergy[ic]=keptPFCandidates[ic].ecalEnergy();
     PFData.rawEcalEnergy[ic]=keptPFCandidates[ic].rawEcalEnergy();
     PFData.hcalEnergy[ic]=keptPFCandidates[ic].hcalEnergy();
     PFData.rawHcalEnergy[ic]=keptPFCandidates[ic].rawHcalEnergy();
     } 

  

   } catch(cms::Exception& e) {
     edm::LogError("CMSDASTreeMaker") << "PFCandidates " << PFCandidateTag << " not available!" << e.what();
   }





#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
   cout << "filling! " << PFData.Size << "pho: " << PhotonData.nPhotons << endl;

   if (fillTreeCut()) myTree->Fill();


}


// ------------ called at the beginning to set up the tree

void 
CMSDASTreeMaker::bookTree() {


EventData.Run=0;
EventData.Lumi=0;
EventData.Event=0;
EventData.Bunch=0;
EventData.Register(myTree);

VertexData.nVertices=0;
VertexData.Register(myTree);

PhotonData.nPhotons=0;
PhotonData.Register(myTree,PhotonDetails);

PFData.Size=0;
PFData.Register(myTree);

if (IsMonteCarlo) {
 GenData.Size=0;
 GenData.Register(myTree);
}

for(unsigned int i=0;i<HLTTriggers.size();i++)
    {
    HLTData.TrigNames[i]=HLTTriggers[i];
    HLTData.Register(myTree,i);
    }
}

void 
CMSDASTreeMaker::flushVectors() {

//tcaloJets->clear();

}

// ------------ determines what events fill the tree

bool
CMSDASTreeMaker::fillTreeCut() {



return true;
}

// ------------ method called once each job just after ending the event loop  ------------
void 
CMSDASTreeMaker::endJob() {
}


//define this as a plug-in
DEFINE_FWK_MODULE(CMSDASTreeMaker);
