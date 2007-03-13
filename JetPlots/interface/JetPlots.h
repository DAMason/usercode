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
  std::string CaloJetAlgorithm, GenJetAlgorithm,label_;
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
  // BinnedMEset me_ptGenAllEtaB;
  //BinnedMEset me_ptGenLowEtaB;
  //BinnedMEset me_ptGenAllEtaBE;
  //BinnedMEset me_ptGenLowEtaBE;
  //BinnedMEset me_ptGenAllEtaE;
  //BinnedMEset me_ptGenLowEtaE;
  //BinnedMEset me_ptGenAllEtaEF;
  //BinnedMEset me_ptGenLowEtaEF;
  //BinnedMEset me_ptGenAllEtaF;
  //BinnedMEset me_ptGenLowEtaF;
  BinnedMEset me_etaGen;
  BinnedMEset me_etaGenLowpt;
  BinnedMEset me_phiGen;


};
#endif
