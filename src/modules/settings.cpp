#include "settings.h"
#include "simpleini.h"

settings::settings()
{

}

void settings::saveIntSetting(QString inifile, QString section, QString key, int value) {

    SI_Error rc;

    CSimpleIniA ini(true, false, false);
    rc = ini.LoadFile(inifile.toStdString().c_str());

    rc = ini.SetLongValue(section.toStdString().c_str(), key.toStdString().c_str(), value);

    ini.SetSpaces(false);
    rc = ini.SaveFile(inifile.toStdString().c_str());
}

int settings::loadIntSetting(QString inifile, QString section, QString key, long def) {

    SI_Error rc;

    CSimpleIniA ini(true, false, false);
    rc = ini.LoadFile(inifile.toStdString().c_str());

    int bValue = ini.GetLongValue(section.toStdString().c_str(), key.toStdString().c_str(), def);

    return(bValue);
}

void settings::saveBoolSetting(QString inifile, QString section, QString key, bool value) {

    SI_Error rc;

    CSimpleIniA ini(true, false, false);
    rc = ini.LoadFile(inifile.toStdString().c_str());

    rc = ini.SetBoolValue(section.toStdString().c_str(), key.toStdString().c_str(), value);

    ini.SetSpaces(false);
    rc = ini.SaveFile(inifile.toStdString().c_str());
}

bool settings::loadBoolSetting(QString inifile, QString section, QString key, bool def) {

    SI_Error rc;

    CSimpleIniA ini(true, false, false);
    rc = ini.LoadFile(inifile.toStdString().c_str());

    bool bValue = ini.GetBoolValue(section.toStdString().c_str(), key.toStdString().c_str(), def);

    return(bValue);
}

void settings::saveStringSetting(QString inifile, QString section, QString key, QString value) {

    SI_Error rc;

    CSimpleIniA ini(true, false, false);
    rc = ini.LoadFile(inifile.toStdString().c_str());

    rc = ini.SetValue(section.toStdString().c_str(), key.toStdString().c_str(), value.toStdString().c_str());

    ini.SetSpaces(false);
    rc = ini.SaveFile(inifile.toStdString().c_str());
}

QString settings::loadStringSetting(QString inifile, QString section, QString key, QString def) {

    SI_Error rc;

    CSimpleIniA ini(true, false, false);
    rc = ini.LoadFile(inifile.toStdString().c_str());

    QString value = ini.GetValue(section.toStdString().c_str(), key.toStdString().c_str(), def.toStdString().c_str());

    return(value);
}

QStringList settings::getAllSection(QString inifile) {

    SI_Error rc;
    QStringList lValues;

    CSimpleIniA ini(true, false, false);
    rc = ini.LoadFile(inifile.toStdString().c_str());

    CSimpleIniA::TNamesDepend test;

    ini.GetAllSections(test);

    typename CSimpleIniA::TNamesDepend::const_iterator iValue = test.begin();
    for ( ; iValue != test.end(); ++iValue) {

        lValues << iValue->pItem;
    }

    return(lValues);
}

QStringList settings::GetAllKeys(QString inifile, QString section) {

    SI_Error rc;
    QStringList lValues;
    bool retCode;

    CSimpleIniA ini(true, false, false);
    rc = ini.LoadFile(inifile.toStdString().c_str());

    CSimpleIniA::TNamesDepend lNames;

    retCode = ini.GetAllKeys(section.toStdString().c_str(), lNames);

    typename CSimpleIniA::TNamesDepend::const_iterator iValue = lNames.begin();
    for ( ; iValue != lNames.end(); ++iValue) {

        lValues << iValue->pItem;
    }

    return(lValues);
}

void settings::Delete(QString inifile, QString section, QString key) {

    SI_Error rc;
    bool retCode;

    CSimpleIniA ini(true, false, false);
    rc = ini.LoadFile(inifile.toStdString().c_str());

    retCode = ini.Delete(section.toStdString().c_str(), key.toStdString().c_str(), true);

    ini.SetSpaces(false);
    rc = ini.SaveFile(inifile.toStdString().c_str());
}
