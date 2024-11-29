/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdio.h>

#define DS1307_ADDRESS 0x68 << 1 // This adderess for rtc operation
char timeData[15];
char dateData[15];

#define power pos
uint16_t pos;
uint16_t power;
uint8_t sw1_count = 1;
uint8_t sw2_count = 0;
uint8_t sw3_count = 0;
uint8_t sw4_count = 0;
uint8_t sw5_count = 0;
uint8_t sw6_count = 0;
uint8_t sw7_count = 0;

char msg[20];
uint16_t read_value=90;
float batt_persen;
uint16_t i = 0;

/********************--------DC VOLTAGE SENSE DEECLARATION START------------***************/
float dcvout = 0.0;
float dcvin = 0.0;
float R1 = 14000;
float R2 = 4600;
int dcvalue = 0;
/********************--------DC VOLTAGE SENSE DEECLARATION END------------***************/
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
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

RTC_HandleTypeDef hrtc;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
// enum batt_persen {}



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_RTC_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/********************** simple ocde start******************/

enum power
{
  standby,
  scrn_status,
  qc,
  pd,
  dc_9v,
  dc_12v,
  AC
};

void standby_data()
{

  if (sw1_count == 1)
  {
    // lcd_clear();
    // default_lcd_print_page1();
    HAL_GPIO_WritePin(on_off_led1_GPIO_Port, on_off_led1_Pin, GPIO_PIN_SET);
    //	  HAL_Delay(300);
    HAL_GPIO_WritePin(sreen_status_led2_GPIO_Port, sreen_status_led2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(qc_led3_GPIO_Port, qc_led3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(pd_led4_GPIO_Port, pd_led4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(nine_led5_GPIO_Port, nine_led5_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(led6_GPIO_Port, led6_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(sreen_status_led2_GPIO_Port, sreen_status_led2_Pin, GPIO_PIN_RESET);
    power = 0;
  }
  else if (sw1_count == 0)
  {
    // lcd_clear();
    power = 0;
  }
}
// uint16_t batt_per = 0;
void screen_status_data()
{
  if (sw2_count == 1)
  {

    HAL_GPIO_WritePin(sreen_status_led2_GPIO_Port, sreen_status_led2_Pin, GPIO_PIN_SET);

    lcd_puts(0, 7, (int8_t *)timeData);
    lcd_puts(1, 7, (int8_t *)dateData);
    power = 1;
    // lcd_puts(0, 7, (int8_t *)batt_per);
  }
  else if (sw2_count == 0)
  {
    // HAL_GPIO_WritePin(sreen_status_led2_GPIO_Port, sreen_status_led2_Pin, GPIO_PIN_RESET);
    lcd_puts(0, 7, (int8_t *)timeData);
    lcd_puts(1, 7, (int8_t *)dateData);
    power = 1;
  }
}

void Qc_data()
{
  if (sw3_count == 1)
  {
    HAL_GPIO_WritePin(qc_led3_GPIO_Port, qc_led3_Pin, GPIO_PIN_SET);
    lcd_puts(0, 17, (int8_t *)"ON");
    // lcd_puts(0, 19, (int8_t *)" ");
    power = 2;
    // HAL_Delay(300);
  }
  else if (sw3_count == 0)
  {
    HAL_GPIO_WritePin(qc_led3_GPIO_Port, qc_led3_Pin, GPIO_PIN_RESET);
    lcd_puts(0, 17, (int8_t *)"OFF");
    //    lcd_puts(0, 16, (int8_t *)">");

    power = 2;
    // HAL_Delay(300);
  }
}
void pd_data()
{
  if (sw4_count == 1)
  {
    HAL_GPIO_WritePin(pd_led4_GPIO_Port, pd_led4_Pin, GPIO_PIN_SET);
    lcd_puts(1, 17, (int8_t *)"ON");

    power = 3;
    // HAL_Delay(300);
  }
  else if (sw4_count == 0)
  {
    HAL_GPIO_WritePin(pd_led4_GPIO_Port, pd_led4_Pin, GPIO_PIN_RESET);
    lcd_puts(1, 17, (int8_t *)"OFF");

    power = 3;
    // HAL_Delay(300);
  }
}
void dc9v_data()
{
  if (sw5_count == 1)
  {
    HAL_GPIO_WritePin(nine_led5_GPIO_Port, nine_led5_Pin, GPIO_PIN_SET);
    lcd_puts(0, 9, (int8_t *)"ON");
    //    lcd_puts(0, 8, (int8_t *)">");
    // nine_led5_GPIO_Port
    power = 4;
    // HAL_Delay(300);
  }
  else if (sw5_count == 0)
  {
    HAL_GPIO_WritePin(nine_led5_GPIO_Port, nine_led5_Pin, GPIO_PIN_RESET);
    lcd_puts(0, 8, (int8_t *)"OFF");
    //    lcd_puts(0, 8, (int8_t *)">");

    power = 4;
    // HAL_Delay(300);
  }
}
void dc12v_data()
{
  if (sw6_count == 1)
  {
    HAL_GPIO_WritePin(led6_GPIO_Port, led6_Pin, GPIO_PIN_SET);
    lcd_puts(1, 9, (int8_t *)"ON");
    //    lcd_puts(1, 8, (int8_t *)">");
    power = 5;
    // HAL_Delay(300);
  }
  else if (sw6_count == 0)
  {
    HAL_GPIO_WritePin(led6_GPIO_Port, led6_Pin, GPIO_PIN_RESET);
    lcd_puts(1, 8, (int8_t *)"OFF");
    //    lcd_puts(1, 8, (int8_t *)">");
    power = 5;
    // HAL_Delay(300);
  }
}
void AC_data()
{
  if (sw7_count == 1)
  {
    //	  HAL_GPIO_WritePin(AC_led7_GPIO_Port, AC_led7_Pin, GPIO_PIN_RESET);
    lcd_puts(2, 9, (int8_t *)"ON");
    //    lcd_puts(1, 8, (int8_t *)">");
    power = 5;
    // HAL_Delay(300);
  }
  else if (sw7_count == 0)
  {
    //	  HAL_GPIO_WritePin(AC_led7_GPIO_Port, AC_led7_Pin, GPIO_PIN_SET);
    lcd_puts(2, 8, (int8_t *)"OFF");
    //    lcd_puts(1, 8, (int8_t *)">");
    power = 6;
    // HAL_Delay(300);
  }
}

void initail_condition_off()
{
  HAL_GPIO_WritePin(on_off_led1_GPIO_Port, on_off_led1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(sreen_status_led2_GPIO_Port, sreen_status_led2_Pin, GPIO_PIN_RESET);
}

void uart1_test_serial_data()
{
//  HAL_ADC_Start(&hadc1);
//  HAL_ADC_PollForConversion(&hadc1, 300);
//  read_value = HAL_ADC_GetValue(&hadc1);
  //		  		  sprintf(msg, "read =  %hu\r\n", read_value);
  //		  		  HAL_Delay(500);
  //   HAL_UART_Transmit(&huart1, (uint16_t *)msg, strlen(msg), HAL_MAX_DELAY);
  //
  //		  if(read_value < 1900)
  //		  {
  //			  read_value =0;
  //		  }
  //		float  hh =read_value*(3.3 /4096);
  //	//	    i++;
  //		batt_persen =hh *5.001;
  //		  		  sprintf(msg, " DC volt =  %.2f\r\n", hh );
  //		  		HAL_UART_Transmit(&huart1, (uint8_t *)msg, strlen(msg), 300);
  //		  sprintf(buffer, "%02d", data_reg.intensity);
  //	     			  lcd_puts(0, 0, (int8_t *)msg);
  // HAL_Delay(500);
}

/********************** simple code end ******************/

/***************---RTC START CODE---****************/

// Convert normal decimal numbers to binary coded decimal

uint8_t decToBcd(int val) // change by rahul  start
{
  return (uint8_t)((val / 10 * 16) + (val % 10)); // change by rahul  start
}

// Convert binary coded decimal to normal decimal numbers
int bcdToDec(uint8_t val) // change by rahul  start
{
  return (int)((val / 16 * 10) + (val % 16));
}

typedef struct
{
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hour;
  uint8_t dayofweek;
  uint8_t dayofmonth;
  uint8_t month;
  uint8_t year;
} TIME;

TIME time;

// char timeData[15];
// char dateData[15];

void set_time(uint8_t hr, uint8_t min, uint8_t sec)
{
  RTC_TimeTypeDef sTime = {0};

  sTime.Hours = hr;
  sTime.Minutes = min;
  sTime.Seconds = sec;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
}

void set_date(uint8_t year, uint8_t month, uint8_t date, uint8_t day) // monday = 1   // change by rahul
{

  RTC_DateTypeDef sDate = {0};
  sDate.WeekDay = day;
  sDate.Month = month;
  sDate.Date = date;
  sDate.Year = year;
  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x2345); // backup register
}

void get_time_date(char *time, char *date) // change by rahul
{
  RTC_DateTypeDef gDate;
  RTC_TimeTypeDef gTime;

  /* Get the RTC current Time */
  HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
  /* Get the RTC current Date */
  HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);

  /* Display time Format: hh:mm:ss */
  sprintf((char *)time, "%02d:%02d:%02d", gTime.Hours, gTime.Minutes, gTime.Seconds);

  /* Display date Format: dd-mm-yyyy */
  sprintf((char *)date, "%02d-%02d-%2d", gDate.Date, gDate.Month, 2000 + gDate.Year);
}

/**
 * @brief  Write an amount of data in blocking mode to a specific memory address
 * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
 *                the configuration information for the specified I2C.
 * @param  DevAddress Target device address: The device 7 bits address value
 *         in datasheet must be shifted to the left before calling the interface
 * @param  MemAddress Internal memory address
 * @param  MemAddSize Size of internal memory address
 * @param  pData Pointer to data buffer
 * @param  Size Amount of data to be sent
 * @param  Timeout Timeout duration
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c1, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);

/***************---RTC END CODE---****************/


/*********************************------PERSENTAGE CODE START---------*********************/
void battery_persentage()
{
//    HAL_ADC_Start(&hadc1);
//    HAL_ADC_PollForConversion(&hadc1, 300);
//    read_value = HAL_ADC_GetValue(&hadc1);
//    sprintf(msg, "read =  %hu\r\n", read_value);
//  //		  		  HAL_Delay(500);
//     HAL_UART_Transmit(&huart1, (uint16_t *)msg, strlen(msg), HAL_MAX_DELAY);


	    HAL_ADC_Start(&hadc1);
	    HAL_ADC_PollForConversion(&hadc1, 300);
	    dcvalue = HAL_ADC_GetValue(&hadc1);
	    dcvout = (dcvalue * 5.0)  / 4096;
	    dcvin = dcvout / (R2 / (R1 + R2));
	    sprintf(msg, "Batt % =  %3.2f\r\n", dcvin);
	    HAL_UART_Transmit(&huart1, (uint16_t *)msg, strlen(msg), HAL_MAX_DELAY);
	    if ( dcvin > 12.50)
	    {
	    	lcd_puts(2, 9, (int8_t *)" ");
	    	lcd_puts(2, 6, (int8_t *)"100%");
	    	sprintf(msg, "100% \r\n");
//	        Serial.println("batt = 00%");
	      //   digitalWrite(a, HIGH);
	      //   Serial.println("100%");
	      }else if(dcvin <= 12.5 && dcvin > 12.42)
	      {
	    	  lcd_puts(2, 9, (int8_t *)" ");
	    	  lcd_puts(2, 6, (int8_t *)"90%");
	    	  sprintf(msg, "90% \r\n");
//	         Serial.println("batt = 10%");
	      //   digitalWrite(a, LOW);
	      }else if(dcvin <= 12.42 && dcvin > 12.32)
	      {
	    	  lcd_puts(2, 9, (int8_t *)" ");
	    	  lcd_puts(2, 6, (int8_t *)"80%");
	    	  sprintf(msg, "80% \r\n");
//	         Serial.println("batt = 20%");
	      //   digitalWrite(a, LOW);
	      }else if(dcvin <= 12.32 && dcvin > 12.20)
	      {
	    	  lcd_puts(2, 9, (int8_t *)" ");
	    	  lcd_puts(2, 6, (int8_t *)"70%");
	    	  sprintf(msg, "70% \r\n");
//	         Serial.println("batt = 30%");
	      //   digitalWrite(a, LOW);
	      }else if(dcvin <= 12.20 && dcvin > 12.06)
	      {
	    	  lcd_puts(2, 9, (int8_t *)" ");
	    	  lcd_puts(2, 6, (int8_t *)"60%");
	    	  sprintf(msg, "60% \r\n");
//	         Serial.println("batt = 40%");
	      //   digitalWrite(a, LOW);
	      }else if(dcvin <= 12.06 && dcvin > 11.9)
	      {
	    	  lcd_puts(2, 9, (int8_t *)" ");
	    	  lcd_puts(2, 6, (int8_t *)"50%");
	    	  sprintf(msg, "50% \r\n");
//	         Serial.println("batt = 50%");
	      //   digitalWrite(a, LOW);
	      }else if(dcvin <= 11.9 && dcvin > 11.75)
	      {
	    	  lcd_puts(2, 9, (int8_t *)" ");
	    	  lcd_puts(2, 6, (int8_t *)"40%");
	    	  sprintf(msg, "40% \r\n");
//	         Serial.println("batt = 60%");
	      //   digitalWrite(a, LOW);
	      }else if(dcvin <= 11.75 && dcvin > 11.58)
	      {
	    	  lcd_puts(2, 9, (int8_t *)" ");
	    	  lcd_puts(2, 6, (int8_t *)"30%");
	    	  sprintf(msg, "30% \r\n");
//	         Serial.println("batt = 70%");
	      //   digitalWrite(a, LOW);
	      }else if(dcvin <= 11.58 && dcvin > 11.31)
	      {
	    	  lcd_puts(2, 9, (int8_t *)" ");
	    	  lcd_puts(2, 6, (int8_t *)"20%");
	    	  sprintf(msg, "20% \r\n");
//	         Serial.println("batt = 80%");
	      //   digitalWri,te(a, LOW);
	      }else if(dcvin <= 11.31 && dcvin > 10.75)
	      {
	    	  lcd_puts(2, 9, (int8_t *)" ");
	    	  lcd_puts(2, 6, (int8_t *)"10%");
	    	  sprintf(msg, "10% \r\n");
//	         Serial.println("batt = 90%");
	      //   digitalWrite(a, LOW);
	      }else if(dcvin <= 10.75 )
	      {
	    	  lcd_puts(2, 9, (int8_t *)" ");
	    	  lcd_puts(2, 6, (int8_t *)"00%");
	    	  sprintf(msg, "00% \r\n");
//	         Serial.println("batt = 100%");
	      //   digitalWrite(a, LOW);
	      }
	    HAL_UART_Transmit(&huart1, (uint16_t *)msg, strlen(msg), HAL_MAX_DELAY);

//     dcvalue = analogRead(A1);
//     dcvout = (dcvalue * 5.0)  / 1024;
//     // vin = vout / (R2 / (R1 + R2));
//      dcvin = dcvout / (R2 / (R1 + R2));
//     Serial.println("Input Voltage = ");
//     Serial.println(vin);
  //
  //		  if(read_value < 1900)
  //		  {
  //			  read_value =0;
  //		  }
  //		float  hh =read_value*(3.3 /4096);
  //	//	    i++;
  //		batt_persen =hh *5.001;
  //		  		  sprintf(msg, " DC volt =  %.2f\r\n", hh );
  //		  		HAL_UART_Transmit(&huart1, (uint8_t *)msg, strlen(msg), 300);
  //		  sprintf(buffer, "%02d", data_reg.intensity);
  //	     			  lcd_puts(0, 0, (int8_t *)msg);
   HAL_Delay(1000);

}
/*********************************------PERSENTAGE CODE END---------*********************/



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
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_RTC_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  lcd_init();
  /***************---RTC START CODE---****************/
  if (HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1) != 0x2345)
  {
    set_time(17, 30, 2);
    set_date(24, 11, 21, 7);
  }
  /***************---RTC END CODE---****************/

  //   lcd_puts(0, 0, (int8_t *)"hello  ");
  //  HAL_ADC_Start(&hadc1);
  //	  HAL_ADC_PollForConversion(&hadc1,20);
  //	uint16_t  read_value = HAL_ADC_GetValue(&hadc1);
  //	  sprintf(msg, "the value of =  %hu\r\n", read_value );
  //  HAL_UART_Transmit(&huart1, (const uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
  //  lcd_put_cur(0,0);
  //  lcd_send_string ("hello world");
  //&huart1
  //  HAL_UART_Transmit(&huart1, test, sizeof(test), 1000);
  //  HAL_UART_Transmit(&huart1, nl, sizeof(nl), 1000);
  //  HAL_UART_Transmit(&huart1, test1, sizeof(test1), 1000);
  //  HAL_UART_Transmit(&huart1, nl1, sizeof(nl1), 25);
  //  HAL_UART_Transmit(&huart2, test, sizeof(test), 1000);
  //  HAL_UART_Transmit(&huart1, nl, sizeof(nl), 1000);
  //  HAL_UART_Transmit(&huart1, test1, sizeof(test1), 1000);
  //  HAL_UART_Transmit(&huart1, nl1, sizeof(nl1), 25);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    /***************---RTC START CODE---****************/

    get_time_date(timeData, dateData);
//    battery_persentage();
    //	  sprintf(msg, "the value of =  %hu\r\n", read_value );
    // lcd_puts(0, 6, (int8_t *)timeData);
    // lcd_puts(1, 6, (int8_t *)dateData);
    //    HAL_UART_Transmit(&huart1, (const uint8_t *)timeData, strlen(timeData), HAL_MAX_DELAY);
    //    HAL_UART_Transmit(&huart1, (const uint8_t *)"\r\n", 2, HAL_MAX_DELAY);
    //    HAL_UART_Transmit(&huart1, (const uint8_t *)dateData, strlen(dateData), HAL_MAX_DELAY);
    //    HAL_UART_Transmit(&huart1, (const uint8_t *)"\r\n", 2, HAL_MAX_DELAY);
    //    HAL_Delay(1000);
    /***************---RTC END CODE---****************/

    uart1_test_serial_data();
    initail_condition_off();
    /***********************************Prg start*************************************/
    if (HAL_GPIO_ReadPin(sw1_on_off_GPIO_Port, sw1_on_off_Pin) == 1) // This is pin connected to pc7
    {
      lcd_clear();
      sw1_count++;
      if (sw1_count == 2)
      {
        sw1_count = 0;
        power = 0;
      }
      power = 0;
      // HAL_Delay(300);
    }
    else if (HAL_GPIO_ReadPin(sw2_screen_status_GPIO_Port, sw2_screen_status_Pin) == 1) // This is pin connected to pc8
    {
      lcd_clear();

      sw2_count++;
      if (sw2_count == 2)
      {
        sw2_count = 0;
        power = 1;
      }
      power = 1;
      // HAL_Delay(300);
    }
    else if (HAL_GPIO_ReadPin(sw3_qc_GPIO_Port, sw3_qc_Pin) == 1) // This is pin connected to pc9
    {
      lcd_clear();
      sw3_count++;
      if (sw3_count == 2)
      {
        sw3_count = 0;
        power = 2;
      }
      power = 2;
      // HAL_Delay(300);
    }
    else if (HAL_GPIO_ReadPin(sw4_pd_GPIO_Port, sw4_pd_Pin) == 1) // This is pin connected to PA8
    {
      lcd_clear();
      sw4_count++;
      if (sw4_count == 2)
      {
        sw4_count = 0;
        power = 3;
      }
      power = 3;
      // HAL_Delay(300);
    }
    else if (HAL_GPIO_ReadPin(sw5_9v_GPIO_Port, sw5_9v_Pin) == 1) // This is pin connected to PA9
    {
      lcd_clear();
      sw5_count++;
      if (sw5_count == 2)
      {
        sw5_count = 0;
        power = 4;
      }
      power = 4;
      // HAL_Delay(300);
    }
    else if (HAL_GPIO_ReadPin(sw6_12v_GPIO_Port, sw6_12v_Pin) == 1) // This is pin connected to PA10
    {
      lcd_clear();
      sw6_count++;
      if (sw6_count == 2)
      {
        sw6_count = 0;
        power = 5;
      }
      power = 5;
      //       HAL_Delay(300);
    }
    //      else if (HAL_GPIO_ReadPin(sw7_AC_GPIO_Port, sw7_AC_Pin) == 1) // This is pin connected to PA10
    //    {
    //      lcd_clear();
    //      sw7_count++;
    //      if (sw6_count == 2)
    //      {
    //        sw7_count = 0;
    //        power = 6;
    //      }
    //      power = 6;
    // HAL_Delay(300);
    //    }

    switch (pos)
    {
    case standby:
      /* code */
    	 battery_persentage();
      standby_data();
      get_time_date(timeData, dateData);
      HAL_GPIO_WritePin(on_off_led1_GPIO_Port, on_off_led1_Pin, GPIO_PIN_SET);
      // lcd_clear();
      default_lcd_print_page1();
      // HAL_Delay(100);

      break;
    case scrn_status:
      /* code */

      HAL_GPIO_WritePin(sreen_status_led2_GPIO_Port, sreen_status_led2_Pin, GPIO_PIN_SET);

      default_lcd_print_page2();
      screen_status_data();
      break;
    case qc:
      /* code */
      lcd_puts(0, 11, (int8_t *)">");
      lcd_puts(1, 11, (int8_t *)" ");
      default_lcd_print_page3();
      Qc_data();
      pd_data();
      dc9v_data();
      dc12v_data();
      AC_data();
      //    lcd_puts(1, 9, (int8_t *)"OFF");

      break;
    case pd:
      /* code */
      lcd_puts(0, 0, (int8_t *)" ");
      lcd_puts(1, 0, (int8_t *)" ");
      lcd_puts(2, 0, (int8_t *)" ");
      lcd_puts(0, 11, (int8_t *)" ");
      lcd_puts(1, 11, (int8_t *)">");
      default_lcd_print_page3();
      pd_data();
      Qc_data();
      dc9v_data();
      dc12v_data();
      AC_data();

      break;
    case dc_9v:
      /* code */
      lcd_puts(0, 0, (int8_t *)">");
      lcd_puts(1, 0, (int8_t *)" ");
      lcd_puts(2, 0, (int8_t *)" ");
      lcd_puts(0, 11, (int8_t *)" ");
      lcd_puts(1, 11, (int8_t *)" ");
      default_lcd_print_page3();
      dc9v_data();
      dc12v_data();
      pd_data();
      Qc_data();
      AC_data();
      break;
    case dc_12v:
      lcd_puts(0, 0, (int8_t *)" ");
      lcd_puts(1, 0, (int8_t *)">");
      lcd_puts(2, 0, (int8_t *)" ");
      lcd_puts(0, 11, (int8_t *)" ");
      lcd_puts(1, 11, (int8_t *)" ");
      default_lcd_print_page3();
      dc9v_data();
      dc12v_data();
      pd_data();
      Qc_data();
      AC_data();
    case AC:
      //    	lcd_puts(0, 0, (int8_t *)" ");
      //    	    	lcd_puts(1, 0, (int8_t *)" ");
      //    	    	lcd_puts(2, 0, (int8_t *)">");
      //    	    	lcd_puts(0, 11, (int8_t *)" ");
      //    	    	lcd_puts(1, 11, (int8_t *)" ");
      default_lcd_print_page3();
      dc9v_data();
      dc12v_data();
      pd_data();
      Qc_data();
      AC_data();
      /* code */
      break;

    default:
      break;
    }

    /*************************GPIOPA7 START*********************************/
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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief ADC1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
   */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.GainCompensation = 0;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the ADC multi-mode
   */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
   */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */
}

/**
 * @brief I2C1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x10B17DB5;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
   */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
   */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */
}

/**
 * @brief RTC Initialization Function
 * @param None
 * @retval None
 */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
   */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  hrtc.Init.OutPutPullUp = RTC_OUTPUT_PULLUP_NONE;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */
}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */
  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, charging_cut_off_Pin | ac_led8_Pin | sw8_ac_Pin | lcd_rs_Pin | sw1_on_off_Pin | sw2_screen_status_Pin | sw3_qc_Pin | qc_led3_Pin | pd_led4_Pin | nine_led5_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, torch_led7_Pin | sw7_torch_Pin | buzzer_Pin | lcd_d7_Pin | lcd_d6_Pin | lcd_d5_Pin | lcd_d4_Pin | lcd_Enable_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, sw4_pd_Pin | sw5_9v_Pin | sw6_12v_Pin | on_off_led1_Pin | sreen_status_led2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(led6_GPIO_Port, led6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : charging_cut_off_Pin ac_led8_Pin sw8_ac_Pin lcd_rs_Pin
                           sw1_on_off_Pin sw2_screen_status_Pin sw3_qc_Pin qc_led3_Pin
                           pd_led4_Pin nine_led5_Pin */
  GPIO_InitStruct.Pin = charging_cut_off_Pin | ac_led8_Pin | sw8_ac_Pin | lcd_rs_Pin | sw1_on_off_Pin | sw2_screen_status_Pin | sw3_qc_Pin | qc_led3_Pin | pd_led4_Pin | nine_led5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : torch_led7_Pin sw7_torch_Pin buzzer_Pin lcd_d7_Pin
                           lcd_d6_Pin lcd_d5_Pin lcd_d4_Pin lcd_Enable_Pin */
  GPIO_InitStruct.Pin = torch_led7_Pin | sw7_torch_Pin | buzzer_Pin | lcd_d7_Pin | lcd_d6_Pin | lcd_d5_Pin | lcd_d4_Pin | lcd_Enable_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : sw4_pd_Pin sw5_9v_Pin sw6_12v_Pin on_off_led1_Pin
                           sreen_status_led2_Pin */
  GPIO_InitStruct.Pin = sw4_pd_Pin | sw5_9v_Pin | sw6_12v_Pin | on_off_led1_Pin | sreen_status_led2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : led6_Pin */
  GPIO_InitStruct.Pin = led6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(led6_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : pwm_L2_Pin pmm_H2_Pin */
  GPIO_InitStruct.Pin = pwm_L2_Pin | pmm_H2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : pwm_L1_Pin pwm_H1_Pin */
  GPIO_InitStruct.Pin = pwm_L1_Pin | pwm_H1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  /* USER CODE END MX_GPIO_Init_2 */
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

#ifdef USE_FULL_ASSERT
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
