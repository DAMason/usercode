/*
DQMGlommer -- a DQM client that hooks into the collector -- auto subscribing
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

class DQMGlommer
{
public:
  // ---------------------------------------------------------------------
  // constructor
  DQMGlommer(string hostname, int port_no, string cfuname)
  {
    updates = last_plotting = last_save = last_qtests = last_operation=-1;
    guys_done=0;
    enable_accumulate = enable_softReset = true;

    cout<< " Client " << cfuname << " begins requesting monitoring from host " 
	<< hostname << endl;
  
    int reconnect_delay_secs = 5;
    bool actasserver=false;
    // start user interface instance
    mui = new MonitorUIRoot(hostname, port_no, cfuname, 
			    reconnect_delay_secs,actasserver);
    //  subscribe to all available monitorable
    mui->subscribe("Collector/*");

    //  set this guy to act like a server too for monitoring 
    //mui->actAsServer(9091,"Blinky");
  }

  // ---------------------------------------------------------------------
  // destructor
  ~DQMGlommer(void)
  {
    if(mui)delete mui;
  }

  // ---------------------------------------------------------------------
  // receive monitoring data (+send subscription requests)
  // return success flag
  bool receiveMonitoring(void)
  {

    bool useCallback = false;
    
    if(useCallback){
      seal::Callback action(seal::CreateCallback(this, // pointer to class
						 // pointer to method
						 &DQMGlommer::save,
						 // method argument
						 1));

      mui->addCallback(action);
    }
    
    // this is the "main" loop where we receive monitoring
    bool ret = mui->update();

    if(!useCallback)
      {
	// save monitoring structure every 100 monitoring cycles
	this->save(100);
      }

     //subscribe to new monitorable
     mui->subscribeNew("Collector/*");


     // register and book collateME's
     registerAndCollate();

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
	mui->save("GlommedMEs.root");
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

	//        string collector,node,mename;
	//      extractpieces(fullpathname,collector,node,mename);
        //    meRegistry[mename]++;

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

  void registerAndCollate(void)
  {
    char cename[37];
//  char cewildcard[37];
    vector<string> subdirs = mui->getSubdirs();
    vector<string> contents = mui->getMEs();
    vector<string>::const_iterator it = contents.begin();
    while(it != contents.end())
      {
      string fullpathname = mui->pwd() + "/" + (*it);
      //cout << *it << endl;
      //     if (matcher(*it,"\\w+\\_is\\_dead")) cout <<" dead! "<< endl;
      //   we will now save only when a "_is_done" message is received 
      //   increment guys_done -- if nonzero we save later...
      //  guys_done++;
      string collector,node,mename,truncmename;
      extractpieces(fullpathname,collector,node,mename);
      if (matcher(mename,"[\\S\\s]+")&&collector!="Summed"){
        //cout << fullpathname <<"  "<< collector << "   "<< node <<"   "<< mename << endl;

        meRegistry[mename]++;
        truncmename=(*it);
        //cout << "meRegistry: " << mename << "  " << meRegistry[mename] << endl;
        if (meRegistry[mename]==1) {
          cout << "New histo set: " << truncmename << endl;
          sprintf(cename,"%s-sum",truncmename.c_str());
          if (matcher(truncmename,"2D.+")) {
	    cout << "booking 2D ME for " << truncmename << endl;
            cmes_All[truncmename]=mui->collate2D(truncmename,cename,"Summed");
          } else {
          cmes_All[truncmename]=mui->collate1D(truncmename,cename,"Summed");
          }
        }

     
        subscRegistry[fullpathname]++;
//      note we're assuming the ME's will all have unique names.
//      this is the case in PA now where the NameAsSource is tweaked
//      on a run by run basis, but not necessarily (Collector can
//      recycle numbered nodenames) 
        if (subscRegistry[fullpathname]==1) {
          mui->add(cmes_All[truncmename],fullpathname);
          }

      }

      

      ++it;
    }

    vector<string> moncontents;
    mui->getAddedMonitorable(moncontents);
    vector<string>::const_iterator mit = moncontents.begin();
    while(mit != moncontents.end()) {
//      this records the guys that have been declared done
//        cout <<" New: " << *mit << endl;
        if (matcher(*mit,".*_is_done")) doneRegistry[*mit]++;
        ++mit;
    }
  

    it = subdirs.begin();
    while(it != subdirs.end())
      {
       mui->cd(*it);
       registerAndCollate();
       mui->goUp();
       ++it;
      }
   }





  bool matcher(const string& testthing, const string& theregex) {
    boost::regex e(theregex);
    boost::smatch what;
    //       cout << testthing << "  "  << theregex << endl;
    return boost::regex_match(testthing,what,e,boost::match_extra);
  }

  bool didsomebodyfinish(void) {
    if (doneRegistry.size()>guys_done) {
      guys_done=doneRegistry.size();
      cout << doneRegistry.size() << " Jobs have finished so far..." << endl;
      return true;
    }
    return false;
  }


  void extractpieces(const string& fullpath, string& collector,string& node, string& mepath) {
//    boost::regex e("^(\\w+)\\W\\d+\\W/(\\w+)\\W\\d+\\W/(.+)");
      boost::regex e("^(\\w+)\\d*/(\\w+-*\\w+)\\d*/([\\s\\S]+)");
//    boost::regex e("^.(\\w+)(.+)");
    boost::smatch what; 
    if(boost::regex_match(fullpath, what, e, boost::match_extra))
       {
       if (what.size()>=3) {
//	          cout << "Collector: " << what[1] << " Node: " << what[2] << " ME: " << what[3] << endl;
	 collector=what[1];
         node=what[2];
         mepath=what[3];
          }
//      unsigned i;
//       std::cout << "** Match found **\n   Sub-Expressions:\n";
//       for(i = 0; i < what.size(); ++i)
//           std::cout << "      $" << i << " = \"" << what[i] << "\"\n";
//       std::cout << "   Captures:\n";
       }
  }

  //  void addtoTH1(MonitorElement * me_In, TH1 * H1out)
  //  {
  //  if(me_In->GetTitle() != H1out->GetTitle())    H1out->setTitle(me_In->GetTitle());
  //  H1out->setAxisRange(xmin,xmax,
  //
  //  } 



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
  // flag that counts guys which finished in last round...
  unsigned int guys_done;

  typedef std::map< string, int > maptype;
  maptype meRegistry;
  maptype subscRegistry;
  maptype doneRegistry;

  typedef std::map< string, CollateMonitorElement* > CMESet;
  CMESet cmes_All;

  };




// usage: DQMGlommer <name> <host name> <port_no>
// <name>: name of client; default: DQMGlommer
// <host name>: name of collector; 
//                examples: cmstst1.fnal.gov (default), lxcmse2.cern.ch, etc.
// <port_no>: port number for connection with collector
int main(int argc, char** argv)
{
  TApplication app("app",&argc,argv);
  // default client name
  string cfuname = "DQMGlommer";
  // default collector host name
  string hostname = "cmstst1.fnal.gov";
  // default port #
  int port_no = 9090;

  if(argc >= 2) cfuname = argv[1];
  if(argc >= 3) hostname = argv[2];
  if(argc >= 4) port_no = atoi(argv[3]);

  DQMGlommer * glommage = new DQMGlommer(hostname, port_no, cfuname);

  bool stay_in_loop = true;

  stay_in_loop = glommage->receiveMonitoring();

  glommage->listContents();

  while(stay_in_loop)
    {
      // receive monitoring data (+send subscription requests)
      // return success flag
      stay_in_loop = glommage->receiveMonitoring();

      // draw (next in line) MonitorElement every 5 monitoring cycles
      // commenting this out -- not clear that randomly displaying plots is
      // all that useful
      //glommage->draw(5);


      // force a save whenever a job finishes somewhere
      if (glommage->didsomebodyfinish()) {
	cout << "  Job(s) finished -- forcing a save..." << endl;
        glommage->save(1);
      }

    }

  // save into root file just before exit
  glommage->save(1);
  
  return 0;
}

