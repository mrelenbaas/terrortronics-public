# Generated by O3DE install

set_property(TARGET MyGem
    APPEND_STRING PROPERTY IMPORTED_LOCATION
        $<$<CONFIG:profile>:${LY_ROOT_FOLDER}/bin/Windows/profile/Default/./MyGem.dll>
)
set_property(TARGET MyGem
    PROPERTY IMPORTED_LOCATION_PROFILE
        ${LY_ROOT_FOLDER}/bin/Windows/profile/Default/./MyGem.dll
)
