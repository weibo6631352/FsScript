#pragma once

#include <QtCore/qglobal.h>

#ifndef QT_STATIC
# if defined(FSSCRIPT_LIB)
#  define FSSCRIPT_EXPORT Q_DECL_EXPORT
# else
#  define FSSCRIPT_EXPORT Q_DECL_IMPORT
# endif
#else
# define FSSCRIPT_EXPORT
#endif



#define GameWindowTitle "Fs"
#define loginWindowTitle "fojoy"
#define DMReg "weibo6631352360bacafd8993f750d5371df41162a4d"
#define DMExtracode "2KmFF"
