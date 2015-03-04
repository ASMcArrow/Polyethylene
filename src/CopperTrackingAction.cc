#include "CopperTrackingAction.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "G4TrackVector.hh"
#include "CopperTrackInformation.hh"
#include "CopperEventAction.hh"
#include "G4TrackStatus.hh"
#include "CopperDetectorConstruction.hh"

void
CopperTrackingAction::PreUserTrackingAction(const G4Track* track)
{
    if(track->GetParentID()==0 && track->GetUserInformation()==0)
    {
        CopperTrackInformation* trackInfo = new CopperTrackInformation(track);
        G4Track* newTrack = (G4Track*)track;
        newTrack->SetUserInformation(trackInfo);
    }
}

void CopperTrackingAction::PostUserTrackingAction(const G4Track* track)
{
    double before = 0;
    double after = 0;
    CopperTrackInformation* trackInfo = (CopperTrackInformation*)(track->GetUserInformation());
    if((trackInfo->IsProtonInelastic())||(track->GetCreatorProcess() == 0))
    {
    //    std::cout << "Particle dies and is... " << track->GetParticleDefinition()->GetParticleName()
    //                 << " Volume is... " << track->GetVolume()->GetName()
    //                 << " Charge is... " << track->GetDefinition()->GetPDGCharge() << std::endl;

      //  if(track->GetMaterial() == CopperDetectorConstruction::Instance()->GetCH2())
      //  {
           // G4ThreeVector position = track->GetPosition();
          //  before = (track->GetPosition().getX()/10)-(track->GetVolume()->GetObjectTranslation().getX()/10+0.00127-0.1585);
          //  after = (track->GetVolume()->GetObjectTranslation().getX()/10+0.00127+0.1585)-(track->GetPosition().getX()/10);
           /* QMessageBox msgBox;
            msgBox.setText("Proton stopped in... "+QString::fromStdString(track->GetMaterial()->GetName())+" Volume is... "+QString::fromStdString(track->GetVolume()->GetName())+
                          " Translation is... "+QString::number(track->GetVolume()->GetObjectTranslation().getX())+
                           " "+QString::number(track->GetVolume()->GetObjectTranslation().getY())+" "
                           +QString::number(track->GetVolume()->GetObjectTranslation().getZ())+
                           " Position of a particle is... "+QString::number(track->GetPosition().getX())+
                           " "+QString::number(track->GetPosition().getY())+" "+
                           QString::number(track->GetPosition().getZ())+"Distance is... "+
                           QString::number(before)+" "+QString::number(after));

            msgBox.exec();*/
       // }

        CopperEventAction::Instance()->Record(track->GetVolume()->GetName(),
                                              track->GetDefinition()->GetPDGCharge(),
                                              before, after);
    }

    G4TrackVector* secondaries = fpTrackingManager->GimmeSecondaries();
    if(secondaries)
    {
        size_t numSeco = secondaries->size();
        if(numSeco > 0)
        {
            for(size_t i = 0; i < numSeco; i++)
            {
                CopperTrackInformation* trackInfoNew = new CopperTrackInformation(trackInfo);
                (*secondaries)[i]->SetUserInformation(trackInfoNew);
                if (((*secondaries)[i]->GetCreatorProcess()->GetProcessName() == "ProtonInelastic")||(trackInfo->IsProtonInelastic()))
                {
                  //  QMessageBox msgBox;
                  //  msgBox.setText("Secondary particle is born and is... "+QString::fromStdString((*secondaries)[i]->GetDefinition()->GetParticleName())+
                  //                 " Volume is... "+QString::fromStdString((*secondaries)[i]->GetVolume()->GetName())+
                  //                 " Charge is... "+QString::number((*secondaries)[i]->GetDefinition()->GetPDGCharge()));
                  //  msgBox.exec();

                    CopperEventAction::Instance()->Record((*secondaries)[i]->GetVolume()->GetName(),
                                                          (-1.0)*(*secondaries)[i]->GetDefinition()->GetPDGCharge());

                    CopperTrackInformation* inelastictrackInfo = (CopperTrackInformation*)(*secondaries)[i]->GetUserInformation();
                    inelastictrackInfo->SetIsProtonInelastic((*secondaries)[i]);
                }

            }
        }
    }
}
