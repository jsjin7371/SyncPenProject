#ifndef MPU6050_H
#define MPU6050_H

#include "main.h"

#define MPU6050_ADDR         0xD0  // 0x68 << 1 (AD0 = LOW)
#define MPU6050_REG_WHO_AM_I 0x75
#define MPU6050_REG_PWR_MGMT 0x6B
#define MPU6050_REG_ACCEL    0x3B  // ACCEL_XOUT_H ~ GYRO_ZOUT_L (14 bytes)

typedef struct {
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
} MPU6050_Data;

HAL_StatusTypeDef MPU6050_Init(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef MPU6050_Read(I2C_HandleTypeDef *hi2c, MPU6050_Data *data);

#endif
