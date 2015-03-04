#include "CopperDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4AssemblyVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4NistManager.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4VSensitiveDetector.hh"
#include "G4MultiFunctionalDetector.hh"
#include "globals.hh"

#include <QMessageBox>
#include <QString>

CopperDetectorConstruction* CopperDetectorConstruction::m_Instance = 0;

CopperDetectorConstruction::CopperDetectorConstruction()
{ m_Instance = this; }

CopperDetectorConstruction* CopperDetectorConstruction::Instance()
{
    return m_Instance;
}

G4VPhysicalVolume* CopperDetectorConstruction::Construct()
{
    G4NistManager* nistManager = G4NistManager::Instance();
    G4Element* H = nistManager->FindOrBuildElement(1);
    G4Element* C = nistManager->FindOrBuildElement(6);
    G4Element* N = nistManager->FindOrBuildElement(7);
    G4Element* O = nistManager->FindOrBuildElement(8);
    G4Element* Zn = nistManager->FindOrBuildElement(30);
    G4Element* Cu = nistManager->FindOrBuildElement(29);

    G4Material* Air = nistManager->FindOrBuildMaterial("G4_AIR");

    Brass = new G4Material("Brass", 8.40*g/cm3, 2);
    Brass -> AddElement(Zn, 3);
    Brass -> AddElement(Cu, 7);

    CH2 = new G4Material("Polyethylene", 0.98*g/cm3, 2);
    CH2->AddElement(H,2);
    CH2->AddElement(C,1);

    G4double xWorld = 2*m;
    G4double yWorld = 0.1*m;
    G4double zWorld = 0.1*m;
    G4Box* world = new G4Box("World", xWorld, yWorld, zWorld);
    m_WorldLogic = new G4LogicalVolume(world, Air,"WorldLogic");
    m_WorldPhys = new G4PVPlacement(0, G4ThreeVector(),
                                    m_WorldLogic,"WorldPhys", 0, false, 0);

    G4Box* brassSheet = new G4Box("BrassSheet", 0.00127*cm, 7.5*cm, 7.5*cm);
    m_BrassLogic = new G4LogicalVolume(brassSheet, Brass, "BrassLogic");

    G4Box* CH2Sheet = new G4Box("CH2Sheet", 0.1585*cm, 7.5*cm, 7.5*cm);
    m_CH2Logic = new G4LogicalVolume(CH2Sheet, CH2, "CH2Logic");

    G4ThreeVector firstPos(0, 0, 0);
    G4ThreeVector secondPos((0.1585*cm + 0.00127*cm), 0, 0);

    G4double channelWidth = (0.00127*cm + 0.1585*cm)*2;
    G4AssemblyVolume* channelLogic = new G4AssemblyVolume();
    channelLogic->AddPlacedVolume(m_BrassLogic, firstPos, 0);
    channelLogic->AddPlacedVolume(m_CH2Logic, secondPos, 0);

    for( unsigned int i = 0; i <= 64; i++ )
    {
        G4ThreeVector offset((channelWidth*i), 0, 0);
        channelLogic->MakeImprint(m_WorldLogic, offset, 0);
     /*   QMessageBox msgBox;
        msgBox.setText("Offset is... "+QString::number(offset.getX()));
        msgBox.exec();*/
    }

    G4VPhysicalVolume* lastBrassSheet
        = new G4PVPlacement(0,
                            G4ThreeVector(65*channelWidth, 0, 0),
                            m_BrassLogic,
                            "LastBrassSheet",
                            m_WorldLogic,
                            false,
                            0);

    return m_WorldPhys;
}

