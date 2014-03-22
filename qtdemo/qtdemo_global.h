#ifndef QTDEMO_GLOBAL_H
#define QTDEMO_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTDEMO_LIBRARY)
#  define QTDEMOSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTDEMOSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QTDEMO_GLOBAL_H
