/** 
* @file Interleave_load.cpp
* @brief This is needed for forcing the linker to load all components
* of the library.
*
*  $Header: /nfs/slac/g/glast/ground/cvs/Interleave/src/Dll/Interleave_load.cxx,v 1.2 2007/06/27 19:52:14 usher Exp $
*/

#include "GaudiKernel/DeclareFactoryEntries.h"

DECLARE_FACTORY_ENTRIES(Interleave) {
    DECLARE_TOOL( RegisterSampledBackground );
    DECLARE_TOOL( BkgndTupleSelectTool );
    DECLARE_ALGORITHM( InterleaveAlg);
    DECLARE_ALGORITHM( FilterFailAlg);
} 

