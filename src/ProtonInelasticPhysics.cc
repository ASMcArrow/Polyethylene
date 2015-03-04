#include "ProtonInelasticPhysics.hh".hh"

#include "globals.hh"
#include "G4ios.hh"
#include <iomanip>
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"

#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4ShortLivedConstructor.hh"
#include "G4ProcessManager.hh"

ProtonInelasticPhysics::ProtonInelasticPhysics():
    G4VPhysicsConstructor("ProtonInelasticPhysics")
{}

void
ProtonInelasticPhysics::CreateModels()
{
    thePro=new G4ProtonBuilder;
    thePro->RegisterMe(theLEPPro=new G4LEPProtonBuilder);
}

ProtonInelasticPhysics::~ProtonInelasticPhysics()
{
    delete theLEPPro;
    delete thePro;
}

void
ProtonInelasticPhysics::ConstructParticle()
{
    G4BaryonConstructor pBaryonConstructor;
    pBaryonConstructor.ConstructParticle();

    G4MesonConstructor pMesonConstructor;
    pMesonConstructor.ConstructParticle();
}

void ProtonInelasticPhysics::ConstructProcess()
{
    CreateModels();
    thePro->Build();
}


