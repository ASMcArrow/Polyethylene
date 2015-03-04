#include "PolyethyleneParallelWorld.hh"
#include "PolyethyleneDetectorSD.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4PVReplica.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"
#include "G4UserLimits.hh"

PolyethyleneParallelWorld::PolyethyleneParallelWorld(G4String worldName)
    :G4VUserParallelWorld(worldName)
{   }

//PolyethyleneParallelWorld::~PolyethyleneParallelWorld()
//{}

void PolyethyleneParallelWorld::Construct()
{
    G4VPhysicalVolume *ghostWorld = GetWorld();
    G4LogicalVolume *worldLog = ghostWorld->GetLogicalVolume();

    G4double channelWidth = (0.00127*cm + 0.1585*cm)*2;
    G4double polyWidth = 2*0.1585*cm;
    G4double brassWidth = 2*0.00127*cm;

    G4Box *ghostDetector = new G4Box("GhostDetectorBox", 7.5*cm, 7.5*cm, 64*channelWidth/2);
    GhostDetectorLog = new G4LogicalVolume(ghostDetector, 0, "GhostDetectorLog");
    new G4PVPlacement(0, G4ThreeVector(0, 0, (64*channelWidth/2)/* + brassWidth + (polyWidth/2)*/), GhostDetectorLog, "GhostDetectorPhys", worldLog, 0, 0);

    G4double maxStep = 0.2*channelWidth;
    G4UserLimits* stepLimit = new G4UserLimits(maxStep);
    GhostDetectorLog->SetUserLimits(stepLimit);

    G4VisAttributes* visAttributes = new G4VisAttributes;
    visAttributes->SetColor(0,0,1);
    GhostDetectorLog->SetVisAttributes(visAttributes);

 // Divide along Z coordinate
    G4Box* ghostZBox = new G4Box("ghostXBox", 7.5*cm, 7.5*cm, channelWidth/2);
    GhostZBoxLog = new G4LogicalVolume(ghostZBox, 0, "GhostZBoxLog");
    new G4PVReplica("GhostZBoxPhys", GhostZBoxLog, GhostDetectorLog, kZAxis, 64, channelWidth, 0);
    GhostZBoxLog->SetVisAttributes(visAttributes);
}

void PolyethyleneParallelWorld::ConstructSD()
{
    G4SDManager* sDman = G4SDManager::GetSDMpointer();

    G4VSensitiveDetector* detector = new PolyethyleneDetectorSD("Detector", "EnergyCollection", "ChargeCollection");
    sDman->AddNewDetector(detector);
    GhostZBoxLog->SetSensitiveDetector(detector);
}
