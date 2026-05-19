#include "mpu6050.h"

HAL_StatusTypeDef MPU6050_Init(I2C_HandleTypeDef *hi2c)
{
    uint8_t check, data;

    HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, MPU6050_REG_WHO_AM_I, 1, &check, 1, 100);
    if (check != 0x68)
        return HAL_ERROR;

    data = 0x00;
    return HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, MPU6050_REG_PWR_MGMT, 1, &data, 1, 100);
}

HAL_StatusTypeDef MPU6050_Read(I2C_HandleTypeDef *hi2c, MPU6050_Data *data)
{
    uint8_t buf[14];
    HAL_StatusTypeDef status;

    status = HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, MPU6050_REG_ACCEL, 1, buf, 14, 100);
    if (status != HAL_OK)
        return status;
    // 3축 가속도
    data->ax = (int16_t)(buf[0] << 8 | buf[1]);
    data->ay = (int16_t)(buf[2] << 8 | buf[3]);
    data->az = (int16_t)(buf[4] << 8 | buf[5]);
    // buf[6], buf[7] = 온도 (사용 안 함)

    // 3축 각속도
    data->gx = (int16_t)(buf[8] << 8 | buf[9]);
    data->gy = (int16_t)(buf[10] << 8 | buf[11]);
    data->gz = (int16_t)(buf[12] << 8 | buf[13]);

    return HAL_OK;
}
