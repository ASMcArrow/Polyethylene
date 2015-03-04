#ifndef POLYETHYLENETRACKINFORMATION_H
#define POLYETHYLENETRACKINFORMATION_H

#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4Track.hh"
#include "G4Allocator.hh"
#include "G4VUserTrackInformation.hh"

class PolyethyleneTrackInformation : public G4VUserTrackInformation
{

public:
    PolyethyleneTrackInformation();
    PolyethyleneTrackInformation(const G4Track* track);
    PolyethyleneTrackInformation(const PolyethyleneTrackInformation* trackInfo);
    ~PolyethyleneTrackInformation() {}

    inline void *operator new(size_t);
    inline void operator delete(void *info);

    void Print() const {}
    void SetIsProtonInelastic(const G4Track* track);

    inline bool IsProtonInelastic() const
    {
        if (ProtonInelastic)
            return true;
        else
            return false;
    }

    inline G4String GetInteractionVolume() const
    {
        if (ProtonInelastic)
            return InteractionVolume;
    }

    inline void SetRecordedWhenBorn()
    {
        RecordedWhenBorn = true;
    }

    inline bool GetRecordedWhenBorn() const
    {
        return RecordedWhenBorn;
    }

private:
    G4String InteractionVolume;
    bool ProtonInelastic;
    bool RecordedWhenBorn;
};

extern G4ThreadLocal G4Allocator<PolyethyleneTrackInformation>* PolyethyleneTrackInformationAllocator;

inline void* PolyethyleneTrackInformation::operator new(size_t)
{
    if(!PolyethyleneTrackInformationAllocator)
        PolyethyleneTrackInformationAllocator = new G4Allocator<PolyethyleneTrackInformation>;

    return (void *)PolyethyleneTrackInformationAllocator->MallocSingle();
}

inline void PolyethyleneTrackInformation::operator delete(void *info)
{
    PolyethyleneTrackInformationAllocator->FreeSingle((PolyethyleneTrackInformation*)info);
}

#endif
