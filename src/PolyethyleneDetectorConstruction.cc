#include "PolyethyleneDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4VSolid.hh"
#include "G4AssemblyVolume.hh"

using namespace CLHEP;

G4VPhysicalVolume* PolyethyleneDetectorConstruction::Construct()
{
    // Cleanup old geometry
    /* G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean(); */

    this->InitializeMaterials();

    G4VisAttributes* visAttributes = new G4VisAttributes;
    visAttributes->SetForceWireframe(true);

    G4Box* world = new G4Box("World", 3*m, 3*m, 3*m);
    G4LogicalVolume *worldLogic = new G4LogicalVolume(world, MaterialMap["Air"], "WorldLogic");
    G4VPhysicalVolume *worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLogic, "WorldPhys", 0, false, 0);
    worldLogic->SetVisAttributes(visAttributes);

    G4VisAttributes* visAttributesInner = new G4VisAttributes;
    visAttributesInner->SetForceSolid(true);

    G4Box* brassSheet = new G4Box("BrassSheet", 7.5*cm, 7.5*cm, 0.00127*cm);
    G4LogicalVolume *brassLogic = new G4LogicalVolume(brassSheet, MaterialMap["Brass"], "BrassLogic");
    brassLogic->SetVisAttributes(visAttributesInner);

    G4Box* CH2Sheet = new G4Box("CH2Sheet", 7.5*cm, 7.5*cm, 0.1585*cm);
    G4LogicalVolume *CH2Logic = new G4LogicalVolume(CH2Sheet, MaterialMap["Polyethylene"], "CH2Logic");
    CH2Logic->SetVisAttributes(visAttributesInner);

    G4ThreeVector firstPos(0, 0, 0);
    G4ThreeVector secondPos(0, 0, (0.1585*cm + 0.00127*cm));
    G4double channelWidth = (0.00127*cm + 0.1585*cm)*2;

    G4AssemblyVolume* channelLogic = new G4AssemblyVolume();
    channelLogic->AddPlacedVolume(brassLogic, firstPos, 0);
    channelLogic->AddPlacedVolume(CH2Logic, secondPos, 0);

    for( unsigned int i = 0; i <= 64; i++ )
    {
        G4ThreeVector offset(0, 0, (channelWidth*i));
        channelLogic->MakeImprint(worldLogic, offset, 0);
    }

    new G4PVPlacement(0, G4ThreeVector(0, 0, 65*channelWidth), brassLogic, "LastBrassSheet", worldLogic,
                                                          false, 0);
    return worldPhys;
}

void PolyethyleneDetectorConstruction::InitializeMaterials()
{
    G4NistManager* nistManager = G4NistManager::Instance();

    G4Element* H = nistManager->FindOrBuildElement(1);
    G4Element* C = nistManager->FindOrBuildElement(6);
    G4Element* O = nistManager->FindOrBuildElement(8);
    G4Element* N = nistManager->FindOrBuildElement(7);
    G4Element* Mg = nistManager->FindOrBuildElement(12);
    G4Element* P = nistManager->FindOrBuildElement(15);
    G4Element* S = nistManager->FindOrBuildElement(16);
    G4Element* Ca = nistManager->FindOrBuildElement(20);
    G4Element* Zn = nistManager->FindOrBuildElement(30);
    G4Element* Na = nistManager->FindOrBuildElement(11);
    G4Element* K = nistManager->FindOrBuildElement(19);
    G4Element* Cl = nistManager->FindOrBuildElement(17);
    G4Element* Fe = nistManager->FindOrBuildElement(26);
    G4Element* Si = nistManager->FindOrBuildElement(14);
    G4Element* Cr = nistManager->FindOrBuildElement(24);
    G4Element* Mn = nistManager->FindOrBuildElement(12);
    G4Element* Ni = nistManager->FindOrBuildElement(28);
    G4Element* Cu = nistManager->FindOrBuildElement(29);
    G4Element* Pb = nistManager->FindOrBuildElement(82);

    G4Material* Air = nistManager->FindOrBuildMaterial("G4_AIR");
    MaterialMap["Air"] = Air;

    G4Material* Mylar = nistManager->FindOrBuildMaterial("G4_MYLAR");
    MaterialMap["Mylar"] = Mylar;

    G4Material* Brass = new G4Material("Brass", 8.50*g/cm3, 4);
    Brass->AddElement(Zn, 0.354);
    Brass->AddElement(Cu, 0.6175);
    Brass->AddElement(Pb, 0.025);
    Brass->AddElement(Fe, 0.0035);
    MaterialMap["Brass"] = Brass;

    G4Material* PMMA = new G4Material("PMMA", 1.17*g/cm3, 3);
    PMMA -> AddElement(H, 8);
    PMMA -> AddElement(C, 5);
    PMMA -> AddElement(O, 2);
    MaterialMap["PMMA"] = PMMA;

    G4Material* StainlessSteel = new G4Material("StainlessSteel", 8.06*g/cm3, 6);
    StainlessSteel->AddElement(C, 0.001);
    StainlessSteel->AddElement(Si, 0.007);
    StainlessSteel->AddElement(Cr, 0.18);
    StainlessSteel->AddElement(Mn, 0.01);
    StainlessSteel->AddElement(Fe, 0.712);
    StainlessSteel->AddElement(Ni, 0.09);
    MaterialMap["StainlessSteel"] = StainlessSteel;

    G4Material* Water = nistManager->FindOrBuildMaterial("G4_WATER");
    MaterialMap["Water"] = Water;

    G4Material* CH2 = new G4Material("Polyethylene", 0.98*g/cm3, 2);
    CH2->AddElement(H,2);
    CH2->AddElement(C,1);
    MaterialMap["Polyethylene"] = CH2;
}


