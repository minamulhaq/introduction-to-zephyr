#include <zephyr/random/random.h>


static const int32_t sleep_time_ms = 1000;


int main(void){
    
    static uint32_t count = 0;
    uint32_t rnd;
    
    for (;;) {
        rnd = sys_rand32_get();
        
        printk("Random value %ld: %u\r\n", count++, rnd);
        k_msleep(sleep_time_ms);
        
    }
    return 0;
}