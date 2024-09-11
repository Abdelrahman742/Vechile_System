/*
 * Project of course C.c
 * Created on: Apr 18, 2024
 * Author: Abdelrahman Ibrahem Adel
 * Describtion:Vehicle control system
 */
#include<stdio.h>
#define WITH_ENGINE_TEMP_CONTROLLER 1
//**************************Start Function Prototypes*************************************************//
void Start_up(void);
void Turn_off(void);
void Turn_on(void);
void Sensors_set_menu(void);
void Set_traffic_light(void);
void Set_room_temperature(void);
void Set_engine_temperature(void);
void Check_speed(void);
void Print_Variables(void);
//**************************End Function Prototypes*************************************************//
//**************************Start Global Variables and structure*************************************************//
char choose;//variable to make the user determine the main state
struct Vehicle_Variables
{
	int Engine_state;
	int AC;
	float Vehicle_Speed;
	float Room_Temperature;
	int Engine_Temperature_Controller_State;
	float Engine_Temperature;
}state;
//***************************End Global Variables and structure************************************************//
int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	state.Room_Temperature=25;
	state.Engine_Temperature=110;
	while(1)
	{
		Start_up();//display the start menu
		//if user choose to quit system
		if(choose=='c')
		{
			printf("Quit the system\n");
			return 0;//Quit the system
		}
		//if user want to turn off the engine
		else if(choose=='b')
		{
			state.Engine_state=0;//turn off the engine
			Turn_off();
		}
		//if user want to turn on the engine
		else if(choose=='a')
		{
			state.Engine_state=1;//turn on the engine
			//loop to allow change sensors' states while the engine on
			while(state.Engine_state==1)
			{
				Turn_on();
			}
		}
	}
}
//start up menu
void Start_up(void)
{
	printf("Start up menu :\n\n");
	printf("a.Turn on the vehicle engine\nb.Turn off the vehicle engine\nc.Quit the system\n");
	scanf(" %c",&choose);
	printf("\n");
}
//function to turn off the engine if user want
void Turn_off(void)
{
	printf("Turn off the vehicle engine\n\n");
}
//function to turn on the engine if user want
void Turn_on(void)
{
	Sensors_set_menu();
}
//function to dispaly options and modify on them
void Sensors_set_menu(void)
{
	char st;//to determine the state of sensors
	//loop to sure that user enter right choose
	do{
	printf("Sensors set Menu :\n");
	printf("a. Turn off the engine\nb. Set the traffic light color.\nc. Set the room temperature (Temperature Sensor)\nd. Set the engine temperature (Engine Temperature Sensor)\n");
	scanf(" %c",&st);
	printf("\n");
	}while(st!='a' && st!='b' && st!='c' && st!='d' );
	if(st=='b')
	{
		Set_traffic_light();
		Print_Variables();
	}
	else if(st=='c')
	{
		Set_room_temperature();
		Print_Variables();
	}
	else if(st=='d')
	{
		#if  WITH_ENGINE_TEMP_CONTROLLER
		Set_engine_temperature();
		#endif
		Print_Variables();
	}
	else if(st=='a')
	{
		Turn_off();
		state.Engine_state=0;
	}
}
//modify the speed
void Set_traffic_light(void)
{
	char Required_color;
	//loop to sure that user enter right choose
	do{
	printf("Enter sensor read value(G/R/O) :\n");
	scanf(" %c",&Required_color);
	}while(Required_color!='G' && Required_color!='R' && Required_color!='O');
	if(Required_color=='G')
	{
		state.Vehicle_Speed=100;
	}
	else if(Required_color=='R')
	{
		state.Vehicle_Speed=0;
	}
	else if(Required_color=='O')
	{
		state.Vehicle_Speed=30;
		Check_speed();
	}
}
//modify room temperature
void Set_room_temperature(void)
{
	float room_temperature;
	printf("Enter the room temperature :");
	scanf("%f",&room_temperature);
	if(room_temperature<10 || room_temperature>30)
	{
		state.AC=1;
		state.Room_Temperature=20;
	}
	else
	{
		state.AC=0;
	}
}
//modify engine temperature
void Set_engine_temperature(void)
{
	float engine_temperature;
	printf("Enter the room temperature :");
	scanf("%f",&engine_temperature);
	if(engine_temperature<100 || engine_temperature>150)
	{
		state.Engine_Temperature_Controller_State=1;
		state.Engine_Temperature=125;
	}
	else
	{
		state.Engine_Temperature_Controller_State=0;
	}
}
//function to check speed =30
void Check_speed(void)
{
	if(state.Vehicle_Speed==30)
	{
		state.Engine_Temperature_Controller_State=1;
		state.Engine_Temperature = state.Engine_Temperature * (1.25) + 1;
		state.AC=1;
		state.Room_Temperature=state.Room_Temperature*(1.25)+1;
	}
}
//function dispaly the sensor's states
void Print_Variables(void)
{
	printf("Vehicle variables :\n\n");
	printf("Engine state is ");(state.Engine_state==1)?printf("ON\n"):printf("OFF\n");
	printf("AC is ");(state.AC==1)?printf("ON\n"):printf("OFF\n");
	printf("Vehicle Speed = %f Km/h\n",state.Vehicle_Speed);
	printf("Room Temperature = %f C\n",state.Room_Temperature);
	printf("Engine_Temperature_Controller_State is ");(state.Engine_Temperature_Controller_State==1)?printf("ON\n"):printf("OFF\n");
	printf("Engine_Temperature = %f C\n\n",state.Engine_Temperature);
}
