#include<reg51.h>
sbit Fan=P2^0;
sbit Light=P2^1;

char str;
char a;

void delay(unsigned int x);
void ISR_ex0(void);
void Serialwrite(char byte)
{
  SBUF=byte;
  while(!TI);
  TI=0;
}
void Send(char *p)
{
  while(*p)
  {
    Serialwrite(*p);
    p++;
  }
  Serialwrite(0x0d);
}
void Serialbegin()
{
   TMOD=0x20;
   SCON=0x50;
   TH1=0xfd;
   TR1=1;
}
void main()
{
  P2=0x00;
  Serialbegin();
  Send("System Ready...");
  delay(50);
  while(1)
  {
    while(!RI);
    a=SBUF;
    str=a;
    RI=0;
      if(str=='a')
      {
        Fan=1;
        Send(" Fan ON");
        delay(50);
      }
      else if(str=='b')
      {
        Fan=0;
        Send(" Fan OFF");
        delay(50);
      }
       else if(str=='c')
      {
        Light=1;
        Send(" Light ON");
        delay(50);
      }
       else if(str=='d')
      {
        Light=0;
        Send(" Light OFF");
        delay(50);
      }
      str='0';
  }
}
void delay(unsigned int x)
{
	unsigned int i,j;
	for(i = 0;i<x;i++)
	{
		for(j = 0;j<1275;j++);
	}
}
void ISR_ex0(void) interrupt 0    
{
	Light = 0;
	Fan = 0;
}