# Generated by O3DE install

set_property(TARGET BookProject.Private.Object
    APPEND_STRING PROPERTY IMPORTED_LOCATION
        $<$<CONFIG:profile>:${LY_ROOT_FOLDER}/lib/Windows/profile/Default/BookProject.Private.Object.lib>
)
set_property(TARGET BookProject.Private.Object
    PROPERTY IMPORTED_LOCATION_PROFILE
        ${LY_ROOT_FOLDER}/lib/Windows/profile/Default/BookProject.Private.Object.lib
)