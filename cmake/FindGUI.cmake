if(WIN32)
    set(USE_WIN32 ON)
else(WIN32)
    find_package(GTK2)
    if(GTK2_FOUND)
        set(HAVE_GTK2 ON)
        set(USE_GTK2 ON)
        include_directories(${GTK2_INCLUDE_DIRS})
    else(GTK2_FOUND)
        message(NOT FOUND GTK2)
    endif(GTK2_FOUND)
endif(WIN32)