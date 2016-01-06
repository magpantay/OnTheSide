@echo off

goto :beginning

:beginning
set /p isDeleted="Are the partitions deleted? (Y/N): "
if /i {%isDeleted%}=={Y} (goto :yes)
if /i {%isDeleted%}=={y} (goto :yes)
if /i {%isDeleted%}=={N} (goto :no)
if /i {%isDeleted%}=={n} (goto :no)
if /i {%isDeleted%}=={exit} (goto :exit)
if /i {%isDeleted%}=={bye} (goto :exit)
goto :incorrectChoice

:yes
echo Creating partitions, please wait...

diskpart
list disk
set /p diskNumber="Type in disk number (typically 0): "
select disk %diskNumber%
create partition efi size=100
list partition
format quick fs=fat32 label="System"
assign letter=P
create partition msr size=128
list partition
list vol
set /p volumeNumber="Type in the volume number that C is located in (typically 3): "
select vol %volumeNumber%
assign letter=C
exit

echo Copying EFI files, please wait...

mkdir P:\EFI\Microsoft\Boot
xcopy /s C:\Windows\Boot\EFI\*.* P:\EFI\Microsoft\Boot

echo Creating BCD store, please wait...

P:
cd EFI\Microsoft\Boot
bcdedit /createstore BCD
bcdedit /store BCD  /create {bootmgr} /d “Windows Boot Manager”
bcdedit /store BCD /create /d “Windows 10” /application osloader
set /p guidNumber="Input the GUID number just outputted by the previous command (including {}): "
bcdedit /store BCD /set {bootmgr} default guidNumber
bcdedit /store BCD /set {bootmgr} path \EFI\Microsoft\Boot\bootmgfw.efi
bcdedit /store BCD /set {bootmgr} displayorder {default}
bcdedit /store BCD /set {default} device partition=c:
bcdedit /store BCD /set {default} osdevice partition=c:
bcdedit /store BCD /set {default} path \Windows\System32\winload.efi
bcdedit /store BCD /set {default} systemroot \Windows

echo Done.
pause
exit

:no
echo Partition deleting features will be available at a later time. Please delete the partitions first before proceeding.
pause
exit

:incorrectChoice
echo You have typed in an invalid choice.
pause
goto :beginning

:exit
echo Goodbye.
pause
exit
