#ifndef PROFILE_H
#define PROFILE_H

#include <QString>
#include <QPixmap>

class Profile
{
public:
    Profile(const QString &name, const QString &avatar);
    ~Profile();

    QString getName() const;
    QString getAvatarPath() const;
    int getRecord(int mode) const; // mode 0: mode1, mode 1: mode2, mode 2: mode3

    void setName(const QString &name);
    void setAvatar(const QString &avatar);
    void setRecord(int mode, int time);

    bool saveProfile(const QString &filePath) const;
    static Profile* loadProfile(const QString &filePath);

private:
    QString m_name;
    QString m_avatar;
    int m_records[3]; // Store records for each mode

    
};
Q_DECLARE_METATYPE(Profile*)

#endif // PROFILE_H
