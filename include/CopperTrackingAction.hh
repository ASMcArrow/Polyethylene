#ifndef COPPERSTAPPINGACTION_H
#define COPPERSTAPPINGACTION_H

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"
#include "G4String.hh"
#include "globals.hh"
#include <QMessageBox>
#include <QString>

class CopperTrackingAction : public G4UserTrackingAction
{

public:
    CopperTrackingAction() {}
    ~CopperTrackingAction() {}

    void PreUserTrackingAction(const G4Track *track);
    void PostUserTrackingAction(const G4Track *track);
};

#endif

