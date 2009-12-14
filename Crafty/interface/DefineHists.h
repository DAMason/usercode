
      typedef std::map<int, TH1D*> BinnedHSet;
      BinnedHSet h_EventCounter;

      BinnedHSet h_CaloMET;
      BinnedHSet h_CaloSumET;
      BinnedHSet h_CaloMETRatio;


      BinnedHSet h_LBarrelCaloJetPt;
      BinnedHSet h_CaloJetPt;
      BinnedHSet h_LCaloJetPt;
      BinnedHSet h_LCaloJetPtJet30trig;
      BinnedHSet h_CaloJetPtJet30trig;
      BinnedHSet h_LCaloJetPtJet50trig;
      BinnedHSet h_CaloJetPtJet50trig;
      BinnedHSet h_BarrelCaloJetPt;

      BinnedHSet h_CaloMETRatioJet5;
      BinnedHSet h_CaloMETRatioJet10;
      BinnedHSet h_CaloMETRatioJet15;
      BinnedHSet h_CaloMETRatioJet30;
      BinnedHSet h_CaloMETRatioJet50;
      BinnedHSet h_CaloMETRatioJet80;
      BinnedHSet h_CaloMETRatioJet110;


      BinnedHSet h_TowerMETRatio;
      BinnedHSet h_CaloTowerEt;
      BinnedHSet h_AcceptedCaloTowerEt;


      BinnedHSet h_TowerMETRatioJet30trig;
      BinnedHSet h_TowerMETRatioJet50trig;

      BinnedHSet h_LBarrelCaloWideJetPt;
      BinnedHSet h_BarrelCaloWideJetPt;


      BinnedHSet h_CaloMETRatioJet5Jet30trig;
      BinnedHSet h_CaloMETRatioJet10Jet30trig;
      BinnedHSet h_CaloMETRatioJet15Jet30trig;
      BinnedHSet h_CaloMETRatioJet30Jet30trig;
      BinnedHSet h_CaloMETRatioJet50Jet30trig;
      BinnedHSet h_CaloMETRatioJet80Jet30trig;
      BinnedHSet h_CaloMETRatioJet110Jet30trig;


      BinnedHSet h_CaloMETRatioJet5Jet50trig;
      BinnedHSet h_CaloMETRatioJet10Jet50trig;
      BinnedHSet h_CaloMETRatioJet15Jet50trig;
      BinnedHSet h_CaloMETRatioJet30Jet50trig;
      BinnedHSet h_CaloMETRatioJet50Jet50trig;
      BinnedHSet h_CaloMETRatioJet80Jet50trig;
      BinnedHSet h_CaloMETRatioJet110Jet50trig;

      BinnedHSet h_TriggerMonitor;

      typedef std::map<int, TH2D*> Binned2DHSet;
      Binned2DHSet h_CaloJetEtaPhi;
      Binned2DHSet h_EtaPhiAcceptedTowers;
      Binned2DHSet h_CaloJetEtaPhiJet30trig;
      Binned2DHSet h_CaloJetEtaPhiJet50trig;
      Binned2DHSet h_CaloJetEtaPhiJetsGreater110;

      Binned2DHSet h_CaloJetPtCaloMETRatio;
      Binned2DHSet h_LCaloJetPtCaloMETRatio;
      Binned2DHSet h_MaxCaloJetPtCaloMETRatio;
      Binned2DHSet h_First100LumisTriggerMonitor;
      Binned2DHSet h_First1000LumisTriggerMonitor;
      Binned2DHSet h_First100LumisL1TechTriggerMonitor;

