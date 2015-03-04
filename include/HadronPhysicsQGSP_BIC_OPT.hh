#ifndef HADRONPHYSICSQGSP_BIC_OPT_H
#define HADRONPHYSICSQGSP_BIC_OPT_H

#include "globals.hh"
#include "G4ios.hh"

#include "G4VPhysicsConstructor.hh"
#include "G4MiscLHEPBuilder.hh"

#include "G4PiKBuilder.hh"
#include "G4LEPPiKBuilder.hh"
#include "G4QGSPPiKBuilder.hh"

#include "G4ProtonBuilder.hh"
#include "G4LEPProtonBuilder.hh"
#include "PreEquilibProtonBuilder.hh"

#include "G4NeutronBuilder.hh"
#include "G4LEPNeutronBuilder.hh"
#include "G4QGSPNeutronBuilder.hh"
#include "G4BinaryNeutronBuilder.hh"

#include <QMessageBox>

class HadronPhysicsQGSP_BIC_OPT : public G4VPhysicsConstructor
{

public:
    enum InelasticModels {LOW_ENERGY, PRE_COMPOUND};

    HadronPhysicsQGSP_BIC_OPT();
    ~HadronPhysicsQGSP_BIC_OPT();

    void ConstructParticle();
    void ConstructProcess();

private:
    void CreateModels();

    InelasticModels m_InelasticModel;

    G4NeutronBuilder *m_Neutrons;
    G4LEPNeutronBuilder *m_LEPNeutronBuilder;
    G4QGSPNeutronBuilder *m_QGSPNeutronBuilder;
    G4BinaryNeutronBuilder *m_BinaryNeutronBuilder;

    G4PiKBuilder *m_PiK;
    G4LEPPiKBuilder *m_LEPPiKBuilder;
    G4QGSPPiKBuilder *m_QGSPPiKBuilder;
    
    G4ProtonBuilder *m_Protons;
    G4LEPProtonBuilder *m_LEPProtonBuilder;
    PreEquilibProtonBuilder *m_PreEquilibProtonBuilder;
    
    G4MiscLHEPBuilder *m_MiscLHEPBuilder;
};

#endif

