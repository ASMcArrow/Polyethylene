#ifndef COPPERSTEPPINGACTION_H
#define COPPERSTEPPINGACTION_H

#include "G4UserSteppingAction.hh"

class DetectorConstruction;
class EventAction;

class CopperSteppingAction : public G4UserSteppingAction
{
public:
  CopperSteppingAction();
  virtual ~CopperSteppingAction();

  void UserSteppingAction(const G4Step*);

private:
  DetectorConstruction* detector;
  EventAction*          eventaction;
};

#endif

