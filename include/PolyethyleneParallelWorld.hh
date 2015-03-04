#ifndef PolyethylenePARALLELWORLD_H
#define PolyethylenePARALLELWORLD_H

#include "globals.hh"
#include "G4VUserParallelWorld.hh"
#include "CLHEP/Units/SystemOfUnits.h"

using namespace CLHEP;

class PolyethyleneParallelWorld : public G4VUserParallelWorld
{
public:
    PolyethyleneParallelWorld(G4String worldName);
    virtual ~PolyethyleneParallelWorld()
    {
        if (sDetector != NULL)
            delete sDetector;
    }

    virtual void Construct();
    virtual void ConstructSD();

private:
    G4LogicalVolume *GhostDetectorLog;
    G4LogicalVolume *GhostZBoxLog;

    G4VSensitiveDetector* sDetector;
};
#endif

