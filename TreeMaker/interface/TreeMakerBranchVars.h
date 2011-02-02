
#define CaloJetSize     100


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
  tree->Branch("CaloJet_n90Hits"   , &n90Hits[0]   , "CaloJet_n90Hits[nCaloJets]/I");
  tree->Branch("CaloJet_rawpt"   , &rawpt[0]   , "CaloJet_rawpt[nCaloJets]/F");
  tree->Branch("CaloJet_rawpt"   , &rawpt[0]   , "CaloJet_rawpt[nCaloJets]/F");
  tree->Branch("CaloJet_rawE"    , &rawE[0]    , "CaloJet_rawE[nCaloJets]/F");
  tree->Branch("CaloJet_rawphi"  , &rawphi[0]  , "CaloJet_rawphi[nCaloJets]/F");
  tree->Branch("CaloJet_raweta"  , &raweta[0]  , "CaloJet_raweta[nCaloJets]/F");
  tree->Branch("CaloJet_emf"     , &emf[0]     , "CaloJet_emf[nCaloJets]/F");
  tree->Branch("CaloJet_corpt"   , &corpt[0]   , "CaloJet_corpt[nCaloJets]/F");
  tree->Branch("CaloJet_corE"    , &corE[0]    , "CaloJet_corE[nCaloJets]/F");
  tree->Branch("CaloJet_coreta"  , &coreta[0]  , "CaloJet_coreta[nCaloJets]/F");
  tree->Branch("CaloJet_fHPD"    , &fHPD[0]    , "CaloJet_fHPD[nCaloJets]/F");
  tree->Branch("CaloJet_fRBX"    , &fRBX[0]    , "CaloJet_fRBX[nCaloJets]/F");
  if (detailed){
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




    typedef struct {
      reco::CaloJet rawjet;
      reco::CaloJet corjet;
      float fHPD;
      float fRBX;
      int n90hits;
    } RawCorJetPair;


