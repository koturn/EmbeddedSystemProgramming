#ifndef CONSTANT_H
#define CONSTANT_H


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


#endif  /* CONSTANT_H */
