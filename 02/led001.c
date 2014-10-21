/*!
 * @file push_switch.c
 * @brief Count up from 0b0000 (0) to 0b1111 (16) and show it on LEDs.
 * @author koturn
 */
/*!
 * @brief Light up LEDs
 * @param [in] led_data  Data of LED.
 */
void
led_out(unsigned int led_data)
{
  /* Clear LED connection bit */
  *((volatile unsigned int *) 0xfffff434) = 0x0000000f;
  /* Do not change values other than LED connection bit */
  led_data = led_data & 0x0000000f;
  /* Write data to LED connection bit */
  *((volatile unsigned int *) 0xfffff430) = led_data;
}


/*!
 * @brief Initialize LEDs
 */
void
led_init(void)
{
  /* PIO Enable Register */
  *((volatile unsigned char *) 0xfffff400) = 0x0000000f;
  /* Output Enable Register */
  *((volatile unsigned char *) 0xfffff410) = 0x0000000f;
}


#define DELAY_LOOP 0x80000L  /* Number of loops */
/*!
 * @brief Wait until count up is end
 */
void
busy_wait(void)
{
  long i;
  for (i = 0; i < DELAY_LOOP; i++);
}


/*!
 * @brief the entry point of this program
 */
int
main(void)
{
  /* Initialize hardware */
  led_init();
  for (;;) {
    int i;
    for (i = 0x00000000; i < 0x00000010; i++) {
      led_out(i);
      busy_wait();
    }
  }
  return 0;
}
