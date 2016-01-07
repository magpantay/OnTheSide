@echo off
set batchSaveLocation=%cd%
goto :beginning

:beginning
set /p isDeleted="Are the boot partitions deleted? (Y/N) (most likely N): "
if /i {%isDeleted%}=={Y} (goto :inputs)
if /i {%isDeleted%}=={y} (goto :inputs)
if /i {%isDeleted%}=={N} (goto :no)
if /i {%isDeleted%}=={n} (goto :no)
if /i {%isDeleted%}=={exit} (goto :seeya)
if /i {%isDeleted%}=={bye} (goto :seeya)
goto :incorrectChoice

:inputs
echo Then hopefully you should remember the sizes of your partitions.
set /p SysPartSize="What was the exact size of your EFI/System partition (usually 100 or 260, type only the numbers): "
set /p MSRSize="Type in the exact size of your MSR partition (type only the numbers or type none if you did not have one): "
echo Thanks.
if /i {%MSRSize%}=={none} (goto :NOMSRdiskprt)
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
echo Deleting disk partitions, please wait...
echo >diskpartDel.txt LIST DISK
diskpart /s diskpartDel.txt
set /p diskNumber="Type in disk number (typically 0): "
echo >>diskpartDel.txt Select disk %diskNumber%
echo >>diskpartDel.txt LIST PART
diskpart /s diskpartDel.txt
set /p partitionSys="Type in partition number that has the name System and is about 100 or 260MB large (type exit if you came here by mistake): "
if /i {%partitionSys%}=={exit} (goto :diskprt)
set /p SysPartSize="Type in whether the size of that partition was closer to 100 or 260 (only the numbers): "
echo >diskpartDel2.txt Select disk %diskNumber%
echo >>diskpartDel2.txt sel part %partitionSys%
echo >>diskpartDel2.txt del part override
diskpart /s diskpartDel2.txt
set /p partitionRes="Type in partition number that has the name Reserved and is 128MB large (type only the numbers or type none if there isn't one): "
if /i {%partitionRes%}=={none} (goto :NOMSRdiskprt)
set /p MSRSize="Type in the exact size of that partition: "
echo >diskpartDel3.txt Select disk %diskNumber%
echo >>diskpartDel3.txt sel part %partitionRes%
echo >>diskPartDel3.txt del part override
diskpart /s diskpartDel3.txt
echo Done. Onto the rest of the program.
pause
if /i {%SysPartSize%}=={100} (goto :diskprt)
if /i {%SysPartSize%}=={260} (goto :diskprt)
goto :incorrectChoice

:diskprt
echo Creating partitions, please wait...
echo >diskpart.txt LIST DISK
diskpart /s diskpart.txt
set /p diskNumber="Type in disk number (typically 0): "
echo >>diskpart.txt Select disk %diskNumber%
echo >>diskpart.txt create partition efi size=%SysPartSize%
echo >>diskpart.txt format quick fs=fat32 label="System"
echo >>diskpart.txt assign letter=P
echo >>diskpart.txt create partition msr size=%MSRSize%
echo >>diskpart.txt LIST VOL
diskpart /s diskpart.txt
set /p volumeNumber="Type in the volume number that C is located in (typically 3): "
echo >diskpart2.txt Select vol %volumeNumber%
echo >>diskpart2.txt assign letter=C
echo >>diskpart2.txt exit
diskpart /s diskpart2.txt
pause
goto :osNumChoose

:NOMSRdiskprt
echo Creating partitions, please wait...
echo >diskpart.txt LIST DISK
diskpart /s diskpart.txt
set /p diskNumber="Type in disk number (typically 0): "
echo >>diskpart.txt Select disk %diskNumber%
echo >>diskpart.txt create partition efi size=%SysPartSize%
echo >>diskpart.txt format quick fs=fat32 label="System"
echo >>diskpart.txt assign letter=P
echo >>diskpart.txt LIST VOL
diskpart /s diskpart.txt
set /p volumeNumber="Type in the volume number that C is located in (typically 3): "
echo >diskpart2.txt Select vol %volumeNumber%
echo >>diskpart2.txt assign letter=C
echo >>diskpart2.txt exit
diskpart /s diskpart2.txt
pause
goto :osNumChoose

:osNumChoose
set /p OSnum="Before we continue, is this Windows version 7, 8, 8.1, or 10: "
if /i {%OSnum%}=={7} (goto :7copyEFIfiles)
if /i {%OSnum%}=={8} (goto :8copyEFIfiles)
if /i {%OSnum%}=={8.1} (goto :8copyEFIfiles)
if /i {%OSnum%}=={10} (goto :8copyEFIfiles)
goto :incorrectChoice

:7copyEFIfiles
echo Copying EFI files, please wait...
mkdir P:\EFI\Microsoft\Boot
xcopy /s C:\Windows\Boot\EFI\*.* P:\EFI\Microsoft\Boot
pause
goto :7bcdcreate

:7bcdcreate
echo Creating BCD store, please wait...
P:
cd EFI\Microsoft\Boot
bcdedit /createstore BCD
bcdedit /store BCD /create {bootmgr} /d "Windows Boot Manger"
bcdedit /store BCD /create /d "Windows 7" /application osloader
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

:8copyEFIfiles
echo Copying EFI files and creating BCD store, please wait...
bcdboot C:\Windows
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
if EXIST %batchSaveLocation%\diskpart.txt (del %batchSaveLocation%\diskpart.txt)
if EXIST %batchSaveLocation%\diskpart2.txt (del %batchSaveLocation%\diskpart2.txt)
if EXIST %batchSaveLocation%\diskpartDel.txt (del %batchSaveLocation%\diskpartDel.txt)
if EXIST %batchSaveLocation%\diskpartDel2.txt (del %batchSaveLocation%\diskpartDel2.txt)
if EXIST %batchSaveLocation%\diskpartDel3.txt (del %batchSaveLocation%\diskpartDel3.txt)
echo Goodbye.
exit /b 0

