#ifndef CLIP_EXPORT_INCLUDED
#define CLIP_EXPORT_INCLUDED
#pragma once
#include "../clip.h"

#ifdef clip_export_EXPORTS
#if defined(__clang__) || defined(__GNUC__)
#define CLIP_API  __attribute__ ((dllexport))
#else
#define CLIP_API __declspec(dllexport)
#endif
#else
#if defined(__clang__) || defined(__GNUC__)
#define CLIP_API __attribute__ ((dllimport))
#else
#define CLIP_API __declspec(dllimport)
#endif
#endif

#if defined(__clang__) || defined(__GNUC__)
#define CLIP_CCONV __attribute__ ((stdcall))
#else
#define CLIP_CCONV __stdcall
#endif

using namespace clip;

#ifdef __cplusplus
extern "C" {
#endif

// clip::lock

CLIP_API lock* CLIP_CCONV lock_create();
CLIP_API lock* CLIP_CCONV lock_create_hwnd(void *hwnd);
CLIP_API void CLIP_CCONV lock_delete(lock *lock);

CLIP_API bool CLIP_CCONV lock_locked(const lock *lock);
CLIP_API bool CLIP_CCONV lock_clear(lock *lock);

CLIP_API bool CLIP_CCONV lock_is_convertible(const lock *lock, format format);
CLIP_API bool CLIP_CCONV lock_set_data(lock *lock, format f, const char *buf, size_t len);
CLIP_API bool CLIP_CCONV lock_get_data(const lock *lock, format f, char *buf, size_t len);
CLIP_API size_t CLIP_CCONV lock_get_data_length(const lock *lock, format f);

CLIP_API bool CLIP_CCONV lock_set_image(lock *lock, const image *image);
CLIP_API bool CLIP_CCONV lock_get_image(const lock *lock, image *image);
CLIP_API bool CLIP_CCONV lock_get_image_spec(const lock *lock, image_spec *spec);

// formats

CLIP_API format CLIP_CCONV register_format(const char *name);
CLIP_API format CLIP_CCONV empty_format();
CLIP_API format CLIP_CCONV text_format();
CLIP_API format CLIP_CCONV image_format();
CLIP_API bool CLIP_CCONV has(format f);
CLIP_API bool CLIP_CCONV clear();

// error handling

CLIP_API void CLIP_CCONV set_error_handler(error_handler f);
CLIP_API error_handler CLIP_CCONV get_error_handler();

// text (HLAPI)

CLIP_API bool CLIP_CCONV set_text(const char *value);
CLIP_API bool CLIP_CCONV get_text(char *value);

// image

CLIP_API image* CLIP_CCONV image_create();
CLIP_API image* CLIP_CCONV image_create_spec(const image_spec *spec);
CLIP_API image* CLIP_CCONV image_create_data_spec(const void *data, const image_spec *spec);
CLIP_API image* CLIP_CCONV image_create_image(const image *other_image);

CLIP_API char* CLIP_CCONV image_data(const image *image);
CLIP_API const image_spec* CLIP_CCONV spec(const image *image);
CLIP_API bool CLIP_CCONV image_is_valid(const image *image);
CLIP_API void CLIP_CCONV image_reset(image *image);

// image (HLAPI)

CLIP_API bool CLIP_CCONV set_image(const image *img);
CLIP_API bool CLIP_CCONV get_image(image *img);
CLIP_API bool CLIP_CCONV get_image_spec(image_spec *spec);

// only for X11

CLIP_API void CLIP_CCONV set_x11_wait_timeout(int msecs);
CLIP_API int CLIP_CCONV get_x11_wait_timeout();

#ifdef __cplusplus
} // extern "C"
#endif

#endif // CLIP_EXPORT_INCLUDED
