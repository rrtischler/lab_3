@echo off
pushd ..\
setlocal

:process_arg
if "%1"=="" goto end_process_arg
set name=%1
set value=

:process_arg_value
if NOT "%value%"=="" set value=%value% %2
if "%value%"=="" set value=%2
shift
if "%2"=="!" goto set_arg
if "%2"=="" goto set_arg
goto process_arg_value

:set_arg
set %name%=%value%
shift
shift
goto process_arg
:end_process_arg

echo. > temp_preBuildStep_Release.bat

echo cd webpage >> temp_preBuildStep_Release.bat
echo makewebpage -d.sdram >> temp_preBuildStep_Release.bat
echo cd .. >> temp_preBuildStep_Release.bat

call temp_preBuildStep_Release.bat
del temp_preBuildStep_Release.bat

endlocal
popd
