#include "PolyethyleneDetectorSD.hh"
#include "PolyethyleneDetectorHit.hh"
#include "PolyethyleneTrackInformation.hh"

#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4VProcess.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4SteppingManager.hh"

#include <cstdio>

PolyethyleneDetectorSD::PolyethyleneDetectorSD(G4String name, G4String collname1, G4String collname2):
    G4VSensitiveDetector(name)
{
    collectionName.insert(collname1);
    collectionName.insert(collname2);
    ChargeHitsCollection = NULL;
    EnergyHitsCollection = NULL;
    SensitiveDetectorName = name;
    verboseLevel = 0;
}

PolyethyleneDetectorSD::~PolyethyleneDetectorSD()
{}

void
PolyethyleneDetectorSD::Initialize(G4HCofThisEvent*)
{
    EnergyHitsCollection = new PolyethyleneDetectorHitsCollection(SensitiveDetectorName,
                                                                  collectionName[0]);
    ChargeHitsCollection = new PolyethyleneDetectorHitsCollection(SensitiveDetectorName,
                                                                  collectionName[1]);
}

G4bool
PolyethyleneDetectorSD::ProcessHits(G4Step* aStep, G4TouchableHistory* obsolete)
{
    if (aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "WorldPhys")
        return false;

    G4StepPoint* preStep = aStep->GetPreStepPoint();
    G4TouchableHistory* touchable = (G4TouchableHistory*)(preStep->GetTouchable());
    G4int i = touchable->GetReplicaNumber(0);

    G4double energyDeposit = aStep->GetTotalEnergyDeposit();

    if(energyDeposit != 0)
    {
        PolyethyleneDetectorHit* detectorHit = new PolyethyleneDetectorHit();
        detectorHit->SetEdep(energyDeposit);
        detectorHit->SetPos(G4ThreeVector(i, 0, 0));
        EnergyHitsCollection->insert(detectorHit);
        if (verboseLevel > 0)
        {
         //   G4cout << " Energy deposition is ..." << aStep->GetTotalEnergyDeposit() << G4endl;
        }
    }

    G4double charge = aStep->GetTrack()->GetParticleDefinition()->GetPDGCharge();
    PolyethyleneTrackInformation* trackInfo = (PolyethyleneTrackInformation*)aStep->GetTrack()->GetUserInformation();

    //  First recording the stopped particles
    if (((aStep->GetTrack()->GetTrackStatus() == fStopButAlive)&&(energyDeposit == 0))
            ||((aStep->GetTrack()->GetTrackStatus() == fStopAndKill)))
    {
        if (aStep->GetTrack()->GetCreatorProcess() == NULL)
        {
            PolyethyleneDetectorHit* detectorHitPrime = new PolyethyleneDetectorHit();
            if (verboseLevel > 0)
            {
                G4cout << " Primary particle stopped ..." << aStep->GetTrack()->GetParticleDefinition()->GetParticleName()
                       << " Charge is... " << charge
                       << " Replica number is "<< i << G4endl;
            }
            detectorHitPrime->SetPos(G4ThreeVector(i, 0, 0));
            detectorHitPrime->SetCharge(charge);
            ChargeHitsCollection->insert(detectorHitPrime);
            return true;
        }
        else if (trackInfo->IsProtonInelastic())
        {
            PolyethyleneDetectorHit* detectorHitSec = new PolyethyleneDetectorHit();
            if (verboseLevel > 0)
            {
                G4cout << " Particle stopped ..." << aStep->GetTrack()->GetParticleDefinition()->GetParticleName()
                       << " Charge is... " << charge
                       << " Creator process is... " << aStep->GetTrack()->GetCreatorProcess()->GetProcessName()
                       << " Replica number is "<< i << G4endl;
            }
            detectorHitSec->SetPos(G4ThreeVector(i, 0, 0));
            detectorHitSec->SetCharge(charge);
            ChargeHitsCollection->insert(detectorHitSec);
            return true;
        }
    }

    //  Second record the secondary particles born in inelastic interactions
    else if (((aStep->GetTrack()->GetTrackStatus() == fAlive)||(aStep->GetTrack()->GetTrackStatus() == fStopButAlive))
             &&(!trackInfo->GetRecordedWhenBorn())&&(trackInfo->IsProtonInelastic()))
    {
        PolyethyleneDetectorHit* detectorHitSec = new PolyethyleneDetectorHit();
        if (verboseLevel > 0)
        {
            G4cout << " Secondary particle is born ..." << aStep->GetTrack()->GetParticleDefinition()->GetParticleName()
                   << " Charge is... " << charge
                   << " Creator process is... " << aStep->GetTrack()->GetCreatorProcess()->GetProcessName()
                   << " Replica number is "<< i << G4endl;
        }
        detectorHitSec->SetPos(G4ThreeVector(i, 0, 0));
        detectorHitSec->SetCharge(-charge);
        ChargeHitsCollection->insert(detectorHitSec);
        trackInfo->SetRecordedWhenBorn();
        return true;
    }

    return false;
}

void PolyethyleneDetectorSD::EndOfEvent(G4HCofThisEvent* HCE)
{
    int HCID;
    G4int num;

    HCID = GetCollectionID(0);
    num = EnergyHitsCollection->entries();
    HCE->AddHitsCollection(HCID, EnergyHitsCollection);

    HCID = GetCollectionID(1);
    num = ChargeHitsCollection->entries();
    HCE->AddHitsCollection(HCID, ChargeHitsCollection);
}

