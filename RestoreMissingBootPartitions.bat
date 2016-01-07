@echo off

goto :beginning

:beginning
set /p isDeleted="Are the partitions deleted? (Y/N): "
if /i {%isDeleted%}=={Y} (goto :yes)
if /i {%isDeleted%}=={y} (goto :yes)
if /i {%isDeleted%}=={N} (goto :no)
if /i {%isDeleted%}=={n} (goto :no)
if /i {%isDeleted%}=={exit} (goto :seeya)
if /i {%isDeleted%}=={bye} (goto :seeya)
goto :incorrectChoice

:yes
echo Creating partitions, please wait...
goto :diskprt

:no
set /p needsToBeDeleted="Do the partitions need to be deleted? (Y/N): "
if /i {%needsToBeDeleted%}=={Y} (goto :needsToBeDeleted)
if /i {%needsToBeDeleted%}=={y} (goto :needsToBeDeleted)
if /i {%needsToBeDeleted%}=={N} (goto :logicCheck)
if /i {%needsToBeDeleted%}=={n} (goto :logicCheck)
if /i {%needsToBeDeleted%}=={exit} (goto :seeya)
if /i {%needsToBeDeleted%}=={bye} (goto :seeya)
goto :incorrectChoice

:needsToBeDeleted
echo >diskpartDel.txt LIST DISK
diskpart /s diskpartDel.txt
set /p diskNumber="Type in disk number (typically 0): "
echo >>diskpartDel.txt Select disk %diskNumber%
echo >>diskpartDel.txt LIST PART
diskpart /s diskpartDel.txt
set /p partitionSys="Type in partition number that has the name System and is usually approx. 100-250MB large: "
if /i {%partitionSys%}=={exit} (goto :diskprt)
echo >diskpartDel2.txt sel part %partitionSys%
echo >>diskpartDel2.txt del part override
diskpart /s diskpartDel2.txt
set /p partitionRes="Type in partition number that has the name Reserved and is usually approx. 128MB large: "
if /i {%partitionRes%}=={exit} (goto :diskprt)
echo >diskpartDel3.txt sel part %partitionRes%
echo >>diskPartDel3.txt del part override
diskpart /s diskpartDel3.txt
goto :diskprt


:diskprt
echo >diskpart.txt LIST DISK
diskpart /s diskpart.txt
set /p diskNumber="Type in disk number (typically 0): "
echo >>diskpart.txt Select disk %diskNumber%
echo >>diskpart.txt create partition efi size=100
echo >>diskpart.txt format quick fs=fat32 label="System"
echo >>diskpart.txt assign letter=P
echo >>diskpart.txt create partition msr size=128
echo >>diskpart.txt LIST VOL
diskpart /s diskpart.txt
set /p volumeNumber="Type in the volume number that C is located in (typically 3): "
echo >diskpart2.txt Select vol %volumeNumber%
echo >>diskpart2.txt assign letter=C
echo >>diskpart2.txt exit
diskpart /s diskpart2.txt
pause
goto :copyEFIfiles

:copyEFIfiles
echo Copying EFI files, please wait...
mkdir P:\EFI\Microsoft\Boot
xcopy /s C:\Windows\Boot\EFI\*.* P:\EFI\Microsoft\Boot
pause
goto :bcdcreate

:bcdcreate
echo Creating BCD store, please wait...
P:
cd EFI\Microsoft\Boot
bcdedit /createstore BCD
bcdedit /store BCD /create {bootmgr} /d "Windows Boot Manger"
bcdedit /store BCD /create /d "Windows 10" /application osloader
set /p guidNumber="Input the GUID number just outputted by the previous command (including {}): "
bcdedit /store BCD /set {bootmgr} default %guidNumber%
bcdedit /store BCD /set {bootmgr} path \EFI\Microsoft\Boot\bootmgfw.efi
bcdedit /store BCD /set {bootmgr} displayorder {default}
bcdedit /store BCD /set {default} device partition=c:
bcdedit /store BCD /set {default} osdevice partition=c:
bcdedit /store BCD /set {default} path \Windows\System32\winload.efi
bcdedit /store BCD /set {default} systemroot \Windows
echo Done.
goto :seeya

:incorrectChoice
echo You have typed in an invalid choice.
set /p wantToRestart="Would you like to start again? (Y/N): "
if /i {%wantToRestart%}=={Y} (goto :beginning)
if /i {%wantToRestart%}=={y} (goto :beginning)
if /i {%wantToRestart%}=={N} (goto :seeya)
if /i {%wantToRestart%}=={n} (goto :seeya)
echo I will take that as a no...
goto :seeya

:logicCheck
echo Why are you even here then? It seems like you don't need this program.
goto :seeya

:seeya
if EXIST diskpart.txt (del diskpart.txt)
if EXIST diskpart2.txt (del diskpart2.txt)
if EXIST diskpartDel.txt (del diskpartDel.txt)
if EXIST dispartDel2.txt (del diskpartDel2.txt)
if EXIST diskpartDel3.txt (del diskpartDel3.txt)
echo Goodbye.
exit /b 0

