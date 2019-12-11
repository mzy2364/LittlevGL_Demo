/*
*******************************************************************************************************
*
* �ļ����� : main.c
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : 
==============================================================================
����ASCII��
ƫ����32 
ASCII�ַ���: !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
PC2LCD2002ȡģ��ʽ���ã�����+����ʽ+˳��+C51��ʽ
�ܹ���3���ַ�����12*12��16*16��24*24��32*32�����û������������������ֱ��ʵ��ַ�����
ÿ���ַ���ռ�õ��ֽ���Ϊ:(size/8+((size%8)?1:0))*(size/2),����size:���ֿ�����ʱ�ĵ����С(12/16/24/32...)
==============================================================================
*
*
* 
*******************************************************************************************************
*/







//32*32 ASCII�ַ�������
const unsigned char asc_32[95][64]={
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*" ",0*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xF0,0x00,0xC0,0x07,0xFF,0xE1,0xE0,0x07,0xF0,0x01,0xE0,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"!",1*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x01,0xC0,0x00,0x00,0x07,0x80,0x00,0x00,0x1F,0x00,0x00,0x00,0x1E,0x00,0x00,0x00,0x1C,0x20,0x00,0x00,0x01,0xC0,0x00,0x00,0x07,0x80,0x00,0x00,0x1F,0x00,0x00,0x00,0x1E,0x00,0x00,0x00,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*""",2*/
{0x00,0x00,0x00,0x00,0x00,0x18,0x0C,0x00,0x00,0x18,0x0C,0x00,0x00,0x18,0x0F,0xE0,0x00,0x1F,0xFC,0x00,0x03,0xF8,0x0C,0x00,0x00,0x18,0x0C,0x00,0x00,0x18,0x0C,0x00,0x00,0x18,0x0C,0x00,0x00,0x18,0x0C,0x00,0x00,0x18,0x0F,0xE0,0x00,0x1F,0xFC,0x00,0x03,0xF8,0x0C,0x00,0x00,0x18,0x0C,0x00,0x00,0x18,0x0C,0x00,0x00,0x00,0x00,0x00},/*"#",3*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x80,0x00,0x78,0x07,0xC0,0x00,0xFC,0x06,0x40,0x01,0x0E,0x00,0x20,0x03,0x07,0x00,0x20,0x02,0x03,0x80,0x20,0x0F,0xFF,0xFF,0xFC,0x02,0x01,0xC0,0x20,0x02,0x00,0xE0,0x60,0x01,0x30,0x70,0x40,0x01,0xF0,0x3F,0x80,0x00,0xF0,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"$",4*/
{0x00,0xFE,0x00,0x00,0x01,0xFF,0x00,0x00,0x03,0x01,0x80,0x00,0x02,0x00,0x80,0x60,0x03,0x01,0x81,0xC0,0x01,0xFF,0x07,0x00,0x00,0xFE,0x18,0x00,0x00,0x00,0xE0,0x00,0x00,0x03,0xBF,0x00,0x00,0x0C,0xFF,0xC0,0x00,0x71,0x80,0x60,0x01,0xC1,0x00,0x20,0x03,0x01,0x80,0x60,0x00,0x00,0xFF,0xC0,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x00},/*"%",5*/
{0x00,0x00,0x1F,0x00,0x00,0x00,0x7F,0xC0,0x00,0xFC,0xC0,0xC0,0x01,0xFF,0x80,0x60,0x03,0x03,0xE0,0x20,0x02,0x02,0x78,0x20,0x02,0x06,0x1E,0x20,0x03,0xFC,0x07,0x40,0x01,0xF0,0x03,0x80,0x00,0x01,0x03,0xC0,0x00,0x01,0x1C,0x60,0x00,0x01,0xE0,0x20,0x00,0x01,0x00,0x20,0x00,0x01,0x00,0x40,0x00,0x00,0x01,0x80,0x00,0x00,0x00,0x00},/*"&",6*/
{0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x1C,0x60,0x00,0x00,0x1C,0x40,0x00,0x00,0x1F,0x80,0x00,0x00,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"'",7*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xF8,0x00,0x00,0x3F,0xFF,0x00,0x00,0x78,0x07,0xC0,0x01,0xC0,0x00,0xE0,0x03,0x00,0x00,0x30,0x04,0x00,0x00,0x08,0x08,0x00,0x00,0x04,0x10,0x00,0x00,0x02,0x00,0x00,0x00,0x00},/*"(",8*/
{0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x02,0x08,0x00,0x00,0x04,0x04,0x00,0x00,0x08,0x03,0x00,0x00,0x30,0x01,0xC0,0x00,0xE0,0x00,0x78,0x07,0xC0,0x00,0x3F,0xFF,0x00,0x00,0x07,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*")",9*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x18,0x00,0x00,0x0E,0x38,0x00,0x00,0x0E,0x38,0x00,0x00,0x06,0x30,0x00,0x00,0x03,0x60,0x00,0x00,0x61,0x43,0x80,0x00,0xFF,0xFF,0x80,0x00,0x61,0x43,0x00,0x00,0x03,0x60,0x00,0x00,0x06,0x30,0x00,0x00,0x0E,0x38,0x00,0x00,0x0E,0x38,0x00,0x00,0x0C,0x18,0x00,0x00,0x00,0x00,0x00},/*"*",10*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x7F,0xFF,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00},/*"+",11*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0xE3,0x00,0x00,0x00,0xE2,0x00,0x00,0x00,0xFC,0x00,0x00,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*",",12*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00},/*"-",13*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x01,0xE0,0x00,0x00,0x01,0xE0,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*".",14*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0xE0,0x00,0x00,0x03,0x80,0x00,0x00,0x0E,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0xE0,0x00,0x00,0x03,0x80,0x00,0x00,0x0E,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0xE0,0x00,0x00,0x03,0x80,0x00,0x00,0x0E,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"/",15*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xF8,0x00,0x00,0x7F,0xFF,0x00,0x00,0xF0,0x07,0x80,0x01,0x80,0x00,0xC0,0x03,0x00,0x00,0x60,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x03,0x00,0x00,0x60,0x01,0x80,0x00,0xC0,0x00,0xE0,0x03,0x80,0x00,0x7F,0xFF,0x00,0x00,0x0F,0xF8,0x00,0x00,0x00,0x00,0x00},/*"0",16*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x20,0x00,0x80,0x00,0x20,0x00,0x80,0x00,0x20,0x00,0x80,0x00,0x60,0x01,0xFF,0xFF,0xE0,0x03,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"1",17*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x00,0xE0,0x00,0x98,0x01,0x60,0x01,0x00,0x02,0x60,0x02,0x00,0x04,0x60,0x02,0x00,0x08,0x60,0x02,0x00,0x10,0x60,0x02,0x00,0x20,0x60,0x02,0x00,0x40,0x60,0x03,0x00,0x80,0x60,0x01,0x83,0x00,0x60,0x01,0xFE,0x00,0xE0,0x00,0x7C,0x07,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"2",18*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x07,0x80,0x01,0xF0,0x07,0xC0,0x01,0x00,0x00,0x40,0x02,0x00,0x00,0x20,0x02,0x01,0x00,0x20,0x02,0x01,0x00,0x20,0x02,0x01,0x00,0x20,0x03,0x03,0x80,0x20,0x01,0x86,0x80,0x40,0x01,0xFC,0xC0,0xC0,0x00,0x78,0x7F,0x80,0x00,0x00,0x1E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"3",19*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x48,0x00,0x00,0x01,0x88,0x00,0x00,0x06,0x08,0x00,0x00,0x0C,0x08,0x10,0x00,0x30,0x08,0x10,0x00,0x40,0x08,0x10,0x01,0xFF,0xFF,0xF0,0x03,0xFF,0xFF,0xF0,0x03,0xFF,0xFF,0xF0,0x00,0x00,0x08,0x10,0x00,0x00,0x08,0x10,0x00,0x00,0x08,0x10,0x00,0x00,0x00,0x00},/*"4",20*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x80,0x00,0x1F,0x86,0x40,0x03,0xE1,0x00,0x20,0x03,0x02,0x00,0x20,0x03,0x04,0x00,0x20,0x03,0x04,0x00,0x20,0x03,0x04,0x00,0x20,0x03,0x04,0x00,0x20,0x03,0x06,0x00,0x40,0x03,0x03,0x01,0xC0,0x03,0x01,0xFF,0x80,0x03,0x00,0x7E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"5",21*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xFC,0x00,0x00,0x3F,0xFF,0x00,0x00,0x70,0xC3,0x80,0x00,0x81,0x80,0xC0,0x01,0x01,0x00,0x60,0x03,0x02,0x00,0x20,0x02,0x02,0x00,0x20,0x02,0x02,0x00,0x20,0x02,0x02,0x00,0x20,0x02,0x03,0x00,0x40,0x01,0xC1,0x80,0xC0,0x00,0xC0,0xFF,0x80,0x00,0x00,0x7E,0x00,0x00,0x00,0x00,0x00},/*"6",22*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x00,0x00,0x03,0xC0,0x00,0x00,0x03,0x80,0x00,0x00,0x03,0x00,0x00,0x00,0x03,0x00,0x07,0xE0,0x03,0x00,0x3F,0xE0,0x03,0x01,0xC0,0x00,0x03,0x06,0x00,0x00,0x03,0x18,0x00,0x00,0x03,0x60,0x00,0x00,0x03,0x80,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"7",23*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x00,0x00,0x78,0x3F,0x80,0x00,0xFC,0x60,0xC0,0x01,0x8E,0xC0,0x40,0x03,0x07,0x80,0x20,0x02,0x03,0x00,0x20,0x02,0x01,0x80,0x20,0x02,0x01,0x80,0x20,0x02,0x01,0xC0,0x20,0x03,0x01,0xE0,0x40,0x01,0x86,0x70,0xC0,0x00,0xFC,0x3F,0x80,0x00,0x78,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"8",24*/
{0x00,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0xFF,0x81,0xC0,0x01,0xC0,0xC1,0xC0,0x01,0x00,0x60,0x20,0x02,0x00,0x20,0x20,0x02,0x00,0x20,0x20,0x02,0x00,0x20,0x20,0x02,0x00,0x20,0x60,0x02,0x00,0x40,0xC0,0x01,0x00,0xC1,0x80,0x00,0xC1,0x8F,0x00,0x00,0x7F,0xFE,0x00,0x00,0x1F,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"9",25*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0xC0,0x00,0x07,0x81,0xE0,0x00,0x07,0x81,0xE0,0x00,0x03,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*":",26*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x66,0x00,0x06,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*";",27*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x01,0xC0,0x00,0x00,0x03,0x60,0x00,0x00,0x06,0x30,0x00,0x00,0x0C,0x18,0x00,0x00,0x18,0x0C,0x00,0x00,0x30,0x06,0x00,0x00,0x60,0x03,0x00,0x00,0xC0,0x01,0x80,0x01,0x00,0x00,0x40,0x02,0x00,0x00,0x20,0x04,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"<",28*/
{0x00,0x00,0x00,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x00,0x00,0x00},/*"=",29*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x10,0x02,0x00,0x00,0x20,0x01,0x00,0x00,0x40,0x00,0xC0,0x01,0x80,0x00,0x60,0x03,0x00,0x00,0x30,0x06,0x00,0x00,0x18,0x0C,0x00,0x00,0x0C,0x18,0x00,0x00,0x06,0x30,0x00,0x00,0x03,0x60,0x00,0x00,0x01,0xC0,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*">",30*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x00,0x00,0x01,0xF8,0x00,0x00,0x02,0x38,0x00,0x00,0x02,0x00,0x00,0x00,0x04,0x00,0x00,0xC0,0x04,0x00,0x79,0xE0,0x04,0x00,0x81,0xE0,0x04,0x01,0x00,0xC0,0x04,0x03,0x00,0x00,0x02,0x02,0x00,0x00,0x03,0x06,0x00,0x00,0x01,0xFC,0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00},/*"?",31*/
{0x00,0x00,0x00,0x00,0x00,0x0F,0xF8,0x00,0x00,0x3F,0xFE,0x00,0x00,0x70,0x07,0x80,0x00,0xC0,0x00,0xC0,0x01,0x01,0xF8,0x40,0x03,0x07,0xFC,0x20,0x02,0x1E,0x04,0x20,0x02,0x30,0x08,0x20,0x02,0x20,0x30,0x20,0x02,0x3F,0xFC,0x20,0x01,0x3F,0x04,0x40,0x01,0x80,0x0C,0xC0,0x00,0xE0,0x31,0x80,0x00,0x1F,0xC2,0x00,0x00,0x00,0x00,0x00},/*"@",32*/
{0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x60,0x00,0x00,0x03,0xE0,0x00,0x00,0x3E,0x20,0x00,0x03,0xE0,0x20,0x00,0x3E,0x20,0x00,0x03,0xE0,0x20,0x00,0x03,0x80,0x20,0x00,0x07,0xFC,0x20,0x00,0x00,0x3F,0xE0,0x00,0x00,0x03,0xFE,0x20,0x00,0x00,0x3F,0xE0,0x00,0x00,0x01,0xE0,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00},/*"A",33*/
{0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x03,0xFF,0xFF,0xE0,0x03,0xFF,0xFF,0xE0,0x02,0x01,0x00,0x20,0x02,0x01,0x00,0x20,0x02,0x01,0x00,0x20,0x02,0x01,0x00,0x20,0x02,0x01,0x00,0x20,0x03,0x03,0x00,0x20,0x01,0x86,0x80,0x60,0x01,0xFC,0xC0,0xC0,0x00,0xF8,0x7F,0x80,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x00},/*"B",34*/
{0x00,0x00,0x00,0x00,0x00,0x07,0xF8,0x00,0x00,0x3F,0xFF,0x00,0x00,0x70,0x07,0x80,0x00,0xC0,0x00,0xC0,0x01,0x00,0x00,0x40,0x03,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x01,0x00,0x00,0x40,0x01,0x80,0x00,0xC0,0x03,0xC0,0x01,0x80,0x00,0x30,0x06,0x00,0x00,0x00,0x00,0x00},/*"C",35*/
{0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x03,0xFF,0xFF,0xE0,0x03,0xFF,0xFF,0xE0,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x03,0x00,0x00,0x60,0x01,0x00,0x00,0x40,0x01,0x80,0x00,0xC0,0x00,0xF0,0x07,0x80,0x00,0x7F,0xFE,0x00,0x00,0x0F,0xF8,0x00,0x00,0x00,0x00,0x00},/*"D",36*/
{0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x03,0xFF,0xFF,0xE0,0x03,0xFF,0xFF,0xE0,0x02,0x01,0x00,0x20,0x02,0x01,0x00,0x20,0x02,0x01,0x00,0x20,0x02,0x01,0x00,0x20,0x02,0x01,0x00,0x20,0x02,0x03,0x80,0x20,0x02,0x0F,0xE0,0x20,0x03,0x00,0x00,0x60,0x03,0xC0,0x00,0xE0,0x00,0x60,0x03,0x00,0x00,0x00,0x00,0x00},/*"E",37*/
{0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x03,0xFF,0xFF,0xE0,0x03,0xFF,0xFF,0xE0,0x02,0x01,0x00,0x20,0x02,0x01,0x00,0x20,0x02,0x01,0x00,0x00,0x02,0x01,0x00,0x00,0x02,0x01,0x00,0x00,0x02,0x01,0x00,0x00,0x02,0x03,0x80,0x00,0x03,0x0F,0xE0,0x00,0x03,0x00,0x00,0x00,0x03,0xC0,0x00,0x00,0x00,0x60,0x00,0x00},/*"F",38*/
{0x00,0x00,0x00,0x00,0x00,0x07,0xF8,0x00,0x00,0x3F,0xFE,0x00,0x00,0x70,0x07,0x80,0x01,0xC0,0x01,0xC0,0x01,0x00,0x00,0x40,0x03,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x01,0x00,0x20,0x20,0x01,0x00,0x20,0x40,0x03,0xC0,0x3F,0x80,0x00,0x30,0x3F,0x80,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00},/*"G",39*/
{0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x03,0xFF,0xFF,0xE0,0x03,0xFF,0xFF,0xE0,0x02,0x00,0x80,0x20,0x02,0x00,0x80,0x20,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x02,0x00,0x80,0x20,0x02,0x00,0x80,0x20,0x03,0xFF,0xFF,0xE0,0x03,0xFF,0xFF,0xE0,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x00,0x00,0x00,0x00},/*"H",40*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x03,0xFF,0xFF,0xE0,0x03,0xFF,0xFF,0xE0,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"I",41*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x01,0x02,0x00,0x00,0x01,0x02,0x00,0x00,0x01,0x02,0x00,0x00,0x03,0x02,0x00,0x00,0x06,0x03,0xFF,0xFF,0xFC,0x03,0xFF,0xFF,0xF8,0x02,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"J",42*/
{0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x03,0xFF,0xFF,0xE0,0x03,0xFF,0xFF,0xE0,0x02,0x00,0xC0,0x20,0x02,0x01,0x00,0x20,0x00,0x07,0x80,0x00,0x00,0x0F,0xE0,0x00,0x00,0x30,0xF8,0x00,0x02,0x60,0x3E,0x20,0x03,0x80,0x0F,0x20,0x03,0x00,0x03,0xE0,0x02,0x00,0x00,0xE0,0x02,0x00,0x00,0x20,0x00,0x00,0x00,0x20},/*"K",43*/
{0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x03,0xFF,0xFF,0xE0,0x03,0xFF,0xFF,0xE0,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0xE0,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00},/*"L",44*/
{0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x03,0xFF,0xFF,0xE0,0x03,0xE0,0x00,0x20,0x03,0xFF,0x00,0x20,0x00,0x1F,0xF0,0x00,0x00,0x01,0xFF,0x80,0x00,0x00,0x0F,0xE0,0x00,0x00,0x1E,0x00,0x00,0x03,0xE0,0x00,0x00,0x3E,0x00,0x20,0x03,0xE0,0x00,0x20,0x03,0xFF,0xFF,0xE0,0x03,0xFF,0xFF,0xE0,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20},/*"M",45*/
{0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x03,0xFF,0xFF,0xE0,0x03,0x80,0x00,0x20,0x03,0xF0,0x00,0x20,0x00,0xFC,0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0x07,0xC0,0x00,0x00,0x01,0xF0,0x00,0x00,0x00,0x7C,0x00,0x02,0x00,0x1F,0x80,0x02,0x00,0x07,0xE0,0x03,0xFF,0xFF,0xE0,0x02,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"N",46*/
{0x00,0x00,0x00,0x00,0x00,0x0F,0xF8,0x00,0x00,0x3F,0xFE,0x00,0x00,0xF0,0x07,0x80,0x01,0x80,0x00,0xC0,0x01,0x00,0x00,0x40,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x01,0x00,0x00,0x40,0x01,0x80,0x00,0xC0,0x00,0xF0,0x03,0x80,0x00,0x3F,0xFE,0x00,0x00,0x0F,0xF8,0x00,0x00,0x00,0x00,0x00},/*"O",47*/
{0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x03,0xFF,0xFF,0xE0,0x03,0xFF,0xFF,0xE0,0x02,0x00,0x80,0x20,0x02,0x00,0x80,0x20,0x02,0x00,0x80,0x00,0x02,0x00,0x80,0x00,0x02,0x00,0x80,0x00,0x02,0x00,0x80,0x00,0x03,0x01,0x80,0x00,0x01,0x83,0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x00,0x00,0x00},/*"P",48*/
{0x00,0x00,0x00,0x00,0x00,0x0F,0xF8,0x00,0x00,0x7F,0xFF,0x00,0x00,0xF0,0x03,0x80,0x01,0x80,0x01,0xC0,0x01,0x00,0x06,0x40,0x02,0x00,0x04,0x20,0x02,0x00,0x04,0x20,0x02,0x00,0x06,0x20,0x02,0x00,0x03,0xE0,0x01,0x00,0x00,0xF8,0x01,0x80,0x00,0x5C,0x00,0xE0,0x03,0x8C,0x00,0x3F,0xFF,0x0C,0x00,0x0F,0xFC,0x18,0x00,0x00,0x00,0x00},/*"Q",49*/
{0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x03,0xFF,0xFF,0xE0,0x03,0xFF,0xFF,0xE0,0x02,0x01,0x00,0x20,0x02,0x01,0x00,0x20,0x02,0x01,0x80,0x00,0x02,0x01,0xE0,0x00,0x02,0x01,0xFC,0x00,0x03,0x03,0x3F,0x80,0x01,0x86,0x07,0xE0,0x01,0xFC,0x00,0xE0,0x00,0xF8,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00},/*"R",50*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x06,0x00,0x00,0xFE,0x01,0xE0,0x01,0x86,0x00,0xC0,0x03,0x03,0x00,0x40,0x02,0x03,0x00,0x20,0x02,0x01,0x80,0x20,0x02,0x01,0x80,0x20,0x02,0x01,0xC0,0x20,0x02,0x00,0xC0,0x20,0x01,0x00,0xE0,0x60,0x01,0x80,0x70,0xC0,0x03,0xE0,0x3F,0x80,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x00},/*"S",51*/
{0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x03,0x80,0x00,0x00,0x03,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x03,0xFF,0xFF,0xE0,0x03,0xFF,0xFF,0xE0,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x00,0x00,0x00},/*"T",52*/
{0x02,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x03,0xFF,0xFF,0x00,0x03,0xFF,0xFF,0xC0,0x02,0x00,0x00,0x40,0x02,0x00,0x00,0x60,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x02,0x00,0x00,0x40,0x02,0x00,0x00,0x80,0x03,0xFF,0xFF,0x00,0x02,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"U",53*/
{0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x03,0xC0,0x00,0x00,0x03,0xFC,0x00,0x00,0x02,0x3F,0xC0,0x00,0x00,0x03,0xF8,0x00,0x00,0x00,0x7F,0x80,0x00,0x00,0x07,0xE0,0x00,0x00,0x07,0x80,0x00,0x00,0x78,0x00,0x02,0x03,0xC0,0x00,0x02,0x3C,0x00,0x00,0x03,0xC0,0x00,0x00,0x02,0x00,0x00,0x00,0x02,0x00,0x00,0x00},/*"V",54*/
{0x02,0x00,0x00,0x00,0x03,0xC0,0x00,0x00,0x03,0xFF,0x80,0x00,0x02,0x3F,0xFE,0x00,0x02,0x00,0x7F,0xE0,0x00,0x00,0x0F,0x00,0x02,0x00,0xF0,0x00,0x03,0xEF,0x00,0x00,0x03,0xFF,0x80,0x00,0x02,0x0F,0xFE,0x00,0x00,0x00,0x3F,0xE0,0x00,0x00,0x1F,0x00,0x02,0x07,0xE0,0x00,0x03,0xF8,0x00,0x00,0x03,0x00,0x00,0x00,0x02,0x00,0x00,0x00},/*"W",55*/
{0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x03,0x80,0x00,0xE0,0x03,0xF0,0x03,0x20,0x02,0xFC,0x0C,0x20,0x02,0x1F,0x30,0x00,0x00,0x07,0xC0,0x00,0x00,0x07,0xF0,0x00,0x02,0x18,0x7C,0x00,0x02,0x60,0x1F,0x20,0x03,0x80,0x03,0xE0,0x02,0x00,0x00,0xE0,0x02,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00},/*"X",56*/
{0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x03,0xC0,0x00,0x00,0x03,0xF8,0x00,0x00,0x02,0x3E,0x00,0x20,0x02,0x0F,0xC0,0x20,0x00,0x01,0xFF,0xE0,0x00,0x00,0x7F,0xE0,0x00,0x03,0x80,0x20,0x02,0x1C,0x00,0x20,0x02,0x70,0x00,0x00,0x03,0x80,0x00,0x00,0x02,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"Y",57*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x60,0x00,0xE0,0x03,0x80,0x03,0xE0,0x03,0x00,0x0F,0xA0,0x02,0x00,0x3E,0x20,0x02,0x00,0xF8,0x20,0x02,0x03,0xE0,0x20,0x02,0x0F,0x80,0x20,0x02,0x3E,0x00,0x20,0x02,0x78,0x00,0x20,0x03,0xE0,0x00,0x60,0x03,0x80,0x00,0xE0,0x02,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"Z",58*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFF,0xFC,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"[",59*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x03,0xC0,0x00,0x00,0x00,0x78,0x00,0x00,0x00,0x1E,0x00,0x00,0x00,0x03,0xC0,0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x1E,0x00,0x00,0x00,0x07,0x80,0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"\",60*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x10,0x00,0x00,0x04,0x1F,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"]",61*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"^",62*/
{0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01},/*"_",63*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"`",64*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x00,0x01,0x8F,0xC0,0x00,0x03,0x8C,0x60,0x00,0x06,0x18,0x20,0x00,0x04,0x10,0x20,0x00,0x04,0x10,0x20,0x00,0x04,0x20,0x20,0x00,0x04,0x20,0x40,0x00,0x06,0x20,0x40,0x00,0x03,0xFF,0xC0,0x00,0x01,0xFF,0xE0,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0x00},/*"a",65*/
{0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x03,0xFF,0xFF,0xE0,0x07,0xFF,0xFF,0xC0,0x00,0x01,0x80,0xC0,0x00,0x02,0x00,0x60,0x00,0x02,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x06,0x00,0x40,0x00,0x03,0x00,0xC0,0x00,0x01,0xFF,0x80,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,0x00},/*"b",66*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x00,0x00,0x01,0xFF,0x80,0x00,0x03,0x81,0xC0,0x00,0x02,0x00,0x40,0x00,0x06,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x06,0x00,0x20,0x00,0x03,0xC0,0x40,0x00,0x01,0xC0,0x80,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"c",67*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x00,0x00,0x01,0xFF,0x80,0x00,0x03,0x80,0xC0,0x00,0x06,0x00,0x60,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x02,0x04,0x00,0x40,0x02,0x02,0x00,0x80,0x03,0xFF,0xFF,0xE0,0x07,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00},/*"d",68*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x00,0x00,0x01,0xFF,0x80,0x00,0x03,0x11,0xC0,0x00,0x02,0x10,0x40,0x00,0x04,0x10,0x60,0x00,0x04,0x10,0x20,0x00,0x04,0x10,0x20,0x00,0x04,0x10,0x20,0x00,0x06,0x10,0x20,0x00,0x03,0x10,0x40,0x00,0x01,0xF0,0xC0,0x00,0x00,0x71,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"e",69*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x7F,0xFF,0xE0,0x01,0xFF,0xFF,0xE0,0x01,0x04,0x00,0x20,0x03,0x04,0x00,0x20,0x02,0x04,0x00,0x20,0x02,0x04,0x00,0x20,0x02,0x04,0x00,0x00,0x02,0x00,0x00,0x00,0x01,0xC0,0x00,0x00,0x01,0xC0,0x00,0x00},/*"f",70*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0xE3,0x3E,0x00,0x03,0xFF,0xC2,0x00,0x02,0x0C,0xC3,0x00,0x04,0x04,0xC1,0x00,0x04,0x04,0xC1,0x00,0x04,0x04,0xC1,0x00,0x04,0x04,0xC1,0x00,0x06,0x0C,0xC1,0x00,0x03,0xF8,0xC3,0x00,0x05,0xF0,0x62,0x00,0x06,0x00,0x7E,0x00,0x06,0x00,0x3C,0x00,0x00,0x00,0x00},/*"g",71*/
{0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x03,0xFF,0xFF,0xE0,0x07,0xFF,0xFF,0xE0,0x00,0x01,0x00,0x20,0x00,0x02,0x00,0x20,0x00,0x06,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x04,0x00,0x20,0x00,0x06,0x00,0x20,0x00,0x03,0xFF,0xE0,0x00,0x01,0xFF,0xE0,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20},/*"h",72*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x03,0x87,0xFF,0xE0,0x03,0x8F,0xFF,0xE0,0x03,0x80,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"i",73*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x04,0x00,0x01,0x00,0x04,0x00,0x01,0x00,0x04,0x00,0x03,0x00,0x04,0x00,0x06,0x03,0x87,0xFF,0xFC,0x03,0x8F,0xFF,0xF8,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"j",74*/
{0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x03,0xFF,0xFF,0xE0,0x07,0xFF,0xFF,0xE0,0x00,0x00,0x08,0x20,0x00,0x00,0x10,0x20,0x00,0x00,0x30,0x00,0x00,0x00,0xFC,0x00,0x00,0x05,0x8E,0x00,0x00,0x07,0x07,0xA0,0x00,0x06,0x01,0xE0,0x00,0x04,0x00,0xE0,0x00,0x04,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00},/*"k",75*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x02,0x00,0x00,0x20,0x03,0xFF,0xFF,0xE0,0x07,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"l",76*/
{0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x20,0x00,0x07,0xFF,0xE0,0x00,0x0F,0xFF,0xE0,0x00,0x02,0x00,0x20,0x00,0x04,0x00,0x00,0x00,0x04,0x00,0x20,0x00,0x07,0xFF,0xE0,0x00,0x03,0xFF,0xE0,0x00,0x02,0x00,0x20,0x00,0x04,0x00,0x00,0x00,0x04,0x00,0x20,0x00,0x07,0xFF,0xE0,0x00,0x03,0xFF,0xE0,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00},/*"m",77*/
{0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x07,0xFF,0xE0,0x00,0x0F,0xFF,0xE0,0x00,0x01,0x00,0x20,0x00,0x02,0x00,0x20,0x00,0x02,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x04,0x00,0x20,0x00,0x06,0x00,0x20,0x00,0x03,0xFF,0xE0,0x00,0x01,0xFF,0xE0,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20},/*"n",78*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0xFF,0x80,0x00,0x03,0x81,0xC0,0x00,0x02,0x00,0x40,0x00,0x06,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x06,0x00,0x20,0x00,0x02,0x00,0x40,0x00,0x03,0x81,0xC0,0x00,0x01,0xFF,0x80,0x00,0x00,0x7E,0x00,0x00,0x00,0x00,0x00},/*"o",79*/
{0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x01,0x00,0x04,0x00,0x01,0x00,0x07,0xFF,0xFF,0x00,0x0F,0xFF,0xFF,0x00,0x01,0x00,0xC1,0x00,0x02,0x00,0x41,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x06,0x00,0x40,0x00,0x03,0x01,0xC0,0x00,0x01,0xFF,0x80,0x00,0x00,0x7E,0x00,0x00,0x00,0x00,0x00},/*"p",80*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x00,0x00,0x01,0xFF,0x80,0x00,0x03,0x80,0xC0,0x00,0x02,0x00,0x60,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x02,0x00,0x41,0x00,0x03,0x00,0xC1,0x00,0x03,0xFF,0xFF,0x00,0x07,0xFF,0xFF,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01},/*"q",81*/
{0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x0F,0xFF,0xE0,0x00,0x0F,0xFF,0xE0,0x00,0x00,0xC0,0x20,0x00,0x01,0x00,0x20,0x00,0x02,0x00,0x20,0x00,0x06,0x00,0x20,0x00,0x04,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00},/*"r",82*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xE0,0x00,0x01,0xC0,0xE0,0x00,0x03,0xE0,0x40,0x00,0x06,0x30,0x20,0x00,0x04,0x30,0x20,0x00,0x04,0x18,0x20,0x00,0x04,0x18,0x20,0x00,0x04,0x18,0x20,0x00,0x04,0x0C,0x20,0x00,0x02,0x0C,0x60,0x00,0x03,0x07,0xC0,0x00,0x07,0x83,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"s",83*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x0C,0x00,0x00,0x00,0x1F,0xFF,0x80,0x00,0xFF,0xFF,0xC0,0x00,0x04,0x00,0x60,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x40,0x00,0x00,0x01,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"t",84*/
{0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x07,0xFF,0x80,0x00,0x0F,0xFF,0xC0,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x04,0x00,0x40,0x00,0x04,0x00,0x80,0x00,0x07,0xFF,0xE0,0x00,0x0F,0xFF,0xC0,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x40},/*"u",85*/
{0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x07,0x80,0x00,0x00,0x07,0xF0,0x00,0x00,0x04,0xFE,0x00,0x00,0x04,0x1F,0xC0,0x00,0x00,0x03,0xE0,0x00,0x00,0x03,0x80,0x00,0x00,0x1C,0x00,0x00,0x04,0x60,0x00,0x00,0x07,0x80,0x00,0x00,0x06,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"v",86*/
{0x00,0x04,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x07,0xC0,0x00,0x00,0x07,0xFC,0x00,0x00,0x04,0x3F,0x80,0x00,0x00,0x03,0xE0,0x00,0x04,0x0F,0x80,0x00,0x06,0xF0,0x00,0x00,0x07,0xF0,0x00,0x00,0x07,0xFF,0x80,0x00,0x04,0x0F,0xE0,0x00,0x00,0x03,0x80,0x00,0x04,0x3C,0x00,0x00,0x07,0xC0,0x00,0x00,0x06,0x00,0x00,0x00,0x04,0x00,0x00},/*"w",87*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x04,0x00,0x20,0x00,0x04,0x00,0x60,0x00,0x07,0x00,0xE0,0x00,0x07,0x83,0x20,0x00,0x07,0xE6,0x00,0x00,0x04,0xF8,0x00,0x00,0x00,0x3C,0x00,0x00,0x04,0x5E,0x20,0x00,0x05,0x87,0xA0,0x00,0x06,0x01,0xE0,0x00,0x04,0x00,0x60,0x00,0x04,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00},/*"x",88*/
{0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x04,0x00,0x03,0x00,0x07,0x00,0x03,0x00,0x07,0xE0,0x01,0x00,0x04,0xF8,0x01,0x00,0x04,0x1F,0x02,0x00,0x00,0x07,0xFC,0x00,0x00,0x00,0xE0,0x00,0x00,0x07,0x00,0x00,0x04,0x38,0x00,0x00,0x07,0xC0,0x00,0x00,0x06,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00},/*"y",89*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x80,0x60,0x00,0x06,0x00,0xE0,0x00,0x04,0x03,0xE0,0x00,0x04,0x07,0xA0,0x00,0x04,0x0E,0x20,0x00,0x04,0x3C,0x20,0x00,0x04,0x70,0x20,0x00,0x05,0xE0,0x20,0x00,0x07,0x80,0x20,0x00,0x07,0x00,0x60,0x00,0x04,0x00,0xE0,0x00,0x00,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"z",90*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x01,0x40,0x00,0x07,0xFE,0x3F,0xF8,0x08,0x00,0x00,0x04,0x10,0x00,0x00,0x02,0x10,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"{",91*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"|",92*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x02,0x10,0x00,0x00,0x02,0x08,0x00,0x00,0x04,0x07,0xFE,0x3F,0xF8,0x00,0x01,0x40,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"}",93*/
{0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x0C,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"~",94*/
};










