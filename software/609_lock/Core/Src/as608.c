/*
 * @Author: Ifan-Y 1241562325@qq.com
 * @Date: 2022-08-27 17:58:37
 * @LastEditors: Ifan-Y 1241562325@qq.com
 * @LastEditTime: 2022-08-28 17:32:36
 * @FilePath: \609_lock\Core\Src\as608.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "as608.h"

uint8_t test_conected(void)
{
	uint8_t bool = 0;
  uint8_t r_paswd[12];
  // uint8_t r_img1[12] = {0};
  // uint8_t r_gen1[12] = {0};
  // uint8_t r_img2[12] = {0};
  // uint8_t r_gen2[12] = {0};
  uint8_t r_search1[16];
	uint8_t inits[100] = {0};
  // uint8_t r_search2[17] = {0};
  uint8_t r_reg[12] = {0};
  //获取指纹图像：ef 01 ff ff ff ff 01 00 03 01 00 05
  //对口令：EF 01 FF FF FF FF 01 00 07 13 00 00 00 00 00 1B
  //对口令回复：EF 01 FF FF FF FF 07 00 03 00 00 0A

  //口令
  uint8_t password[16] = {0xEF, 0X01, 0XFF, 0XFF, 0XFF, 0XFF, 0X01, 0X00, 0X07, 0X13, 0X00, 0X00, 0X00, 0X00, 0X00, 0X1B};
  //获得图片
  uint8_t get_img[12] = {0xef, 0x01, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x03, 0x01, 0x00, 0x05};
  //生成特征1
  uint8_t ps_genchar1[13] = {0xef, 0x01, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x04, 0x02, 0x01, 0x00, 0x08};
  //生成特征2
  uint8_t ps_genchar2[13] = {0xef, 0x01, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x04, 0x02, 0x02, 0x00, 0x09};
  //合并特征
  uint8_t ps_regmodel[12] = {0xef, 0x01, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x03, 0x05, 0x00, 0x09};
  //搜索指纹1
  uint8_t ps_search1[17] = {0xef, 0x01, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x08, 0x1b, 0x01, 0x00, 0x00, 0x00, 0x64, 0x00, 0x89};
  // //搜索指纹2
  // uint8_t ps_search2[17] = {0xef, 0x01, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x08, 0x04, 0x02, 0x00, 0x00, 0x00, 0x64, 0x00, 0x8a};

	// 初始化
	HAL_UART_Receive(&huart1, (uint8_t *)&inits, 100, 1);
  // 口令
  HAL_UART_Transmit(&huart1, (uint8_t *)&password, 16, 100);
  HAL_UART_Receive(&huart1, (uint8_t *)&r_paswd, 12, 100);
	HAL_Delay(10);

  // 获得图片1
  HAL_UART_Transmit(&huart1, (uint8_t *)&get_img, 12, 100);
  HAL_UART_Receive(&huart1, (uint8_t *)&r_reg, 12, 2000);
		HAL_Delay(10);

  // 生成特征1
  HAL_UART_Transmit(&huart1, (uint8_t *)&ps_genchar1, 13, 100);
  HAL_UART_Receive(&huart1, (uint8_t *)&r_reg, 12, 2000);
		HAL_Delay(10);

  // 获得图片2
  HAL_UART_Transmit(&huart1, (uint8_t *)&get_img, 12, 100);
  HAL_UART_Receive(&huart1, (uint8_t *)&r_reg, 12, 2000);
	HAL_Delay(10);

  // 生成特征2
  HAL_UART_Transmit(&huart1, (uint8_t *)&ps_genchar2, 13, 100);
  HAL_UART_Receive(&huart1, (uint8_t *)&r_reg, 12, 2000);
	HAL_Delay(10);

  // 合并特征
  HAL_UART_Transmit(&huart1, (uint8_t *)&ps_regmodel, 12, 100);
  HAL_UART_Receive(&huart1, (uint8_t *)&r_reg, 12, 2000);
	HAL_Delay(10);

  // 比对
  HAL_UART_Transmit(&huart1, (uint8_t *)&ps_search1, 17, 100);
  HAL_UART_Receive(&huart1, (uint8_t *)&r_search1, 16, 2000);
	HAL_Delay(10);

  // // 比对2
  // HAL_UART_Transmit(&huart1, (uint8_t *)&ps_search2, 17, 100);
  // HAL_UART_Receive(&huart1, (uint8_t *)&r_search2, 16, 2000);

if(r_search1[9]==0x00 && r_search1[0]!=0x00)
		bool = 1;
	
  return bool;
}
