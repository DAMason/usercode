#ifndef RecoExamples_JetPlots_h
#define RecoExamples_JetPlots_h
/* \class JetPlots
 *
 * \author D. Mason -- based on JetPlotsExample.h by R. Harris
 *
 * \version -12.35
 *
 */



class JetPlots : public edm::EDAnalyzer {
public:
  JetPlots( const edm::ParameterSet & );

protected:
  void beginJob( const edm::EventSetup & );
  void bookBinnedMEs ( int );
  void analyze( const edm::Event& , const edm::EventSetup& );
  void endJob();

private:
  
  bool BinIsBooked[21];
  std::string CaloJetAlgorithm, GenJetAlgorithm, CorJetAlgorithm, label_;
  DaqMonitorBEInterface* dbe_;
  //MonitorElement* me_ptHatAll;
  //MonitorElement* me_ptHatLow;
  //MonitorElement* me_ptGenAll;
  //MonitorElement* me_ptGenLow;
  //MonitorElement* me_ptGenAllEtaB;
  //MonitorElement* me_ptGenLowEtaB;
  //MonitorElement* me_ptGenAllEtaBE;
  //MonitorElement* me_ptGenLowEtaBE;
  //MonitorElement* me_ptGenAllEtaE;
  //MonitorElement* me_ptGenLowEtaE;
  //MonitorElement* me_ptGenAllEtaEF;
  //MonitorElement* me_ptGenLowEtaEF;
  //MonitorElement* me_ptGenAllEtaF;
  //MonitorElement* me_ptGenLowEtaF;
  //MonitorElement* me_etaGen;
  //MonitorElement* me_etaGenLowpt;
  //MonitorElement* me_phiGen;


  typedef std::map< char*, int > maptype;
  maptype meRegistry;

  typedef std::map< int, MonitorElement* > BinnedMEset;

  BinnedMEset me_ptHatAll;
  BinnedMEset me_ptHatLow;
  BinnedMEset me_ptGenAll;
  BinnedMEset me_ptGenLow;
  BinnedMEset me_ptGenAllEtaB;
  BinnedMEset me_ptGenLowEtaB;
  BinnedMEset me_ptGenAllEtaBE;
  BinnedMEset me_ptGenLowEtaBE;
  BinnedMEset me_ptGenAllEtaE;
  BinnedMEset me_ptGenLowEtaE;
  BinnedMEset me_ptGenAllEtaEF;
  BinnedMEset me_ptGenLowEtaEF;
  BinnedMEset me_ptGenAllEtaF;
  BinnedMEset me_ptGenLowEtaF;
  BinnedMEset me_GenDjMEtaBB;
  BinnedMEset me_GenDjM;
  BinnedMEset me_GenEtaEtaBB;
  BinnedMEset me_GenEtaEta;
  BinnedMEset me_GenPtPt;
  BinnedMEset me_GenPtPtBB;
  BinnedMEset me_etaGen;
  BinnedMEset me_etaGenLowpt;
  BinnedMEset me_phiGen;
  BinnedMEset me_ptCalAll;
  BinnedMEset me_ptCalLow;
  BinnedMEset me_ptCalAllEtaB;
  BinnedMEset me_ptCalLowEtaB;
  BinnedMEset me_ptCalAllEtaBE;
  BinnedMEset me_ptCalLowEtaBE;
  BinnedMEset me_ptCalAllEtaE;
  BinnedMEset me_ptCalLowEtaE;
  BinnedMEset me_ptCalAllEtaEF;
  BinnedMEset me_ptCalLowEtaEF;
  BinnedMEset me_ptCalAllEtaF;
  BinnedMEset me_ptCalLowEtaF;
  BinnedMEset me_CalDjMEtaBB;
  BinnedMEset me_CalDjM;
  BinnedMEset me_CalEtaEtaBB;
  BinnedMEset me_CalEtaEta;
  BinnedMEset me_CalPtPt;
  BinnedMEset me_CalPtPtBB;
  BinnedMEset me_ptCorAll;
  BinnedMEset me_ptCorLow;
  BinnedMEset me_ptCorAllEtaB;
  BinnedMEset me_ptCorLowEtaB;
  BinnedMEset me_ptCorAllEtaBE;
  BinnedMEset me_ptCorLowEtaBE;
  BinnedMEset me_ptCorAllEtaE;
  BinnedMEset me_ptCorLowEtaE;
  BinnedMEset me_ptCorAllEtaEF;
  BinnedMEset me_ptCorLowEtaEF;
  BinnedMEset me_ptCorAllEtaF;
  BinnedMEset me_ptCorLowEtaF;
  BinnedMEset me_CorDjMEtaBB;
  BinnedMEset me_CorDjM;
  BinnedMEset me_CorEtaEtaBB;
  BinnedMEset me_CorEtaEta;
  BinnedMEset me_CorPtPt;
  BinnedMEset me_CorPtPtBB;

};
#endif
