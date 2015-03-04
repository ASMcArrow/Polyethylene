#include "PolyethyleneDetectorHit.hh"

#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4ThreadLocal G4Allocator<PolyethyleneDetectorHit>* PolyethyleneDetectorHitAllocator = 0;

PolyethyleneDetectorHit::PolyethyleneDetectorHit()
{
    EnergyDeposit = 0;
    Position.set(0,0,0);
    Charge = 0;
}

PolyethyleneDetectorHit::~PolyethyleneDetectorHit()
{}

PolyethyleneDetectorHit::PolyethyleneDetectorHit(const PolyethyleneDetectorHit &right)
    :G4VHit()
{
   Position = right.Position;
   EnergyDeposit = right.EnergyDeposit;
   Charge = right.Charge;
}

const PolyethyleneDetectorHit&
PolyethyleneDetectorHit::operator=(const PolyethyleneDetectorHit &right)
{
    Position = right.Position;
    EnergyDeposit = right.EnergyDeposit;
    Charge = right.Charge;

    return *this;
}

void PolyethyleneDetectorHit::Draw()
{
    G4Circle circle(Position);
    circle.SetScreenDiameter(10.0);
    circle.SetFillStyle (G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
}

int PolyethyleneDetectorHit::operator==(const PolyethyleneDetectorHit &right) const
{
    return((Position==right.Position)&&(EnergyDeposit==right.EnergyDeposit)&&(Charge==right.Charge));
}


