#ifndef PREEQUILIBPROTONBUILDER_H
#define PREEQUILIBPROTONBUILDER_H

#include "globals.hh"

#include "G4ProtonInelasticProcess.hh"
#include "G4VProtonBuilder.hh"
#include "G4ExcitationHandler.hh"
#include "G4PreCompoundModel.hh"

class PreEquilibProtonBuilder : public G4VProtonBuilder
{

public:
    PreEquilibProtonBuilder();
    ~PreEquilibProtonBuilder();

    void Build(G4HadronElasticProcess* process) {}
    void Build(G4ProtonInelasticProcess* process);
    
private:
    G4PreCompoundModel* m_PreEquilib;
    G4ExcitationHandler* m_ExcitationHandler;
};

#endif

