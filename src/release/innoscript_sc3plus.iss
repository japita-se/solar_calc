[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{312563ED-30F0-49E0-9088-7E7111B8D686}
AppName=Solar Calc 3 Plus
AppVerName=SolarCalc 3 Plus
AppPublisher=StudioIacovoni.org
DefaultDirName={pf}\Solar Calc 3 Plus
DefaultGroupName=Solar Calc Plus
LicenseFile=C:\Users\giuseppe\Documents\Programmi\sclicense.txt
OutputBaseFilename=solarc-3P-setup
Compression=lzma
SolidCompression=yes
Uninstallable=yes
SetupIconFile=app.ico
WizardImageFile=box_plus.bmp
ChangesAssociations = yes
AlwaysRestart = no

DirExistsWarning=yes

[Languages]
Name: mytrans; MessagesFile: compiler:Languages\ItalianSC.isl



[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}";
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}";

[Files]
Source: "solar.exe"; DestDir: "{app}";
Source: "QtCore4.dll"; DestDir: "{app}";
Source: "QtGui4.dll";  DestDir: "{app}";
Source: "QtSql4.dll";  DestDir: "{app}";
Source: "QtXml4.dll";  DestDir: "{app}";
Source: "qwt5.dll";    DestDir: "{app}";
Source: "mingwm10.dll"; DestDir: "{app}";
Source: "libgcc_s_dw2-1.dll"; DestDir: "{app}";
Source: "QtSvg4.dll";   DestDir: "{app}";
Source: "QtWebKit4.dll";   DestDir: "{app}";
Source: "QtNetwork4.dll";   DestDir: "{app}";
Source: "sqldrivers\*"; DestDir: "{app}\sqldrivers";
Source: "imageformats\*"; DestDir: "{app}\imageformats";
Source: "raw2005.txt";     DestDir: "{app}";
Source: "datiUNIEnea.db"; DestDir: "{app}";
Source: "bs\*"; DestDir: "{app}";
 
Source: "panels.db";   DestDir: "{app}"; Flags: onlyifdoesntexist;
;Source: "22yr_T10M";      DestDir: "{app}"
;Source: "10yr_wspd50m";      DestDir: "{app}"
Source: "phonon4.dll"; DestDir: "{app}";
Source: "index.html"; DestDir: "{app}"
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Registry]
Root: HKCU; Subkey: "Software\StudioIacovoni.org\SolarCalc 3 Plus"; Flags: uninsdeletekey
Root: HKCU; Subkey: "Software\StudioIacovoni.org\SolarCalc 3"; Flags: uninsdeletekey

Root: HKCR; Subkey: ".scta"; ValueType: string; ValueName: ""; ValueData: "SolarCalc Data - Costs"; Flags: uninsdeletevalue
Root: HKCR; Subkey: "SolarCalc Data - Costs"; ValueType: string; ValueName: ""; ValueData: "SolarCalc Costs"; Flags: uninsdeletekey

Root: HKCR; Subkey: ".scb"; ValueType: string; ValueName: ""; ValueData: "SolarCalc Data - Bands"; Flags: uninsdeletevalue
Root: HKCR; Subkey: "SolarCalc Data - Bands"; ValueType: string; ValueName: ""; ValueData: "SolarCalc Data Bands"; Flags: uninsdeletekey

Root: HKCR; Subkey: ".scpm"; ValueType: string; ValueName: ""; ValueData: "SolarCalc Data - Min Prices"; Flags: uninsdeletevalue
Root: HKCR; Subkey: "SolarCalc Data - Min Prices"; ValueType: string; ValueName: ""; ValueData: "SolarCalc Data Min Prices"; Flags: uninsdeletekey

Root: HKCR; Subkey: ".scp"; ValueType: string; ValueName: ""; ValueData: "SolarCalc Data - Prices"; Flags: uninsdeletevalue
Root: HKCR; Subkey: "SolarCalc Data - Prices"; ValueType: string; ValueName: ""; ValueData: "SolarCalc Data Prices"; Flags: uninsdeletekey

Root: HKCR; Subkey: ".tax"; ValueType: string; ValueName: ""; ValueData: "SolarCalc Data - Tax"; Flags: uninsdeletevalue
Root: HKCR; Subkey: "SolarCalc Data - Tax"; ValueType: string; ValueName: ""; ValueData: "SolarCalc Data Tax"; Flags: uninsdeletekey
    
Root: HKCR; Subkey: ".sc"; ValueType: string; ValueName: ""; ValueData: "SolarCalc 3"; Flags: uninsdeletevalue
Root: HKCR; Subkey: "SolarCalc 3"; ValueType: string; ValueName: ""; ValueData: "SolarCalc File"; Flags: uninsdeletekey
Root: HKCR; Subkey: "SolarCalc 3\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\solar.EXE,0"
Root: HKCR; Subkey: "SolarCalc 3\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\solar.exe"" ""%1"""

[Icons]
Name: "{group}\Solar Calc 3 Plus"; Filename: "{app}\solar.exe"; workingdir: "{app}"
Name: "{group}\{cm:UninstallProgram,Solar Calc 3 Plus }"; Filename: "{uninstallexe}"
Name: "{commondesktop}\Solar Calc 3 Plus"; Filename: "{app}\solar.exe"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\Solar Calc Plus"; Filename: "{app}\solar{{312563ED-30F0-49E0-9088-7E7111B8D686}}.exe"; Tasks: quicklaunchicon




[Run]
Filename: "{app}\solar.exe"; Description: "{cm:LaunchProgram,Solar Calc }"; Flags: nowait postinstall skipifsilent

[_EndOfScript]
; c HiSoft2000 http://www.Hisoft2000.de Mail: HiSoft2000@HiSoft2000.de c 2002-2005
; Visual dBase, dB2K, dBase SE and dBase Plus c dataBased Intelligence.Inc Homepage: http://www.databi.com/
; dQuery for Delphi,C++,dBASE PLUS c dataBased Intelligence.Inc see also Homepage: http://www.dQuery.com/





