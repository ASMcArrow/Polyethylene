#include "PolyethyleneRunAction.hh"
#include "PolyethyleneRun.hh"
#include "PolyethyleneDetectorHit.hh"
#include "PolyethyleneDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "PolyethyleneDetectorConstruction.hh"
#include "G4THitsMap.hh"
#include "G4SDManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Run.hh"
#include "G4HadronicInteraction.hh"
#include "G4HadronicInteractionRegistry.hh"
#include "G4INCLXXInterface.hh"
#include "G4AblaInterface.hh"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#define _USE_MATH_DEFINES

PolyethyleneRunAction::PolyethyleneRunAction(const G4String detectorName) : G4UserRunAction()
{
    DetectorName = detectorName;

    for (G4int i = 0; i < 64; i++)
    {
        Charge[i] = 0;
        Energy[i] = 0;
    }
}

PolyethyleneRunAction::~PolyethyleneRunAction()
{}

G4Run* PolyethyleneRunAction::GenerateRun()
{
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    G4VSensitiveDetector* detector = SDman->FindSensitiveDetector(DetectorName);

    CollName1 = detector->GetCollectionName(0);
    CollName2 = detector->GetCollectionName(1);

    CollectionID1 = SDman->GetCollectionID(CollName1);
    CollectionID2 = SDman->GetCollectionID(CollName2);

    return new PolyethyleneRun(DetectorName, 0);
}

void PolyethyleneRunAction::BeginOfRunAction(const G4Run* aRun)
{
    G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

    // Get hold of a pointer to the INCL++ model interface
    G4HadronicInteraction *interaction = G4HadronicInteractionRegistry::Instance()->FindModel("INCL++ v5.1.14");
    G4INCLXXInterface *theINCLInterface = static_cast<G4INCLXXInterface*>(interaction);
    if(theINCLInterface)
    {
        // Instantiate the ABLA model
        interaction = G4HadronicInteractionRegistry::Instance()->FindModel("ABLA");
        G4AblaInterface *theAblaInterface = static_cast<G4AblaInterface*>(interaction);

        if(!theAblaInterface)
            theAblaInterface = new G4AblaInterface;

        // Couple INCL++ to ABLA
        G4cout << "Coupling INCLXX to ABLA" << G4endl;
        theINCLInterface->SetDeExcitation(theAblaInterface);
    }
}

void PolyethyleneRunAction::EndOfRunAction(const G4Run* aRun)
{
    if(!IsMaster()) return;

    PolyethyleneRun *polyethyleneRun = (PolyethyleneRun*)aRun;

    G4int hitNum = polyethyleneRun->GetNumberOfHits(CollectionID2);
    for (G4int i = 0; i < hitNum; i++)
    {
        PolyethyleneDetectorHit* hit = (PolyethyleneDetectorHit*)(polyethyleneRun->GetHit(CollectionID2, i));
        if(hit != NULL)
        {
            G4int j = hit->GetPos()[0];
            Charge[j] = Charge[j]+hit->GetCharge();
        }
    }

    std::ofstream chargeFile("PolyethyleneChargeMT_ICNLAbla.txt");
    G4double sum = 0;
    for (G4int i = 0; i < 64; i++)
    {
        chargeFile << i+1 << " " << Charge[i]<< "\n"; //(((Charge[i]*1.60217646e-19)/1.0e-12)/aRun->GetNumberOfEvent())*1.0e9 << "\n";
        sum = sum + Charge[i];
    }

    chargeFile << "Sum = " << sum;

    G4int hitNum2 = polyethyleneRun->GetNumberOfHits(CollectionID1);
    for (G4int i = 0; i < hitNum2; i++)
    {
        PolyethyleneDetectorHit* hit = (PolyethyleneDetectorHit*)(polyethyleneRun->GetHit(CollectionID1, i));
        if(hit != NULL)
        {
            G4int j = hit->GetPos()[0];
            Energy[j] = Energy[j]+hit->GetEdep();
        }
    }

    std::ofstream energyFile("PolyethyleneEnergyMT_ICNLAbla.txt");
    for (G4int i = 0; i < 64; i++)
        energyFile << i << ", " << Energy[i] << ",\n";
}

