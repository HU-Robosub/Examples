#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/devicetree.h>
#include <stdio.h>
#include <math.h>

#define MPU_ADDRESS 0x68 // Device address of the MPU9250

// Function to combine two bytes into a 16-bit value (considering the value as signed)
static inline int16_t combine_bytes(uint8_t high, uint8_t low) {
    return (int16_t)((high << 8) | low);
}

// Function to read multiple bytes from a register
static int read_register_bytes(const struct device *i2c_dev, uint8_t start_reg_addr, uint8_t *data_buffer, uint32_t num_bytes) {
    return i2c_burst_read(i2c_dev, MPU_ADDRESS, start_reg_addr, data_buffer, num_bytes);
}

float get_offset_from_register(const struct device *i2c_dev) {
    uint8_t Buf[14];
    int az;

    if (read_register_bytes(i2c_dev, 0x3B, Buf, 14) == 0) {
        az = combine_bytes(Buf[4], Buf[5]);
        float offset = get_offset(az, 9.81);
        return offset;
    }

    return 0.0; // return a default value if read_register_bytes fails
}

void main(void) {
    const struct device *i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c1));
    if (!device_is_ready(i2c_dev)) {
        printk("I2C device not found or not ready.\n");
        return;
    }
    printk("time_stamp, ax, ay, az, gx, gy, gz\n");

    uint8_t Buf[14];
    int16_t ax, ay, az, gx, gy, gz;
    float offset = get_offset_from_register(i2c_dev);

    while (1) {
        int64_t time_stamp = k_uptime_get();

        if (read_register_bytes(i2c_dev, 0x3B, Buf, 14) == 0) {
            // RAW Accelerometer data
            ax = combine_bytes(Buf[0], Buf[1]);
            ay = combine_bytes(Buf[2], Buf[3]);
            az = combine_bytes(Buf[4], Buf[5]);

            // RAW Gyroscope data
            gx = combine_bytes(Buf[8], Buf[9]);
            gy = combine_bytes(Buf[10], Buf[11]);
            gz = combine_bytes(Buf[12], Buf[13]);

            // printk("%lld, %d, %d, %d, %d, %d, %d\n", time_stamp, ax, ay, az, gx, gy, gz);
            printk("%lld, %lf, %f, %f, %f, %f, %f\n", time_stamp, 
                   (double)calculate_speed_xy(ax, offset), 
                   (double)calculate_speed_xy(ay, offset), 
                   (double)calculate_speed_z(az, offset), 
                   (double)calculate_speed_xy(gx, offset), 
                   (double)calculate_speed_xy(gy, offset), 
                   (double)calculate_speed_z(gz, offset));
        } else {
            printk("Failed to read from I2C device.\n");
        }

        k_sleep(K_MSEC(1));
    }
}