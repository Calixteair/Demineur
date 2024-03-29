#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include "headerFiles/Models/Profile.h"

class InfoDialog : public QDialog
{
    Q_OBJECT

public:
    InfoDialog(Profile *profile, QWidget *parent = nullptr);
    void addRecordLabel(QVBoxLayout *layout, const QString &text, const QString &value, const QString &style);
    void addStatLabel(QVBoxLayout *layout, const QString &text, const QString &value, const QString &style);
    ~InfoDialog();

private:
    Profile *m_profile;

    // Widgets pour afficher les informations du profil
    QLabel *m_nameLabel;
    QLabel *m_avatarLabel;
    QLabel *m_recordLabel1;
    QLabel *m_recordLabel2;
    QLabel *m_recordLabel3;
    QLabel *m_recordLabel4;
    QLabel *m_winRateLabel;
    QLabel *m_gamesPlayedLabel;
    QLabel *m_gamesWonLabel;
    QLabel *m_gamesLostLabel;
};

#endif // INFODIALOG_H