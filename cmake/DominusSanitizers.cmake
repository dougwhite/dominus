option(
    DOMINUS_ENABLE_SANITIZERS
    "Enable AddressSanitizer and UndefinedBehaviorSanitizer"
    OFF
)

add_library(dominus_project_sanitizers INTERFACE)

if(DOMINUS_ENABLE_SANITIZERS)
    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        message(FATAL_ERROR
            "Dominus sanitizers currently support GCC and Clang only"
        )
    endif()

    target_compile_options(dominus_project_sanitizers
        INTERFACE
            $<$<COMPILE_LANGUAGE:CXX>:-fsanitize=address,undefined>
            $<$<COMPILE_LANGUAGE:CXX>:-fno-omit-frame-pointer>
            $<$<COMPILE_LANGUAGE:CXX>:-fno-sanitize-recover=all>
    )

    target_link_options(dominus_project_sanitizers
        INTERFACE
            -fsanitize=address,undefined
    )
endif()

function(dominus_enable_sanitizers target)
    target_link_libraries(${target}
        PRIVATE
            dominus_project_sanitizers
    )
endfunction()