#ifndef COPPERDETECTORCONSTRUCTION_H
#define COPPERDETECTORCONSTRUCTION_H

#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;

class CopperDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    CopperDetectorConstruction();
    ~CopperDetectorConstruction() {}

    static CopperDetectorConstruction* Instance();

    G4VPhysicalVolume* Construct();

    G4Material* GetCH2()
    { return CH2; }

private:
    static CopperDetectorConstruction* m_Instance;
    G4Material *Brass, *CH2;

 // Logical volumes
    G4LogicalVolume* m_WorldLogic;
    G4LogicalVolume* m_BrassLogic;
    G4LogicalVolume* m_CH2Logic;

 // Physical volumes
    G4VPhysicalVolume* m_WorldPhys;
    G4VPhysicalVolume* m_BrassPhys;
    G4VPhysicalVolume* m_CH2Phys;
};

#endif

