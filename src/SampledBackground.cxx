/** @file SampledBackground.cxx

@brief declaration and definition of the class SampledBackground

$Header: /nfs/slac/g/glast/ground/cvs/Interleave/src/SampledBackground.cxx,v 1.4 2006/10/25 17:14:30 burnett Exp $

*/
#include "SampledBackground.h"
#include "BackgroundManager.h"

#include "flux/EventSource.h"



SampledBackground::SampledBackground(const std::string& params)
: m_tupleVar(params)
{
    BackgroundManager::instance()->defineSource(params);
}

// Gives back energy
double SampledBackground::energy(double /*time*/)
{ 
    // tell the InterleaveAlg that we were the one to generate this event
//    InterleaveAlg::currentSource(m_tupleVar);
    return 0.;
}

// Gives back paticle direction in cos(theta) and phi[rad]
std::pair<double,double> SampledBackground::dir(double /*energy*/)
{ 
    return std::make_pair(0., 0.);
}

// Gives back the total flux into the standard area (limited to downlink here)
double SampledBackground::flux(double /*time*/) const // calculate the flux [c/s/m^2/sr]
{ 
    return  BackgroundManager::instance()->downlinkRate(m_tupleVar)/(EventSource::totalArea() * solidAngle());
}


// Gives back solid angle from which particles come
double SampledBackground::solidAngle() const
{ return 4*M_PI;}

