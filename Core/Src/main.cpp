/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "spi_com.h"
#include "motor_drive.h"
#include "PL_sensor.h"
#include "intermod.h"
#include "encoder.h"
#include "stdio.h"
#include "Init_Controll_Objs.h"
#include "Act_Pat.h"
#include "math.h"
#include "InitAlgo.h"
//#include "kasoku.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_USART3_UART_Init();
  MX_ADC2_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();
  MX_TIM8_Init();
  MX_TIM2_Init();
  MX_TIM7_Init();
  MX_TIM11_Init();
  MX_TIM3_Init();
  MX_TIM12_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
  uint8_t reg;
  float gyro;
  //gyro_init();
  HAL_TIM_Base_Start_IT(&htim6);
  //HAL_TIM_Base_Start_IT(&htim2);
  //HAL_TIM_PWM_MspInit(&htim2);
  //HAL_TIM_Base_Start_IT(&htim3);
  HAL_TIM_PWM_MspInit(&htim3);
  //HAL_TIM_Base_Start_IT(&htim12);
  HAL_TIM_PWM_MspInit(&htim12);

  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
  __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_1, 0);
  __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, 0);
  HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);
  /*pl_encoder_init();
  int16_t cnt_R=0;
  int16_t cnt_L=0;
  float t=0;
   */
  int mode=0;
  int pre_mode=0;
  int modenum=5;
  float t=0;
  Init_Controll();
  InitAlgo();
  bool isStart[7]={false};
  bool isBattSafe=false;
  float batave=0;
  using namespace controll;
  using namespace application;
  using namespace Algorizm;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  if(!isBattSafe)
	  {
		  for(int i=0;i<500;i++)
		  {
			  float batf;
			  uint16_t bat;
			  //HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);
			  HAL_ADC_Start(&hadc2);
			  HAL_ADC_PollForConversion(&hadc2, 100);
			  bat = HAL_ADC_GetValue(&hadc2);
			  HAL_ADC_Stop(&hadc2);
			  batf = (float) bat / 1024.0 * (100.0 + 50.0) / 50.0/1.1;
			  batave+=batf;
		  }
		  batave/=500;
		  if(batave<7.4)
		  {
			  printf("Warning!! BATT=%f\n\r",batave);
			  continue;
		  }
		  else
		  {
			  isBattSafe=true;
			  printf("BATT=%f\n\r",batave);
		  }
	  }


	  mode=(int)(modenum*fabs(input_obj.enc_v_R_sum)/(32767.0));//modeの決�?
	  if(pre_mode!=mode)
	  {
		  test_sound(1.25,50);
		  pre_mode=mode;
	  }
	  switch(mode)
	  {
	  case 0://0センサ計測モー�?
		  HAL_Delay(100);
		  led_obj.set_all_led(0b00000001);
		  printf("sensorL_1=%d,sensorL_2=%d,sensorF=%d,sensorR_1=%d,sensorR_2=%d\n\r",input_obj.g_sensor_now[0],input_obj.g_sensor_now[1],input_obj.g_sensor_now[2],input_obj.g_sensor_now[3],input_obj.g_sensor_now[4]);
		  break;

	  case 1://1探索モード
		  led_obj.set_all_led(0b00000010);
		  if(isStart[1]==true)
		  {
			  isStart[1]=false;
			  gyro_obj.OffsetStart();
			  HAL_Delay(1200);
			  while(!issue_obj.isStop)
			  {
				  UpDataAlgo();
			  }
			  HAL_Delay(1000);
		  }
		  break;

	  case 2://Logモー�?
		  led_obj.set_all_led(0b00000100);
		  if(isStart[2]==true)
		  {
			  isStart[2]=false;
			  t=0;
			  /*for(int i=0;i<1200;i++)
			  {
				  printf("%f,%f,%f,%f,%f,%f,%f\n\r",t,ksk_obj.now_v_log[i],ksk_obj.now_x_log[i],pwm_obj.now_R_log[i],pwm_obj.now_L_log[i],pid_obj.log_enc[i],pid_obj.log_gyro[i]);
				  //printf("%f,%d,%d,\n\r",t,pl_obj.log_sensor_lr[0][i],pl_obj.log_sensor_lr[1][i]);
				  t+=0.001;
			  }*/
			  map_obj.ShowMap();
			  HAL_Delay(1000);
		  }
		  break;

	  case 3://3左スラロームテスト
		  led_obj.set_all_led(0b00001000);
		  if(isStart[3]==true)
		  {
			  isStart[3]=false;
			  gyro_obj.OffsetStart();
			  HAL_Delay(1200);
			  //App_Set_Command(Stra);
			  App_Set_Command(Stra_ac_180);
			  App_Set_Command(Front_offset);
			  App_Set_Command(Left_sla);
			  //App_Set_Command(Right_sen);
			  App_Set_Command(Left_b_off);
			  App_Set_Command(Stra_de_180);
			  //App_Set_Command(Right_sen);
			  HAL_Delay(1000);
		  }
		  break;

	  case 4://4右スラロームテスト
		  led_obj.set_all_led(0b00010000);

		  if(isStart[4]==true)
		  {
			  isStart[4]=false;
			  gyro_obj.OffsetStart();
			  HAL_Delay(1200);
			  //App_Set_Command(Stra);
			  App_Set_Command(Stra_ac_180);
			  App_Set_Command(Front_offset);
			  App_Set_Command(Right_sla);
			  App_Set_Command(Right_b_off);
			  App_Set_Command(Stra_de_180);
			  //App_Set_Command(Left_sen);
			  HAL_Delay(1000);
		  }
		  break;

	  case 5:
		  led_obj.set_all_led(0b00100000);
		  break;

	  case 6:
		  led_obj.set_all_led(0b01000000);
		  break;

	  }

	  if(input_obj.g_sensor_now[2]>450)
	  {
		  isStart[mode]=true;
	  }
	  else
	  {
		  isStart[mode]=false;
	  }

	  /* USER CODE END WHILE */

	  /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
