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

    // If avatar is empty, set it to default
    if (m_avatar.isEmpty()) {
        m_avatar = "";
    }

    // If name is empty, set it to "Unknown"
    if (m_name.isEmpty()) {
        m_name = "Unknown";
    }



}

Profile::Profile() : m_name(""), m_avatar("")
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

void Profile::setName(const QString &name)
{
    m_name = name;
}

void Profile::setAvatar(const QString &avatar)
{
    m_avatar = avatar;
}

QString Profile::getAvatarPath()
{
    return m_avatar;
}

void Profile::setRecord(int mode, int time)
{
    if (mode >= 0 && mode < 3) {
        m_records[mode] = time;
    }
}


void Profile::setEasyRecord(int time)
{
    m_records[0] = time;
}

int Profile::getEasyRecord()
{
   return m_records[0];
}

void Profile::setMediumRecord(int time)
{
    m_records[1] = time;
}

int Profile::getMediumRecord()
{
    return m_records[1];
}

void Profile::setHardRecord(int time)
{
    m_records[2] = time;
}

int Profile::getHardRecord()
{
    return m_records[2];
}

void Profile::setCustomRecord(int time)
{
    m_records[3] = time;
}


void Profile::setUuid(const QString &uuid)
{
    m_uuid = uuid;
}

void Profile::setPartiesJouer(int partiesJouer)
{
    m_partiesJouer = partiesJouer;
}

void Profile::setPartiesGagner(int partiesGagner)
{
    m_partiesGagner = partiesGagner;
}

void Profile::setPartiesPerdu(int partiesPerdu)
{
    m_partiesPerdu = partiesPerdu;
}

void Profile::setAvatarPath(QString avatarPath)
{
    m_avatar = avatarPath;
}


