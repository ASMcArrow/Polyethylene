#include "PolyethyleneTrackInformation.hh"
#include "G4ios.hh"

G4ThreadLocal G4Allocator<PolyethyleneTrackInformation>* PolyethyleneTrackInformationAllocator = 0;

PolyethyleneTrackInformation::PolyethyleneTrackInformation()
{
    InteractionVolume.clear();
    ProtonInelastic = false;
    RecordedWhenBorn = false;
}

PolyethyleneTrackInformation::PolyethyleneTrackInformation(const G4Track* track)
{
    InteractionVolume.clear();
    ProtonInelastic = false;
    RecordedWhenBorn =false;
}

PolyethyleneTrackInformation::PolyethyleneTrackInformation(const PolyethyleneTrackInformation* trackInfo)
{
    InteractionVolume = trackInfo->InteractionVolume;
    ProtonInelastic = trackInfo->ProtonInelastic;
    RecordedWhenBorn = false;
}

void
PolyethyleneTrackInformation::SetIsProtonInelastic(const G4Track* track)
{
    InteractionVolume = track->GetVolume()->GetName();
    ProtonInelastic = true;
}





