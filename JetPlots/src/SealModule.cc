#include "PluginManager/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "DQMServices/Core/interface/DaqMonitorBEInterface.h"
#include "DQMServices/Daemon/interface/MonitorDaemon.h"
#include "FWCore/ServiceRegistry/interface/Service.h"


#include <TH1.h>
#include <TFile.h>
#include "RecoJets/JetPlots/interface/JetPlots.h"
 
DEFINE_SEAL_MODULE();
DEFINE_ANOTHER_FWK_MODULE( JetPlots );
