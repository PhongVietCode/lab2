#include "7segmentLED.h"
int num0[7] = {0, 0, 0, 0, 0, 0, 1};
int num1[7] = {1, 0, 0, 1, 1, 1, 1};
int num2[7] = {0, 0, 1, 0, 0, 1, 0};
int num3[7] = {0, 0, 0, 0, 1, 1, 0};
int num4[7] = {1, 0, 0, 1, 1, 0, 0};
int num5[7] = {0, 1, 0, 0, 1, 0, 0};
int num6[7] = {0, 1, 0, 0, 0, 0, 0};
int num7[7] = {0, 0, 0, 1, 1, 1, 1};
int num8[7] = {0, 0, 0, 0, 0, 0, 0};
int num9[7] = {0, 0, 0, 0, 1, 0, 0};
void displayNumber(int numberArr[])
{
    HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, numberArr[0]);
    HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, numberArr[1]);
    HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, numberArr[2]);
    HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, numberArr[3]);
    HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, numberArr[4]);
    HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, numberArr[5]);
    HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, numberArr[6]);
}
void clearDisplay7Seg()
{
    HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, 1);
    HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, 1);
    HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, 1);
    HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, 1);
    HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, 1);
    HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, 1);
    HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, 1);
}
void display7Seg(int num)
{
    switch (num)
    {
    case 0:
        displayNumber(num0);
        break;
    case 1:
        displayNumber(num1);
        break;
    case 2:
        displayNumber(num2);
        break;
    case 3:
        displayNumber(num3);
        break;
    case 4:
        displayNumber(num4);
        break;
    case 5:
        displayNumber(num5);
        break;
    case 6:
        displayNumber(num6);
        break;
    case 7:
        displayNumber(num7);
        break;
    case 8:
        displayNumber(num8);
        break;
    case 9:
        displayNumber(num9);
        break;
    }
}
