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
#include "SettingsType-RDBCpuType.h"
#include <Project64-core/N64System/N64Types.h>

CSettingTypeRDBCpuType::CSettingTypeRDBCpuType(const char * Name, SettingID DefaultSetting ) :
    CSettingTypeRomDatabase(Name,DefaultSetting)
{
}

CSettingTypeRDBCpuType::CSettingTypeRDBCpuType(const char * Name, uint32_t DefaultValue ) :
    CSettingTypeRomDatabase(Name,DefaultValue)
{
}

CSettingTypeRDBCpuType::~CSettingTypeRDBCpuType()
{
}

bool CSettingTypeRDBCpuType::Load (uint32_t /*Index*/, bool & /*Value*/ ) const
{
    g_Notify->BreakPoint(__FILE__, __LINE__);
    return false;
}

bool CSettingTypeRDBCpuType::Load (uint32_t Index, uint32_t & Value ) const
{
    stdstr strValue;
    bool bRes = m_SettingsIniFile->GetString(m_SectionIdent->c_str(),m_KeyName.c_str(),m_DefaultStr,strValue);
    if (!bRes)
    {
        LoadDefault(Index,Value);
        return false;
    }
    const char * String = strValue.c_str();

    if (strcmp(String,"Interpreter") == 0)      { Value = CPU_Interpreter; }
    else if (strcmp(String,"Recompiler") == 0)  { Value = CPU_Recompiler; }
    else if (strcmp(String,"SyncCores") == 0)   { Value = CPU_SyncCores; }
    else if (strcmp(String,"default") == 0)
    {
        LoadDefault(Index,Value);
        return false;
    }
    else { g_Notify->BreakPoint(__FILE__, __LINE__); }

    return true;
}

bool CSettingTypeRDBCpuType::Load (uint32_t /*Index*/, std::string & /*Value*/ ) const
{
    g_Notify->BreakPoint(__FILE__, __LINE__);
    return false;
}

//return the default values
void CSettingTypeRDBCpuType::LoadDefault (uint32_t /*Index*/, bool & /*Value*/ ) const
{
    g_Notify->BreakPoint(__FILE__, __LINE__);
}

void CSettingTypeRDBCpuType::LoadDefault (uint32_t /*Index*/, uint32_t & Value  ) const
{
    if (m_DefaultSetting != Default_None)
    {
        if (m_DefaultSetting == Default_Constant)
        {
            Value = m_DefaultValue;
        } else {
            g_Settings->LoadDword(m_DefaultSetting,Value);
        }
    }
}

void CSettingTypeRDBCpuType::LoadDefault (uint32_t /*Index*/, std::string & /*Value*/ ) const
{
    g_Notify->BreakPoint(__FILE__, __LINE__);
}

//Update the settings
void CSettingTypeRDBCpuType::Save (uint32_t /*Index*/, bool /*Value*/ )
{
    g_Notify->BreakPoint(__FILE__, __LINE__);
}

void CSettingTypeRDBCpuType::Save (uint32_t /*Index*/, uint32_t Value )
{
    stdstr strValue;
    switch (Value)
    {
    case CPU_Interpreter: strValue = "Interpreter"; break;
    case CPU_Recompiler:  strValue = "Recompiler"; break;
    case CPU_SyncCores:   strValue = "SyncCores"; break;
    default:
        g_Notify->BreakPoint(__FILE__, __LINE__);
    }
    m_SettingsIniFile->SaveString(m_SectionIdent->c_str(),m_KeyName.c_str(),strValue.c_str());
}

void CSettingTypeRDBCpuType::Save (uint32_t /*Index*/, const std::string & /*Value*/ )
{
    g_Notify->BreakPoint(__FILE__, __LINE__);
}

void CSettingTypeRDBCpuType::Save (uint32_t /*Index*/, const char * /*Value*/ )
{
    g_Notify->BreakPoint(__FILE__, __LINE__);
}

void CSettingTypeRDBCpuType::Delete(uint32_t /*Index*/ )
{
    m_SettingsIniFile->SaveString(m_SectionIdent->c_str(),m_KeyName.c_str(),NULL);
}
