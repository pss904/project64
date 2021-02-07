/****************************************************************************
*                                                                           *
* Project64 - A Nintendo 64 emulator.                                      *
* http://www.pj64-emu.com/                                                  *
* Copyright (C) 2012 Project64. All rights reserved.                        *
*                                                                           *
* License:                                                                  *
* GNU/GPLv2 http://www.gnu.org/licenses/gpl-2.0.html                        *
*                                                                           *
****************************************************************************/
#include "stdafx.h"
#include "SettingsType-RomDatabase.h"
#include "SettingsType-RDBOnOff.h"

CSettingTypeRDBOnOff::CSettingTypeRDBOnOff(const char * Name, SettingID DefaultSetting ) :
    CSettingTypeRomDatabase(Name,DefaultSetting)
{
}

CSettingTypeRDBOnOff::CSettingTypeRDBOnOff(const char * Name, uint32_t DefaultValue ) :
    CSettingTypeRomDatabase(Name,DefaultValue)
{
}

CSettingTypeRDBOnOff::~CSettingTypeRDBOnOff()
{
}

bool CSettingTypeRDBOnOff::Load (uint32_t Index, bool & Value ) const
{
    stdstr strValue;
    bool bRes = m_SettingsIniFile->GetString(m_SectionIdent->c_str(),m_KeyName.c_str(),m_DefaultStr,strValue);
    if (!bRes)
    {
        LoadDefault(Index,Value);
        return false;
    }
    const char * String = strValue.c_str();

    if (strcmp(String,"On") == 0)    { Value = true; }
    else if (strcmp(String,"Off") == 0)  { Value = false; }
    else if (strcmp(String,"Global") == 0 || strcmp(String,"default"))
    {
        LoadDefault(Index,Value);
        return false;
    }
    else { g_Notify->BreakPoint(__FILE__, __LINE__); }

    return true;
}

bool CSettingTypeRDBOnOff::Load (uint32_t /*Index*/, uint32_t & /*Value*/ ) const
{
    g_Notify->BreakPoint(__FILE__, __LINE__);
    return false;
}

bool CSettingTypeRDBOnOff::Load (uint32_t /*Index*/, std::string & /*Value*/ ) const
{
    g_Notify->BreakPoint(__FILE__, __LINE__);
    return false;
}

//return the default values
void CSettingTypeRDBOnOff::LoadDefault (uint32_t /*Index*/, bool & Value ) const
{
    if (m_DefaultSetting != Default_None)
    {
        if (m_DefaultSetting == Default_Constant)
        {
            Value = m_DefaultValue != 0;
        } else {
            g_Settings->LoadBool(m_DefaultSetting,Value);
        }
    }
}

void CSettingTypeRDBOnOff::LoadDefault (uint32_t /*Index*/, uint32_t & /*Value*/ ) const
{
    g_Notify->BreakPoint(__FILE__, __LINE__);
}

void CSettingTypeRDBOnOff::LoadDefault (uint32_t /*Index*/, std::string & /*Value*/ ) const
{
    g_Notify->BreakPoint(__FILE__, __LINE__);
}

//Update the settings
void CSettingTypeRDBOnOff::Save (uint32_t /*Index*/, bool Value )
{
    m_SettingsIniFile->SaveString(m_SectionIdent->c_str(),m_KeyName.c_str(),Value? "On" : "Off");
}

void CSettingTypeRDBOnOff::Save (uint32_t /*Index*/, uint32_t /*Value*/ )
{
    g_Notify->BreakPoint(__FILE__, __LINE__);
}

void CSettingTypeRDBOnOff::Save (uint32_t /*Index*/, const std::string & /*Value*/ )
{
    g_Notify->BreakPoint(__FILE__, __LINE__);
}

void CSettingTypeRDBOnOff::Save (uint32_t /*Index*/, const char * /*Value*/ )
{
    g_Notify->BreakPoint(__FILE__, __LINE__);
}

void CSettingTypeRDBOnOff::Delete(uint32_t /*Index*/ )
{
    m_SettingsIniFile->SaveString(m_SectionIdent->c_str(),m_KeyName.c_str(),NULL);
}
