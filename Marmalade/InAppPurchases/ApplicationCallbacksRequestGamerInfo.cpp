/*
 * Copyright (C) 2012, 2013 OUYA, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Application.h"
#include "ApplicationCallbacksRequestGamerInfo.h"
#include "ApplicationGamerInfo.h"
#include "CallbacksRequestGamerInfo.h"
#include "CallbackSingleton.h"
#include "ExtensionGamerInfo.h"

#include "IwDebug.h"

#include <stdio.h>

void RequestGamerInfoOnSuccess(s3eRequestGamerInfoSuccessEvent* event)
{
	IwTrace(DEFAULT, ("void RequestGamerInfoOnSuccess(event)"));
	if (event)
	{
		OuyaSDK::GamerInfo gamerInfo;
		gamerInfo.Copy(event->m_gamerInfo);
		Application::m_ui.m_callbacksRequestGamerInfo->OnSuccess(gamerInfo);
	}
	else
	{
		Application::m_ui.m_callbacksRequestGamerInfo->OnFailure(-1, "Success event is null");
	}
}

void RequestGamerInfoOnFailure(s3eRequestGamerInfoFailureEvent* event)
{
	//IwTrace(DEFAULT, ("void RequestGamerInfoOnFailure(event)"));
	if (event)
	{
		Application::m_ui.m_callbacksRequestGamerInfo->OnFailure(event->m_errorCode, event->m_errorMessage);
	}
	else
	{
		Application::m_ui.m_callbacksRequestGamerInfo->OnFailure(-1, "Failure event is null");
	}
}

void RequestGamerInfoOnCancel(s3eRequestGamerInfoCancelEvent* event)
{
	//IwTrace(DEFAULT, ("void RequestGamerInfoOnCancel(event)"));
	if (event)
	{
		Application::m_ui.m_callbacksRequestGamerInfo->OnCancel();
	}
	else
	{
		Application::m_ui.m_callbacksRequestGamerInfo->OnFailure(-1, "Cancel event is null");
	}
}

s3eCallback ApplicationCallbacksRequestGamerInfo::GetSuccessEvent()
{
	return (s3eCallback)RequestGamerInfoOnSuccess;
}

s3eCallback ApplicationCallbacksRequestGamerInfo::GetFailureEvent()
{
	return (s3eCallback)RequestGamerInfoOnFailure;
}

s3eCallback ApplicationCallbacksRequestGamerInfo::GetCancelEvent()
{
	return (s3eCallback)RequestGamerInfoOnCancel;
}

void ApplicationCallbacksRequestGamerInfo::OnSuccess(const OuyaSDK::GamerInfo& gamerInfo)
{
	//IwTrace(DEFAULT, ("OnSuccess"));

	//char buffer[256];
	//sprintf(buffer, "OnSuccess:  %s", gamerUUID.c_str());
	//IwTrace(DEFAULT, (buffer));

	Application::m_ui.SetMessage("ApplicationCallbacksRequestGamerInfo::OnSuccess");
	Application::m_ui.SetUsername(gamerInfo.Username);
	Application::m_ui.SetGamerUUID(gamerInfo.Uuid);
}

void ApplicationCallbacksRequestGamerInfo::OnFailure(int errorCode, const std::string& errorMessage)
{
	//IwTrace(DEFAULT, ("OnFailure"));

	//char buffer[256];
	//sprintf(buffer, "OnFailure errorCode=%d errorMessage=%s", errorCode, errorMessage.c_str());
	//IwTrace(DEFAULT, (buffer));

	std::string msg = "ApplicationCallbacksRequestGamerInfo::OnFailure";
	msg.append(" errorMessage=");
	msg.append(errorMessage);
	Application::m_ui.SetMessage(msg);
}

void ApplicationCallbacksRequestGamerInfo::OnCancel()
{
	//IwTrace(DEFAULT, ("OnCancel"));

	Application::m_ui.SetMessage("ApplicationCallbacksRequestGamerInfo::OnCancel");
}