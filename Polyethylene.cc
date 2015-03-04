#include <cstdio>
#include <ctime>

//#undef G4VIS_USE
//#undef G4UI_USE

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#include "G4UImanager.hh"
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "PolyethylenePhysicsList.hh"
#include "PolyethyleneDetectorConstruction.hh"
#include "PolyethylenePrimaryGeneratorAction.hh"
#include "PolyethyleneActionInitialization.hh"
#include "PolyethyleneParallelWorld.hh"
#include "G4Navigator.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"
#include "G4TrackingManager.hh"
#include "FTFP_INCLXX.hh"

int main(int argc,char** argv)
{
    // Set the custom seed for the random engine
    G4Random::setTheEngine(new CLHEP::RanecuEngine);
    G4long seed = time(NULL);
    G4Random::setTheSeed(seed);

#ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
    runManager->SetNumberOfThreads(1);
#else
    G4RunManager* runManager = new G4RunManager;
#endif

    PolyethyleneDetectorConstruction* massWorld = new PolyethyleneDetectorConstruction;
    massWorld->RegisterParallelWorld(new PolyethyleneParallelWorld("PolyethyleneParallelWorld"));
    runManager->SetUserInitialization(massWorld);

    G4VModularPhysicsList* physicsList = new PolyethylenePhysicsList;
    physicsList->SetVerboseLevel(0);

    runManager->SetUserInitialization(physicsList);

    runManager->SetUserInitialization(new PolyethyleneActionInitialization);

    runManager->Initialize();
    //  runManager->BeamOn(10000);

#ifdef G4UI_USE
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    UImanager->ApplyCommand("/control/execute init_vis.mac");
#endif
    ui->SessionStart();
    delete ui;
#endif

    delete runManager;
    return 0;
}


