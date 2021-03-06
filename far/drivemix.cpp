﻿/*
drivemix.cpp

Misc functions for drive/disk info
*/
/*
Copyright © 1996 Eugene Roshal
Copyright © 2000 Far Group
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the authors may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// Self:
#include "drivemix.hpp"

// Internal:
#include "config.hpp"
#include "notification.hpp"
#include "global.hpp"

// Platform:
#include "platform.fs.hpp"
#include "platform.security.hpp"

// Common:

// External:

//----------------------------------------------------------------------------

static std::optional<os::fs::drives_set> SavedLogicalDrives;

void UpdateSavedDrives(const std::any& Payload)
{
	if (!SavedLogicalDrives)
		return;

	const auto& Message = std::any_cast<const update_devices_message&>(Payload);
	const os::fs::drives_set Drives(Message.Drives);

	if (Message.Arrival)
		*SavedLogicalDrives |= Drives;
	else
		*SavedLogicalDrives &= ~Drives;
}

os::fs::drives_set allowed_drives_mask()
{
	return Global->Opt->Policies.ShowHiddenDrives?
		os::fs::drives_set{}.set() :
		os::security::allowed_drives_mask();
}

os::fs::drives_set os::fs::get_logical_drives()
{
	if (!SavedLogicalDrives || !(Global && Global->Opt && Global->Opt->RememberLogicalDrives))
	{
		SavedLogicalDrives = GetLogicalDrives();
	}

	return *SavedLogicalDrives;
}

bool IsDriveTypeRemote(UINT DriveType)
{
	return DriveType == DRIVE_REMOTE || DriveType == DRIVE_REMOTE_NOT_CONNECTED;
}
