# Qt does not go well with -Weffc++
include(../RibiLibraries/ConsoleApplicationNoWeffcpp.pri)

include(../RibiLibraries/Boost.pri)
include(../RibiLibraries/GeneralConsole.pri)

include(../RibiClasses/CppMusic/CppMusic.pri)
include(../MusicTheory/MusicTheoryConsole.pri)

SOURCES += main.cpp
