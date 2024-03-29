#include "headerFiles/Views/InfoDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

InfoDialog::InfoDialog(Profile *profile, QWidget *parent)
    : QDialog(parent), m_profile(profile)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Créer les labels pour afficher les informations du profil
    m_nameLabel = new QLabel("Name: " + m_profile->getName(), this);
    layout->addWidget(m_nameLabel);

    m_avatarLabel = new QLabel(this);
    m_avatarLabel->setPixmap(QPixmap(m_profile->getAvatarPath())); // Assurez-vous que le chemin de l'avatar est correct
    layout->addWidget(m_avatarLabel);


// recuperer les QTime de record verifier si il sont valide sinon  mettre "pas de record"
    QTime record1 = m_profile->getRecord(0);
    QTime record2 = m_profile->getRecord(1);
    QTime record3 = m_profile->getRecord(2);
    QTime record4 = m_profile->getRecord(3);

    if (record1 == QTime(0, 0, -1)) {
        m_recordLabel1 = new QLabel("Record: Pas de record", this);
    } else {
        m_recordLabel1 = new QLabel("Record: " + record1.toString(), this);
    }
    layout->addWidget(m_recordLabel1);

    if (record2 == QTime(0, 0, -1)) {
        m_recordLabel2 = new QLabel("Record: Pas de record", this);
    } else {
        m_recordLabel2 = new QLabel("Record: " + record2.toString(), this);
    }
    layout->addWidget(m_recordLabel2);

    if (record3 == QTime(0, 0, -1)) {
        m_recordLabel3 = new QLabel("Record: Pas de record", this);
    } else {
        m_recordLabel3 = new QLabel("Record: " + record3.toString(), this);
    }
    layout->addWidget(m_recordLabel3);

    if (record4 == QTime(0, 0, -1)) {
        m_recordLabel4 = new QLabel("Record: Pas de record", this);
    } else {
        m_recordLabel4 = new QLabel("Record: " + record4.toString(), this);
    }
    layout->addWidget(m_recordLabel4);

    m_gamesPlayedLabel = new QLabel("Games Played: " + QString::number(m_profile->getPartiesJouer()), this);
    layout->addWidget(m_gamesPlayedLabel);

    m_gamesWonLabel = new QLabel("Games Won: " + QString::number(m_profile->getPartiesGagner()), this);
    layout->addWidget(m_gamesWonLabel);

    m_gamesLostLabel = new QLabel("Games Lost: " + QString::number(m_profile->getPartiesPerdu()), this);
    layout->addWidget(m_gamesLostLabel);

    //winrate par le calcul des games won et games played
    double winRate = 0;
    if (m_profile->getPartiesJouer() != 0) {
        winRate = (double)m_profile->getPartiesGagner() / m_profile->getPartiesJouer() * 100;
    }
    m_winRateLabel = new QLabel("Win Rate: " + QString::number(winRate) + "%", this);
    layout->addWidget(m_winRateLabel);

    setWindowTitle("Profile Information");
}

InfoDialog::~InfoDialog()
{
}
