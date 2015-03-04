#include "PolyethyleneRun.hh"
#include "G4SDManager.hh"

PolyethyleneRun::PolyethyleneRun(const G4String detectorName, G4bool verbose) : G4Run()
{
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    G4VSensitiveDetector* detector = SDman->FindSensitiveDetector(detectorName);

    CollName1 = detector->GetCollectionName(0);
    CollName2 = detector->GetCollectionName(1);

    CollectionID1 = SDman->GetCollectionID(CollName1);
    CollectionID2 = SDman->GetCollectionID(CollName2);

    Verbose = verbose;
}

PolyethyleneRun::~PolyethyleneRun()
{
    HitVector1.clear();
    HitVector2.clear();
}

void PolyethyleneRun::RecordEvent(const G4Event* aEvent)
{
    numberOfEvent++;

    G4HCofThisEvent* HCE = aEvent->GetHCofThisEvent();
    if(HCE!=NULL)
    {
        PolyethyleneDetectorHitsCollection* HC1 = (PolyethyleneDetectorHitsCollection*)(HCE -> GetHC(CollectionID1));
        if(HC1!=NULL)
        {
            if (Verbose) G4cout << CollectionID1 << " " << HC1->entries() << G4endl;
            this->AddHitToVector(HC1, &HitVector1);
        }

        PolyethyleneDetectorHitsCollection* HC2 = (PolyethyleneDetectorHitsCollection*)(HCE -> GetHC(CollectionID2));
        if(HC2!=NULL)
        {
            if (Verbose) G4cout << CollectionID2 << " " << HC2->entries() << G4endl;
            this->AddHitToVector(HC2, &HitVector2);
        }
    }
}

void PolyethyleneRun::AddHitToVector(PolyethyleneDetectorHitsCollection *HC, std::vector<PolyethyleneDetectorHit *> *vector)
{
    for (G4int j = 0; j < HC->entries(); j++)
    {
        PolyethyleneDetectorHit *hit = (PolyethyleneDetectorHit*)(HC->GetHit(j));
        if (Verbose)
        {
            G4cout << "Vector Initial: "<< G4endl << "j = "<< j << " Energy deposition is " << hit->GetEdep()
                   << " Position is " << hit->GetPos()[0] << " Charge is " << hit->GetCharge() << G4endl;
        }
        PolyethyleneDetectorHit *copyHit = new PolyethyleneDetectorHit(*hit);
        vector->push_back((PolyethyleneDetectorHit*)(copyHit));
    }
}

void PolyethyleneRun::Merge(const G4Run * aRun)
{
    const PolyethyleneRun *localRun = static_cast<const PolyethyleneRun*>(aRun);
    for (G4int i = 0; i < localRun -> HitVector1.size(); i++)
        HitVector1.push_back(localRun -> HitVector1[i]);
    for (G4int j = 0; j < localRun -> HitVector2.size(); j++)
        HitVector2.push_back(localRun -> HitVector2[j]);

    G4Run::Merge(aRun);
}


