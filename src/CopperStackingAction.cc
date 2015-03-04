#include "CopperStackingAction.hh"
#include "CopperEventAction.hh"
#include "CopperTrackingAction.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"

#include <QMessageBox>
#include <QString>

CopperStackingAction* CopperStackingAction::m_Instance = 0;

G4ClassificationOfNewTrack
CopperStackingAction::ClassifyNewTrack(const G4Track * track)
{
    if(track->GetParentID()>0)
        return fWaiting;
    else
        return fUrgent;
}

void
CopperStackingAction::NewStage()
{}

void
CopperStackingAction::PrepareNewEvent()
{}
