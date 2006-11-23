/** @file BackgroundSelection.h

    @brief declaration of the BackgroundSelection class

$Header: /nfs/slac/g/glast/ground/cvs/Interleave/src/BackgroundSelection.h,v 1.20 2006/11/22 18:53:28 burnett Exp $

*/


#ifndef BackgroundSelection_h
#define BackgroundSelection_h

#include <string>
#include <vector>

class IFetchEvents;
class TTree;
class TFile;
class TChain;
class TLeaf;

/** @class BackgroundSelection
    @brief manage the selection of background events to merge with signal events
    @author Dan Flath

It uses the name of a tuple variable as a key to look up trigger and downlink rates of a background
source depending on the value of that variable. See the corresponding member functions. Given such
a value, it expects to find a source of such events generated with that value which can be inserted 
into the Gleam output tuple.

*/
class BackgroundSelection
{
public:

    /** @brief ctor
        @param varname tuple variable name
        @param xmlFileName
        @param disableList list of strings specifying branches to disable
        @param outputTree pointer to tree to copy to
    */
    BackgroundSelection(const std::string& varname, const std::string& xmlFileName,
        std::vector<std::string> disableList,
        TTree* outputTree);

    ~BackgroundSelection();

    ///! The current value of the quantity that we are selecting on
    double value()const;

    /** @brief select an event and copy the contents to the output tree
    */
    void selectEvent();

 
    /**@brief the current trigger rate for the current value
    */
    double triggerRate()const{return m_triggerRate;}

    /**@brief the downlink rate for the current value
    */
    double downlinkRate()const{return m_downlinkRate;}

    const std::string& name()const{return m_varname;}

private:
    /** @brief disable branches in the tree, from the disableList
    */
    void disableBranches(TTree*);

    /**@brief Set the addresses of active leaves, so that a GetEvent will perform a copy
    */
    void setLeafPointers(TTree*);

    /**@brief Retrieve the correct tree for current value of the variable(s) so copyEvent comes from correct sample bin
    */
    void setCurrentTree(double val);

    std::string m_varname; ///< name of the variable that we use to key the rates
    TLeaf* m_varleaf;      ///< corresponding TLeaf for access to current value

    unsigned int m_event, m_eventOffset;
   
    TTree* m_outputTree; ///< the tree to copy data to
    TTree* m_inputTree; ///< the tree to copy data from
    
    TFile* m_inputFile; ///< the file that contains the input tree
    std::vector<std::string>m_disableList; ///< list of strings for disable
    std::string m_xmlFileName;  ///< either path to a ROOT file to sample from, or a directory containing files

    IFetchEvents *m_fetch; ///< abstract guy that processes the xml file
    bool m_useChain; ///< flag that we are expecting to find lists of files to combine into TChain objects
    double m_value; ///< current value
    double m_downlinkRate, m_triggerRate;
};


#endif
