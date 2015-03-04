#include "CopperSteppingAction.hh"

#include "CopperDetectorConstruction.hh"
#include "CopperEventAction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CopperSteppingAction::CopperSteppingAction()
{
  detector = (DetectorConstruction*)
             G4RunManager::GetRunManager()->GetUserDetectorConstruction();
  eventaction = (EventAction*)
                G4RunManager::GetRunManager()->GetUserEventAction();
 }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CopperSteppingAction::~CopperSteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CopperSteppingAction::UserSteppingAction(const G4Step* aStep)
{
  // get volume of the current step
 // G4String volume = aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName();

  // collect energy and track length step by step
 // G4double edep = aStep->GetTotalEnergyDeposit();

 // CopperEventAction::Instance()->Record(volume, edep);
  /*G4double stepl = 0.;
  if (aStep->GetTrack()->GetDefinition()->GetPDGCharge() != 0.)
    stepl = aStep->GetStepLength();

  if (volume == detector->GetAbsorber()) eventaction->AddAbs(edep,stepl);
  if (volume == detector->GetGap())      eventaction->AddGap(edep,stepl);*/

  //example of saving random number seed of this event, under condition
  //// if (condition) G4RunManager::GetRunManager()->rndmSaveThisEvent();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

