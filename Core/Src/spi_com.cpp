/*
 * spi_com.c
 *
 *  Created on: Mar 22, 2023
 *      Author: Ryu
 */
#include <main.h>
#include "spi.h"
#include "usart.h"
#include "spi_com.h"
#include "stdio.h"
#include "BaseSencing.h"

namespace module
{

	uint8_t module::Gyro::read_spi(uint8_t reg)
	{
		uint8_t ret;
		uint8_t bureg=(reg|0x80);
		HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);   // CS = 0
		HAL_SPI_Transmit(&hspi1,&bureg, 1, 100);
		HAL_SPI_Receive(&hspi1,&ret, 1, 100);
		HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);   // CS = 1
		return ret;
	}

	void module::Gyro::write_spi(uint8_t reg, uint8_t data)
	{
		uint8_t bureg=(reg&0x7F);
		HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);   // CS = 0
		HAL_SPI_Transmit(&hspi1,&bureg, 1, 100);
		HAL_SPI_Transmit(&hspi1,&data, 1, 100);
		HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);   // CS = 1
	}

	void module::Gyro::gyro_init(void)
	{
		uint8_t who_am_i=0;
		who_am_i=read_spi(0x75);//who am iをダミーリード
		HAL_Delay(50);
		write_spi(0x6B,0x00);//pwr
		HAL_Delay(50);
		write_spi(0x1A,0x00);//config
		HAL_Delay(50);
		write_spi(0x1B,0x18);//gyro_config
		HAL_Delay(50);
		write_spi(0x1C,0x18);//accel_config
		HAL_Delay(50);
	}

	float module::Gyro::gyro_get(uint8_t H_reg)
	{
		float ret_gyro;
		int16_t data=(int16_t)( (uint16_t)(read_spi(H_reg) << 8 ) | (uint16_t)read_spi(H_reg+1) );
		ret_gyro=(float)(data/16.4f);
		return ret_gyro;
	}

	float module::Gyro::accel_get(uint8_t H_reg)
	{
		float ret_accel;
		int16_t data=(int16_t)( (uint16_t)(read_spi(H_reg) << 8 ) | (uint16_t)read_spi(H_reg+1) );
		ret_accel=(float)(data/2048.0f);
		return ret_accel;
	}

	void module::Gyro::Update_ICM(void)
	{
		accel_x=accel_get(0x3B);
		accel_y=accel_get(0x3D);
		accel_z=accel_get(0x3F);
		gyro_x=gyro_get(0x43);
		gyro_y=gyro_get(0x45);
		gyro_z=gyro_get(0x47);
	}

	void module::Gyro::Show_ICM(void)
	{
		printf("gyro_x=%f, gyro_y=%f, gyro_z=%f\n\r",gyro_x,gyro_y,gyro_z);
		printf("accel_x=%f, accel_y=%f, accel_z=%f\n\r",accel_x,accel_y,accel_z);
	}

	void module::Gyro::sensor_input()//機体の速度を計算してInputDataに入力する
	{
		Update_ICM();
		my_input->omega_gyro=gyro_z;
	}
}

