#ifndef COPPERSTACKINGACTION_H
#define COPPERSTACKINGACTION_H

#include "G4UserStackingAction.hh"
#include "globals.hh"

class CopperStackingAction : public G4UserStackingAction
{

public:
    CopperStackingAction()
    { m_Instance = this; }

    ~CopperStackingAction()
    { m_Instance = 0; }

    G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track *track);
    void NewStage();
    void PrepareNewEvent();

    static CopperStackingAction* Instance()
    { return m_Instance; } 

private:
    static CopperStackingAction* m_Instance;
};

#endif
