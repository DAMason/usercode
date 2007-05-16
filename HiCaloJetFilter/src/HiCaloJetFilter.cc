// -*- C++ -*-
//
// Package:    HiCaloJetFilter
// Class:      HiCaloJetFilter
// 
/**\class HiCaloJetFilter HiCaloJetFilter.cc RecoJets/HiCaloJetFilter/src/HiCaloJetFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  David_Mason
//         Created:  Mon May  7 10:59:28 CDT 2007
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/CaloJet.h"

#include <cmath>
#include <iostream>
#include <stdio.h>

using namespace edm;
using namespace reco;
using namespace std;

//
// class declaration
//

class HiCaloJetFilter : public edm::EDFilter {
   public:
      explicit HiCaloJetFilter(const edm::ParameterSet&);
      ~HiCaloJetFilter();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      std::string CaloJetAlgorithm;
      double CaloJetPtCut;
      virtual void endJob() ;
      
      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
HiCaloJetFilter::HiCaloJetFilter(const edm::ParameterSet& iConfig) :
  CaloJetAlgorithm( iConfig.getParameter<string>( "CaloJetAlgorithm" ) ),
  CaloJetPtCut( iConfig.getParameter<double>( "CaloJetPtCut" ) )
{
   //now do what ever initialization is needed

}


HiCaloJetFilter::~HiCaloJetFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
HiCaloJetFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;



  //Get the CaloJet collection
  Handle<CaloJetCollection> caloJets;
  math::XYZTLorentzVector p4cal;
  iEvent.getByLabel( CaloJetAlgorithm, caloJets );
  double jeteta,jetpt;


  //Loop over the two leading CaloJets and fill some histograms
  int jetInd = 0;
  for( CaloJetCollection::const_iterator cal = caloJets->begin(); cal != caloJets->end(); ++ cal ) {
    jetInd++;
    p4cal=cal->p4();
    jeteta=p4cal.eta();
    jetpt=p4cal.pt();
    if (jetpt > CaloJetPtCut) {
 
      cout << "Event Selected! " << endl;
       cout << "CaloJet: " <<jetInd << " pt: " << jetpt << " Eta: " << jeteta << endl; 
       return true;
    }


  }
  return false; 




}

// ------------ method called once each job just before starting event loop  ------------
void 
HiCaloJetFilter::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
HiCaloJetFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(HiCaloJetFilter);
