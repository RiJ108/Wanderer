
#ifndef OBJIMPORTER_EXPORT_H
#define OBJIMPORTER_EXPORT_H

#ifdef OBJIMPORTER_STATIC_DEFINE
#  define OBJIMPORTER_EXPORT
#  define OBJIMPORTER_NO_EXPORT
#else
#  ifndef OBJIMPORTER_EXPORT
#    ifdef objImporter_EXPORTS
        /* We are building this library */
#      define OBJIMPORTER_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define OBJIMPORTER_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef OBJIMPORTER_NO_EXPORT
#    define OBJIMPORTER_NO_EXPORT 
#  endif
#endif

#ifndef OBJIMPORTER_DEPRECATED
#  define OBJIMPORTER_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef OBJIMPORTER_DEPRECATED_EXPORT
#  define OBJIMPORTER_DEPRECATED_EXPORT OBJIMPORTER_EXPORT OBJIMPORTER_DEPRECATED
#endif

#ifndef OBJIMPORTER_DEPRECATED_NO_EXPORT
#  define OBJIMPORTER_DEPRECATED_NO_EXPORT OBJIMPORTER_NO_EXPORT OBJIMPORTER_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef OBJIMPORTER_NO_DEPRECATED
#    define OBJIMPORTER_NO_DEPRECATED
#  endif
#endif

#endif /* OBJIMPORTER_EXPORT_H */
