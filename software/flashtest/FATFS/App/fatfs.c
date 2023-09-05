/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file   fatfs.c
  * @brief  Code for fatfs applications
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
#include "fatfs.h"

uint8_t retUSER;    /* Return value for USER */
char USERPath[4];   /* USER logical drive path */
FATFS USERFatFS;    /* File system object for USER logical drive */
FIL USERFile;       /* File object for USER */

/* USER CODE BEGIN Variables */
#include "w25qxx.h"
#include <stdio.h>
#include <string.h>
//#include "rtc.h"
//RTC_DateTypeDef sdatestructureget;
//RTC_TimeTypeDef stimestructureget;
//uint8_t workbuf[4096];
/* USER CODE END Variables */

void MX_FATFS_Init(void)
{
  /*## FatFS: Link the USER driver ###########################*/
  retUSER = FATFS_LinkDriver(&USER_Driver, USERPath);

  /* USER CODE BEGIN Init */
  /* additional user code for init */
    char wtext[120]={0};
    uint32_t byteswritten=0;                     /* File write/read counts */
    if(retUSER == FR_OK)
    {
        retUSER = f_mount(&USERFatFS,(TCHAR const*)USERPath,1) ;
        if(retUSER != FR_OK)
        {
            retUSER = FR_INT_ERR;
//            f_mkfs((TCHAR const*)USERPath, 0, 0,workbuf,4096);
            FRESULT ret=f_mkfs((TCHAR const*)USERPath, 0, 4096);
            Debugger_log(DBG, "f_mkfs(): %lu\n", ret);
        }
        else
        {
            if(f_open(&USERFile, "readme.txt", FA_CREATE_NEW | FA_WRITE) == FR_OK)
            {
                sprintf(wtext,"W25QXX\nFlash ID: 0x%04x\nFlash Size: %d MB\n\n", W25Qx_Para.FLASH_ID, W25Qx_Para.FLASH_SIZE / 1024 / 1024);
                f_write(&USERFile, wtext, strlen(wtext), (void *)&byteswritten);

                sprintf(wtext,"STM32F1 Nano Board Design By easy-smart.ch\nBoard Version: 1.0.1\n");
                f_write(&USERFile, wtext, strlen(wtext), (void *)&byteswritten);

                f_close(&USERFile);
            }
        }
    }

  /* USER CODE END Init */
}

/**
  * @brief  Gets Time from RTC
  * @param  None
  * @retval Time in DWORD
  */
DWORD get_fattime(void)
{
  /* USER CODE BEGIN get_fattime */
  return 0;
  /* USER CODE END get_fattime */
}

/* USER CODE BEGIN Application */

/* USER CODE END Application */
