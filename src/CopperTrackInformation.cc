#include "CopperTrackInformation.hh"
#include "G4ios.hh"

G4Allocator<CopperTrackInformation> aTrackInformationAllocator;

CopperTrackInformation::CopperTrackInformation()
{
    m_InteractionVolume.clear();
    m_ProtonInelastic = false;
}

CopperTrackInformation::CopperTrackInformation(const G4Track* track)
{
    m_InteractionVolume.clear();
    m_ProtonInelastic = false;
}

CopperTrackInformation::CopperTrackInformation(const CopperTrackInformation* trackInfo)
{
    m_InteractionVolume = trackInfo->m_InteractionVolume;
    m_ProtonInelastic = trackInfo->m_ProtonInelastic;
}

void
CopperTrackInformation::SetIsProtonInelastic(const G4Track* track)
{
    m_InteractionVolume = track->GetVolume()->GetName();
    m_ProtonInelastic = true;
}





