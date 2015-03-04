 #include "HadronPhysicsQGSP_BIC_OPT.hh"
#include "PreEquilibProtonBuilder.hh"

#include "globals.hh"
#include "G4ios.hh"
#include <iomanip>   
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4ProcessManager.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

#include <QMessageBox>

HadronPhysicsQGSP_BIC_OPT::HadronPhysicsQGSP_BIC_OPT() : G4VPhysicsConstructor("Hadron Inelastic QGSP_BIC_OPT")
{
    m_InelasticModel = PRE_COMPOUND; //LOW_ENERGY
}

void
HadronPhysicsQGSP_BIC_OPT::CreateModels()
{
    m_Neutrons = new G4NeutronBuilder;
    m_Neutrons->RegisterMe(m_QGSPNeutronBuilder = new G4QGSPNeutronBuilder(true));
    m_Neutrons->RegisterMe(m_LEPNeutronBuilder = new G4LEPNeutronBuilder);
    m_LEPNeutronBuilder->SetMinInelasticEnergy(9.5*GeV);
    m_LEPNeutronBuilder->SetMaxInelasticEnergy(25*GeV);
    m_Neutrons->RegisterMe(m_BinaryNeutronBuilder = new G4BinaryNeutronBuilder);
    m_BinaryNeutronBuilder->SetMaxEnergy(9.9*GeV);

    m_Protons = new G4ProtonBuilder;
    switch (m_InelasticModel)
    {
    case (LOW_ENERGY):
        m_Protons->RegisterMe(m_LEPProtonBuilder = new G4LEPProtonBuilder);
        m_LEPProtonBuilder->SetMinEnergy(0.0*GeV);
        m_LEPProtonBuilder->SetMaxEnergy(25*GeV);
        break;
    case (PRE_COMPOUND): m_Protons->RegisterMe(m_PreEquilibProtonBuilder =
                new PreEquilibProtonBuilder);
        break;
    default:
        m_Protons->RegisterMe(m_LEPProtonBuilder = new G4LEPProtonBuilder);
        m_LEPProtonBuilder->SetMinEnergy(0.0*GeV);
        m_LEPProtonBuilder->SetMaxEnergy(25*GeV);
        break;
    }

    m_PiK = new G4PiKBuilder;
    m_PiK->RegisterMe(m_QGSPPiKBuilder = new G4QGSPPiKBuilder(true));
    m_PiK->RegisterMe(m_LEPPiKBuilder = new G4LEPPiKBuilder);
    m_LEPPiKBuilder->SetMaxEnergy(25*GeV);

    m_MiscLHEPBuilder = new G4MiscLHEPBuilder;
}

HadronPhysicsQGSP_BIC_OPT::~HadronPhysicsQGSP_BIC_OPT()
{
   delete m_MiscLHEPBuilder;
   delete m_QGSPNeutronBuilder;
   delete m_LEPNeutronBuilder;
   delete m_BinaryNeutronBuilder;
   if (m_PreEquilibProtonBuilder)
           delete m_PreEquilibProtonBuilder;
   if (m_LEPProtonBuilder)
           delete m_LEPProtonBuilder;
   delete m_Protons;
   delete m_QGSPPiKBuilder;
   delete m_LEPPiKBuilder;
   delete m_PiK;
}

void HadronPhysicsQGSP_BIC_OPT::ConstructParticle()
{
    G4MesonConstructor mesonConstructor;
    mesonConstructor.ConstructParticle();

    G4BaryonConstructor baryonConstructor;
    baryonConstructor.ConstructParticle();

    G4ShortLivedConstructor shortLivedConstructor;
    shortLivedConstructor.ConstructParticle();
}


void HadronPhysicsQGSP_BIC_OPT::ConstructProcess()
{
    CreateModels();
    m_Neutrons->Build();
    m_Protons->Build();
    m_PiK->Build();
    m_MiscLHEPBuilder->Build();
}

