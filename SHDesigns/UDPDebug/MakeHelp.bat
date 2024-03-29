@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by UDPDEBUG.HPJ. >"hlp\UDPDebug.hm"
echo. >>"hlp\UDPDebug.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\UDPDebug.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\UDPDebug.hm"
echo. >>"hlp\UDPDebug.hm"
echo // Prompts (IDP_*) >>"hlp\UDPDebug.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\UDPDebug.hm"
echo. >>"hlp\UDPDebug.hm"
echo // Resources (IDR_*) >>"hlp\UDPDebug.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\UDPDebug.hm"
echo. >>"hlp\UDPDebug.hm"
echo // Dialogs (IDD_*) >>"hlp\UDPDebug.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\UDPDebug.hm"
echo. >>"hlp\UDPDebug.hm"
echo // Frame Controls (IDW_*) >>"hlp\UDPDebug.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\UDPDebug.hm"
REM -- Make help for Project UDPDEBUG


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\UDPDebug.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\UDPDebug.hlp" goto :Error
if not exist "hlp\UDPDebug.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\UDPDebug.hlp" Debug
if exist Debug\nul copy "hlp\UDPDebug.cnt" Debug
if exist Release\nul copy "hlp\UDPDebug.hlp" Release
if exist Release\nul copy "hlp\UDPDebug.cnt" Release
echo.
goto :done

:Error
echo hlp\UDPDebug.hpj(1) : error: Problem encountered creating help file

:done
echo.
