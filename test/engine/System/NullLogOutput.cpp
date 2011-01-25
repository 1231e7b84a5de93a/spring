/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#include "LogOutput.h"

#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

/******************************************************************************/
/******************************************************************************/

CLogSubsystem* CLogSubsystem::linkedList;
static CLogSubsystem LOG_DEFAULT("", true);


CLogSubsystem::CLogSubsystem(const char* name, bool enabled)
: name(name), next(linkedList), enabled(enabled)
{
}

/******************************************************************************/
/******************************************************************************/

CLogOutput logOutput;

LogObject::LogObject(const CLogSubsystem& _subsys) : subsys(_subsys)
{
}

LogObject::LogObject() : subsys(LOG_DEFAULT)
{
}

LogObject::~LogObject()
{
}

CLogOutput::CLogOutput()
{
}


CLogOutput::~CLogOutput()
{
}


void CLogOutput::End()
{
}

void CLogOutput::Flush()
{
}

static const std::string someString = "";

const std::string& CLogOutput::GetFileName() const
{
	return someString;
}
const std::string& CLogOutput::GetFilePath() const
{
	return someString;
}
void CLogOutput::SetFileName(std::string fname)
{
}

std::string CLogOutput::CreateFilePath(const std::string& fileName)
{
	return someString;
}


void CLogOutput::SetLogFileRotating(bool enabled)
{
}
bool CLogOutput::IsLogFileRotating() const
{
	return false;
}

void CLogOutput::RotateLogFile() const
{
}

void CLogOutput::Initialize()
{
}

void CLogOutput::InitializeSubsystems()
{
}


void CLogOutput::Output(const CLogSubsystem& subsystem, const std::string& str)
{
}


void CLogOutput::SetLastMsgPos(const float3& pos)
{
}



void CLogOutput::AddSubscriber(ILogSubscriber* ls)
{
}

void CLogOutput::RemoveSubscriber(ILogSubscriber *ls)
{
}



void CLogOutput::SetSubscribersEnabled(bool enabled) {
}

bool CLogOutput::IsSubscribersEnabled() const {
	return false;
}



// ----------------------------------------------------------------------
// Printing functions
// ----------------------------------------------------------------------

void CLogOutput::Print(CLogSubsystem& subsystem, const char* fmt, ...)
{
}


void CLogOutput::Printv(CLogSubsystem& subsystem, const char* fmt, va_list argp)
{
}


void CLogOutput::Print(const char* fmt, ...)
{
}


void CLogOutput::Print(const std::string& text)
{
}


void CLogOutput::Prints(const CLogSubsystem& subsystem, const std::string& text)
{
}


CLogSubsystem& CLogOutput::GetDefaultLogSubsystem()
{
	return LOG_DEFAULT;
}



void CLogOutput::ToStdout(const CLogSubsystem& subsystem, const std::string& message)
{
}

void CLogOutput::ToFile(const CLogSubsystem& subsystem, const std::string& message)
{
}
