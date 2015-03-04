#include "PolyethylenePrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4SingleParticleSource.hh"
#include "G4SPSAngDistribution.hh"
#include "G4Proton.hh"

using namespace CLHEP;

PolyethylenePrimaryGeneratorAction::PolyethylenePrimaryGeneratorAction()
{
    CircleSource = new G4SingleParticleSource();
    CircleSource->SetParticleDefinition(G4Proton::Definition());

    G4SPSEneDistribution* energy = CircleSource->GetEneDist();
    energy->SetEnergyDisType("Gauss");
    energy->SetBeamSigmaInE(0.5 *MeV);
    energy->SetMonoEnergy(160 *MeV);

    G4SPSPosDistribution* position = CircleSource->GetPosDist();
    position->SetPosDisType("Plane");
    position->SetPosDisShape("Circle");
    position->SetRadius(0.5*cm);
    position->SetCentreCoords(G4ThreeVector(0.0*m, 0.0*m, -1.5*m));

    G4SPSAngDistribution* angular = CircleSource->GetAngDist();
    angular->SetParticleMomentumDirection(G4ThreeVector(0.0,0.0,1.0));

    CircleSource->SetNumberOfParticles(1);
}

PolyethylenePrimaryGeneratorAction::~PolyethylenePrimaryGeneratorAction()
{
    delete CircleSource;
}

void PolyethylenePrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    CircleSource->GeneratePrimaryVertex(event);
}
