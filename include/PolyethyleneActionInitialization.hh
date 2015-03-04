#ifndef POLYETHYLENEACTIONINITIASLIZATION_HH
#define POLYETHYLENEACTIONINITIASLIZATION_HH

#include "G4VUserActionInitialization.hh"

class PolyethyleneActionInitialization : public G4VUserActionInitialization
{
  public:

    PolyethyleneActionInitialization();
    virtual ~PolyethyleneActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif // POLYETHYLENEACTIONINITIASLIZATION_HH
