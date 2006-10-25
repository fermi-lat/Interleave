/** @file InterleaveAlg.h

@brief declaration  of the class InterleaveAlg

$Header: /nfs/slac/g/glast/ground/cvs/Interleave/src/InterleaveAlg.h,v 1.8 2006/01/18 23:30:15 burnett Exp $

*/
#ifndef InterleaveAlg_h
#define InterleaveAlg_h

#include "BackgroundSelection.h"

#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/Property.h"
#include <map>
#include <string>
class BackgroundSelection;
class INTupleWriterSvc;
class ILivetimeSvc;
class SampledBackground;
class TTree;
class TFile;
class TLeaf;


/** @class InterleaveAlg
    @brief Gaudi Alg that will fill the ntuple with a background event
 
    It is expected to be invoked for every non-triggering event, on a branch for the Trigger
    algorithm sequence.

 */


class InterleaveAlg : public Algorithm {
public:
    InterleaveAlg(const std::string& name, ISvcLocator* pSvcLocator);
    StatusCode initialize();
    StatusCode execute();
    StatusCode finalize();

    ///! 
    static double downlinkRate(const std::string& tvar="");
    static double triggerRate(const std::string& tvar="");

    ///! Set the current source, 
    static void currentSource(const std::string& tvar);
    static void defineSource(const std::string& tvar);

    ///! set the current selector
    void setSelector(BackgroundSelection* selector){m_selector=selector;}
    
private: 
    void copyEventInfo(); ///< set up 

    //double magneticLatitude();
    
    BackgroundSelection* m_selector; ///< current selector


    /// access the ntupleWriter service to write out to ROOT ntuples
    INTupleWriterSvc * m_rootTupleSvc;

    ILivetimeSvc * m_LivetimeSvc;

    StringProperty m_treeName; ///< name of the tree to process
    StringProperty m_rootFile; ///< root file or path to sample events from
    StringArrayProperty m_disableList;
    StringProperty m_mapName;  ///< name of the map tree
    int m_count;   ///< number of processed events
    int m_downlink;

    int m_run, m_event;   ///< current
    int m_irun, m_ievent; ///< interleaved run, event
    TTree * m_meritTuple;

  //  TLeaf * m_magLatLeaf;
    TLeaf * m_runLeaf;
    TLeaf * m_eventLeaf;


    static double s_rate;


};

#endif
