#ifndef COPPERPRIMARYGENERATORACTION_H
#define COPPERPRIMARYGENERATORACTION_H

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4SPSPosDistribution.hh"
#include "G4Types.hh"
#include "G4SingleParticleSource.hh"

class G4ParticleGun;
class G4Event;

class CopperPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{

public:
    CopperPrimaryGeneratorAction();
    ~CopperPrimaryGeneratorAction();

    void GeneratePrimaries(G4Event* event);

private:
    G4SingleParticleSource* m_CircleSource;
};

#endif


