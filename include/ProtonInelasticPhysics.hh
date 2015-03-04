#ifndef H_PROTONINELASTICPHYSICS
#define H_PROTONINELASTICPHYSICS

#include "globals.hh"
#include "G4ios.hh"

#include "G4VPhysicsConstructor.hh"
#include "G4MiscLHEPBuilder.hh"

#include "G4PiKBuilder.hh"
#include "G4LEPPiKBuilder.hh"
#include "G4QGSPPiKBuilder.hh"

#include "G4ProtonBuilder.hh"
#include "G4LEPProtonBuilder.hh"
#include "G4QGSPProtonBuilder.hh"
#include "G4BinaryProtonBuilder.hh"

#include "G4NeutronBuilder.hh"
#include "G4LEPNeutronBuilder.hh"
#include "G4QGSPNeutronBuilder.hh"
#include "G4BinaryNeutronBuilder.hh"

class ProtonInelasticPhysics : public G4VPhysicsConstructor
{
  public:

    ProtonInelasticPhysics();
    ~ProtonInelasticPhysics();

    void ConstructParticle();
    void ConstructProcess();

  private:

    G4ProtonBuilder * thePro;
    G4LEPProtonBuilder * theLEPPro;
    G4QGSPProtonBuilder * theQGSPPro;
    G4BinaryProtonBuilder * theBinaryPro;

    void CreateModels();
};

#endif


