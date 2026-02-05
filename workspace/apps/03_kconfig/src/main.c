#include <zephyr/random/random.h>


static const int32_t sleep_time_ms = 1000;


int main(void){
    
    uint32_t rnd;
    
    for (;;) {
        rnd = sys_rand32_get();
        
        printk("Random value: %u\r\n", rnd);
        k_msleep(sleep_time_ms);
        
    }
    return 0;
}