@echo off

if not "%GAUDI_NO_STRIP_PATH%" == "" goto :eof

set tmpfile="%TEMP%\StripPath_tmpsetup.bat"

python %GAUDIPOLICYROOT%\scripts\PathStripper.py --shell=bat --output=%tmpfile% -e PATH -e PYTHONPATH -e JOBOPTSEARCHPATH -e HPATH

call %tmpfile%


if exist %tmpfile% del %tmpfile%
set tmpfile=

