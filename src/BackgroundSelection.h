/** @file BackgroundSelection.h

    @brief declaration of the BackGroundSelection class

$Header: /nfs/slac/g/glast/ground/cvs/Interleave/src/BackgroundSelection.h,v 1.10 2006/01/16 00:04:34 burnett Exp $

*/


#ifndef BackgroundSelection_h
#define BackgroundSelection_h

#include <string>
#include <vector>
class TTree;
class TFile;

/** @class BackgroundSelection
    @brief manage the selection of background events to merge with signal events

*/
class BackgroundSelection
{
public:

    /** @brief ctor
        @param rootFileDirectory name of the directory containing the root files
        @param disableList list of strings specifying branches to disable
        @param outputTree pointer to tree to copy to
    */
    BackgroundSelection(const std::string& rootFileDirectory,
        std::vector<std::string> disableList,
        TTree* outputTree);

    ~BackgroundSelection();


    /** @brief select an event and copy the contents to the output tree
        @param maglat the current magnetic latitude
    */
    void selectEvent(double maglat);

 
    /**@brief the trigger rate for the given magnetic latitude
    */
    static double triggerRate(double maglat);

    /**@brief the downlink rate for the given magnetic latitude
    */
    static double downlinkRate(double maglat);

private:
    /** @brief disable branches in the tree, from the disableList
    */
    void disableBranches(TTree*);

    /**@brief Set the addresses of active leaves, so that a GetEvent will perform a copy
    */
    void setLeafPointers();
    void setLeafPointers(TTree*);

    unsigned int m_event;
    TTree* m_outputTree; ///< the tree to copy data to
    TFile* m_inputFiles[42];
    TTree* m_inputTrees[42];
    int m_inputTreeIndexes[42];
    std::vector<std::string>m_disableList; ///< list of strings for disable
};


#endif
