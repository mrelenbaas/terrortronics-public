# Generated by O3DE install

set_property(TARGET BookProject.ServerLauncher
    APPEND_STRING PROPERTY IMPORTED_LOCATION
        $<$<CONFIG:profile>:${LY_ROOT_FOLDER}/bin/Windows/profile/Default/./BookProject.ServerLauncher.exe>
)
set_property(TARGET BookProject.ServerLauncher
    PROPERTY IMPORTED_LOCATION_PROFILE
        ${LY_ROOT_FOLDER}/bin/Windows/profile/Default/./BookProject.ServerLauncher.exe
)
