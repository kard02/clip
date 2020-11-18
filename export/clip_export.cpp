#include "clip_export.h"

// clip::lock

lock *lock_create() { return new lock(); }
lock *lock_create_hwnd(void *hwnd) { return new lock(hwnd); }
void lock_delete(lock *lock) { delete lock; }

bool lock_locked(const lock *lock) { return lock->locked(); }
bool lock_clear(lock *lock) { return lock->clear(); }

bool lock_is_convertible(const lock *lock, format format) { return lock->is_convertible(format); }
bool lock_set_data(lock *lock, format f, const char *buf, size_t len) { return lock->set_data(f, buf, len); }
bool lock_get_data(const lock *lock, format f, char *buf, size_t len) { return lock->get_data(f, buf, len); }
size_t lock_get_data_length(const lock *lock, format f) { return lock->get_data_length(f); }

bool lock_set_image(lock *lock, const image *image) { return lock->set_image(*image); }
bool lock_get_image(const lock *lock, image *image) { return lock->get_image(*image); }
bool lock_get_image_spec(const lock *lock, image_spec *spec) { return lock->get_image_spec(*spec); }

// formats

format register_format(const char *name) { return clip::register_format(std::string(name)); } // TODO: ?
format empty_format() { return clip::empty_format(); }
format text_format() { return clip::text_format(); }
format image_format() { return clip::image_format(); }
bool has(format f) { return clip::has(f); }
bool clear() { return clip::clear(); }

// error handling

void set_error_handler(error_handler f) { clip::set_error_handler(f); }
error_handler get_error_handler() { return clip::get_error_handler(); }

// text (HLAPI)

bool set_text(const char *value) { return clip::set_text(std::string(value)); } // TODO: ?

bool get_text(char *value) {
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

image *image_create() { return new image(); }
image *image_create_spec(const image_spec *spec) { return new image(*spec); }
image *image_create_data_spec(const void *data, const image_spec *spec) { return new image(data, *spec); }
image *image_create_image(const image *other_image) { return new image(*other_image); }

char *image_data(const image *image) { return image->data(); }
const image_spec *spec(const image *image) { return &image->spec(); }
bool image_is_valid(const image *image) { return image->is_valid(); }
void image_reset(image *image) { image->reset(); }

// image (HLAPI)

bool set_image(const image *img) { return clip::set_image(*img); }
bool get_image(image *img) { return clip::get_image(*img); }
bool get_image_spec(image_spec *spec) { return clip::get_image_spec(*spec); }

// only for X11

void set_x11_wait_timeout(int msecs) { clip::set_x11_wait_timeout(msecs); }
int get_x11_wait_timeout() { return clip::get_x11_wait_timeout(); }
