
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
  float rawpt[CaloJetSize];
  float rawE[CaloJetSize];
  float rawphi[CaloJetSize];
  float raweta[CaloJetSize];
  float corpt[CaloJetSize];
  float corE[CaloJetSize];
  float corphi[CaloJetSize];
  float coreta[CaloJetSize];
  float emf[CaloJetSize];

  void Register(TTree *tree) {
  tree->Branch("nCaloJets"       , &nCaloJets  , "nCaloJets/I");
  tree->Branch("CaloJet_rawpt"   , &rawpt[0]   , "CaloJet_rawpt[nCaloJets]/F");
  tree->Branch("CaloJet_rawE"    , &rawE[0]    , "CaloJet_rawE[nCaloJets]/F");
  tree->Branch("CaloJet_rawphi"  , &rawphi[0]  , "CaloJet_rawphi[nCaloJets]/F");
  tree->Branch("CaloJet_raweta"  , &raweta[0]  , "CaloJet_raweta[nCaloJets]/F");
  tree->Branch("CaloJet_emf"     , &emf[0]     , "CaloJet_emf[nCaloJets]/F");
  tree->Branch("CaloJet_corpt"   , &corpt[0]   , "CaloJet_corpt[nCaloJets]/F");
  tree->Branch("CaloJet_corE"    , &corE[0]    , "CaloJet_corE[nCaloJets]/F");
  tree->Branch("CaloJet_coreta"  , &coreta[0]  , "CaloJet_coreta[nCaloJets]/F");
  tree->Branch("CaloJet_corphi"  , &corphi[0]  , "CaloJet_corphi[nCaloJets]/F");
  }
};


    typedef struct {
      reco::CaloJet rawjet;
      reco::CaloJet corjet;
    } RawCorJetPair;


