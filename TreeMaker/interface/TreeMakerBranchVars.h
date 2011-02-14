
#define CaloJetSize     (100)
#define PhotonSize      (100)
#define GenParticles    (10000) //gigantic?
#define GenDaughters    (10) //gigantic?
#define Triggers        (100)

class EventBranches {
public:
  int Run;
  int Lumi;
  int Bunch;
  int Event;

  void Register(TTree *tree) {
    tree->Branch("Run"       , &Run    ,  "Run/I");
    tree->Branch("Lumi"      , &Lumi   ,  "Lumi/I");
    tree->Branch("Bunch"     , &Bunch  ,  "Bunch/I");
    tree->Branch("Event"     , &Event  ,  "Event/I");
  }
};

class CaloJetBranches {
public:
  int nCaloJets;
  int n90[CaloJetSize];
  int n90Hits[CaloJetSize];
  int nTowers[CaloJetSize];
  float HT20,rawHT20;
  float MHT20,rawMHT20;
  float MHT20Phi,rawMHT20Phi;
  float rawpt[CaloJetSize];
  float rawE[CaloJetSize];
  float rawphi[CaloJetSize];
  float raweta[CaloJetSize];
  float corpt[CaloJetSize];
  float corE[CaloJetSize];
  float corphi[CaloJetSize];
  float coreta[CaloJetSize];
  float emf[CaloJetSize];
  float jecUnc[CaloJetSize];
  float fHPD[CaloJetSize];
  float fRBX[CaloJetSize];
  float etaMoment[CaloJetSize];
  float phiMoment[CaloJetSize];
  float HBE[CaloJetSize];
  float HEE[CaloJetSize];
  float HFE[CaloJetSize];
  float HOE[CaloJetSize];
  float EBE[CaloJetSize];
  float EEE[CaloJetSize];
  float EMHFE[CaloJetSize];

  void Register(TTree *tree,bool detailed) {
  tree->Branch("nCaloJets"       , &nCaloJets  , "nCaloJets/I");
  tree->Branch("CaloJet_HT20"    , &HT20       , "Calojet_HT20/F");
  tree->Branch("CaloJet_MHT20"    , &MHT20       , "Calojet_MHT20/F");
  tree->Branch("CaloJet_MHT20Phi"    , &MHT20Phi       , "Calojet_MHT20Phi/F");
  tree->Branch("CaloJet_rawHT20"    , &rawHT20       , "Calojet_rawHT20/F");  
  tree->Branch("CaloJet_rawMHT20"    , &rawMHT20       , "Calojet_rawMHT20/F");  
  tree->Branch("CaloJet_rawMHT20Phi"    , &rawMHT20Phi       , "Calojet_rawMHT20Phi/F");

  tree->Branch("CaloJet_n90Hits"   , &n90Hits[0]   , "CaloJet_n90Hits[nCaloJets]/I");
  tree->Branch("CaloJet_rawpt"   , &rawpt[0]   , "CaloJet_rawpt[nCaloJets]/F");
  tree->Branch("CaloJet_rawE"    , &rawE[0]    , "CaloJet_rawE[nCaloJets]/F");
  tree->Branch("CaloJet_rawphi"  , &rawphi[0]  , "CaloJet_rawphi[nCaloJets]/F");
  tree->Branch("CaloJet_raweta"  , &raweta[0]  , "CaloJet_raweta[nCaloJets]/F");
  tree->Branch("CaloJet_emf"     , &emf[0]     , "CaloJet_emf[nCaloJets]/F");
  tree->Branch("CaloJet_corpt"   , &corpt[0]   , "CaloJet_corpt[nCaloJets]/F");
  tree->Branch("CaloJet_corE"    , &corE[0]    , "CaloJet_corE[nCaloJets]/F");
  tree->Branch("CaloJet_coreta"  , &coreta[0]  , "CaloJet_coreta[nCaloJets]/F");
  tree->Branch("CaloJet_corphi"  , &corphi[0]  , "CaloJet_corphi[nCaloJets]/F");
  tree->Branch("CaloJet_fHPD"    , &fHPD[0]    , "CaloJet_fHPD[nCaloJets]/F");
  if (detailed){
    tree->Branch("CaloJet_fRBX"    , &fRBX[0]    , "CaloJet_fRBX[nCaloJets]/F");
    tree->Branch("CaloJet_n90"       , &n90[0]     , "CaloJet_n90[nCaloJets]/I");
    tree->Branch("CaloJet_etaMoment" , &etaMoment[0]  , "CaloJet_etaMoment[nCaloJets]/F");
    tree->Branch("CaloJet_phiMoment" , &phiMoment[0]  , "CaloJet_phiMoment[nCaloJets]/F");
    tree->Branch("CaloJet_HBE"       , &HBE[0]     , "CaloJet_HBE[nCaloJets]/F");
    tree->Branch("CaloJet_HEE"       , &HEE[0]     , "CaloJet_HEE[nCaloJets]/F");
    tree->Branch("CaloJet_HOE"       , &HOE[0]     , "CaloJet_HOE[nCaloJets]/F");
    tree->Branch("CaloJet_EBE"       , &EBE[0]     , "CaloJet_EBE[nCaloJets]/F");
    tree->Branch("CaloJet_EEE"       , &EEE[0]     , "CaloJet_EEE[nCaloJets]/F");
    tree->Branch("CaloJet_EMHFE"       , &EMHFE[0]     , "CaloJet_EMHFE[nCaloJets]/F");
  }
  }
};

class PhotonBranches {
public:
  int nPhotons;
  float pt[PhotonSize];
  float eta[PhotonSize];
  float phi[PhotonSize];
  float E[PhotonSize];
  float ScE[PhotonSize];
  float ScRawE[PhotonSize];
  float ScEta[PhotonSize];
  float ScPhi[PhotonSize];
  float HoverE[PhotonSize];
  float EcalIso[PhotonSize];
  float HcalIso[PhotonSize];
  float TrackIsoPtHol[PhotonSize];
  float TrackIsoPtSol[PhotonSize];
  int nTrackSol[PhotonSize];
  int nTrackHol[PhotonSize];
  float EcalIsoDR03[PhotonSize];
  float HcalIsoDR03[PhotonSize];
  float TrackIsoPtHolDR03[PhotonSize];
  float TrackIsoPtSolDR03[PhotonSize];
  int nTrackHolDR03[PhotonSize];
  int nTrackSolDR03[PhotonSize];
  float sigmaIetaIeta[PhotonSize];
  float r9[PhotonSize];
  int hasPixelSeed[PhotonSize];
  int isEGGap[PhotonSize];
  int isEB[PhotonSize];
  int isEBEEGap[PhotonSize];
  int isConv[PhotonSize];
  

  void Register(TTree *tree,bool detailed) {
  tree->Branch("nPhotons"       , &nPhotons  , "nPhotons/I");
  tree->Branch("Photon_pt"    , &pt[0]       , "Photon_pt[nPhotons]/F");
  tree->Branch("Photon_E"    , &E[0]       , "Photon_E[nPhotons]/F");
  tree->Branch("Photon_eta"    , &eta[0]       , "Photon_eta[nPhotons]/F");
  tree->Branch("Photon_phi"    , &phi[0]       , "Photon_phi[nPhotons]/F");
  tree->Branch("Photon_HoverE"    , &HoverE[0]       , "Photon_HoverE[nPhotons]/F");
  tree->Branch("Photon_EcalIso"    , &EcalIso[0]       , "Photon_EcalIso[nPhotons]/F");
  tree->Branch("Photon_HcalIso"    , &HcalIso[0]       , "Photon_HcalIso[nPhotons]/F");
  tree->Branch("Photon_TrackIsoPtHol"    , &TrackIsoPtHol[0]       , "Photon_TrackIsoPtHol[nPhotons]/F");
  tree->Branch("Photon_TrackIsoPtSol"    , &TrackIsoPtSol[0]       , "Photon_TrackIsoPtSol[nPhotons]/F");
  tree->Branch("Photon_sigmaIetaIeta"    , &sigmaIetaIeta[0]       , "Photon_sigmaIetaIeta[nPhotons]/F");
  tree->Branch("Photon_r9"    , &r9[0]       , "Photon_r9[nPhotons]/F");
  tree->Branch("Photon_hasPixelSeed"    , &hasPixelSeed[0]       , "Photon_hasPixelSeed[nPhotons]/I");
  tree->Branch("Photon_isEGGap"    , &isEGGap[0]       , "Photon_isEGGap[nPhotons]/I");
  tree->Branch("Photon_isEB"    , &isEB[0]       , "Photon_isEB[nPhotons]/I");
  tree->Branch("Photon_isEBEEGap"    , &isEBEEGap[0]       , "Photon_isEBEEGap[nPhotons]/I");
  tree->Branch("Photon_isConv"    , &isConv[0]       , "Photon_isConv[nPhotons]/I");
    if (detailed) {
      tree->Branch("Photon_ScE"    , &ScE[0]       , "Photon_ScE[nPhotons]/F");
      tree->Branch("Photon_ScRawE"    , &ScRawE[0]       , "Photon_ScRawE[nPhotons]/F");
      tree->Branch("Photon_ScEta"    , &ScEta[0]       , "Photon_ScEta[nPhotons]/F");
      tree->Branch("Photon_ScPhi"    , &ScPhi[0]       , "Photon_ScPhi[nPhotons]/F");
      tree->Branch("Photon_nTrackHol"    , &nTrackHol[0]       , "Photon_nTrackHol[nPhotons]/I");
      tree->Branch("Photon_nTrackSol"    , &nTrackSol[0]       , "Photon_nTrackSol[nPhotons]/I");
      tree->Branch("Photon_EcalIsoDR03"    , &EcalIsoDR03[0]       , "Photon_EcalIsoDR03[nPhotons]/F");
      tree->Branch("Photon_HcalIsoDR03"    , &HcalIsoDR03[0]       , "Photon_HcalIsoDR03[nPhotons]/F");
      tree->Branch("Photon_TrackIsoPtHolDR03"    , &TrackIsoPtHolDR03[0]       , "Photon_TrackIsoPtHolDR03[nPhotons]/F");
      tree->Branch("Photon_TrackIsoPtSolDR03"    , &TrackIsoPtSolDR03[0]       , "Photon_TrackIsoPtSolDR03[nPhotons]/F");
      tree->Branch("Photon_nTrackHolDR03"    , &nTrackHolDR03[0]       , "Photon_nTrackHolDR03[nPhotons]/I");
      tree->Branch("Photon_nTrackSolDR03"    , &nTrackSolDR03[0]       , "Photon_nTrackSolDR03[nPhotons]/I");
    }      
  }

};

class GenInfoBranches {
public:
  int   Size;
  float mChi0;
  float mGluino;
  float mSquark;
  float xsec;
  int   Index[GenParticles];
  int   Charge[GenParticles];
  int   Status[GenParticles];
  int   pdgId[GenParticles];
  float Pt[GenParticles];
  float Pz[GenParticles];
  float Mass[GenParticles];
  float Phi[GenParticles];
  float Eta[GenParticles];
  float Vx[GenParticles];
  float Vy[GenParticles];
  float Vz[GenParticles];
  int   nMothers[GenParticles];
  int   nDaughters[GenParticles];
  int   momIndex[GenParticles];
  int   dauIndex[GenParticles][GenDaughters];

  void Register(TTree *root) {
        root->Branch("GenInfo_Size"            	, &Size, "GenInfo_Size/I");
        root->Branch("GenInfo_mChi0"            , &mChi0, "GenInfo_mChi0/F");
        root->Branch("GenInfo_mGluino"          , &mGluino, "GenInfo_mGluino/F");
        root->Branch("GenInfo_mSquark"          , &mSquark, "GenInfo_mSquark/F");
        root->Branch("GenInfo_xsec"            	, &xsec, "GenInfo_xsec/F");
        root->Branch("GenInfo_Index"           	, &Index[0], "GenInfo_Index[GenInfo_Size]/I");
        root->Branch("GenInfo_Charge"        	, &Charge[0], "GenInfo_Charge[GenInfo_Size]/I");
        root->Branch("GenInfo_Status"          	, &Status[0], "GenInfo_Status[GenInfo_Size]/I");
        root->Branch("GenInfo_pdgId"           	, &pdgId[0], "GenInfo_pdgId[GenInfo_Size]/I");
        root->Branch("GenInfo_Pt"               , &Pt[0], "GenInfo_Pt[GenInfo_Size]/F");
        root->Branch("GenInfo_Pz"               , &Pz[0], "GenInfo_Pz[GenInfo_Size]/F");
        root->Branch("GenInfo_Mass"            	, &Mass[0], "GenInfo_Mass[GenInfo_Size]/F");
        root->Branch("GenInfo_Phi"             	, &Phi[0], "GenInfo_Phi[GenInfo_Size]/F");
        root->Branch("GenInfo_Eta"             	, &Eta[0], "GenInfo_Eta[GenInfo_Size]/F");
        root->Branch("GenInfo_Vx"              	, &Vx[0], "GenInfo_Vx[GenInfo_Size]/F");
        root->Branch("GenInfo_Vy"               , &Vy[0], "GenInfo_Vy[GenInfo_Size]/F");
        root->Branch("GenInfo_Vz"               , &Vz[0], "GenInfo_Vz[GenInfo_Size]/F");
        root->Branch("GenInfo_nMothers"         , &nMothers[0], "GenInfo_nMothers[GenInfo_Size]/I");
        root->Branch("GenInfo_nDaughters"      	, &nDaughters[0], "GenInfo_nDaughters[GenInfo_Size]/I");
        root->Branch("GenInfo_momIndex"        	, &momIndex[0], "GenInfo_momIndex[GenInfo_Size]/I");
        root->Branch("GenInfo_dauIndex"       	, &dauIndex[0][0],"GenInfo_dauIndex[GenInfo_Size][10]/I");
  }
};


typedef struct 
    {
      int L1prescale;
      int HLTprescale;
      int fired;
    } TrigStruct;


class TrigBranches {
public:
  string TrigNames[Triggers];
  TrigStruct trigState[Triggers]; 
  void Register(TTree *tree,int iTrig) {
       const char* branchname=TrigNames[iTrig].c_str();
       tree->Branch(branchname, &trigState[iTrig],"L1prescale/I:HLTprescale/I:fired/I");
  }

};







    typedef struct {
      reco::CaloJet rawjet;
      reco::CaloJet corjet;
      float fHPD;
      float fRBX;
      int n90hits;
    } RawCorJetPair;


