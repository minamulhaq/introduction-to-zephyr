#include <zephyr/random/random.h>

#ifdef CONFIG_SAY_HELLO
#include <say_hello.h>
#endif

static const int32_t sleep_time_ms = 1000;

int main(void) {
    static uint32_t count = 0;
    uint32_t rnd;

    for (;;) {
        rnd = sys_rand32_get();
        double rnd_float = (double)rnd / (UINT32_MAX + 1.0);

        printk("Random value %d: %.3f\r\n", count++, rnd_float);
#ifdef CONFIG_SAY_HELLO
        say_hello();
#endif
        k_msleep(sleep_time_ms);
    }
    return 0;
}