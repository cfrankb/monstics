/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File: midi.cpp
 *
 ***************************************************************************/

#include "stdafx.h"
#include "mmsystem.h"
#include "windows.h"
#include "midi.h"
#include "stdio.h"

// Plays a specified MIDI file by using MCI_OPEN and MCI_PLAY. Returns 
// as soon as playback begins. The window procedure function for the 
// given window will be notified when playback is complete. Returns 0L 
// on success; otherwise, it returns an MCI error code.
DWORD playMIDIFile(HWND hWndNotify, LPSTR lpszMIDIFileName)
{
    UINT wDeviceID;
    DWORD dwReturn;
    MCI_OPEN_PARMS mciOpenParms;
    MCI_PLAY_PARMS mciPlayParms;
    MCI_STATUS_PARMS mciStatusParms;
    //MCI_SEQ_SET_PARMS mciSeqSetParms;

    // Open the device by specifying the device and filename.
    // MCI will attempt to choose the MIDI mapper as the output port.
    mciOpenParms.lpstrDeviceType = "sequencer";
    mciOpenParms.lpstrElementName = lpszMIDIFileName;
    if (dwReturn = mciSendCommand(NULL, MCI_OPEN,
        MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,
        (DWORD)(LPVOID) &mciOpenParms))
    {
        // Failed to open device. Don't close it; just return error.
        return (dwReturn);
    }

    // The device opened successfully; get the device ID.
    wDeviceID = mciOpenParms.wDeviceID;

    // Check if the output port is the MIDI mapper.
    mciStatusParms.dwItem = MCI_SEQ_STATUS_PORT;
    if (dwReturn = mciSendCommand(wDeviceID, MCI_STATUS, 
        MCI_STATUS_ITEM, (DWORD)(LPVOID) &mciStatusParms))
    {
        mciSendCommand(wDeviceID, MCI_CLOSE, 0, NULL);
        return (dwReturn);
    }

    // The output port is not the MIDI mapper. 
    // Ask if the user wants to continue.
    if (LOWORD(mciStatusParms.dwReturn) != MIDI_MAPPER)
    {
		OutputDebugString("The MIDI mapper is not available.\n");
		
        // just close the device and return.
        mciSendCommand(wDeviceID, MCI_CLOSE, 0, NULL);
        return (0L);
    }

    // Begin playback. The window procedure function for the parent 
    // window will be notified with an MM_MCINOTIFY message when 
    // playback is complete. At this time, the window procedure closes 
    // the device.
    mciPlayParms.dwCallback = (DWORD) hWndNotify;
    if (dwReturn = mciSendCommand(wDeviceID, MCI_PLAY, MCI_NOTIFY, 
        (DWORD)(LPVOID) &mciPlayParms))
    {
        mciSendCommand(wDeviceID, MCI_CLOSE, 0, NULL);
        return (dwReturn);
    }

    return (0L);
}
 
  


//------------------------------------------------------------------
// 
// Function	: PlayMidi()
//
// Purpose	: Plays a midi file
//
//------------------------------------------------------------------

BOOL PlayMidi(HWND hWnd, char *sFileName)
{
    char buf[256];

    sprintf(buf, "open %s type sequencer alias MUSIC", sFileName);
    
    if (mciSendString("close all", NULL, 0, NULL) != 0)
    {
	return(FALSE);
    }

    if (mciSendString(buf, NULL, 0, NULL) != 0)
    {
	return(FALSE);
    }

    if (mciSendString("play MUSIC from 0 notify", NULL, 0, hWnd) != 0)
    {
	return(FALSE);
    }
    
    // Yahoo!
    return TRUE;
}

//------------------------------------------------------------------
// 
// Function	: PauseMidi()
//
// Purpose	: Pauses midi file
//
//------------------------------------------------------------------

BOOL PauseMidi(HWND hWnd)
{
    // Pause if we're not already paused...
    if (mciSendString("stop MUSIC", NULL, 0, NULL) != 0)
    {
	return(FALSE);
    }

    
    // Yahoo!
    return TRUE;
}

//------------------------------------------------------------------
// 
// Function	: ResumeMidi()
//
// Purpose	: Resumes playing of a midi file
//
//------------------------------------------------------------------

BOOL ResumeMidi(HWND hWnd)
{	
    // Resume midi
    if (mciSendString("play MUSIC notify", NULL, 0, hWnd) != 0)
    {
	return(FALSE);
    }

    // Yahoo!
    return TRUE;
}

//------------------------------------------------------------------
// 
// Function	: StopMidi
//
// Purpose	: Stops a midi file playing
//
//------------------------------------------------------------------

BOOL StopMidi(HWND hWnd)
{
    if (mciSendString("close all", NULL, 0, NULL) != 0)
    {
	return(FALSE);
    }	

    // Yahoo!
    return TRUE;
}

//------------------------------------------------------------------
// 
// Function	: ReplayMidi()
//
// Purpose	: Replays a midi file
//
//------------------------------------------------------------------

BOOL ReplayMidi(HWND hWnd)
{
    // Replay midi
    if (mciSendString("play MUSIC from 0 notify", NULL, 0, hWnd) != 0)
    {
	return(FALSE);
    }

    // Yahoo!
    return TRUE;
}

