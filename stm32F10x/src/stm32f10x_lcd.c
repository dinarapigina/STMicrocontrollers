#include "stm32f10x_i2c.h"
#include "string.h"
#define lcd_addr  ((uint8_t)0x4e)

void lcdBeginTransmission(uint8_t data)
{
	data |= 0x00;
	i2cTransmissionByte(lcd_addr,data);	// ����� ������
	i2cTransmissionByte(lcd_addr,(data | 0x04));	// � � �������
	for(int i=0;i<100;i++){};
	i2cTransmissionByte(lcd_addr,(data & (~0x04)));	// � � ����
	for(int i=0;i<1000;i++){};

}

void lcdTransmission(uint8_t data)
{
	data |= 0x08;
	i2cTransmissionByte(lcd_addr,data);	// ����� ������
	i2cTransmissionByte(lcd_addr,(data | 0x04));	// � � �������
	for(int i=0;i<100;i++){};
	i2cTransmissionByte(lcd_addr,(data & (~0x04)));	// � � ����
	for(int i=0;i<1000;i++){};
}

void lcdBegin()
{
	i2cBegin();

	//i2cTransmissionByte(lcd_addr,0x00);
	for(uint32_t i=0;i<1000;i++);
	lcdBeginTransmission(0x30);
	for(uint32_t i=0;i<1000;i++);
	lcdBeginTransmission(0x30);
	for(uint32_t i=0;i<1000;i++);
	lcdBeginTransmission(0x30);
	for(uint32_t i=0;i<1000;i++);
	lcdBeginTransmission(0x20);
	lcdBeginTransmission(0x20);
	lcdBeginTransmission(0x80);
	lcdBeginTransmission(0x00);
	lcdBeginTransmission(0xC0);
	lcdBeginTransmission(0x00);
	lcdBeginTransmission(0x10);
	lcdBeginTransmission(0x00);
	lcdBeginTransmission(0x60);
	lcdBeginTransmission(0x20);
	//i2cTransmissionByte(lcd_addr,0x08);
}

void clear()
{
	lcdTransmission(0x00);
	lcdTransmission(0x10);
	for(uint32_t i=0;i<10000;i++);
}

void setCursor()
{
	lcdBeginTransmission(0x80);
}

void writeByte(uint8_t byte)
{
	uint8_t byte_h;
	uint8_t byte_l;
	byte_h = ((byte & 0xf0) << 0) | (0x01);
	byte_l = ((byte & 0x0f) << 4) | (0x01);
	lcdTransmission(byte_h);
	lcdTransmission(byte_l);
}

void lcdWrite(char *string)
{
	for(int i=0; i < strlen(string);i++)
	{
		writeByte(string[i]);
	}
}

int main()
{

	lcdBegin();
	setCursor();

	while(1)
	{
		lcdWrite("Sveta Privet");
		for(uint32_t i=0; i<10000000; i++){};
		clear();
		lcdWrite("Eto Stas");
		for(uint32_t i=0; i<10000000; i++){};
		clear();
		lcdWrite("Nakonec-to tebe ");
		for(uint32_t i=0; i<10000000; i++){};
		clear();
		lcdWrite("42 goda");
		for(uint32_t i=0; i<10000000; i++){};
		clear();
		lcdWrite("Happy Birthday");
		for(uint32_t i=0; i<10000000; i++){};
		clear();
		lcdWrite("ZHelayu");
		for(uint32_t i=0; i<10000000; i++){};
		clear();
		lcdWrite("Tebe");
		for(uint32_t i=0; i<10000000; i++){};
		clear();
		lcdWrite("Schast'ya");
		for(uint32_t i=0; i<10000000; i++){};
		clear();
		lcdWrite("Zdorov'ya");
		for(uint32_t i=0; i<10000000; i++){};
		clear();
		lcdWrite("Lyubvi");
		for(uint32_t i=0; i<10000000; i++){};
		clear();
		lcdWrite("Poka-poka");
		for(uint32_t i=0; i<10000000; i++){};
		clear();
		lcdWrite("(*_*)      (*_*)");
		for(uint32_t i=0; i<10000000; i++){};
		clear();
	}

}
