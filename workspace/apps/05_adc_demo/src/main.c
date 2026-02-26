
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/adc.h>

// Settings
static const int32_t sleep_time_ms = 100;

/* Get device tree configuration */
#define MY_ADC_CH DT_ALIAS(my_adc_channel) // - are converted to _ so in device tree overlay it will find my-adc-channel

static const struct device *adc = DEVICE_DT_GET(DT_ALIAS(my_adc)); // gets full adc node &adc0 from DT

static const struct adc_channel_cfg adc_ch = ADC_CHANNEL_CFG_DT(MY_ADC_CH);

int main(void)
{
    int ret;
    uint16_t buf;
    uint16_t val_mv;
    int32_t vref_mv;

    // Get Vref (mV) from Devicetree property
    // Channel node in  define as zephyr,vref-mv = <3894>; // 1.1V * 3.54 = 3.894V
    // , and - are converted to _
    vref_mv = DT_PROP(MY_ADC_CH, zephyr_vref_mv);

    // Buffer and options for ADC (defined in adc.h)
    // We need to define sampling seq, look in adc.h for this struct
    struct adc_sequence seq = {
        .channels = BIT(adc_ch.channel_id), // you can bitmask multiple channel, adc is capable of sampling multiple channels but we're using only one.
        .buffer = &buf,                     // Output of adc goes to this buffer.
        .buffer_size = sizeof(buf),
        .resolution = DT_PROP(MY_ADC_CH, zephyr_resolution)};

    // Make sure ADC is ready
    if (!device_is_ready(adc))
    {
        printk("ADC is nore ready\r\n");
        return 0;
    }

    // configure the adc channel
    ret = adc_channel_setup(adc, &adc_ch);
    if (ret < 0)
    {
        printk("ADC channel setup failed\r\n");
        return 0;
    }

    while (1)
    {
        // sample ADC

        ret = adc_read(adc, &seq);
        if (ret < 0)
        {
            printk("Could not read adc %d \r\n", ret);
            continue;
        }

        // calculate adc value in mv
        val_mv = buf * vref_mv / (1 << seq.resolution);

        // print ADC value
        printk("Raw: %u, mV: %u\r\n", buf, val_mv);

        // sleep
        k_msleep(sleep_time_ms);
    }

    return 0;
}