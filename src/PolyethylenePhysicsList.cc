#include "PolyethylenePhysicsList.hh"

// Physic lists (contained inside the Geant4 source code, in the 'physicslists folder')
#include "G4HadronPhysicsQGSP_BIC.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4LossTableManager.hh"
#include "G4UnitsTable.hh"
#include "G4ProcessManager.hh"
#include "G4IonFluctuations.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4EmProcessOptions.hh"
#include "G4ParallelWorldPhysics.hh"
#include "G4ParallelWorldScoringProcess.hh"
#include "G4HadronPhysicsQGSP_BERT.hh"
#include "G4HadronPhysicsINCLXX.hh"
#include "G4StepLimiter.hh"

PolyethylenePhysicsList::PolyethylenePhysicsList() : G4VModularPhysicsList()
{
    G4LossTableManager::Instance();
    defaultCutValue = 1.*mm;
    cutForGamma     = defaultCutValue;
    cutForElectron  = defaultCutValue;
    cutForPositron  = defaultCutValue;

    SetVerboseLevel(1);

    RegisterPhysics(new G4EmStandardPhysics_option3);
    RegisterPhysics(new G4HadronPhysicsINCLXX);
    RegisterPhysics(new G4EmExtraPhysics);
    RegisterPhysics(new G4HadronElasticPhysics);
    RegisterPhysics(new G4StoppingPhysics);
    RegisterPhysics(new G4IonBinaryCascadePhysics);
    RegisterPhysics(new G4NeutronTrackingCut);
    //  RegisterPhysics(new G4DecayPhysics);
    //  RegisterPhysics(new G4RadioactiveDecayPhysics);
}

PolyethylenePhysicsList::~PolyethylenePhysicsList()
{}

void PolyethylenePhysicsList::ConstructProcess()
{
    AddParallelScoring();
    G4VModularPhysicsList::ConstructProcess();
}

void PolyethylenePhysicsList::AddParallelScoring()
{
    G4StepLimiter* stepLimiter = new G4StepLimiter();

    G4ParallelWorldScoringProcess* theParallelWorldScoringProcess
            = new G4ParallelWorldScoringProcess("ParaWorldScoringProcCharge");
    theParallelWorldScoringProcess->SetParallelWorld("PolyethyleneParallelWorld");

    /*G4ParallelWorldScoringProcess* theParallelWorldScoringProcessProfile
            = new G4ParallelWorldScoringProcess("ParaWorldScoringProcEnergy");
    theParallelWorldScoringProcessProfile->SetParallelWorld("PolyethyleneParallelWorld");*/

    theParticleIterator->reset();
    while((*theParticleIterator)())
    {
        G4ProcessManager* pmanager = theParticleIterator->value()->GetProcessManager();
        pmanager->AddDiscreteProcess(stepLimiter);
        pmanager->AddProcess(theParallelWorldScoringProcess);
        // pmanager->AddProcess(theParallelWorldScoringProcessProfile);
        pmanager->SetProcessOrderingToLast(theParallelWorldScoringProcess, idxAtRest);
        //  pmanager->SetProcessOrderingToLast(theParallelWorldScoringProcessProfile, idxAtRest);
        pmanager->SetProcessOrdering(theParallelWorldScoringProcess, idxAlongStep, 1);
        // pmanager->SetProcessOrdering(theParallelWorldScoringProcessProfile, idxAlongStep, 1);
        pmanager->SetProcessOrderingToLast(theParallelWorldScoringProcess, idxPostStep);
        // pmanager->SetProcessOrderingToLast(theParallelWorldScoringProcessProfile, idxPostStep);
    }
}

void PolyethylenePhysicsList::SetCuts()
{
    // set cut values for gamma at first and for e- second and next for e+,
    // because some processes for e+/e- need cut values for gamma
    SetCutValue(cutForGamma, "gamma");
    SetCutValue(cutForElectron, "e-");
    SetCutValue(cutForPositron, "e+");
}

