#ifndef COPPERPHYSICSLIST_H
#define COPPERPHYSICSLIST_H

#include "G4VModularPhysicsList.hh"
#include "G4VPhysicsConstructor.hh"
#include "HadronPhysicsQGSP_BIC_OPT.hh"
#include "globals.hh"
#include <vector>

class CopperPhysicsList: public G4VModularPhysicsList
{

public:
    CopperPhysicsList();
    ~CopperPhysicsList();

protected:
    G4VPhysicsConstructor* m_EMPhysicsList;
    G4VPhysicsConstructor* m_DecPhysicsList;
    G4VPhysicsConstructor* m_RadDecPhysicsList;
    HadronPhysicsQGSP_BIC_OPT* m_HadInelasticPhysicsList;

    std::vector<G4VPhysicsConstructor*>  m_HadPhysicsVector;

    void ConstructParticle();
    void ConstructProcess();
    void SetCuts();
};

#endif







