#include "../clip.h"

#define CLIP_API __declspec(dllexport)

using namespace clip;

// clip::lock

CLIP_API lock *lock_create() { return new lock(); }
CLIP_API lock *lock_create_hwnd(void *hwnd) { return new lock(hwnd); }
CLIP_API void lock_delete(lock *lock) { delete lock; }

CLIP_API bool lock_locked(const lock *lock) { return lock->locked(); }
CLIP_API bool lock_clear(lock *lock) { return lock->clear(); }

CLIP_API bool lock_is_convertible(const lock *lock, format format) { return lock->is_convertible(format); }
CLIP_API bool lock_set_data(lock *lock, format f, const char *buf, size_t len) { return lock->set_data(f, buf, len); }
CLIP_API bool lock_get_data(const lock *lock, format f, char *buf, size_t len) { return lock->get_data(f, buf, len); }
CLIP_API size_t lock_get_data_length(const lock *lock, format f) { return lock->get_data_length(f); }

CLIP_API bool lock_set_image(lock *lock, const image *image) { return lock->set_image(*image); }
CLIP_API bool lock_get_image(const lock *lock, image *image) { return lock->get_image(*image); }
CLIP_API bool lock_get_image_spec(const lock *lock, image_spec *spec) { return lock->get_image_spec(*spec); }

// formats

CLIP_API format register_format(const char *name) { return clip::register_format(std::string(name)); } // TODO: ?
CLIP_API format empty_format() { return clip::empty_format(); }
CLIP_API format text_format() { return clip::text_format(); }
CLIP_API format image_format() { return clip::image_format(); }
CLIP_API bool has(format f) { return clip::has(f); }
CLIP_API bool clear() { return clip::clear(); }

// error handling

CLIP_API void set_error_handler(error_handler f) { clip::set_error_handler(f); }
CLIP_API error_handler get_error_handler() { return clip::get_error_handler(); }

// text (HLAPI)

CLIP_API bool set_text(const char *value) { return clip::set_text(std::string(value)); } // TODO: ?

CLIP_API bool get_text(char *value) {
    std::string result;

    if (clip::get_text(result)) {
        value = new char[result.size() + 1]; // mind the 'new'
        std::strcpy(value, result.c_str());
        return true;
    }
    else
        return false;
}

// image

CLIP_API image *image_create() { return new image(); }
CLIP_API image *image_create_spec(const image_spec *spec) { return new image(*spec); }
CLIP_API image *image_create_data_spec(const void *data, const image_spec *spec) { return new image(data, *spec); }
CLIP_API image *image_create_image(const image *other_image) { return new image(*other_image); }

CLIP_API char *image_data(const image *image) { return image->data(); }
CLIP_API const image_spec *spec(const image *image) { return &image->spec(); }
CLIP_API bool image_is_valid(const image *image) { return image->is_valid(); }
CLIP_API void image_reset(image *image) { image->reset(); }

// image (HLAPI)

CLIP_API bool set_image(const image *img) { return clip::set_image(*img); }
CLIP_API bool get_image(image *img) { return clip::get_image(*img); }
CLIP_API bool get_image_spec(image_spec *spec) { return clip::get_image_spec(*spec); }

// only for X11

CLIP_API void set_x11_wait_timeout(int msecs) { clip::set_x11_wait_timeout(msecs); }
CLIP_API int get_x11_wait_timeout() { return clip::get_x11_wait_timeout(); }
