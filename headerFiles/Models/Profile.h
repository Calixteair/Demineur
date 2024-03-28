#ifndef PROFILE_H
#define PROFILE_H

#include <QString>
#include <QPixmap>
#include <QTime>
#include <QMetaType>
#include <QTime>

class Profile
{
public:
    Profile(const QString &name, const QString &avatar);
    Profile();
    ~Profile();

    QString getName() const;
    QString getAvatarPath() const;
    QTime getRecord(int mode);

    void setName(const QString &name);
    void setAvatar(const QString &avatar);
    void setRecord(int mode, QTime time);
    void setUuid(const QString &uuid);
    void setPartiesJouer(int nb);
    void setPartiesGagner(int nb);
    void setPartiesPerdu(int nb);
    void setAvatarPath(QString path);
    int getPartiesJouer();
    int getPartiesGagner();
    int getPartiesPerdu();
    QString getAvatarPath();
    QString getUuid();



private:
    QString m_uuid;
    QString m_name;
    QString m_avatar;
    QTime m_records[4];
    int m_partiesJouer;
    int m_partiesGagner;
    int m_partiesPerdu;


    
};
Q_DECLARE_METATYPE(Profile*)

#endif // PROFILE_H
