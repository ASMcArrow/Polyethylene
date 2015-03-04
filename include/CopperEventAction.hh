#ifndef COPPEREVENTACTION_H
#define COPPEREVENTACTION_H

#include "G4UserEventAction.hh"
#include "G4LogicalVolume.hh"
#include "globals.hh"

class CopperEventAction : public G4UserEventAction
{

public:
    CopperEventAction();
    ~CopperEventAction();
    
    static CopperEventAction* Instance();

    void BeginOfEventAction(const G4Event* event);
    void EndOfEventAction(const G4Event* event);

    void Record(G4String volume, G4double charge, double before = 0, double after = 0);
    void Reset();

    std::vector<double> GetBins()
    { return m_Bins; }

private:
    static CopperEventAction* m_Instance;
    std::vector<double> m_Bins;
    int m_Num;
};

#endif

    
