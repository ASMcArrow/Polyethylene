#ifndef PolyethylenePRIMARYGENERATORACTION_H
#define PolyethylenePRIMARYGENERATORACTION_H

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4SingleParticleSource.hh"

class G4Event;

class PolyethylenePrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{

public:
    PolyethylenePrimaryGeneratorAction();
    ~PolyethylenePrimaryGeneratorAction();

    void GeneratePrimaries(G4Event* event);

private:
    G4SingleParticleSource* CircleSource;
};

#endif


