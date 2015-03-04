#include "PreEquilibProtonBuilder.hh"
#include "G4PreCompoundModel.hh"
#include "G4ExcitationHandler.hh"
#include "G4ProtonInelasticProcess.hh"

PreEquilibProtonBuilder::PreEquilibProtonBuilder()
{
    m_PreEquilib = new G4PreCompoundModel(m_ExcitationHandler = new G4ExcitationHandler);
}

void
PreEquilibProtonBuilder::Build(G4ProtonInelasticProcess* process)
{
    process->RegisterMe(m_PreEquilib);
}

PreEquilibProtonBuilder::~PreEquilibProtonBuilder()
{
    delete m_PreEquilib;
    delete m_ExcitationHandler;
}


