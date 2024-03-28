#ifndef PROFILE_H
#define PROFILE_H

#include <QString>
#include <QPixmap>

class Profile
{
public:
    Profile(const QString &name, const QString &avatar);
    Profile();
    ~Profile();

    QString getName() const;
    QString getAvatarPath() const;
    int getRecord(int mode) const; // mode 0: mode1, mode 1: mode2, mode 2: mode3

    void setName(const QString &name);
    void setAvatar(const QString &avatar);
    void setRecord(int mode, int time);
    void setEasyRecord(int time);
    void setMediumRecord(int time);
    void setHardRecord(int time);
    void setUuid(const QString &uuid);
    void setPartiesJouer(int nb);
    void setPartiesGagner(int nb);
    void setPartiesPerdu(int nb);
    void setAvatarPath(QString path);
    void setCustomRecord(int time);
    int getEasyRecord();
    int getMediumRecord();
    int getHardRecord();
    int getPartiesJouer();
    int getPartiesGagner();
    int getPartiesPerdu();
    int getCustomRecord();
    
    QString getAvatarPath();
    QString getUuid();



private:
    QString m_uuid;
    QString m_name;
    QString m_avatar;
    int m_records[4]; // Store records for each mode
    int m_partiesJouer;
    int m_partiesGagner;
    int m_partiesPerdu;


    
};
Q_DECLARE_METATYPE(Profile*)

#endif // PROFILE_H
