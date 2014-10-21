/*!
 * @file push_switch.c
 * @brief Count up when push button 1 is pushed and show it's counter on LED 
 * @author koturn
 */
/* ========================================================================= *
 * Constants of address                                                      *
 * ========================================================================= */
#define TADR_PIO_PER   ((volatile unsigned int *) 0xfffff400)  /* PIO Enable Register (W) */
#define TADR_PIO_PDR   ((volatile unsigned int *) 0xfffff400)  /* PIO Disable Register (W) */
#define TOFF_PIO_PER   TADR_PIO_PER
#define TOFF_PIO_PDR   TADR_PIO_PDR

#define TADR_PIO_OER   ((volatile unsigned int *) 0xfffff410)  /* PIO Output Enable Register (W) */
#define TADR_PIO_ODR   ((volatile unsigned int *) 0xfffff414)  /* PIO Output Disable Register (W) */
#define TOFF_PIO_OER   TADR_PIO_OER
#define TOFF_PIO_ODR   TADR_PIO_ODR

#define TADR_PIO_SODR  ((volatile unsigned int *) 0xfffff430)  /* Set Output Data Register (W) */
#define TADR_PIO_SOCR  ((volatile unsigned int *) 0xfffff434)  /* Clear Output Data Register (W) */

#define TADR_PMC_PCER  ((volatile unsigned int *) 0xfffffc10)  /* Enable PIO Clock (W) */
#define TMDR_PIO_PDSR  ((volatile unsigned int *) 0xfffff43c)  /* PIO Pin Data Status Register (R) */


/* ========================================================================= *
 * Mask constants                                                            *
 * ========================================================================= */
#define LED1  0x00000001
#define LED2  0x00000002
#define LED3  0x00000004
#define LED4  0x00000008
#define LED_MASK  (LED1 | LED2 | LED3 | LED4)

#define PSW1  0x00000010
#define PSW2  0x00000020
#define PSW_MASK  (PSW1 | PSW2)

#define DSW1  0x00000800
#define DSW2  0x00001000
#define DSW3  0x00002000
#define DSW4  0x00004000
#define DSW_MASK  (DSW1 | DSW2 | DSW3 | DSW4)


/*!
 * @brief Initialize hardware (LED, Push down switches and DIP switches)
 */
void
init(void)
{
  /* Use all LEDs, two Push down switch and all DIP switches */
  *TADR_PIO_PER = LED_MASK | PSW_MASK | DSW_MASK;
  /* LEDs are output */
  *TADR_PIO_OER = LED_MASK;
  /* Push down switch and DIP switches are input */
  *TADR_PIO_ODR = PSW_MASK | DSW_MASK;
  /* Set PIO Clock */
  *TADR_PMC_PCER = 0x04;
}


/*!
 * @brief Light up LEDs
 * @param led_data [in]  Data of LED.
 */
void
led_out(unsigned int led_data)
{
  /* Clear LED connection bit */
  *TADR_PIO_CODR = LED_MASK;
  /* Do not change the other bits except LED connection bits */
  led_data &= LED_MASK;
  /* Write data to LED connection bit */
  *TADR_PIO_SODR = led_data;
}


/*!
 * @brief the entry point of this program
 */
int
main(void)
{
  unsigned int cnt = 0;
  init();
  for (;;) {
    if (!(*TMDR_PIO_PDSR & PSW1)) {
      cnt = cnt < 0x0f ? cnt + 1 : 0;
    }
    led_out(cnt);
    while (*TMDR_PIO_PDSR & PSW1);  /* Wait until PSW1 is released */
  }
  return 0;
}
