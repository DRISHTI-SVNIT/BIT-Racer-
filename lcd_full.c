//Bit Racer LCD Game using AVR


#define F_CPU 1000000UL
#include<avr/io.h>								//including required libraries
#include<util/delay.h>
#include<stdlib.h>
#include<avr/interrupt.h>
#include "lcd.h"

										//declaration of variables
uint8_t y=0;
uint8_t rep2=0,rep3=0,rep4=0,rep51=0,rep52=0,rep6=0;				//for repeat;  eg. rep2 is for repeating level 2
uint8_t i,j,k,l;
uint8_t score=0;
char r[4];

int main(void)
{
	DDRB |= 0b11111111;								//Connect LCD data pins on PORTB
	DDRD |= 0b00000011;								//Setting output for RS and EN 
	DDRD &= ~(1<<PIND2);								//Button at pind2 for ext interrupt
	PORTD |= (1<<PIND2);
	GICR = (1<<INT0);								// Enable INT0
	MCUCR = (1<<ISC01) | (1<<ISC00);						// Trigger INT0 on rising edge
	sei();
	
	DDRA |= (1<<PINA0);
	PORTA |= (1<<PINA0);
	
	Lcd4_Init();									//Initialize the LCD in 4bit mode
	
	
    while(1)
    {
        
		
		////////////////////////////////////////////////GAME INTRO///////////////////////////////////////
		
		Lcd4_Set_Cursor(0,0);																													//Game Title
 		SendString("B");	_delay_ms(200);
 		SendString("i");	_delay_ms(200);
 		SendString("T");	_delay_ms(200);
 		SendString(" ");	_delay_ms(200);
 		SendString("R");	_delay_ms(200);
 		SendString("a");	_delay_ms(200);
 		SendString("c");	_delay_ms(200);
 		SendString("e");	_delay_ms(200);
 		SendString("r");	_delay_ms(200);
						
		_delay_ms(500);
																															//End Title
		
		
		
		
		/////////////////////////////////////////GAME START///////////////////////////////////////////////
		
					
			Lcd4_Clear();								//for clear screen
			
			Lcd4_Set_Cursor(0,0);							//Put @ at (0,0)
			Lcd4_Write_String("@");
			
		
		/////////////////////////////////////////OBSTACLE LEVELS/////////////////////////////////////////
		
			
		
		
				///////////////////////////////Classic Level(0)/////////////////////
							//obstacles come at normal speed

					obslvl01:	
					for(i=15;i>=0;i--)					//Obstacle Level	0	1
					{
						
						if(i>0)
						{
							Lcd4_Set_Cursor(i,0);
							Lcd4_Write_String("# ");
							_delay_ms(300);
						}
						
						else
						{
							if(i==0 && y==1)
							{
								Lcd4_Set_Cursor(0,0);
								Lcd4_Write_String("# ");
								_delay_ms(300);
								Lcd4_Set_Cursor(0,0);
								Lcd4_Write_String(" ");
								
								goto obslvl02;
							}
							
							if(i==0 && y==0)				//Collision Detection
							{
								goto end1;
							}
						}
						
					}
					
					
					
					obslvl02:
					for(i=15;i>=0;i--)						//Obstacle Level	0   2
					{
						
						if(i>0)
						{
							Lcd4_Set_Cursor(i,1);
							Lcd4_Write_String("# ");
							_delay_ms(300);
						}
						
						else
						{
							if(i==0 && y==0)
							{
								Lcd4_Set_Cursor(0,1);
								Lcd4_Write_String("# ");
								_delay_ms(300);
								Lcd4_Set_Cursor(0,1);
								Lcd4_Write_String(" ");
								
								goto obslvl11;
							}
							
							if(i==0 && y==1)					//Collision Detection
							{
								goto end2;
							}
						}
						
					}
		
		
		////////////////////////////////////////////////////Classic Fast(1)///////////////////////////////////
							//obstacles come faster		

				obslvl11:
				score++;									//increment score
				for(i=15;i>=0;i--)								//Obstacle Level	1	1
				{
					
					if(i>0)
					{
						Lcd4_Set_Cursor(i,0);
						Lcd4_Write_String("# ");
						_delay_ms(100);
					}
					
					else
					{
						if(i==0 && y==1)
						{
							Lcd4_Set_Cursor(0,0);
							Lcd4_Write_String("# ");
							_delay_ms(100);
							Lcd4_Set_Cursor(0,0);
							Lcd4_Write_String(" ");
							
							goto obslvl12;
						}
						
						if(i==0 && y==0)						//Collision Detection
						{
							goto end1;
						}
					}
					
				}
				
				
				
				obslvl12:
				for(i=15;i>=0;i--)								//Obstacle Level	1   2
				{
					
					if(i>0)
					{
						Lcd4_Set_Cursor(i,1);
						Lcd4_Write_String("# ");
						_delay_ms(100);
					}
					
					else
					{
						if(i==0 && y==0)
						{
							Lcd4_Set_Cursor(0,1);
							Lcd4_Write_String("# ");
							_delay_ms(100);
							Lcd4_Set_Cursor(0,1);
							Lcd4_Write_String(" ");
							
							goto obslvl2;
						}
						
						if(i==0 && y==1)						//Collision Detection
						{
							goto end2;
						}
					}
					
				}
			
		
		//////////////////////////////////////////////Classic Continuous(2)//////////////////////////////////////
							//obstacles come continuously		

				obslvl2:
				score++;
				for(i=15,j=20,k=25,l=30;i>=0,j>=0,k>=0,l>=0;i--,j--,k--,l--)				//Obstacle Level   2	
				{
					
					if(i>0)										/////1
					{
						Lcd4_Set_Cursor(i,0);
						Lcd4_Write_String("# ");
						_delay_ms(30);
						
						if(i==5)
						{
							k=15;
						}
						
					}
					else
					{
						if(i==0 && y==1)
						{
							Lcd4_Set_Cursor(0,0);
							Lcd4_Write_String("# ");
							_delay_ms(30);
							Lcd4_Set_Cursor(0,0);
							Lcd4_Write_String(" ");
						}
						
						if(i==0 && y==0)							//Collision Detection
						{
							goto end1;
						}
					}
					
															//////2					
					if(j>0)
					{
						Lcd4_Set_Cursor(j,1);
						Lcd4_Write_String("# ");
						_delay_ms(30);
						
						if(j==5)
						{
							l=15;
						}
						
					}
					else
					{
						if(j==0 && y==0)
						{
							Lcd4_Set_Cursor(0,1);
							Lcd4_Write_String("# ");
							_delay_ms(30);
							Lcd4_Set_Cursor(0,1);
							Lcd4_Write_String(" ");
						}
						
						if(j==0 && y==1)							//Collision Detection
						{
							goto end2;
						}
					}
					
					
															///3
					if(k>0)
					{
						Lcd4_Set_Cursor(k,0);
						Lcd4_Write_String("# ");
						_delay_ms(30);
						
						if(k==5)
						{
							i=15;
						}
					}
					else
					{
						if(k==0 && y==1)
						{
							Lcd4_Set_Cursor(0,0);
							Lcd4_Write_String("# ");
							_delay_ms(30);
							Lcd4_Set_Cursor(0,0);
							Lcd4_Write_String(" ");
						}
						
						if(k==0 && y==0)							//Collision Detection
						{
							goto end2;
						}
					}
					
					
																////4
					if(l>0)
					{
						Lcd4_Set_Cursor(l,1);
						Lcd4_Write_String("# ");
						_delay_ms(30);
						
						if(l==5)
						{
							j=15;
						}
						
					}
					else
					{
						if(l==0 && y==0)
						{
							Lcd4_Set_Cursor(0,1);
							Lcd4_Write_String("# ");
							_delay_ms(30);
							Lcd4_Set_Cursor(0,1);
							Lcd4_Write_String(" ");
						}
						
						if(l==0 && y==1)							//Collision Detection
						{
							goto end2;
						}
					}
					
					if(rep2==64)
					{
						/*LCDInitialize();*/
						Lcd4_Clear();
						goto obslvl31;
					}
					
					rep2++;
					
					
				}
		

		//////////////////////////////////////////////////For placing the @ at correct position/////////////////////////////////
		
						if(y==0)
						{
							Lcd4_Set_Cursor(0,0);	
							Lcd4_Write_String("@");						//Put @ at (0,0)
						}
						if(y==1)
						{							
							Lcd4_Set_Cursor(0,1);
							Lcd4_Write_String("@");						//Put @ at 0,1
						}
											
						_delay_ms(500);
					
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					
		
		///////////////////////////////////////////////////VARIABLE SPEED(3)////////////////////////////////////////////////
							//the obstacle's speed varies
		obslvl31:
		score++;
		
		for(i=15;i>=0;i--)											//Obstacle Level 3   1
		{
			
			if(i>0)
			{
				Lcd4_Set_Cursor(i,1);
				Lcd4_Write_String("# ");
				
				if(i%4==0)
				{
					_delay_ms(200);
				}
				else
				{
					_delay_ms(50);
				}
				
			}
			
			else
			{
				if(i==0 && y==0)
				{
					Lcd4_Set_Cursor(0,1);
					Lcd4_Write_String("# ");
					_delay_ms(50);
					Lcd4_Set_Cursor(0,1);
					Lcd4_Write_String(" ");
					
					goto obslvl32;
				}
				
				if(i==0 && y==1)									//Collision Detection
				{
					goto end2;
				}
			}
			
		}
		
		
		obslvl32:
		for(i=15;i>=0;i--)											//Obstacle Level 3   2
		{
			
			if(i>0)
			{
				Lcd4_Set_Cursor(i,0);
				Lcd4_Write_String("# ");
								
				if(i%4==0)
				{
					_delay_ms(200);
				}
				else
				{
					_delay_ms(50);
				}
				
			}
			
			else
			{
				if(i==0 && y==1)
				{
					Lcd4_Set_Cursor(0,0);
					Lcd4_Write_String("# ");
					_delay_ms(50);
					Lcd4_Set_Cursor(0,0);
					Lcd4_Write_String(" ");
					
					if(rep3<2)
					{
						rep3++;
						goto obslvl31;
					}
					else
					{
						goto obslvl41;
					}
					
				}
				
				if(i==0 && y==0)									//Collision Detection
				{
					goto end1;
				}
			}
			
			
		}
		
		
		
		
		/////////////////////////////////////////////////UP AND DOWN(4)//////////////////////////////////////////////////////
						//the obstacles move up and down, while also moving closer		

			obslvl41:
			score++;
			for(i=15;i>=0;i--)									//Obstacle Level	4	1
			{
				
				if(i>0)
				{
					if(i%2==0)
					{
						Lcd4_Set_Cursor(i+1,0);
						Lcd4_Write_String(" ");
						Lcd4_Set_Cursor(i,1);
						Lcd4_Write_String("#");
						_delay_ms(150);
					}
					else
					{
						Lcd4_Set_Cursor(i+1,1);
						Lcd4_Write_String(" ");
						Lcd4_Set_Cursor(i,0);
						Lcd4_Write_String("#");
						_delay_ms(150);
					}
				}
				
				else
				{
					if(i==0 && y==0)
					{
						Lcd4_Set_Cursor(1,0);
						Lcd4_Write_String(" ");
						Lcd4_Set_Cursor(0,1);
						Lcd4_Write_String("#");
						_delay_ms(150);
						Lcd4_Set_Cursor(0,1);
						Lcd4_Write_String(" ");
						
						goto obslvl42;
					}
					
					if(i==0 && y==1)									//Collision Detection
					{
						goto end2;
					}
				}
				
			}
			
			
			
			obslvl42:
			for(i=15;i>=0;i--)									//Obstacle Level	4   2
			{
				
				if(i>0)
				{
					if(i%2==0)
					{
						Lcd4_Set_Cursor(i+1,1);
						Lcd4_Write_String(" ");
						Lcd4_Set_Cursor(i,0);
						Lcd4_Write_String("#");
						_delay_ms(150);
					}
					else
					{
						Lcd4_Set_Cursor(i+1,0);
						Lcd4_Write_String(" ");
						Lcd4_Set_Cursor(i,1);
						Lcd4_Write_String("#");
						_delay_ms(150);
					}
				}
				
				else
				{
					if(i==0 && y==1)
					{
						Lcd4_Set_Cursor(1,1);
						Lcd4_Write_String(" ");
						Lcd4_Set_Cursor(0,0);
						Lcd4_Write_String("#");
						_delay_ms(150);
						Lcd4_Set_Cursor(0,0);
						Lcd4_Write_String(" ");
						
						if(rep4<2)
						{
							rep4++;
							goto obslvl41;
						}
						else
						{
							goto obslvl51;	
						}
						
					}
					
					if(i==0 && y==0)									//Collision Detection
					{
						goto end1;
					}
				}
				
			}
			
		
		//////////////////////////////////////////////////////////EVIL TWIN(5)/////////////////////////////////////////
						//there are 2 obstacles(#), you can pass through one of them		

		obslvl51:	
		score++;
		for(i=15;i>=0;i--)										//Obstacle Level	5	1
		{
			
			if(i>0)
			{
				if(i%4==0)
				{
					Lcd4_Set_Cursor(i,0);
					Lcd4_Write_String("# ");
					Lcd4_Set_Cursor(i,1);
					Lcd4_Write_String("  ");
					_delay_ms(100);
				}
				else
				{
					Lcd4_Set_Cursor(i,0);
					Lcd4_Write_String("# ");
					Lcd4_Set_Cursor(i,1);
					Lcd4_Write_String("# ");
					_delay_ms(100);
				}
			}
			
			else
			{
				if(i==0 && y==1)
				{
					Lcd4_Set_Cursor(0,0);
					Lcd4_Write_String("# ");
					Lcd4_Set_Cursor(1,1);
					Lcd4_Write_String(" ");
					_delay_ms(100);
					Lcd4_Set_Cursor(0,0);
					Lcd4_Write_String(" ");
					
					if(rep51<2)
					{
						rep51++;
						goto obslvl51;
					}
					else
					{
						goto obslvl52;
					}
				}
				
				if(i==0 && y==0)									//Collision Detection
				{
					goto end1;
				}
			}
			
		}
		
		
		
		obslvl52:
		for(i=15;i>=0;i--)											//Obstacle Level	5   2
		{
			
			if(i>0)
			{
				if(i%4==0)
				{
					Lcd4_Set_Cursor(i,1);
					Lcd4_Write_String("# ");
					Lcd4_Set_Cursor(i,0);
					Lcd4_Write_String("  ");
					_delay_ms(100);
				}
				else
				{
					Lcd4_Set_Cursor(i,1);
					Lcd4_Write_String("# ");
					Lcd4_Set_Cursor(i,0);
					Lcd4_Write_String("# ");
					_delay_ms(100);
				}
			}
			
			else
			{
				if(i==0 && y==0)
				{
					Lcd4_Set_Cursor(0,1);
					Lcd4_Write_String("# ");
					Lcd4_Set_Cursor(1,0);
					Lcd4_Write_String(" ");
					_delay_ms(100);
					Lcd4_Set_Cursor(0,1);
					Lcd4_Write_String(" ");
					
					if(rep52<2)
					{
						rep52++;
						goto obslvl52;
					}
					else
					{
						goto obslvl61;
											
					}
				}
				
				if(i==0 && y==1)									//Collision Detection
				{
					goto end2;
				}
			}
			
		}
		
		
		
		///////////////////////////////////////////////////////LIGHTS OUT(6)///////////////////////////////////////
							//the backlight of the LCD turns on and off

				obslvl61:
				score++;
				for(i=15;i>=0;i--)								//Obstacle Level	6	1
				{
					
					if(i>0)
					{
						Lcd4_Set_Cursor(i,0);
						Lcd4_Write_String("# ");
						_delay_ms(100);
						
						if(i==10)
						{
							PORTA &= ~(1<<PINA0);
						}
						if(i==5)
						{
							PORTA |= 1<<PINA0;
						}
					}
					
					else
					{
						if(i==0 && y==1)
						{
							Lcd4_Set_Cursor(0,0);
							Lcd4_Write_String("# ");
							_delay_ms(100);
							Lcd4_Set_Cursor(0,0);
							Lcd4_Write_String(" ");
							
							goto obslvl62;
						}
						
						if(i==0 && y==0)							//Collision Detection
						{
							goto end1;
						}
					}
					
				}
				
				
				
				obslvl62:
				for(i=15;i>=0;i--)							//Obstacle Level	6   2
				{
					
					if(i>0)
					{
						Lcd4_Set_Cursor(i,1);
						Lcd4_Write_String("# ");
						_delay_ms(100);
						
						if(i==10)
						{
							PORTA &= ~(1<<PINA0);
						}
						if(i==5)
						{
							PORTA |= 1<<PINA0;
						}
					}
					
					else
					{
						if(i==0 && y==0)
						{
							Lcd4_Set_Cursor(0,1);
							Lcd4_Write_String("# ");
							_delay_ms(100);
							Lcd4_Set_Cursor(0,1);
							Lcd4_Write_String(" ");
							
							if(rep6<2)
							{
								rep6++;
								goto obslvl61;	
							}
							else
							{
								goto obslvl71;
							}
						}
						
						if(i==0 && y==1)							//Collision Detection
						{
							goto end2;
						}
					}
					
				}
				
				
				
		
		
		
		//////////////////////////////////////////////////////////HELL(7)////////////////////////////////////
						//combination of level 5 and 6
		
		obslvl71:
		score++;	
		for(i=15;i>=0;i--)										//Obstacle Level	7	1
		{
			
			if(i>0)
			{
				if(i%4==0)
				{
					Lcd4_Set_Cursor(i,0);
					Lcd4_Write_String("# ");
					Lcd4_Set_Cursor(i,1);
					Lcd4_Write_String("  ");
					_delay_ms(50);
				}
				else
				{
					Lcd4_Set_Cursor(i,0);
					Lcd4_Write_String("# ");
					Lcd4_Set_Cursor(i,1);
					Lcd4_Write_String("# ");
					_delay_ms(50);
					
					
					if(i==10)
					{
						PORTA &= ~(1<<PINA0);
					}
					if(i==5)
					{
						PORTA |= 1<<PINA0;
					}
					
				}
			}
			
			else
			{
				if(i==0 && y==1)
				{
					Lcd4_Set_Cursor(0,0);
					Lcd4_Write_String("# ");
					Lcd4_Set_Cursor(1,1);
					Lcd4_Write_String(" ");
					_delay_ms(50);
					Lcd4_Set_Cursor(0,0);
					Lcd4_Write_String(" ");
					
					goto obslvl72;
				}
				
				if(i==0 && y==0)									//Collision Detection
				{
					goto end1;
				}
			}
			
		}
		
		
		
		obslvl72:
		for(i=15;i>=0;i--)										//Obstacle Level	7   2
		{
			
			if(i>0)
			{
				if(i%4==0)
				{
					Lcd4_Set_Cursor(i,1);
					Lcd4_Write_String("# ");
					Lcd4_Set_Cursor(i,0);
					Lcd4_Write_String("  ");
					_delay_ms(50);
				}
				else
				{
					Lcd4_Set_Cursor(i,1);
					Lcd4_Write_String("# ");
					Lcd4_Set_Cursor(i,0);
					Lcd4_Write_String("# ");
					_delay_ms(50);
				}
				
				
				if(i==10)
				{
					PORTA &= ~(1<<PINA0);
				}
				if(i==5)
				{
					PORTA |= 1<<PINA0;
				}
				
				
			}
			
			
			else
			{
				if(i==0 && y==0)
				{
					Lcd4_Set_Cursor(0,1);
					Lcd4_Write_String("# ");
					Lcd4_Set_Cursor(1,0);
					Lcd4_Write_String(" ");
					_delay_ms(50);
					Lcd4_Set_Cursor(0,1);
					Lcd4_Write_String(" ");
					
					goto obslvl71;								//go back to level 7 1
				}
				
				if(i==0 && y==1)									//Collision Detection
				{
					goto end2;		
				}
			}
			
		}
		
	/////////////////////////////////////////////////////////////INFINITE OBSTACLES////////////////////////////////
							//obstacles keep on repeating from level 7 1
		
		
		
    }																							//End Of while(1)
	
	/////////////////////////////////////////////GAME ENDINGS//////////////////////////////////////////////
	
				end1:															//Game Over!  1
				Lcd4_Set_Cursor(0,0);
				Lcd4_Write_String("@#");
				Lcd4_Write_String("  Game Over!");
				Lcd4_Set_Cursor(0,1);
				Lcd4_Write_String("Score:");
				itoa(score*100,r,10);
				Lcd4_Write_String(r);
				goto theend;
	
				end2:															//Game Over!  2
				Lcd4_Set_Cursor(0,1);
				Lcd4_Write_String("@#");
				Lcd4_Write_String("  Game Over!");
				Lcd4_Set_Cursor(0,0);
				Lcd4_Write_String("Score:");
				itoa(score*100,r,10);
				Lcd4_Write_String(r);
				goto theend;
	
				theend:
				;								//blank statement
	
}																				//End Of main()




///////////////////////////////////////////////////////INTERRUPT FUNCTION/////////////////////////////////

ISR(INT0_vect)
{
	if(y==0)
	{
		Lcd4_Set_Cursor(0,0);
		Lcd4_Write_String(" ");
		Lcd4_Set_Cursor(0,1);
		Lcd4_Write_String("@");
		
		y=1;
		PORTD |= 1<<PD2;
	}
	
	else if(y==1)
	{
		Lcd4_Set_Cursor(0,1);
		Lcd4_Write_String(" ");
		Lcd4_Set_Cursor(0,0);
		Lcd4_Write_String("@");
		
		y=0;
		PORTD |= 1<<PD2;
	}
}

