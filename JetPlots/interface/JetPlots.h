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
  void analyze( const edm::Event& , const edm::EventSetup& );
  void endJob();

private:
  std::string CaloJetAlgorithm, GenJetAlgorithm,label_;
  TH1F h_ptCal, h_etaCal, h_phiCal;
  TH1F h_ptGenAll, h_ptGenLow, h_ptGenAllEtaB, h_ptGenLowEtaB;
  TH1F h_ptGenAllEtaBE, h_ptGenLowEtaBE, h_ptGenAllEtaE, h_ptGenLowEtaE;
  TH1F h_ptGenAllEtaEF, h_ptGenLowEtaEF,h_ptGenAllEtaF,h_ptGenLowEtaF;
  TH1F h_etaGen, h_etaGenLowpt, h_phiGen, h_;
  TH1F h_ptHatAll,h_ptHatLow;
  TFile* m_file;
  DaqMonitorBEInterface* dbe_;
  MonitorElement* me_ptHatAll;
  MonitorElement* me_ptHatLow;
};

#endif
