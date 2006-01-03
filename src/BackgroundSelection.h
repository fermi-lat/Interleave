/** @file BackgroundSelection.h

    @brief declaration of the BackGroundSelection class

$Header: /nfs/slac/g/glast/ground/cvs/Interleave/src/BackgroundSelection.h,v 1.3 2005/12/25 21:44:30 burnett Exp $

*/


#ifndef BackgroundSelection_h
#define BackgroundSelection_h

#include <string>
class TTree;
class TFile;

/** @class BackgroundSelection
    @brief manage the selection of background events to merge with signal events

*/
class BackgroundSelection
{
public:

    /** @brief ctor
        @param rootFileName name of root file (or files) to open
        @param treename name of the TTree containing the tuple data
    */
    BackgroundSelection(const std::string& rootFileName, const std::string& treename, TTree* other);

    ~BackgroundSelection();


    /** @brief select an event and copy the contents to the other tree
        @param maglat the current magnetic latitude
    */
    void selectEvent(double maglat);

 
    /**@brief the trigger rate for the given magnetic latitude
    */
    double triggerRate(double maglat);

    /**@brief the downlink rate for the given magnetic latitude
    */
    double downlinkRate(double maglat);

    /** @brief disable leaves matching the pattern

    */
    void disable(const char* pattern);

private:
    /**@brief Set the addresses of active leaves, so that a GetEvent will perform a copy

    */
    void setLeafPointers();

    unsigned int m_event;
    TTree* m_tree;
    TFile* m_file;
    TTree* m_outputTree; ///< the tree to copy data to
};


#endif
