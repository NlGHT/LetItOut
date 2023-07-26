; Define the application name as a variable
!define AppName "LetItOut"
!define DisplayAppName "Let It Out"
!define Version "1.0.0"
!define PublisherName "Night"
Name "Let It Out"


!include "MUI2.nsh"

; Set the application name and installer
Outfile "${AppName}-Installer.exe"

; Set the default installation directory
InstallDir $PROGRAMFILES64\${AppName}

; Request application privileges for Windows Vista and above
RequestExecutionLevel admin

;--------------------------------
;Pages

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "..\LICENSE"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

;--------------------------------
;Languages

!insertmacro MUI_LANGUAGE "English"

;--------------------------------


; Define the components of your application (optional)
Section "${DisplayAppName}" SEC01
    ; Set output path for this section (where the files will be installed)
    SetOutPath $INSTDIR

    ; Copy all files from the build directory to the installation directory
    File /r "..\build\*.*"

    ; Add any other files you need to install

    ; Create a shortcut for the main executable
    CreateShortcut "$DESKTOP\${AppName}.lnk" "$INSTDIR\${AppName}.exe"
    CreateShortcut "$SMPROGRAMS\${DisplayAppName}.lnk" "$INSTDIR\${AppName}.exe"
    ;
    ; Write the uninstaller executable
    WriteUninstaller "$INSTDIR\Uninstall${AppName}.exe"

    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${AppName}" "DisplayName" "${DisplayAppName}"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${AppName}" "DisplayVersion" "${Version}"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${AppName}" "Publisher" "${PublisherName}"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${AppName}" "UninstallString" '"$INSTDIR\Uninstall${AppName}.exe"'

SectionEnd

; Uninstaller section
Section "Uninstall"

    ; Remove all files and directories from the installation directory
    RMDir /r $INSTDIR

    ; Remove installed shortcuts and start menu entries
    Delete "$DESKTOP\${AppName}.lnk"
    Delete "$SMPROGRAMS\${AppName}\${AppName}.lnk"

    ; Remove registry entries for "Add or Remove Programs"
    DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${AppName}"

    ; Remove installation directory (if it's empty)
    RMDir $INSTDIR

SectionEnd
