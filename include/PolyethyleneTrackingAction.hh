#ifndef POLYETHYLENETRACKINGACTION_H
#define POLYETHYLENETRACKINGACTION_H

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"
#include "G4String.hh"
#include "globals.hh"

class PolyethyleneTrackingAction : public G4UserTrackingAction
{

public:
    PolyethyleneTrackingAction()  {}
    ~PolyethyleneTrackingAction() {}

    void PreUserTrackingAction(const G4Track *track);
    void PostUserTrackingAction(const G4Track *track);
};

#endif

