// File and Version Information:
// $Header: /nfs/slac/g/glast/ground/cvs/Interleave/src/BackgroundManager.cxx,v 1.3 2008/02/08 21:32:11 usher Exp $
//
// Description: Managment and access for interleave background sources
//
// November 7, 2007 - Tracy Usher
//
// Author(s):
//      T.Usher

#include "BackgroundManager.h"
#include "IBkgndTupleSelectTool.h"
#include "SampledBackground.h"

// static pointer to the singleton object
BackgroundManager* BackgroundManager::m_instance = 0;

BackgroundManager* BackgroundManager::instance()
{
  // Purpose and Method: returns a pointer to the object, instantiates if it
  //                     doesn't exist
  // Inputs:  None
  // Outputs:  pointer to the object
  // Dependencies: None
  // Restrictions and Caveats:  None
  if (!m_instance) m_instance = new BackgroundManager();

  return m_instance;
}

//Constructor for the propagator class
BackgroundManager::BackgroundManager() : m_defaultRate(500)
{
    // Purpose and Method:  Instantiates if it doesn't exist
    // Inputs:  None
    // Outputs:  None
    // Dependencies: Requires that the Geant4 Run Manager has been instantiated
    // Restrictions and Caveats:  See above

    return;
}

/*
bool BackgroundManager::initCel(const std::string& fileName, const std::string& openOpt, 
                                const TObjArray *compNames) {
    /// Purpose and Method:  Initialize the CompositeEventList object
    /// Returns:  true if the object is allocated sucessfully, false otherwise
    if (m_cel) delete m_cel;
    m_cel = new CompositeEventList(fileName, openOpt, compNames);
    if ( (!m_cel) || ( !m_cel->isOk() )) {
        m_cel = 0;
        return false;
    }
    return true;
}
*/

BackgroundManager::~BackgroundManager()
{
//    if (m_cel) delete m_cel;
    return;
}

void BackgroundManager::defineSource(const std::string& name)
{ 
    m_sourceNames.push_back(name);
}

double BackgroundManager::downlinkRate(const std::string& name)
{
    if (m_bkgndToSelMap.empty()) return m_defaultRate; // just to get started 

    double ret = 0;
    
    if(name.empty())
    {
        for(BkgndNameToSelMap::const_iterator it(m_bkgndToSelMap.begin()); it!=m_bkgndToSelMap.end();++it)
        {
            ret += it->second->downlinkRate();
        }

    } 
    else
    {
        ret = m_bkgndToSelMap[name]->downlinkRate();
    }
    return ret;
}

double BackgroundManager::triggerRate(const std::string& name)
{
    double ret = 0;

    if(name.empty())
    {
        for(BkgndNameToSelMap::const_iterator it(m_bkgndToSelMap.begin()); it!=m_bkgndToSelMap.end();++it)
        {
            ret += it->second->triggerRate();
        }
    } 
    else
    {
        ret = m_bkgndToSelMap[name]->triggerRate();
    }
    return ret;
}
