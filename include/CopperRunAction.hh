#ifndef COPPERRUNACTION_H
#define COPPERRUNACTION_H

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

class CopperRunAction : public G4UserRunAction
{
public:

    CopperRunAction();
    ~CopperRunAction();

    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
};

#endif


