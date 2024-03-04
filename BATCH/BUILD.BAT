@REM Copyright 2024 Bradley Elenbaas
@REM
@REM Licensed under the Apache License, Version 2.0 (the "License");
@REM you may not use this file except in compliance with the License.
@REM You may obtain a copy of the License at
@REM 
@REM     http://www.apache.org/licenses/LICENSE-2.0
@REM 
@REM Unless required by applicable law or agreed to in writing, software
@REM distributed under the License is distributed on an "AS IS" BASIS,
@REM WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
@REM See the License for the specific language governing permissions and
@REM limitations under the License.

@REM Contact
@REM -------
@REM Title: Twin Cities Traveling Arcade - BUILD.BAT
@REM Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
@REM Version: 1.0.0
@REM Date: February 24, 2024
@REM Copyright 2023 Bradley Elenbaas

@REM Description
@REM -----------
@REM Performs two of the three builds needed for O3DE.

@REM Parameters and Error Levels
@REM ---------------------------
@REM Parameter 0: Path to this script.
@REM Parameter 1: Source directory with project.
@REM Parameter 2: Destination directory for build.
@REM Error Level 0: Success.
@REM Error Level 1-255: Failure.

@REM Unit Tests
@REM ----------
@REM Unit Test 0: Run script with no parameters.
@REM Unit Test 1: Run script with parameters 1 and 2 defined.

@REM Setup function.
@REM Define variables, and accept command line parameters.
:SETUP
    IF "%~1"=="" (
        SET "source=..\O3DE\BookProject"
    ) ELSE ( 
        SET "source=%~1"
    )
    IF "%~2"=="" (
        SET "destination=..\O3DE\BuildBookProject"
        CD "%destination%"
    ) ELSE ( 
        SET "destination=%~2"
    )
    SET "isFailure="
    IF "%1" == "/?" GOTO MANUAL
GOTO MAIN

@REM Teardown function.
@REM Undefine environmental variables.
:TEARDOWN
    SET "source="
    SET "destination="
    IF DEFINED isFailure GOTO FAILURE
GOTO SUCCESS

@REM Main function.
@REM Run cmake build calls.
:MAIN
    cmake -B "%destination%" -S "%source%"
    cmake --build "%destination%" --config profile
GOTO TEARDOWN

@REM Manual function.
@REM Displays the manual.
:MANUAL
    ECHO BUILD.BAT Manual:
    ECHO Runs cmake build calls.
    ECHO Parameter #1. Source directory.
    ECHO Parameter #2. Destination directory.
GOTO TEARDOWN

@REM Success function.
@REM Prints success message, then exits with error level 0.
:SUCCESS
    ECHO SUCCESS: No errors detected.
EXIT /B 0

@REM Failure function.
@REM Prints failure message, then exits with error level 1.
:FAILURE
    @REM IF %ERRORLEVEL% EQU [number] ECHO FAILURE: [message].
    SET "isFailure="
    ECHO FAILURE: Success was not detected.
EXIT /B 1