#ifndef PolyethyleneDETECTORSD_H
#define PolyethyleneDETECTORSD_H

#include "G4VSensitiveDetector.hh"
#include "PolyethyleneDetectorHit.hh"
#include "globals.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class PolyethyleneDetectorSD : public G4VSensitiveDetector
{

public:
  PolyethyleneDetectorSD(G4String name, G4String collname1, G4String collname2);
  ~PolyethyleneDetectorSD();

  void Initialize(G4HCofThisEvent* ); 
  G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* obsolete);
  void EndOfEvent(G4HCofThisEvent* HCE);
 
private:
  PolyethyleneDetectorHitsCollection* ChargeHitsCollection;
  PolyethyleneDetectorHitsCollection* EnergyHitsCollection;
  G4String SensitiveDetectorName;  
};

#endif


