#ifndef PolyethyleneRUNACTION_H
#define PolyethyleneRUNACTION_H

#include "PolyethyleneRun.hh"

#include "G4UserRunAction.hh"
#include "globals.hh"
#include <vector>

class PolyethyleneRunAction : public G4UserRunAction
{
public:

    PolyethyleneRunAction(const G4String detectorName);
    virtual ~PolyethyleneRunAction();

    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

private:
    G4String CollName1, CollName2;
    G4int CollectionID1, CollectionID2;

    G4String DetectorName;
    G4double Charge[64], Energy[64];
};

#endif




