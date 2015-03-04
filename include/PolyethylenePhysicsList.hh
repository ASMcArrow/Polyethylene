#ifndef PolyethylenePHYSICSLIST_H
#define PolyethylenePHYSICSLIST_H

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class PolyethylenePhysicsList: public G4VModularPhysicsList
{
public:

  PolyethylenePhysicsList();
  virtual ~PolyethylenePhysicsList();

  void SetCuts();
  void AddParallelScoring();
  void ConstructProcess();

private:
  G4double cutForGamma;
  G4double cutForElectron;
  G4double cutForPositron;
};

#endif
