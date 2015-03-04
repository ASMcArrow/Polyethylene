#include "CopperPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SingleParticleSource.hh"
#include "G4SPSPosDistribution.hh"
#include "G4Proton.hh"
#include "globals.hh"
#include "Randomize.hh"

CopperPrimaryGeneratorAction::CopperPrimaryGeneratorAction()
{
    m_CircleSource = new G4SingleParticleSource();
    m_CircleSource->SetParticleDefinition(G4Proton::Definition());

    G4SPSEneDistribution* energy = m_CircleSource->GetEneDist();
    energy->SetEnergyDisType("Gauss");
    energy->SetBeamSigmaInE(0.5 *MeV);
    energy->SetMonoEnergy(160.5 *MeV);

    G4SPSPosDistribution* position = m_CircleSource->GetPosDist();
    position->SetPosDisType("Plane");
    position->SetPosDisShape("Circle");
    position->SetCentreCoords(G4ThreeVector(-1.5*m, 0.0*m, 0.0*m));
    position->SetRadius(0.5*cm);
    position->SetPosRot1(G4ThreeVector(0.0, 1.0, 0.0));
    position->SetPosRot2(G4ThreeVector(0.0 ,0.0, 1.0));

    G4SPSAngDistribution* angular = m_CircleSource->GetAngDist();
    angular->SetParticleMomentumDirection(G4ThreeVector(1.0,0.0,0.0));

    m_CircleSource->SetNumberOfParticles(1);;
}

CopperPrimaryGeneratorAction::~CopperPrimaryGeneratorAction()
{
    delete m_CircleSource;
}

void CopperPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    m_CircleSource->GeneratePrimaryVertex(event);
}
