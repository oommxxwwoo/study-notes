#include <common.h>
#include <asm/types.h>
#include <asm-generic/gpio.h>
#include "../drivers/gpio/nuc970_gpio.h"

#include "../common/tmr_func.h"


#define LED_1_YELLOW     GPIO_PD12
#define LED_2_GREEN        GPIO_PD13
#define LED_3_RED            GPIO_PD14

#define KEY_ROW_1 		GPIO_PA4
#define KEY_ROW_2 		GPIO_PA5
#define KEY_ROW_3 		GPIO_PA6

#define KEY_COL_1 		GPIO_PA8
#define KEY_COL_2 		GPIO_PA9


#define WDT_GPIO             LED_1_YELLOW


enum
{
	ON = 0,
	OFF ,	

};




typedef void (*func)(void);
struct tmr_t
{
  u16 interval;
  u32 tick;
  func function;
};


void feed_wdt(void)
{
	static u8 state = 0;
	
	if(state) gpio_direction_output(WDT_GPIO,ON); else gpio_direction_output(WDT_GPIO,OFF);
	state = state ? 0 : 1;
}

enum{NO_KEY = 0,HAVE_KEY,RELAY_KEY};
struct bit_t
{
	u8 bit0 : 1;
	u8 bit1 : 1;
	u8 bit2 : 1;
	u8 bit3 : 1;
	u8 bit4 : 1;
	u8 bit5 : 1;	
	u8 bit6 : 1;
	u8 bit7 : 1;	
};

union value_bit_t
{
	struct bit_t bitcon;
	u8 value;
};

union value_bit_t key_value;
void key_and_led(void)
{
	static u8 state = 0;
	static union value_bit_t real_key_value;
	union value_bit_t tmp_key_value;
	
	switch(state)
	{
		case NO_KEY:
			if(gpio_get_value(KEY_ROW_1) || gpio_get_value(KEY_ROW_2) || gpio_get_value(KEY_ROW_3))
			{
				real_key_value.bitcon.bit0 = gpio_get_value(KEY_ROW_1) ;
				real_key_value.bitcon.bit1 = gpio_get_value(KEY_ROW_2) ;
				real_key_value.bitcon.bit2 = gpio_get_value(KEY_ROW_3) ;
				real_key_value.value = real_key_value.value & 0x07;
				state = HAVE_KEY;
			}
			break;
		case HAVE_KEY:
			if(gpio_get_value(KEY_ROW_1) || gpio_get_value(KEY_ROW_2) || gpio_get_value(KEY_ROW_3))
			{
				tmp_key_value.bitcon.bit0 = gpio_get_value(KEY_ROW_1) ;
				tmp_key_value.bitcon.bit1 = gpio_get_value(KEY_ROW_2) ;
				tmp_key_value.bitcon.bit2 = gpio_get_value(KEY_ROW_3) ;
				tmp_key_value.value = tmp_key_value.value & 0x07;
				
				if(tmp_key_value.value == real_key_value.value)
					state = RELAY_KEY;
			}
			else
				state = NO_KEY;
			
			break;
		
		case RELAY_KEY:
			if(gpio_get_value(KEY_ROW_1) || gpio_get_value(KEY_ROW_2) || gpio_get_value(KEY_ROW_3))
				;
			else
			{
				key_value.value = real_key_value.value;
				state = NO_KEY;	
			}
		
	}

	
}

void bsp_key_init(void)
{

	gpio_request(KEY_ROW_1,NULL);
	gpio_direction_input(KEY_ROW_1);

	gpio_request(KEY_ROW_2,NULL);
	gpio_direction_input(KEY_ROW_2);

	gpio_request(KEY_ROW_3,NULL);
	gpio_direction_input(KEY_ROW_3);

	gpio_request(KEY_COL_1,NULL);
	gpio_direction_input(KEY_COL_1);

	gpio_request(KEY_COL_2,NULL);
	gpio_direction_input(KEY_COL_2);

}



struct tmr_t tmr_handle_func[] =
{
	{
	  .interval = 2,
	  .tick = 0,
	  .function = feed_wdt,
		
	},
	
	{
	  .interval = 5,
	  .tick = 0,
	  .function = key_and_led,
		
	},
	
};


void tmr_handle(u32 _systick)
{
	u8 i = 0;
	for(; i < sizeof(tmr_handle_func)/sizeof(tmr_handle_func[0]) ; i++)
	{
		if(tmr_handle_func[i].interval <=  _systick - tmr_handle_func[i].tick)
		{
			tmr_handle_func[i].tick = _systick;
			
			if(tmr_handle_func[i].function)
				tmr_handle_func[i].function();
		}
	}
	
}

	

