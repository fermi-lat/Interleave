/**  @file BackgroundSelection.cxx
    @brief implementation of class BackgroundSelection
    
  $Header: /nfs/slac/g/glast/ground/cvs/Interleave/src/BackgroundSelection.cxx,v 1.14 2006/01/13 22:13:42 burnett Exp $  
*/

#include "BackgroundSelection.h"

#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"

#include <stdexcept>
#include <cassert>
#include <cmath>

//------------------------------------------------------------------------
BackgroundSelection::BackgroundSelection(const std::string& rootFileDirectory, 
                                          TTree* outputTree)
: m_event(0)
, m_outputTree(outputTree)
{
   
    for (int latBin=0; latBin<42; latBin++) {
      int binIndex = latBin;
      m_inputTreeIndexes[binIndex] = 0;
      
      TString tree_name;
      tree_name += latBin;
      tree_name += "to";
      tree_name += (latBin + 1);

      TString file_name(rootFileDirectory);
      file_name+="/";
      file_name+=tree_name;
      file_name+=".root";

      m_inputFiles[binIndex] = new TFile(file_name.Data(), "readonly");
      if (0 == m_inputFiles[binIndex]) {
	TString error = "Did not find file[" + file_name + "]";
        throw std::invalid_argument(error.Data());
      }

      m_inputTrees[binIndex] =  dynamic_cast<TTree*>(m_inputFiles[binIndex]->Get(tree_name.Data()));
      if (0 == m_inputTrees[binIndex]) {
	TString error = "Did not find tree[" + tree_name + "] in root file";
        throw std::invalid_argument(error.Data());
      }

    }
}
//------------------------------------------------------------------------
BackgroundSelection::~BackgroundSelection()
{
  // Delete the file objects, the trees will go with them.
  for (int i=0; i<42; i++) {
    delete m_inputFiles[i];
  }
}

//------------------------------------------------------------------------
void BackgroundSelection::setLeafPointers(TTree* pTree)
{

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
void BackgroundSelection::selectEvent(double maglat )
{
    // TODO: have this depend on magnetic latitude

    int binIndex = (int)(floor(fabs(maglat)));

    TTree* pTree = m_inputTrees[binIndex];
    if (m_inputTreeIndexes[binIndex] >= pTree->GetEntries())
      m_inputTreeIndexes[binIndex] = 0;

    Long64_t nEvent = m_inputTreeIndexes[binIndex]++;
    pTree->GetEvent(nEvent);
}

//------------------------------------------------------------------------
double BackgroundSelection::triggerRate(double maglat)
{
    //y = 0.0481x3 - 0.9295x2 - 27.72x + 2082.2
    static double c[]={2082.2, -27.72, -0.9295, 0.0481};

    double x = fabs(maglat);
    if( x< 8) x=8;
    return  ((c[3]*x + c[2])*x +c[1])*x + c[0];
}

//------------------------------------------------------------------------
double BackgroundSelection::downlinkRate(double  maglat )
{
    //y = 0.0094x3 - 0.1951x2 - 5.4218x + 508.48
    static double c[]={508.48, -5.4218, -0.1951, 0.0094};

    double x = fabs(maglat);
    if( x< 8) x=8;
    return ((c[3]*x + c[2])*x +c[1])*x + c[0];

}
//------------------------------------------------------------------------
void BackgroundSelection::disable(const char* pattern)
{
  for (int i=0; i<42; i++) {
    m_inputTrees[i]->SetBranchStatus( pattern, 0);
  }
}
//------------------------------------------------------------------------
void BackgroundSelection::setLeafPointers()
{
    for (int i=0; i<42; i++) {
        setLeafPointers(m_inputTrees[i]);
    }
}