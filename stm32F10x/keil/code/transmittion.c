
  usartBegin(USART3,19200);
  usartReceiver(USART3,usart_tx,buffer);
  usartTransmission(USART3,"Restart");
	
char buffer[255];
double valueBuffer = 0;
uint8_t flag = 0;

void usart_tx()
{
	valueBuffer = atof(buffer);
	
	if(!strcmp(buffer,"k1"))
	{
		flag = 1;
		memset(buffer,0,255);	
		return;		
	}
	if(!strcmp(buffer,"k2"))
	{
		flag = 2;
		memset(buffer,0,255);	
		return;
	}
	if(!strcmp(buffer,"k3"))
	{
		flag = 3;
		memset(buffer,0,255);	
		return;
	}
	if(!strcmp(buffer,"k4"))
	{
		flag = 4;
		memset(buffer,0,255);	
		return;
	}
	if(!strcmp(buffer,"pwm"))
	{
		flag = 5;
		memset(buffer,0,255);	
		return;
	}
	switch(flag)
	{
		case(1): K1 = valueBuffer; flag = 0; break;
		case(2): K2 = valueBuffer; flag = 0; break;
		case(3): K3 = valueBuffer; flag = 0; break;
		case(4): K4 = valueBuffer; flag = 0; break;
		case(5): K5 = valueBuffer; flag = 0; break;
	}	
	
//	if(valueBuffer > 0)
//	{
//		forvard = valueBuffer;		
//	}
//	
//	if(valueBuffer < 0)
//	{
//		 back = -valueBuffer;
//	}
	memset(buffer,0,255);
	
}