#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct CurtisCore CurtisCore;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

CurtisCore *curtis_create(float sampleRate, uintptr_t blockSize);
void curtis_destroy(CurtisCore *curtis);

void curtis_segment_min_length(CurtisCore* curtis_core, float ms);
void curtis_repeat(CurtisCore* curtis_core, uintptr_t count);
void curtis_random_range(CurtisCore* curtis_core, uintptr_t range);
void curtis_density(CurtisCore* curtis_core, float density);
void curtis_glisson_enabled(CurtisCore* curtis_core, bool enabled);
void curtis_start_min_speed(CurtisCore* curtis_core, float semitone);
void curtis_start_max_speed(CurtisCore* curtis_core, float semitone);
void curtis_end_min_speed(CurtisCore* curtis_core, float semitone);
void curtis_end_max_speed(CurtisCore* curtis_core, float semitone);
void curtis_start_left(CurtisCore* curtis_core, float position);
void curtis_start_right(CurtisCore* curtis_core, float position);
void curtis_end_left(CurtisCore* curtis_core, float position);
void curtis_end_right(CurtisCore* curtis_core, float position);

void curtis_process(CurtisCore *curtis, float **buffer, uintptr_t block_size);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
