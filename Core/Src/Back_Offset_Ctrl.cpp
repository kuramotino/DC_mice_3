/*
 * Back_Offset_Ctrl.cpp
 *
 *  Created on: 2023/06/20
 *      Author: Ryu
 */
#include "Back_Offset_Ctrl.h"

namespace controll
{
	void controll::Back_Offset_Ctrl::updata(Command cm)
	{
		now_cm=cm;
		isStop=(!(now_cm.isCalBackOffset) || now_cm.isStop);
		if(isStop==false)
		{
			Transmit_Back_Offset(Side_Wall_Offset());//後距離の補正量をkasokuにセットする
		}
	}

	float controll::Back_Offset_Ctrl::Side_Wall_Offset()
	{
		if(my_input->g_sensor_now[1]>my_input->LEFT_SLESHOLD)
		{
			//1左壁ありの時
			float dif=CENTER_L-ABS_CENTER_L;
			float adc=(float)(my_input->g_sensor_now[1])+dif;

			//2左壁との距離を計算
			float len=Side_L_ADtoX[0]+Side_L_ADtoX[1]*adc+Side_L_ADtoX[2]*adc*adc+Side_L_ADtoX[3]*adc*adc*adc+Side_L_ADtoX[4]*adc*adc*adc*adc;

			//3真ん中にいるときの左壁との距離を計算
			float center_len=Side_L_ADtoX[0]+Side_L_ADtoX[1]*CENTER_L+Side_L_ADtoX[2]*CENTER_L*CENTER_L+Side_L_ADtoX[3]*CENTER_L*CENTER_L*CENTER_L+Side_L_ADtoX[4]*CENTER_L*CENTER_L*CENTER_L*CENTER_L;

			//4真ん中からのずれ距離を計算
			float dif_len=center_len-len;

			//5補正量を足した値がマイナスなら0にする
			if(dif_len+r_back_offset<0)
			{
				dif_len=-1*r_back_offset;
			}

			//7補正後距離を返す
			return dif_len;
		}
		else if(my_input->g_sensor_now[3]>my_input->RIGHT_SLESHOLD)
		{
			//1右壁ありの時
			float dif=CENTER_R-ABS_CENTER_R;
			float adc=(float)(my_input->g_sensor_now[3])+dif;

			//2右壁との距離を計算
			float len=Side_R_ADtoX[0]+Side_R_ADtoX[1]*adc+Side_R_ADtoX[2]*adc*adc+Side_R_ADtoX[3]*adc*adc*adc+Side_R_ADtoX[4]*adc*adc*adc*adc;

			//3真ん中にいるときの右壁との距離を計算
			float center_len=Side_R_ADtoX[0]+Side_R_ADtoX[1]*CENTER_R+Side_R_ADtoX[2]*CENTER_R*CENTER_R+Side_R_ADtoX[3]*CENTER_R*CENTER_R*CENTER_R+Side_R_ADtoX[4]*CENTER_R*CENTER_R*CENTER_R*CENTER_R;

			//4真ん中からのずれ距離を計算
			float dif_len=center_len-len;

			//5補正量を足した値がマイナスなら0にする
			if(dif_len+l_back_offset<0)
			{
				dif_len=-1*l_back_offset;
			}

			//7補正後距離を返す
			return dif_len;
		}
		return 0;
	}

	void controll::Back_Offset_Ctrl::Transmit_Back_Offset(float bu_back_offset)
	{
		my_kasoku->Receive_Back_Offset(bu_back_offset);
	}
}

