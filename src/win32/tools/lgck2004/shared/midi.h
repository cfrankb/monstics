/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File: midi.h
 *
 ***************************************************************************/

#ifndef __MIDI_H
#define __MIDI_H

DWORD playMIDIFile(HWND hWndNotify, LPSTR lpszMIDIFileName);

BOOL PlayMidi(HWND hWnd, char *sFileName);
BOOL PauseMidi(HWND hWnd= NULL);
BOOL ResumeMidi(HWND hWnd);
BOOL StopMidi(HWND hWnd= NULL);
BOOL ReplayMidi(HWND hWnd);

#endif

