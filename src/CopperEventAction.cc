#include "CopperEventAction.hh"
#include "CopperStackingAction.hh"
#include "CopperTrackingAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4Types.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Proton.hh"

#include <QMessageBox>
#include <QMap>
#include <QString>
#include "sstream"

CopperEventAction* CopperEventAction::m_Instance = 0;

CopperEventAction* CopperEventAction::Instance()
{
    return m_Instance;
}      

CopperEventAction::CopperEventAction():G4UserEventAction()
{
    m_Instance = this;
    m_Num = 0;
    m_Bins.reserve(64);
    for (int i = 0; i < 64; i++)
        m_Bins.push_back(0);
}

CopperEventAction::~CopperEventAction()
{
    m_Instance = 0;
    m_Num = 0;
}

void
CopperEventAction::BeginOfEventAction(const G4Event* event)
{}

void
CopperEventAction::EndOfEventAction(const G4Event*)
{
    m_Num = m_Num+1;
}

void
CopperEventAction::Reset()
{
    m_Num = 0;
}


void
CopperEventAction::Record(G4String volume, G4double charge, double before, double after)
{
    QVector<int> numbers;

    for (int i = 1; i <= 66; i++)
    {
        std::string pattern = "_impr_";
        std::stringstream stream;
        stream<<i;//+1;
        pattern += stream.str();
        if (volume.contains(pattern))
            numbers.append(i);

        pattern.clear();
    }

    if (!numbers.isEmpty())
    {
     /*   QMessageBox msgBox1;
        msgBox1.setText("out of if m_HitsVector[0] is..."+QString::number(m_HitsVector[0]));
        msgBox1.exec();

        if((numbers.last()==1)&&(before!=0)&&(after!=0))
        {
            m_HitsVector[0] = m_HitsVector[0]+charge*(after/0.317);
            QMessageBox msgBox;
            msgBox.setText("m_HitsVector[0] is..."+QString::number(m_HitsVector[0])+
                           " Charge is... "+ QString::number(charge)+
                           " before is... "+QString::number(before)+
                           " after is... "+QString::number(after));
            msgBox.exec();
        }*/
       // if((numbers.last()==66)&&(before!=0)&&(after!=0))
       // {
     //      m_HitsVector[65] = m_HitsVector[65]+charge*(before/0.317);
     //   }

      //  else if ((numbers.last()!=1)&&(numbers.last()!=66))
            if ((before == 0)&&(after == 0))
                m_Bins[numbers.last()-1] = m_Bins[numbers.last()-1]+charge;
            else
            {
                m_Bins[numbers.last()-1] = m_Bins[numbers.last()-1]+charge*(before/0.317);
                m_Bins[numbers.last()] = m_Bins[numbers.last()]+charge*(after/0.317);
            }
    }

    numbers.clear();
}

