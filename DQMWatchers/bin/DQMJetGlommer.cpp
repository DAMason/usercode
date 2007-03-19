/*
DQMJetGlommer -- a DQM client that hooks into the collector -- auto subscribing
                 all ME's and tries to auto collate the results.  Further it 
                 should then sum together the results from different pthat bins

Lots of this is blatently stolen from the DQMClientExample in DQMServices...

Author:   D. Mason
Date:     2/24/07 and later...
Revision: Often
*/

#include "DQMServices/Core/interface/MonitorElement.h"
#include "DQMServices/UI/interface/MonitorUIRoot.h"
#include "DQMServices/QualityTests/interface/QCriterionRoot.h"

#include <iostream>
#include <math.h>
#include <map>
#include <boost/regex.hpp>

#include <TApplication.h>
#include <TRandom.h> // this is just the random number generator

#include <SealBase/Callback.h>


using std::cout; using std::endl;
using std::string; using std::vector;

class DQMJetGlommer
{
public:
  // ---------------------------------------------------------------------
  // constructor
  DQMJetGlommer(string hostname, int port_no, string cfuname)
  {
    updates = last_plotting = last_save = last_qtests = last_operation=-1;
    enable_accumulate = enable_softReset = true;

    cout<< " Client " << cfuname << " begins requesting monitoring from host " 
	<< hostname << endl;
  
    int reconnect_delay_secs = 5;
    // start user interface instance
    mui = new MonitorUIRoot(hostname, port_no, cfuname, 
			    reconnect_delay_secs);
    //  subscribe to all available monitorable
    mui->subscribe("Collector/*");

    CollateMonitorElement* testsum=mui->collate1D("sum_C2","C2-summary","Summary");
   mui->add(testsum, "*/*/ptHatLowBin*");
  }

  // ---------------------------------------------------------------------
  // destructor
  ~DQMJetGlommer(void)
  {
    if(mui)delete mui;
  }

  // ---------------------------------------------------------------------
  // receive monitoring data (+send subscription requests)
  // return success flag
  bool receiveMonitoring(void)
  {

    bool useCallback = true;
    
    if(useCallback){
      seal::Callback action(seal::CreateCallback(this, // pointer to class
						 // pointer to method
						 &DQMJetGlommer::save,
						 // method argument
						 200));

      mui->addCallback(action);
    }
    
    // this is the "main" loop where we receive monitoring
    bool ret = mui->update();

    if(!useCallback)
      {
	// save monitoring structure every 200 monitoring cycles
	this->save(200);
      }

     //subscribe to new monitorable
     mui->subscribeNew("*");

     //bool useSubfolders = true;
     //mui->subscribeNew("Collector/", useSubfolders);

    // # of full monitoring cycles processed
    updates = mui->getNumUpdates();

    return ret;
  }

  // ---------------------------------------------------------------------
  // draw (next in line) MonitorElement every N monitoring cycles
  void draw(unsigned N)
  {
    // draw all monitoring objects every 5 monitoring cycles
    if(updates % N == 0 && updates != last_plotting)
      {
	mui->drawAll();
	last_plotting = updates;
      }
  }



  // ---------------------------------------------------------------------
  // save monitoring structure every N monitoring cycles
  void save(int N)
  {
    if(updates % N == 0 && updates != last_save)
      {
	// save monitoring structure in root-file
	mui->save("JetGlommer.root");
	last_save = updates;
      }
  }  // ---------------------------------------------------------------------



  // browse through monitorable, print directory contents
  void listContents(void)
  {
    // browse through monitorable; check if MEs exist
    vector<string> subdirs = mui->getSubdirs();
    vector<string> contents = mui->getMEs();
    
    cout << " Directory " << mui->pwd() << " has";
    if(contents.empty())
      cout << " no";
    else
      cout << " " << contents.size();
    
    cout << " monitoring element(s)" << endl;
    cout << " and";
    if(subdirs.empty())
      cout << " no";
    else
      cout << " " << subdirs.size();
    cout << " subfolder(s)" << endl;
    
    vector<string>::const_iterator it = contents.begin();
    while(it != contents.end())
      {
	string fullpathname = mui->pwd() + "/" + (*it);

	//	cout << " Address of Monitoring Element " << *it 
	//	     << " = " << int(mui->get(fullpathname)) << endl;	

        cout << " Address of Monitoring Element " << *it 
	     << " = " << fullpathname << endl;

        string collector,node,mename;
        extractpieces(fullpathname,collector,node,mename);
        meRegistry[mename]++;

	++it;
      }
     
    it = subdirs.begin();
    while(it != subdirs.end())
      {
	cout << " cd(" << *it << ")" << endl;
	mui->cd(*it);
	listContents();
	mui->goUp();
	cout << " cd .. (currently at " << mui->pwd() << ") " << endl;
	++it;
      }
  }

  void extractpieces(const string& fullpath, string& collector,string& node, string& mepath) {
//    boost::regex e("^(\\w+)\\W\\d+\\W/(\\w+)\\W\\d+\\W/(.+)");
      boost::regex e("^(\\w+)\\d*/(\\w+)\\d*/(.+)");
//    boost::regex e("^.(\\w+)(.+)");
    boost::smatch what; 
    if(boost::regex_match(fullpath, what, e, boost::match_extra))
       {
       if (what.size()>=3) {
          cout << "Collector: " << what[1] << " Node: " << what[2] << " ME: " << what[3] << endl;
          }
//      unsigned i;
//       std::cout << "** Match found **\n   Sub-Expressions:\n";
//       for(i = 0; i < what.size(); ++i)
//           std::cout << "      $" << i << " = \"" << what[i] << "\"\n";
//       std::cout << "   Captures:\n";
       }
  }



private:
  MonitorUserInterface * mui;
  // # of full monitoring cycles processed
  int updates;
 // last time monitoring objects were plotted
  int last_plotting;
  // last time root-file was saved
  int last_save;
  // last time quality tests were checked
  int last_qtests;
  // last time "operations" were performed on MonitorElements
  int last_operation;
  // turn accumulate flag on/off
   bool enable_accumulate;
   // turn soft-reset flag on/off
   bool enable_softReset;

  typedef std::map< string, int > maptype;
  maptype meRegistry;

  };




// usage: DQMJetGlommer <name> <host name> <port_no>
// <name>: name of client; default: JetGlommer
// <host name>: name of collector; 
//                examples: cmstst1.fnal.gov (default), lxcmse2.cern.ch, etc.
// <port_no>: port number for connection with collector
int main(int argc, char** argv)
{
  TApplication app("app",&argc,argv);
  // default client name
  string cfuname = "JetGlommer";
  // default collector host name
  string hostname = "cmstst1.fnal.gov";
  // default port #
  int port_no = 9090;

  if(argc >= 2) cfuname = argv[1];
  if(argc >= 3) hostname = argv[2];
  if(argc >= 4) port_no = atoi(argv[3]);

  DQMJetGlommer * glommage = new DQMJetGlommer(hostname, port_no, cfuname);

  bool stay_in_loop = true;

  stay_in_loop = glommage->receiveMonitoring();

  glommage->listContents();

  string a,b,c;
  string nameinput="Collecor[0]/JetGlob[7]/blap/bweep";
  glommage->extractpieces(nameinput,a,b,c);
  cout << a << "/ " << b << "/ " << c << endl;  

  while(stay_in_loop)
    {
      // receive monitoring data (+send subscription requests)
      // return success flag
      stay_in_loop = glommage->receiveMonitoring();

      // draw (next in line) MonitorElement every 5 monitoring cycles
      glommage->draw(5);

    }

  // save into root file just before exit
  glommage->save(1);
  
  return 0;
}

