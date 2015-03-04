#include "CopperPhysicsList.hh"

#include "G4ParticleTypes.hh"
#include "G4ProcessManager.hh"
#include "G4ExcitationHandler.hh"
#include "G4PreCompoundModel.hh"
#include "G4ProtonInelasticProcess.hh"
#include "G4ParticleDefinition.hh"
#include "G4LEProtonInelastic.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4QStoppingPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4ShortLivedConstructor.hh"
#include "G4PhysicsListHelper.hh"
#include "HadronPhysicsQGSP_BIC_OPT.hh"

CopperPhysicsList::CopperPhysicsList(): G4VModularPhysicsList()
{
    m_EMPhysicsList = new G4EmStandardPhysics_option3(1);
    m_EMPhysicsList->SetVerboseLevel(0);
    m_DecPhysicsList = new G4DecayPhysics();
    m_RadDecPhysicsList = new G4RadioactiveDecayPhysics();
    m_HadInelasticPhysicsList = new HadronPhysicsQGSP_BIC_OPT();

    m_HadPhysicsVector.push_back(m_HadInelasticPhysicsList);
    m_HadPhysicsVector.push_back(new G4EmExtraPhysics());
    m_HadPhysicsVector.push_back(new G4HadronElasticPhysics());
    m_HadPhysicsVector.push_back(new G4QStoppingPhysics());
    m_HadPhysicsVector.push_back(new G4IonBinaryCascadePhysics());
    m_HadPhysicsVector.push_back(new G4NeutronTrackingCut());
}

CopperPhysicsList::~CopperPhysicsList()
{
    delete m_EMPhysicsList;
    delete m_DecPhysicsList;
    delete m_RadDecPhysicsList;

    for(size_t i = 0; i < m_HadPhysicsVector.size(); i++)
        delete m_HadPhysicsVector[i];
}

void CopperPhysicsList::ConstructParticle()
{
    m_EMPhysicsList->ConstructParticle();
    m_DecPhysicsList->ConstructParticle();
    m_RadDecPhysicsList->ConstructParticle();
    for(size_t i = 0; i < m_HadPhysicsVector.size(); i++)
        m_HadPhysicsVector[i] -> ConstructParticle();
}

void CopperPhysicsList::ConstructProcess()
{
    AddTransportation();

    m_EMPhysicsList->ConstructProcess();
    m_DecPhysicsList->ConstructProcess();
    m_RadDecPhysicsList->ConstructProcess();

    for(size_t i = 0; i < m_HadPhysicsVector.size(); i++)
        m_HadPhysicsVector[i] -> ConstructProcess();
}

void
CopperPhysicsList::SetCuts()
{
    SetCutsWithDefault();
}

