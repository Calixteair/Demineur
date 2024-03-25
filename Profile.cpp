#include "Profile.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>

Profile::Profile(const QString &name, const QString &avatar) : m_name(name), m_avatar(avatar)
{
    // Initialize records to 0
    for (int i = 0; i < 3; ++i) {
        m_records[i] = 0;
    }
}

Profile::~Profile()
{
}

QString Profile::getName() const
{
    return m_name;
}

QString Profile::getAvatarPath() const
{
    return m_avatar;
}


int Profile::getRecord(int mode) const
{
    if (mode >= 0 && mode < 3) {
        return m_records[mode];
    }
    return -1; // Invalid mode
}

void Profile::setName(const QString &name)
{
    m_name = name;
}

void Profile::setAvatar(const QString &avatar)
{
    m_avatar = avatar;
}

void Profile::setRecord(int mode, int time)
{
    if (mode >= 0 && mode < 3) {
        m_records[mode] = time;
    }
}

bool Profile::saveProfile(const QString &filePath) const
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open file for writing";
        return false;
    }

    QDataStream out(&file);
    out << m_name << m_avatar << m_records[0] << m_records[1] << m_records[2];

    file.close();
    return true;
}

Profile* Profile::loadProfile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file for reading";
        return nullptr;
    }

    QDataStream in(&file);
    QString name;
    QString avatar;
    int records[3];
    in >> name >> avatar >> records[0] >> records[1] >> records[2];

    file.close();

    Profile *profile = new Profile(name, avatar);
    for (int i = 0; i < 3; ++i) {
        profile->setRecord(i, records[i]);
    }

    return profile;
}
