#ifndef COPPERTRACKINFORMATION_H
#define COPPERTRACKINFORMATION_H

#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4Track.hh"
#include "G4Allocator.hh"
#include "G4VUserTrackInformation.hh"

class CopperTrackInformation : public G4VUserTrackInformation
{

public:
    CopperTrackInformation();
    CopperTrackInformation(const G4Track* track);
    CopperTrackInformation(const CopperTrackInformation* trackInfo);
    ~CopperTrackInformation() {}

    void Print() const {}
    void SetIsProtonInelastic(const G4Track* track);
    bool IsProtonInelastic()
    {
        if (m_ProtonInelastic)
            return true;
        else
            return false;
    }

    G4String GetInteractionVolume() const
    {
        if (m_ProtonInelastic)
            return m_InteractionVolume;
    }

private:
    G4String m_InteractionVolume;
    bool m_ProtonInelastic;
};

#endif
