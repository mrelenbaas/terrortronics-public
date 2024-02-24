@ECHO OFF

REM License
REM -------
REM                                  Apache License
REM                            Version 2.0, January 2004
REM                         http://www.apache.org/licenses/
REM
REM    TERMS AND CONDITIONS FOR USE, REPRODUCTION, AND DISTRIBUTION
REM
REM    1. Definitions.
REM
REM       "License" shall mean the terms and conditions for use, reproduction,
REM       and distribution as defined by Sections 1 through 9 of this document.
REM
REM       "Licensor" shall mean the copyright owner or entity authorized by
REM       the copyright owner that is granting the License.
REM
REM       "Legal Entity" shall mean the union of the acting entity and all
REM       other entities that control, are controlled by, or are under common
REM       control with that entity. For the purposes of this definition,
REM       "control" means (i) the power, direct or indirect, to cause the
REM       direction or management of such entity, whether by contract or
REM       otherwise, or (ii) ownership of fifty percent (50%) or more of the
REM       outstanding shares, or (iii) beneficial ownership of such entity.
REM
REM       "You" (or "Your") shall mean an individual or Legal Entity
REM       exercising permissions granted by this License.
REM
REM       "Source" form shall mean the preferred form for making modifications,
REM       including but not limited to software source code, documentation
REM       source, and configuration files.
REM
REM       "Object" form shall mean any form resulting from mechanical
REM       transformation or translation of a Source form, including but
REM       not limited to compiled object code, generated documentation,
REM       and conversions to other media types.
REM
REM       "Work" shall mean the work of authorship, whether in Source or
REM       Object form, made available under the License, as indicated by a
REM       copyright notice that is included in or attached to the work
REM       (an example is provided in the Appendix below).
REM
REM       "Derivative Works" shall mean any work, whether in Source or Object
REM       form, that is based on (or derived from) the Work and for which the
REM       editorial revisions, annotations, elaborations, or other modifications
REM       represent, as a whole, an original work of authorship. For the purposes
REM       of this License, Derivative Works shall not include works that remain
REM       separable from, or merely link (or bind by name) to the interfaces of,
REM       the Work and Derivative Works thereof.
REM
REM       "Contribution" shall mean any work of authorship, including
REM       the original version of the Work and any modifications or additions
REM       to that Work or Derivative Works thereof, that is intentionally
REM       submitted to Licensor for inclusion in the Work by the copyright owner
REM       or by an individual or Legal Entity authorized to submit on behalf of
REM       the copyright owner. For the purposes of this definition, "submitted"
REM       means any form of electronic, verbal, or written communication sent
REM       to the Licensor or its representatives, including but not limited to
REM       communication on electronic mailing lists, source code control systems,
REM       and issue tracking systems that are managed by, or on behalf of, the
REM       Licensor for the purpose of discussing and improving the Work, but
REM       excluding communication that is conspicuously marked or otherwise
REM       designated in writing by the copyright owner as "Not a Contribution."
REM 
REM       "Contributor" shall mean Licensor and any individual or Legal Entity
REM       on behalf of whom a Contribution has been received by Licensor and
REM       subsequently incorporated within the Work.
REM
REM    2. Grant of Copyright License. Subject to the terms and conditions of
REM       this License, each Contributor hereby grants to You a perpetual,
REM       worldwide, non-exclusive, no-charge, royalty-free, irrevocable
REM       copyright license to reproduce, prepare Derivative Works of,
REM       publicly display, publicly perform, sublicense, and distribute the
REM       Work and such Derivative Works in Source or Object form.
REM
REM    3. Grant of Patent License. Subject to the terms and conditions of
REM       this License, each Contributor hereby grants to You a perpetual,
REM       worldwide, non-exclusive, no-charge, royalty-free, irrevocable
REM       (except as stated in this section) patent license to make, have made,
REM       use, offer to sell, sell, import, and otherwise transfer the Work,
REM       where such license applies only to those patent claims licensable
REM       by such Contributor that are necessarily infringed by their
REM       Contribution(s) alone or by combination of their Contribution(s)
REM       with the Work to which such Contribution(s) was submitted. If You
REM       institute patent litigation against any entity (including a
REM       cross-claim or counterclaim in a lawsuit) alleging that the Work
REM       or a Contribution incorporated within the Work constitutes direct
REM       or contributory patent infringement, then any patent licenses
REM       granted to You under this License for that Work shall terminate
REM       as of the date such litigation is filed.
REM
REM    4. Redistribution. You may reproduce and distribute copies of the
REM       Work or Derivative Works thereof in any medium, with or without
REM       modifications, and in Source or Object form, provided that You
REM       meet the following conditions:
REM
REM       (a) You must give any other recipients of the Work or
REM           Derivative Works a copy of this License; and
REM
REM       (b) You must cause any modified files to carry prominent notices
REM           stating that You changed the files; and
REM
REM       (c) You must retain, in the Source form of any Derivative Works
REM           that You distribute, all copyright, patent, trademark, and
REM           attribution notices from the Source form of the Work,
REM           excluding those notices that do not pertain to any part of
REM           the Derivative Works; and
REM
REM       (d) If the Work includes a "NOTICE" text file as part of its
REM           distribution, then any Derivative Works that You distribute must
REM           include a readable copy of the attribution notices contained
REM           within such NOTICE file, excluding those notices that do not
REM           pertain to any part of the Derivative Works, in at least one
REM           of the following places: within a NOTICE text file distributed
REM           as part of the Derivative Works; within the Source form or
REM           documentation, if provided along with the Derivative Works; or,
REM           within a display generated by the Derivative Works, if and
REM           wherever such third-party notices normally appear. The contents
REM           of the NOTICE file are for informational purposes only and
REM           do not modify the License. You may add Your own attribution
REM           notices within Derivative Works that You distribute, alongside
REM           or as an addendum to the NOTICE text from the Work, provided
REM           that such additional attribution notices cannot be construed
REM           as modifying the License.
REM 
REM       You may add Your own copyright statement to Your modifications and
REM       may provide additional or different license terms and conditions
REM       for use, reproduction, or distribution of Your modifications, or
REM       for any such Derivative Works as a whole, provided Your use,
REM       reproduction, and distribution of the Work otherwise complies with
REM       the conditions stated in this License.
REM
REM    5. Submission of Contributions. Unless You explicitly state otherwise,
REM       any Contribution intentionally submitted for inclusion in the Work
REM       by You to the Licensor shall be under the terms and conditions of
REM       this License, without any additional terms or conditions.
REM       Notwithstanding the above, nothing herein shall supersede or modify
REM       the terms of any separate license agreement you may have executed
REM       with Licensor regarding such Contributions.
REM
REM    6. Trademarks. This License does not grant permission to use the trade
REM       names, trademarks, service marks, or product names of the Licensor,
REM       except as required for reasonable and customary use in describing the
REM       origin of the Work and reproducing the content of the NOTICE file.
REM
REM    7. Disclaimer of Warranty. Unless required by applicable law or
REM       agreed to in writing, Licensor provides the Work (and each
REM       Contributor provides its Contributions) on an "AS IS" BASIS,
REM       WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
REM       implied, including, without limitation, any warranties or conditions
REM       of TITLE, NON-INFRINGEMENT, MERCHANTABILITY, or FITNESS FOR A
REM       PARTICULAR PURPOSE. You are solely responsible for determining the
REM       appropriateness of using or redistributing the Work and assume any
REM       risks associated with Your exercise of permissions under this License.
REM
REM    8. Limitation of Liability. In no event and under no legal theory,
REM       whether in tort (including negligence), contract, or otherwise,
REM       unless required by applicable law (such as deliberate and grossly
REM       negligent acts) or agreed to in writing, shall any Contributor be
REM       liable to You for damages, including any direct, indirect, special,
REM       incidental, or consequential damages of any character arising as a
REM       result of this License or out of the use or inability to use the
REM       Work (including but not limited to damages for loss of goodwill,
REM       work stoppage, computer failure or malfunction, or any and all
REM       other commercial damages or losses), even if such Contributor
REM       has been advised of the possibility of such damages.
REM
REM    9. Accepting Warranty or Additional Liability. While redistributing
REM       the Work or Derivative Works thereof, You may choose to offer,
REM       and charge a fee for, acceptance of support, warranty, indemnity,
REM       or other liability obligations and/or rights consistent with this
REM       License. However, in accepting such obligations, You may act only
REM       on Your own behalf and on Your sole responsibility, not on behalf
REM       of any other Contributor, and only if You agree to indemnify,
REM       defend, and hold each Contributor harmless for any liability
REM       incurred by, or claims asserted against, such Contributor by reason
REM       of your accepting any such warranty or additional liability.
REM 
REM    END OF TERMS AND CONDITIONS
REM
REM    APPENDIX: How to apply the Apache License to your work.
REM
REM       To apply the Apache License to your work, attach the following
REM       boilerplate notice, with the fields enclosed by brackets "[]"
REM       replaced with your own identifying information. (Don't include
REM       the brackets!)  The text should be enclosed in the appropriate
REM       comment syntax for the file format. We also recommend that a
REM       file or class name and description of purpose be included on the
REM       same "printed page" as the copyright notice for easier
REM       identification within third-party archives.
REM 
REM    Copyright 2023 Bradley Elenbaas
REM 
REM    Licensed under the Apache License, Version 2.0 (the "License");
REM    you may not use this file except in compliance with the License.
REM    You may obtain a copy of the License at
REM 
REM        http://www.apache.org/licenses/LICENSE-2.0
REM 
REM    Unless required by applicable law or agreed to in writing, software
REM    distributed under the License is distributed on an "AS IS" BASIS,
REM    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
REM    See the License for the specific language governing permissions and
REM    limitations under the License.
REM
REM Contact
REM -------
REM Title: Twin Cities Traveling Arcade - BUILD.BAT
REM Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
REM Version: 1.0.0
REM Date: February 24, 2024
REM Copyright 2023 Bradley Elenbaas

REM Description
REM -----------
REM Performs two of the three builds needed for O3DE.

REM Parameters and Error Levels
REM ---------------------------
REM Parameter 0: Path to this script.
REM Parameter 1: Source directory with project.
REM Parameter 2: Destination directory for build.
REM Error Level 0: Success.
REM Error Level 1-255: Failure.

REM Unit Tests
REM ----------
REM Unit Test 0: Run script with no parameters.
REM Unit Test 1: Run script with parameters 1 and 2 defined.

REM Setup function.
REM Define variables, and accept command line parameters.
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

REM Teardown function.
REM Undefine environmental variables.
:TEARDOWN
    SET "source="
    SET "destination="
    IF DEFINED isFailure GOTO FAILURE
GOTO SUCCESS

REM Main function.
REM Run cmake build calls.
:MAIN
    cmake -B "%destination%" -S "%source%"
    cmake --build "%destination%" --config profile
GOTO TEARDOWN

REM Manual function.
REM Displays the manual.
:MANUAL
    ECHO BUILD.BAT Manual:
    ECHO Runs cmake build calls.
    ECHO Parameter #1. Source directory.
    ECHO Parameter #2. Destination directory.
    ECHO /? flag. Displays the manual.
GOTO TEARDOWN

REM Success function.
REM Prints success message, then exits with error level 0.
:SUCCESS
    ECHO SUCCESS: No errors detected.
EXIT /B 0

REM Failure function.
REM Prints failure message, then exits with error level 1.
:FAILURE
    REM IF %ERRORLEVEL% EQU [number] ECHO FAILURE: [message].
    SET "isFailure="
    ECHO FAILURE: Success was not detected.
EXIT /B 1