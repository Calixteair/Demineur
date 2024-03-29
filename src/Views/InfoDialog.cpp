#include "headerFiles/Views/InfoDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

InfoDialog::InfoDialog(Profile *profile, QWidget *parent)
    : QDialog(parent), m_profile(profile)
{
    // Création du layout vertical
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter); // Centrage du layout

    // Création et ajout des labels pour afficher les informations du profil
    m_nameLabel = new QLabel("Name: " + m_profile->getName(), this);
    m_nameLabel->setStyleSheet("font-weight: bold;"); // Police en gras
    layout->addWidget(m_nameLabel);

    m_avatarLabel = new QLabel(this);
    m_avatarLabel->setPixmap(QPixmap(m_profile->getAvatarPath())); // Chemin de l'avatar
    m_avatarLabel->setAlignment(Qt::AlignCenter); // Centrage de l'avatar
    layout->addWidget(m_avatarLabel);

    // Records
    QString recordStyle = "color: #007bff;"; // Couleur bleue pour les enregistrements
    addRecordLabel(layout, "Record Easy: ", m_profile->getRecord(0).toString(), recordStyle);
    addRecordLabel(layout, "Record Medium: ", m_profile->getRecord(1).toString(), recordStyle);
    addRecordLabel(layout, "Record Hard: ", m_profile->getRecord(2).toString(), recordStyle);
    addRecordLabel(layout, "Record Custom: ", m_profile->getRecord(3).toString(), recordStyle);

    // Statistiques de jeux
    QString gamesStyle = "color: #28a745;"; // Couleur verte pour les statistiques de jeux
    addStatLabel(layout, "Games Played: ", QString::number(m_profile->getPartiesJouer()), gamesStyle);
    addStatLabel(layout, "Games Won: ", QString::number(m_profile->getPartiesGagner()), gamesStyle);
    addStatLabel(layout, "Games Lost: ", QString::number(m_profile->getPartiesPerdu()), gamesStyle);

    // Taux de victoire
    double winRate = (m_profile->getPartiesJouer() != 0) ? (static_cast<double>(m_profile->getPartiesGagner()) / m_profile->getPartiesJouer() * 100) : 0;
    QString winRateStyle = (winRate >= 50) ? "color: #28a745;" : "color: #dc3545;"; // Vert si >= 50%, sinon rouge
    addStatLabel(layout, "Win Rate: ", QString::number(winRate, 'f', 2) + "%", winRateStyle);

    // Définition du titre de la fenêtre
    setWindowTitle("Profile Information");
}

// Fonction pour ajouter un label d'enregistrement
void InfoDialog::addRecordLabel(QVBoxLayout *layout, const QString &text, const QString &value, const QString &style)
{
    QLabel *recordLabel = new QLabel(text + (value.isEmpty() ? "N/A" : value), this);
    recordLabel->setStyleSheet(style);
    layout->addWidget(recordLabel);
}

// Fonction pour ajouter un label de statistique
void InfoDialog::addStatLabel(QVBoxLayout *layout, const QString &text, const QString &value, const QString &style)
{
    QLabel *statLabel = new QLabel(text + value, this);
    statLabel->setStyleSheet(style);
    layout->addWidget(statLabel);
}

InfoDialog::~InfoDialog()
{
}
