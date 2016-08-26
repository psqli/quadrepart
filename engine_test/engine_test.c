/*
 * quadrepart, A simple quadcopter control system
 * Copyright (C) 2016  Ricardo Biehl Pasquali <rbpoficial@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <Servo.h>

/* Time in miliseconds */
#define TIMER_EXPIRE_TIME 500

typedef struct {
	Servo engine;
	int pin;
	int value;
} engine_t;

/* Engine control pins need to be PWM! */
engine_t engine[4] = {
	{ .pin = 3 },
	{ .pin = 5 },
	{ .pin = 6 },
	{ .pin = 9 },
};

unsigned long last_time = 0;
unsigned long current_time = 0;

/**
 * @p engine_id  The engine ID that user has inputted
 * @p value  A value between 0-179 that user has inputted
 */
static int
read_from_terminal(int *engine_id, int *value)
{
	int i;
	char tmp_str[32];

	if(!Serial.available())
		return -1;

	for(i = 0; i < 32 || tmp_str[i] == '\n'; i++)
	{
		
	}
}

void
setup(void)
{
	int i;

	Serial.begin(9600);

	for(i = 0; i < 4; i++)
	{
		engine[i].value = 0;
		engine[i].engine.attach(engine[i].pin);
	}

	/* Wait for 5 seconds to begin the loop() */
	Serial.println("Waiting for 5 seconds ...");
	delay(5000);
}

void
loop(void)
{
	int i;
	/* Variables to put result of terminal input */
	int engine_id = 0;
	int value = 0;

	while(1)
	{
		if(read_from_terminal(&engine_id, &value) == 0)
			engine[engine_id].value = value;

		for(i = 0; i < 4; i++)
			engine[i].engine.write(engine[i].value);
	
		/* Show some info each TIMER_EXPIRE_TIME miliseconds */
		current_time = millis();
		if(current_time > last_time + TIMER_EXPIRE_TIME)
		{
			/* None yet :-) */
			Serial.print("Ok");
		}
	}
}
