#include "headerFiles/Models/Profile.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QTime>
#include <iostream>

Profile::Profile(const QString &name, const QString &avatar) : m_name(name), m_avatar(avatar)
{

    // Initialize records to 0
    // for (int i = 0; i < 4; ++i) {
    
    //         m_records[i] =  
    // }

    // If avatar is empty, set it to default
    if (m_avatar.isEmpty()) {
        m_avatar = "";
    }

    // If name is empty, set it to "Unknown"
    if (m_name.isEmpty()) {
        m_name = "Unknown";
    }

    m_partiesJouer = 0;
    m_partiesGagner = 0;
    m_partiesPerdu = 0;




}

Profile::Profile() : m_name(""), m_avatar("")
{
    // Initialize records to 0
    for (int i = 0; i < 3; ++i) {
            m_records[i] = QTime(0, 0, -1); // 
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

void Profile::setRecord(int index, QTime time) {
    if (index >= 0 && index <= 3) {

        std::cout << "setRecord" << time.toString().toStdString() << std::endl;

        m_records[index] = time;
    }
}

QTime Profile::getRecord(int index) const {
    if (index >= 0 && index <= 3) {
        return m_records[index];
    } else {
        return QTime(99, 59, 59);
    }
}



QTime Profile::getRecord(int row, int col, int mines){
    if(row == 8 && col == 8 && mines == 10){
        return m_records[0];
    }
    if(row == 16 && col == 16 && mines == 40){
        return m_records[1];
    }

    if(row == 16 && col == 30 && mines == 99){
        return m_records[2];
    }

    return m_records[3];
}


void Profile::setUuid(const QString &uuid)
{
    m_uuid = uuid;
}

QString Profile::getUuid(){
    return m_uuid;
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

int Profile::getPartiesJouer() const
{
    return m_partiesJouer;
}


int Profile::getPartiesGagner() const
{
    return m_partiesGagner;
}


int Profile::getPartiesPerdu() const
{
    return m_partiesPerdu;
} 
