/*
 * Copyright (c) 2001,2002 Steven M. Cherry. All rights reserved.
 *
 * This file is a part of slib - a c++ utility library
 *
 * The slib project, including all files needed to compile 
 * it, is free software; you can redistribute it and/or use it and/or modify 
 * it under the terms of the GNU Lesser General Public License as published by 
 * the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * You should have received a copy of the GNU Lesser General Public License 
 * along with this program.  See file COPYING for details.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "OdbcDate.h"
using namespace Helix::Glob;

#include "AnException.h"
using namespace SLib;

OdbcDate::OdbcDate() : Date()
{
	m_odbcStruct = (SQL_TIMESTAMP_STRUCT*)malloc(sizeof(SQL_TIMESTAMP_STRUCT));
	memset(m_odbcStruct, 0, sizeof(SQL_TIMESTAMP_STRUCT));
}	

OdbcDate::OdbcDate(const OdbcDate& d) : Date(d)
{
	m_odbcStruct = (SQL_TIMESTAMP_STRUCT*)malloc(sizeof(SQL_TIMESTAMP_STRUCT));
	memset(m_odbcStruct, 0, sizeof(SQL_TIMESTAMP_STRUCT));
	memcpy(m_odbcStruct, d.m_odbcStruct, sizeof(SQL_TIMESTAMP_STRUCT));	
}

OdbcDate::~OdbcDate()
{
	free(m_odbcStruct);
	m_odbcStruct = NULL;
}

OdbcDate& OdbcDate::operator=(const OdbcDate& d)
{
	Date::operator=(d);

	memset(m_odbcStruct, 0, sizeof(SQL_TIMESTAMP_STRUCT));
	memcpy(m_odbcStruct, d.m_odbcStruct, sizeof(SQL_TIMESTAMP_STRUCT));	

	return *this;
}

SQL_TIMESTAMP_STRUCT* OdbcDate::GetOdbcStruct()
{
	return m_odbcStruct;
}

void OdbcDate::InternalToOdbc()
{
	m_odbcStruct->year = m_TimeStruct->tm_year;
	m_odbcStruct->month = m_TimeStruct->tm_mon;
	m_odbcStruct->day = m_TimeStruct->tm_mday;
	m_odbcStruct->hour = m_TimeStruct->tm_hour;
	m_odbcStruct->minute = m_TimeStruct->tm_min;
	m_odbcStruct->second = m_TimeStruct->tm_sec;
	m_odbcStruct->fraction = 0;
}

void OdbcDate::OdbcToInternal()
{
	m_TimeStruct->tm_year = m_odbcStruct->year;
	m_TimeStruct->tm_mon = m_odbcStruct->month;
	m_TimeStruct->tm_mday = m_odbcStruct->day;
	m_TimeStruct->tm_hour = m_odbcStruct->hour;
	m_TimeStruct->tm_min = m_odbcStruct->minute;
	m_TimeStruct->tm_sec = m_odbcStruct->second;
}
