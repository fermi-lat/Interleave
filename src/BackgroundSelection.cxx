/**  @file BackgroundSelection.cxx
    @brief implementation of class BackgroundSelection
    
  $Header: /nfs/slac/g/glast/ground/cvs/Interleave/src/BackgroundSelection.cxx,v 1.19 2006/01/18 16:37:27 burnett Exp $  
*/

#include "BackgroundSelection.h"

#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"

#include "CLHEP/Random/RandFlat.h"

#include <stdexcept>
#include <cassert>
#include <cmath>
#include <vector>

//------------------------------------------------------------------------
BackgroundSelection::BackgroundSelection(const std::string& rootFileDirectory,
        std::vector<std::string> disableList,
        TTree* outputTree)
: m_event(0)
, m_treeInitialized(0)
, m_eventOffset(0)
, m_currentBinLower(0.)
, m_outputTree(outputTree)
, m_inputTree(0)
, m_inputFile(0)
, m_disableList(disableList)
, m_rootFileDirectory(rootFileDirectory)
{
}
//------------------------------------------------------------------------
BackgroundSelection::~BackgroundSelection()
{
  // Delete the file object if it's been initialized:
  if (m_treeInitialized && m_inputTree)
    delete m_inputTree;
}

//------------------------------------------------------------------------
void BackgroundSelection::setLeafPointers(TTree* pTree)
{

    // first disable the branches
    disableBranches(pTree);

    // iteration over active leaves -- copied from Ttree::Show()

    TObjArray *leaves  = pTree->GetListOfLeaves();
    Int_t nleaves = leaves->GetEntriesFast();
    for (Int_t i=0;i<nleaves;i++) {
        TLeaf *leaf = (TLeaf*)leaves->UncheckedAt(i);
        TBranch *branch = leaf->GetBranch();
        if (branch->TestBit(kDoNotProcess)) continue;
        Int_t len = leaf->GetLen();
        if (len <= 0) continue;

        // here copy the value pointer from the merit tuple
        TLeaf* otherleaf = m_outputTree->GetLeaf(leaf->GetName());
        if( otherleaf==0){
            std::cout << "No leaf " << leaf->GetName() << std::endl;
        }else{
            leaf->SetAddress(otherleaf->GetValuePointer());
        }
    }
}

//------------------------------------------------------------------------
void BackgroundSelection::selectEvent(double maglat)
{
    // make sure we have the right tree selected for new maglat
    setCurrentTree(maglat);    

    do {

        // check event offset for overflow:
        if (m_eventOffset >= m_inputTree->GetEntries())
            m_eventOffset = 0;

        // grab the event:
        m_inputTree->GetEvent(m_eventOffset++);
        
    }while( zenithTheta()>100.);
}
//------------------------------------------------------------------------
double BackgroundSelection::zenithTheta()
{
    double x= m_inputTree->GetLeaf("FT1ZenithTheta")->GetValue();
    return x;
}

//------------------------------------------------------------------------
double BackgroundSelection::triggerRate(double maglat)
{
    // configuration 2: (TKR&&(!VETO||CAL-LO))||CAL-HI:
    // see http://confluence.slac.stanford.edu/display/SCIGRPS/Resulting+Trigger+and+Filter+Rates
    //             y = 0.0981x3 - 2.6109x2 + 7.0757x + 2420.3
    static double c[]={0.0981,   -2.6109,    7.0757,   2420.3};
    double x = fabs(maglat);
    if( x< 9) x=9;
    return  ((c[0]*x + c[1])*x +c[2])*x + c[3];
}

//------------------------------------------------------------------------
double BackgroundSelection::downlinkRate(double  maglat )
{
    // configuration 2: (TKR&&(!VETO||CAL-LO))||CAL-HI:

    //             y = 0.0117x3 - 0.3342x2 - 2.2632x + 498.74
    static double c[]={0.0117,   -0.3342,   -2.2632,   498.74};
    double x = fabs(maglat);
    if( x< 9) x=9;
    return  ((c[0]*x + c[1])*x +c[2])*x + c[3];

}
//------------------------------------------------------------------------
void BackgroundSelection::disableBranches(TTree* t) //const char* pattern)
{
    std::vector<std::string>::const_iterator it= m_disableList.begin();
    for( ; it != m_disableList.end();  ++it) {
        t->SetBranchStatus((*it).c_str(), false);
    }

    // restore this, if needed, for cuts
    t->SetBranchStatus("FT1ZenithTheta", 1);
}
//------------------------------------------------------------------------
void BackgroundSelection::setCurrentTree(double maglat) 
{
    double binLower = floor(fabs(maglat));
    if ( !m_treeInitialized  || (binLower != m_currentBinLower) ) {
      if (m_treeInitialized) {
	// need to clean up current file:
	m_inputFile->Close();  // not sure if we need to close a readonly file
	delete m_inputFile;
      } else {
	// we will be initialized now:
	m_treeInitialized = 1;
      }
      
      // save current bin lower bound for next comparison:
      m_currentBinLower = binLower; 

      // construct tree name from current geolat:
      TString tree_name;
      tree_name += (int)binLower;
      tree_name += "to";
      tree_name += ((int)binLower + 1);
	
      // and then construct file name:
      TString file_name(m_rootFileDirectory);
      file_name+="/";
      file_name+=tree_name;
      file_name+=".root";

      // open file for reading:
      m_inputFile = new TFile(file_name.Data(), "readonly");
      if (0 == m_inputFile) {
	TString error = "Did not find file[" + file_name + "]";
	throw std::invalid_argument(error.Data());
      }
      
      // get the tree:
      m_inputTree =  dynamic_cast<TTree*>(m_inputFile->Get(tree_name.Data()));
      if (0 == m_inputTree) {
	TString error = "Did not find tree[" + tree_name + "] in root file";
	throw std::invalid_argument(error.Data());
      }

      // start at a random location in the tree:
      m_eventOffset = (unsigned int)(RandFlat::shoot()*(m_inputTree->GetEntries() - 1));

      // point tree to buffer for copying events:
      setLeafPointers(m_inputTree);
      
    }  
}
