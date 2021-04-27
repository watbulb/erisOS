#include <stdint.h>

/***********************************************
 * entry.S                                     *
 ***********************************************
 */
extern volatile void
smemset(void *dst, uint8_t val, uint64_t size);
extern volatile void
smemcpy128(void *dst, void *src, uint32_t size);

extern volatile void
setup_el1(void *entrypoint, uint64_t boot_image, uint64_t boot_args);


/***********************************************
 * clearhook.S                                 *
 ***********************************************
 */
#define kClearHookSize 2
extern uint32_t clear_hook_orig_backing[kClearHookSize];
extern uint8_t  clear_hook, clear_hook_end;


/***********************************************
 * jump_to_image.S                             *
 ***********************************************
 */
extern volatile void
jump_to_image(uint64_t image, uint64_t args);

#define kTrampHookSize 5
extern uint32_t tramp_hook[kTrampHookSize];
