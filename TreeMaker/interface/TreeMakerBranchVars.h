
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
  float corpt[CaloJetSize];
  float eta[CaloJetSize];

  void Register(TTree *tree) {
  tree->Branch("nCaloJets"       , &nCaloJets , "nCaloJets/I");
  tree->Branch("CaloJet_rawpt"   , &rawpt[0]  , "CaloJet_rawpt[nCaloJets]/F");
  tree->Branch("CaloJet_corpt"   , &corpt[0]  , "CaloJet_corpt[nCaloJets]/F");
  tree->Branch("CaolJet_eta"     , &eta[0]    , "CaloJet_eta[nCaloJets]/F");
  }
};
