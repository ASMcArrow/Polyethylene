#ifndef POLYETHYLENEDETECTORHIT_H
#define POLYETHYLENEDETECTORHIT_H

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class PolyethyleneDetectorHit : public G4VHit
{

public:
    PolyethyleneDetectorHit();
    ~PolyethyleneDetectorHit();
 
    PolyethyleneDetectorHit(const PolyethyleneDetectorHit &right);
    const PolyethyleneDetectorHit& operator = (const PolyethyleneDetectorHit &right);
    int operator == (const PolyethyleneDetectorHit &right) const;

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);

    void Draw();
 // void Print() {} const;

    void SetEdep(G4double de)
    { EnergyDeposit = de; }

    G4double GetEdep() const
    { return EnergyDeposit; }

    void SetPos(G4ThreeVector xyz)
    { Position = xyz; }

    G4ThreeVector GetPos() const
    { return Position; }

    void SetCharge(G4int charge)
    { Charge = charge; }

    G4int GetCharge() const
    { return Charge; }

private:
    G4ThreeVector Position; // Position
    G4double EnergyDeposit; // Energy deposit associated with the hit
    G4int Charge; // Deposited charge
};

typedef G4THitsCollection<PolyethyleneDetectorHit> PolyethyleneDetectorHitsCollection;
extern G4ThreadLocal G4Allocator<PolyethyleneDetectorHit>* PolyethyleneDetectorHitAllocator;

inline void* PolyethyleneDetectorHit::operator new(size_t)
{
    if(!PolyethyleneDetectorHitAllocator)
        PolyethyleneDetectorHitAllocator = new G4Allocator<PolyethyleneDetectorHit>;

    return (void *)PolyethyleneDetectorHitAllocator->MallocSingle();
}

inline void PolyethyleneDetectorHit::operator delete(void *aHit)
{
    PolyethyleneDetectorHitAllocator->FreeSingle((PolyethyleneDetectorHit*)aHit);
}

#endif


