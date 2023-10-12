/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "fatfs.h"
#include "spi.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
// 25AA040A instructions
const uint8_t EEPROM_READ = 0b00000011;
const uint8_t EEPROM_WRITE = 0b00000010;
const uint8_t EEPROM_WRDI = 0b00000100;
const uint8_t EEPROM_WREN = 0b00000110;
const uint8_t EEPROM_RDSR = 0b00000101;
const uint8_t EEPROM_WRSR = 0b00000001;
const uint8_t EEPROM_SFDP = 0x5a;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
unsigned char SPI_SFDP_Read(uint32_t addr)
{
    unsigned char buf[1];

    HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, (uint8_t *)&EEPROM_SFDP, 1, 100);


    uint8_t tmp=0;
    tmp=((addr & 0xFFFFFF) >> 16);
    HAL_SPI_Transmit(&hspi1, (uint8_t *)&tmp, 1, 100);
    tmp=(((addr & 0xFFFF) >> 8));
    HAL_SPI_Transmit(&hspi1, (uint8_t *)&tmp, 1, 100);
    tmp=(addr & 0xFF);
    HAL_SPI_Transmit(&hspi1, (uint8_t *)&tmp, 1, 100);
    tmp=0xFF;
    HAL_SPI_Transmit(&hspi1, (uint8_t *)&tmp, 1, 100);

//    addr=addr<<8;
//    HAL_SPI_Transmit(&hspi1, (uint8_t *)&addr, 4, 100);

    HAL_SPI_Receive(&hspi1, (uint8_t *)buf, sizeof(buf) / sizeof(buf[0]), 100);
    HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_SET);
    return buf[0];
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  DBG=Debugger_create(0);
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
  MX_SPI1_Init();
  MX_USB_DEVICE_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

    HAL_GPIO_WritePin(LED1_GRN_GPIO_Port,LED1_GRN_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED2_ORG_GPIO_Port,LED2_ORG_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED3_RED_GPIO_Port,LED3_RED_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED4_BLU_GPIO_Port,LED4_BLU_Pin,GPIO_PIN_SET);

    uint8_t pwmset=0;
    uint16_t time=0;
    uint8_t timeflag=0;
    uint8_t timecount=0;

    uint32_t tick1=0;



    char spi_buf[20];

    // CS PIN
    HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_SET);

    // Enable write enable latch (allow write operations)
    HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, (uint8_t *)&EEPROM_WREN, 1, 100);
    HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_SET);

    // Read status register
    HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, (uint8_t *)&EEPROM_RDSR, 1, 100);
    HAL_SPI_Receive(&hspi1, (uint8_t *)spi_buf, 1, 100);
    HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_SET);

    // Print out status register
    Debugger_log(DBG, "Status: 0x%x\n", (unsigned int)spi_buf[0]);

    unsigned char EUI48_Octet5, EUI48_Octet4, EUI48_Octet3, EUI48_Octet2, EUI48_Octet1, EUI48_Octet0;
    EUI48_Octet0=SPI_SFDP_Read(0x261);
    EUI48_Octet1=SPI_SFDP_Read(0x262);
    EUI48_Octet2=SPI_SFDP_Read(0x263);
    EUI48_Octet3=SPI_SFDP_Read(0x264);
    EUI48_Octet4=SPI_SFDP_Read(0x265);
    EUI48_Octet5=SPI_SFDP_Read(0x266);

    // Print out MAC address
    Debugger_log(DBG, "MAC: %02x:%02x:%02x:%02x:%02x:%02x\n", (unsigned int)EUI48_Octet0, (unsigned int)EUI48_Octet1, (unsigned int)EUI48_Octet2, (unsigned int)EUI48_Octet3, (unsigned int)EUI48_Octet4, (unsigned int)EUI48_Octet5);




    while (1)
  {
      if(tick1 - HAL_GetTick() > 10) {
          tick1 = HAL_GetTick();

          /* LED4_BLU Breathing Lamp test */
          /* Breathing Lamp */
          if (timeflag == 0) {
              time++;
              if (time >= 1600) timeflag = 1;
          } else {
              time--;
              if (time == 0) timeflag = 0;
          }

          /* Duty Cycle Setting */
          pwmset = time / 80;

          /* 20ms Pulse Width */
          if (timecount > 20) timecount = 0;
          else timecount++;

          if (timecount >= pwmset) HAL_GPIO_WritePin(LED4_BLU_GPIO_Port, LED4_BLU_Pin, GPIO_PIN_SET);
          else HAL_GPIO_WritePin(LED4_BLU_GPIO_Port, LED4_BLU_Pin, GPIO_PIN_RESET);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV2;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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
