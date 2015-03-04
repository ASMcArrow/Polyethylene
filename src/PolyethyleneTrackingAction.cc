#include "PolyethyleneTrackingAction.hh"
#include "PolyethyleneTrackInformation.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "G4TrackVector.hh"
#include "G4TrackStatus.hh"

void
PolyethyleneTrackingAction::PreUserTrackingAction(const G4Track* track)
{
    if(track->GetParentID() == 0 && track->GetUserInformation() == 0)
    {
        PolyethyleneTrackInformation* trackInfo = new PolyethyleneTrackInformation(track);
        G4Track* newTrack = (G4Track*)track;
        newTrack->SetUserInformation(trackInfo);
    }
}

void PolyethyleneTrackingAction::PostUserTrackingAction(const G4Track* track)
{
    PolyethyleneTrackInformation* trackInfo = (PolyethyleneTrackInformation*)(track->GetUserInformation());

    G4TrackVector* secondaries = fpTrackingManager->GimmeSecondaries();
    if(secondaries)
    {
        size_t numSeco = secondaries->size();
        if(numSeco > 0)
        {
            for(size_t i = 0; i < numSeco; i++)
            {
                PolyethyleneTrackInformation* trackInfoNew = new PolyethyleneTrackInformation(trackInfo);
                (*secondaries)[i]->SetUserInformation(trackInfoNew);

                if (((*secondaries)[i]->GetCreatorProcess()->GetProcessName() == "protonInelastic")||(trackInfo->IsProtonInelastic()))
                {
                    PolyethyleneTrackInformation* inelastictrackInfo = (PolyethyleneTrackInformation*)(*secondaries)[i]->GetUserInformation();
                    inelastictrackInfo->SetIsProtonInelastic((*secondaries)[i]);
                }
            }
        }
    }
}
