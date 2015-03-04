#ifndef PolyethyleneRUN_H
#define PolyethyleneRUN_H

#include "G4Run.hh"
#include "G4Event.hh"

#include "PolyethyleneDetectorHit.hh"

#include <vector>

class PolyethyleneRun : public G4Run
{

public:
    PolyethyleneRun(const G4String detectorName, G4bool verbose);
    virtual ~PolyethyleneRun();

    // virtual method from G4Run.
    // The method is overriden in this class for scoring.
    virtual void RecordEvent(const G4Event*);
    virtual void Merge(const G4Run*);

    inline G4int GetNumberOfHits(G4int collectionID) const
    {
        if (collectionID == CollectionID1)
            return HitVector1.size();
        else if (collectionID == CollectionID2)
            return HitVector2.size();
    }

    inline PolyethyleneDetectorHit* GetHit(G4int collectionID, G4int i)
    {
        if (collectionID == CollectionID1)
            return HitVector1[i];
        else if (collectionID == CollectionID2)
            return HitVector2[i];
    }

private:
    void AddHitToVector(PolyethyleneDetectorHitsCollection* HC, std::vector<PolyethyleneDetectorHit *> *vector);

    G4String CollName1, CollName2;
    G4int CollectionID1, CollectionID2;
    std::vector<PolyethyleneDetectorHit*> HitVector1, HitVector2;
    G4bool Verbose;
};

#endif // PolyethyleneRUN_H


