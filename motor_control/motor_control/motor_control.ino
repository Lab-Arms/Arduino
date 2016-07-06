#include <Servo.h>

Servo servo[3];
int pins[] = {11, 9, 5};
int initial_angles[] = {90, 90, 180};
int int_angles[3];
char buffer[5];

int limit (int num)
{
	if (num > 180)
		return 180;
	if (num < 0)
		return 0;
	return num;
}

void relative ()
{
	for (int i = 0; i < 3; i++)
	{
		Serial.readBytes(buffer, 4);
    int_angles[i] = limit(int_angles[i] + atoi(buffer));
		servo[i].write(int_angles[i]);
	}
}

void absolute ()
{
	for (int i = 0; i < 3; i++)
	{
		Serial.readBytes(buffer, 3);
		int_angles[i] = limit(atoi(buffer));
    servo[i].write(int_angles[i]);
	}
}

void initial_pos ()
{
	for (int i = 0; i < 3; i++)
	{
		int_angles[i] = initial_angles[i];
		servo[i].write(int_angles[i]);
	}
}

void setup()
{
	for (int i = 0; i < 3; i++)
	{
		servo[i].attach(pins[i]);
		servo[i].write(initial_angles[i]);
		int_angles[i] = initial_angles[i];
	}
	Serial.begin(9600);
	while (!Serial) {};
}

void loop()
{
	if (Serial.available())
	{
		char c = Serial.read();
		switch (c)
		{
			case 'A': // relative movement
			absolute ();
			break;
			case 'B': // absolute movement
			relative ();
			break;
			case 'C': // initial position
			initial_pos ();
			default:
			;
		}
	}
}
