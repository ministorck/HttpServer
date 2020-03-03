#ifndef STOOL_GLOBAL_H
#define STOOL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(STOOL_LIBRARY)
#  define STOOLSHARED_EXPORT Q_DECL_EXPORT
#else
#  define STOOLSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // STOOL_GLOBAL_H
