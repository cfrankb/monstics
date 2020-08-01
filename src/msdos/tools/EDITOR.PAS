{************************************************}
{                                                }
{   Turbo Pascal for Windows                     }
{   Demo program                                 }
{   Copyright (c) 1991 by Borland International  }
{                                                }
{************************************************}

program MDIFileEditor;

{$R EDITOR.RES}
{$X+}
{$S-}


uses WObjects, WinTypes, WinProcs, WinDos, StdDlgs, StdWnds, Strings,wincrt;

var Sonia:byte;
var x:byte;
var val:word;

Type LongRecord = Record
		  case  Integer of
		  0: (Long:Longint);
		  1: (low,High:Word);
		  end;


const
  cm_SaveState    = 200;
  cm_RestoreState = 201;

const
  DSKFile = 'c:\windows\EDITOR.INI';

Var INICTRL:TEXT;
var a:integer;

Inidata : array [0..40] of char;



type

  { Declare TMDIFileApp, a TApplication descendant }
  TMDIFileApp = object(TApplication)
    procedure InitMainWindow; virtual;
    procedure InitInstance; virtual;
  end;

  { Declare TMDIFileWindow, a TMDIWindow descendant }
  PMDIFileWindow = ^TMDIFileWindow;
  TMDIFileWindow = object(TMDIWindow)
    procedure SetupWindow; virtual;
    procedure NewFile(var Msg: TMessage);
      virtual cm_First + cm_MDIFileNew;
    procedure OpenFile(var Msg: TMessage);
      virtual cm_First + cm_MDIFileOpen;
    procedure SaveState(var Msg: TMessage);
      virtual cm_First + cm_SaveState;
    procedure RestoreState(var Msg: TMessage);
      virtual cm_First + cm_RestoreState;
    Procedure TSaveState;
    Procedure TRestoreState;
    Procedure GetWindowClass(var bWndClass:TWndClass); virtual;

    Procedure L1000(var Msg: TMessage);
      virtual cm_first + 1000;
    Procedure L1001(var Msg: TMessage);
      virtual cm_first + 1001;
    Procedure L1002(var Msg: TMessage);
      virtual cm_first + 1002;
    Procedure L1003(var Msg: TMessage);
      virtual cm_first + 1003;
    Procedure L1004(var Msg: TMessage);
      virtual cm_first + 1004;
    Procedure L1005(var Msg: TMessage);
      virtual cm_first + 1005;
    Procedure L1006(var Msg: TMessage);
      virtual cm_first + 1006;
    Procedure L1007(var Msg: TMessage);
      virtual cm_first + 1007;
    Procedure L1008(var Msg: TMessage);
      virtual cm_first + 1008;
end;

  { Declare TFileEditor, a TFileWindow desendant }
  PFileEditor = ^TFileEditor;
  TFileEditor = object(TFileWindow)
    constructor Init(AParent: PWindowsObject; AFileName: PChar);
    destructor Done; virtual;
    procedure GetWindowClass(var AWndClass: TWndClass); virtual;
    function GetClassName: PChar; virtual;
  end;

const
  RFileEditor: TStreamRec = (
    ObjType: 1000;
    VmtLink: Ofs(TypeOf(TFileEditor)^);
    Load:    @TFileEditor.Load;
    Store:   @TFileEditor.Store);

{ TFileEditor }

const
  EditorCount: Integer = 0;

type
  TMenuState = (Enable, Disable);

procedure MenuItems(State: TMenuState);

procedure ModifyCommand(Command: Word);
var
  NewState: Word;
begin
  EnableMenuItem(PWindow(Application^.MainWindow)^.Attr.Menu, Command,
    NewState);
{  NewState := mf_ByCommand;
  if State = Enable then Inc(NewState, mf_Enabled)
  else Inc(NewState, mf_Disabled + mf_Grayed);
  EnableMenuItem(PWindow(Application^.MainWindow)^.Attr.Menu, Command,
    NewState);  }
end;

begin
  { Bail out if the window is already closed }
  if Application^.MainWindow^.HWindow = 0 then Exit;
end;

procedure IncEditors;
begin
  if EditorCount = 0 then MenuItems(Enable);
  Inc(EditorCount);
end;

procedure DecEditors;
begin
  Dec(EditorCount);
  if EditorCount = 0 then MenuItems(Disable);
end;

constructor TFileEditor.Init(AParent: PWindowsObject; AFileName: PChar);
begin
  TFileWindow.Init(AParent, '', AFileName);
  IncEditors;
end;

destructor TFileEditor.Done;
begin
  DecEditors;
  TFileWindow.Done;
end;

procedure TFileEditor.GetWindowClass(var AWndClass: TWndClass);
begin
  TFileWindow.GetWindowClass(AWndClass);
  {AWndClass.hIcon := LoadIcon(HInstance, '1');}
  AwndClass.Hicon:=LoadIcon(HInstance,'soso');
end;

function TFileEditor.GetClassName: PChar;
begin
  GetClassName := 'FileEditor';
end;

{ Respond to "New" command by constructing, creating, and setting up a
  new TFileWindow MDI child }
procedure TMDIFileWindow.NewFile(var Msg: TMessage);
begin
  Application^.MakeWindow(New(PFileEditor, Init(@Self, '')));
end;

procedure TMDIFileWindow.SetupWindow;
begin
  TMDIWindow.SetupWindow;
  MenuItems(Disable);
  TRestoreState;

end;

{ Respond to "Open" command by constructing, creating, and setting up a
  new TFileWindow MDI child }
procedure TMDIFileWindow.OpenFile(var Msg: TMessage);
var
  FileName: array[0..fsPathName] of Char;
begin
  if Application^.ExecDialog(New(PFileDialog, Init(@Self, PChar(sd_FileOpen),
      StrCopy(FileName, '*.ini')))) = id_Ok then
    Application^.MakeWindow(New(PFileEditor, Init(@Self, FileName)));
end;

{ Save the the position and contents of the windows to the
  "desk top" file. }
procedure TMDIFileWindow.SaveState(var Msg: TMessage);
begin
TSaveState;exit;
end;

Procedure TMDIFileWindow.TSaveState;

var
  S: PStream;

function FileDelete(Name: PChar): Integer; assembler;
asm
	PUSH	DS
	LDS	DX,Name
	MOV	AH,41H
	INT	21H
	JC	@@1
	XOR	AX,AX
@@1:	NEG	AX
	POP	DS
end;

begin
  S := New(PBufStream, Init(DskFile, stCreate, 1024));
  PutChildren(S^);
  if S^.Status <> stOk then
  begin
    Dispose(S, Done);
    FileDelete(DskFile);
    MessageBox(HWindow, 'Unable to write desktop file.', 'Disk error',
      mb_Ok or mb_IconExclamation);
  end
  else Dispose(S, Done);
end;

{ Read windows positions and contents from the "desk top" file. }
procedure TMDIFileWindow.RestoreState(var Msg: TMessage);
begin
TRestoreState;exit;
end;

Procedure TMDIFileWindow.TRestoreState;
var
  S: PStream;
  ErrorMsg: PChar;
begin
  ErrorMsg := nil;
  S := New(PBufStream, Init(DskFile, stOpenRead, 1024));
  if S^.Status <> stOk then
    ErrorMsg := nil
  else
  begin
    CloseChildren;
    GetChildren(S^);
    if LowMemory then
    begin
      CloseChildren;
      ErrorMsg := 'Not enough memory to open file.';
    if S^.Status <> stOk then exit;
      {ErrorMsg := 'Error reading desktop file.';}
    end
    else CreateChildren;
  end;
  if ErrorMsg <> nil then
    MessageBox(HWindow, ErrorMsg, 'Disk error', mb_Ok or mb_IconExclamation);
end;

Procedure TMDIFileWindow.GetWindowClass(var BWndClass:TWndClass);


begin


     Twindow.GetWindowClass(BWndClass);
     BWndClass.HIcon:=LoadIcon(HInstance,'chart4');


end;

Procedure TMDIFileWindow.L1000(var Msg:TMessage);
begin WinExec('l1000.bat',1);end;

Procedure TMDIFileWindow.L1001(var Msg:TMessage);
begin WinExec('l1001.bat',1);end;

Procedure TMDIFileWindow.L1002(var Msg:TMessage);
begin WinExec('l1002.bat',2);end;

Procedure TMDIFileWindow.L1003(var Msg:TMessage);
begin WinExec('l1003.bat',1);end;

Procedure TMDIFileWindow.L1004(var Msg:TMessage);
begin WinExec('l1004.bat',1);end;

Procedure TMDIFileWindow.L1005(var Msg:TMessage);
begin WinExec('l1005.bat',2);end;

Procedure TMDIFileWindow.L1006(var Msg:TMessage);
begin WinExec('l1006.bat',1);end;

Procedure TMDIFileWindow.L1007(var Msg:TMessage);
begin WinExec('l1007.bat',1);end;

Procedure TMDIFileWindow.L1008(var Msg:TMessage);
begin WinExec('l1008.bat',2);end;

{ Construct the TMDIFileApp's MainWindow of type TMDIFileWindow,
  loading its menu }
procedure TMDIFileApp.InitMainWindow;
begin
  MainWindow := New(PMDIFileWindow, Init('Files Editor',
  LoadMenu(HInstance, 'Commands')));
  PMDIFileWindow(MainWindow)^.ChildMenuPos := 3;







  { Register types to be written to stream }
  RegisterType(RWindow);
  RegisterType(REdit);
  RegisterType(RFileEditor);
end;










{ Initialize each MS-Windows application instance, loading an
  accelerator table }
procedure TMDIFileApp.InitInstance;
begin
  TApplication.InitInstance;
  if Status = 0 then
  begin
    HAccTable := LoadAccelerators(HInstance, 'master');
    if HAccTable = 0 then
      Status := em_InvalidWindow;
  end;
end;

{ Declare a variable of type TFileApp }
var
  MDIFileApp : TMDIFileApp;

{ Run the FileApp }
begin
  MDIFileApp.Init('MDIFileApp');
  MDIFileApp.Run;
  MDIFileApp.Done;
end.
