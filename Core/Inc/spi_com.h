/*
 * spi_com.h
 *
 *  Created on: Mar 22, 2023
 *      Author: Ryu
 */

#ifndef INC_SPI_COM_H_
#define INC_SPI_COM_H_
#include "BaseSencing.h"

namespace module
{
	class Gyro : public BaseSencing
	{
		float gyro_x;
		float gyro_y;
		float gyro_z;
		float accel_x;
		float accel_y;
		float accel_z;
		uint8_t who_am_i;
		float gyro_offset=0;
		int offset_count=0;
		//float gyro_a=1.00138889;
		float gyro_a=0.98;
		bool isStartOffset=false;

	public:
		uint8_t read_spi(uint8_t reg);//readのspi通信
		void write_spi(uint8_t reg, uint8_t data);//writeのspi通信
		void gyro_init(void);//gyroを初期化する
		float gyro_get(uint8_t H_reg);//gyroの値を取得する
		float accel_get(uint8_t H_reg);//accelの値を取得する
		void Update_ICM(void);//現在の角速度、加速度を更新する
		void Show_ICM(void);//角速度、加速度を返す
		void sensor_input();//センサー値をInputDataに入力する関数
		void SetGyroOffset();//オフセットを設定する関数
		void OffsetStart();//オフセット取得をスタートさせる関数
	};
}

#endif /* INC_SPI_COM_H_ */
