
#ifndef SHADER_EXPORT_H
#define SHADER_EXPORT_H

#ifdef SHADER_STATIC_DEFINE
#  define SHADER_EXPORT
#  define SHADER_NO_EXPORT
#else
#  ifndef SHADER_EXPORT
#    ifdef shader_EXPORTS
        /* We are building this library */
#      define SHADER_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define SHADER_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef SHADER_NO_EXPORT
#    define SHADER_NO_EXPORT 
#  endif
#endif

#ifndef SHADER_DEPRECATED
#  define SHADER_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef SHADER_DEPRECATED_EXPORT
#  define SHADER_DEPRECATED_EXPORT SHADER_EXPORT SHADER_DEPRECATED
#endif

#ifndef SHADER_DEPRECATED_NO_EXPORT
#  define SHADER_DEPRECATED_NO_EXPORT SHADER_NO_EXPORT SHADER_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef SHADER_NO_DEPRECATED
#    define SHADER_NO_DEPRECATED
#  endif
#endif

#endif /* SHADER_EXPORT_H */
