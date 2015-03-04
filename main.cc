#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "QGSP_BIC_EMY.hh"

#include "CopperDetectorConstruction.hh"
#include "CopperPrimaryGeneratorAction.hh"
#include "CopperTrackingAction.hh"
#include "CopperEventAction.hh"
#include "CopperPhysicsList.hh"

#include <time.h>
#include <fstream>
#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "QGSP_BERT.hh"
#include "G4VisManager.hh"

int main(int argc,char** argv)
{
    CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
    G4int seed = time( NULL );
    CLHEP::HepRandom::setTheSeed( seed );

  G4RunManager* runManager = new G4RunManager;;
  CopperDetectorConstruction * detector = new CopperDetectorConstruction;
  runManager->SetUserInitialization(detector);
  runManager->SetUserInitialization(new CopperPhysicsList);
 // runManager->SetUserInitialization(new QGSP_BIC_EMY);

  CopperEventAction* eventAction = new CopperEventAction;
  runManager->SetUserAction(new CopperPrimaryGeneratorAction);
  runManager->SetUserAction(eventAction);
  runManager->SetUserAction(new CopperTrackingAction);

  runManager->Initialize();

  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  G4UImanager * uiManager = G4UImanager::GetUIpointer();
  G4UIExecutive * uiExecutive = new G4UIExecutive(argc,argv);

 /* uiManager->ApplyCommand("/vis/open OGL 600x600-0+0");
  uiManager->ApplyCommand("/vis/drawVolume");
 // uiManager->ApplyCommand("/hits/activate Detector");
  uiManager->ApplyCommand("/tracking/storeTrajectory");
  uiManager->ApplyCommand("/vis/scene/add/hits");
  uiManager->ApplyCommand("/vis/scene/add/trajectories");
  uiManager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
  uiManager->ApplyCommand("/run/beamOn 5");
 // uiManager->ApplyCommand("/vis/specify WorldLogic");

  uiExecutive->SessionStart();*/

  int num = 100000;
  runManager->BeamOn(num);

  std::vector<double> bins = eventAction->GetBins();
 // double sum = 0;
  std::ofstream File("PolyChargeCalculation_Explicit.txt");

  for (int i = 0; i <= 63; i++)
  {
      File << i << " ";
      bins[i] = (((bins[i]*1.60217646e-19)/1.0e-12)/num)*1.0e9;
      File << bins[i] << "\n";
    //  sum = sum+bins[i];
  }

 // std::cout << "Sum energy is... " << sum/num << std::endl;

  delete uiExecutive;
  delete visManager;

  return 0;
}
