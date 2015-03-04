#include "PolyethyleneRunAction.hh"
#include "PolyethyleneActionInitialization.hh"
#include "PolyethylenePrimaryGeneratorAction.hh"
#include "PolyethyleneTrackingAction.hh"

PolyethyleneActionInitialization::PolyethyleneActionInitialization()
    : G4VUserActionInitialization()
{}

PolyethyleneActionInitialization::~PolyethyleneActionInitialization()
{}

void PolyethyleneActionInitialization::BuildForMaster() const
{
    SetUserAction(new PolyethyleneRunAction("Detector"));
}

void PolyethyleneActionInitialization::Build() const
{
    SetUserAction(new PolyethylenePrimaryGeneratorAction);
    SetUserAction(new PolyethyleneRunAction("Detector"));
    SetUserAction(new PolyethyleneTrackingAction);
}
