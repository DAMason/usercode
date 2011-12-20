
#define PhotonSize      (100)
#define GenParticles    (10000) 
#define Triggers        (100)
#define NVertices        (100)
#define PFParticles     (10000)

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


class VertexBranches {
public: 
  int nVertices;
  float chi2[NVertices];
  float ndof[NVertices];
  float x[NVertices];
  float y[NVertices];
  float z[NVertices];

  void Register(TTree *tree) {
    tree->Branch("nVertices"       ,  &nVertices,  "nVertices/I");
    tree->Branch("Vertex_chi2"     ,  &chi2     ,  "chi2[nVertices]/F");
    tree->Branch("Vertex_ndof"     ,  &ndof     ,  "ndof[nVertices]/F");
    tree->Branch("Vertex_x"        ,  &x        ,  "x[nVertices]/F");
    tree->Branch("Vertex_y"        ,  &y        ,  "y[nVertices]/F");
    tree->Branch("Vertex_z"        ,  &z        ,  "z[nVertices]/F");
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
  tree->Branch("Photon_EcalIsoDR04"    , &EcalIso[0]       , "Photon_EcalIsoDR04[nPhotons]/F");
  tree->Branch("Photon_HcalIsoDR04"    , &HcalIso[0]       , "Photon_HcalIsoDR04[nPhotons]/F");
  tree->Branch("Photon_TrackIsoPtHolDR04"    , &TrackIsoPtHol[0]       , "Photon_TrackIsoPtHolDR04[nPhotons]/F");
  tree->Branch("Photon_TrackIsoPtSolDR04"    , &TrackIsoPtSol[0]       , "Photon_TrackIsoPtSolDR04[nPhotons]/F");
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
  int   Index[GenParticles];
  int   Status[GenParticles];
  int   pdgId[GenParticles];
  float Pt[GenParticles];
  float Phi[GenParticles];
  float Eta[GenParticles];
  float E[GenParticles];
  float Vx[GenParticles];
  float Vy[GenParticles];
  float Vz[GenParticles];
  int   nMothers[GenParticles];
  int   nDaughters[GenParticles];
  int   momIndex[GenParticles];

  void Register(TTree *root) {
        root->Branch("GenInfo_Size"            	, &Size, "GenInfo_Size/I");
        root->Branch("GenInfo_Index"           	, &Index[0], "GenInfo_Index[GenInfo_Size]/I");
        root->Branch("GenInfo_Status"          	, &Status[0], "GenInfo_Status[GenInfo_Size]/I");
        root->Branch("GenInfo_pdgId"           	, &pdgId[0], "GenInfo_pdgId[GenInfo_Size]/I");
        root->Branch("GenInfo_Pt"               , &Pt[0], "GenInfo_Pt[GenInfo_Size]/F");
        root->Branch("GenInfo_Phi"             	, &Phi[0], "GenInfo_Phi[GenInfo_Size]/F");
        root->Branch("GenInfo_Eta"             	, &Eta[0], "GenInfo_Eta[GenInfo_Size]/F");
        root->Branch("GenInfo_E"             	, &E[0], "GenInfo_E[GenInfo_Size]/F");
        root->Branch("GenInfo_Vx"              	, &Vx[0], "GenInfo_Vx[GenInfo_Size]/F");
        root->Branch("GenInfo_Vy"               , &Vy[0], "GenInfo_Vy[GenInfo_Size]/F");
        root->Branch("GenInfo_Vz"               , &Vz[0], "GenInfo_Vz[GenInfo_Size]/F");
        root->Branch("GenInfo_nMothers"         , &nMothers[0], "GenInfo_nMothers[GenInfo_Size]/I");
        root->Branch("GenInfo_nDaughters"      	, &nDaughters[0], "GenInfo_nDaughters[GenInfo_Size]/I");
        root->Branch("GenInfo_momIndex"        	, &momIndex[0], "GenInfo_momIndex[GenInfo_Size]/I");
  }
};


class PFCandidateBranches {
public:
  int Size;
  int pdgId[PFParticles];
  float charge[PFParticles];
  float pt[PFParticles];
  float eta[PFParticles];
  float phi[PFParticles];
  float E[PFParticles];
  float vx[PFParticles];
  float vy[PFParticles];
  float vz[PFParticles];
  float Ecalx[PFParticles];
  float Ecaly[PFParticles];
  float Ecalz[PFParticles];
  float ecalEnergy[PFParticles];
  float rawEcalEnergy[PFParticles];
  float hcalEnergy[PFParticles];
  float rawHcalEnergy[PFParticles];
  void Register(TTree *root) {
     root->Branch("PF_Size"            , &Size,             "PF_Size/I");
     root->Branch("PF_pdgId"           , &pdgId[0],         "PF_pdgId[PF_Size]/I");
     root->Branch("PF_charge"          , &charge[0],        "PF_charge[PF_Size]/F");
     root->Branch("PF_pt"              , &pt[0],            "PF_pt[PF_Size]/F");
     root->Branch("PF_eta"             , &eta[0],           "PF_eta[PF_Size]/F");
     root->Branch("PF_phi"             , &phi[0],           "PF_phi[PF_Size]/F"); 
     root->Branch("PF_E"               , &E[0],             "PF_E[PF_Size]/F"); 
     root->Branch("PF_vx"              , &vx[0],            "PF_vx[PF_Size]/F");
     root->Branch("PF_vy"              , &vy[0],            "PF_vy[PF_Size]/F");
     root->Branch("PF_vz"              , &vz[0],            "PF_vz[PF_Size]/F");
     root->Branch("PF_Ecalx"           , &Ecalx[0],         "PF_Ecalx[PF_Size]/F");
     root->Branch("PF_Ecaly"           , &Ecaly[0],         "PF_Ecaly[PF_Size]/F");
     root->Branch("PF_Ecalz"           , &Ecalz[0],         "PF_Ecalz[PF_Size]/F");
     root->Branch("PF_ecalEnergy"      , &ecalEnergy[0],    "PF_ecalEnergy[PF_Size]/F");
     root->Branch("PF_rawEcalEnergy"   , &rawEcalEnergy[0], "PF_rawEcalEnergy[PF_Size]/F");
     root->Branch("PF_hcalEnergy"      , &hcalEnergy[0],    "PF_hcalEnergy[PF_Size]/F");
     root->Branch("PF_rawHcalEnergy"      , &rawHcalEnergy[0],    "PF_rawHcalEnergy[PF_Size]/F");


  }

};


typedef struct 
    {
      int version;
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
       tree->Branch(branchname, &trigState[iTrig],"version/I:L1prescale/I:HLTprescale/I:fired/I");
  }

};








