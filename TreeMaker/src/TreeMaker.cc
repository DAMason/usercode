// -*- C++ -*-
//
// Package:    TreeMaker
// Class:      TreeMaker
// 
/**\class TreeMaker TreeMaker.cc DMason/TreeMaker/src/TreeMaker.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  David_Mason
//         Created:  Sat Jan 29 15:42:27 CST 2011
// $Id: TreeMaker.cc,v 1.1 2011/01/29 21:45:21 dmason Exp $
//
//

#include "DMason/TreeMaker/interface/TreeMaker.h"

//
// constructors and destructor
//
TreeMaker::TreeMaker(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

}


TreeMaker::~TreeMaker()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
TreeMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;



#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
TreeMaker::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TreeMaker::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(TreeMaker);
