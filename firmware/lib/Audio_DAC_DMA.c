#include <stdint.h>
#include <ti/devices/msp/msp.h>

#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "Audio_DAC_DMA.h"

// volatile int16_t audioBuffer[AUDIO_TOTAL_SIZE] = {
//     0,     13,    25,    38,    50,    63,    75,    88,    100,   113,   126,
//     138,   151,   163,   176,   188,   201,   213,   226,   238,   251,   263,
//     275,   288,   300,   313,   325,   338,   350,   362,   375,   387,   399,
//     412,   424,   436,   449,   461,   473,   485,   497,   510,   522,   534,
//     546,   558,   570,   582,   594,   606,   618,   630,   642,   654,   666,
//     678,   690,   701,   713,   725,   737,   748,   760,   772,   783,   795,
//     807,   818,   830,   841,   852,   864,   875,   887,   898,   909,   920,
//     932,   943,   954,   965,   976,   987,   998,   1009,  1020,  1031,  1042,
//     1052,  1063,  1074,  1085,  1095,  1106,  1116,  1127,  1137,  1148,  1158,
//     1168,  1179,  1189,  1199,  1209,  1219,  1229,  1239,  1249,  1259,  1269,
//     1279,  1289,  1299,  1308,  1318,  1328,  1337,  1347,  1356,  1365,  1375,
//     1384,  1393,  1402,  1411,  1421,  1430,  1439,  1447,  1456,  1465,  1474,
//     1483,  1491,  1500,  1508,  1517,  1525,  1533,  1542,  1550,  1558,  1566,
//     1574,  1582,  1590,  1598,  1606,  1614,  1621,  1629,  1637,  1644,  1652,
//     1659,  1666,  1674,  1681,  1688,  1695,  1702,  1709,  1716,  1723,  1729,
//     1736,  1743,  1749,  1756,  1762,  1769,  1775,  1781,  1787,  1793,  1799,
//     1805,  1811,  1817,  1823,  1828,  1834,  1840,  1845,  1850,  1856,  1861,
//     1866,  1871,  1876,  1881,  1886,  1891,  1896,  1901,  1905,  1910,  1914,
//     1919,  1923,  1927,  1932,  1936,  1940,  1944,  1948,  1951,  1955,  1959,
//     1962,  1966,  1969,  1973,  1976,  1979,  1983,  1986,  1989,  1992,  1994,
//     1997,  2000,  2003,  2005,  2008,  2010,  2012,  2015,  2017,  2019,  2021,
//     2023,  2025,  2027,  2028,  2030,  2032,  2033,  2035,  2036,  2037,  2038,
//     2039,  2040,  2041,  2042,  2043,  2044,  2045,  2045,  2046,  2046,  2046,
//     2047,  2047,  2047,  2047,  2047,  2047,  2047,  2046,  2046,  2046,  2045,
//     2045,  2044,  2043,  2042,  2041,  2040,  2039,  2038,  2037,  2036,  2035,
//     2033,  2032,  2030,  2028,  2027,  2025,  2023,  2021,  2019,  2017,  2015,
//     2012,  2010,  2008,  2005,  2003,  2000,  1997,  1994,  1992,  1989,  1986,
//     1983,  1979,  1976,  1973,  1969,  1966,  1962,  1959,  1955,  1951,  1948,
//     1944,  1940,  1936,  1932,  1927,  1923,  1919,  1914,  1910,  1905,  1901,
//     1896,  1891,  1886,  1881,  1876,  1871,  1866,  1861,  1856,  1850,  1845,
//     1840,  1834,  1828,  1823,  1817,  1811,  1805,  1799,  1793,  1787,  1781,
//     1775,  1769,  1762,  1756,  1749,  1743,  1736,  1729,  1723,  1716,  1709,
//     1702,  1695,  1688,  1681,  1674,  1666,  1659,  1652,  1644,  1637,  1629,
//     1621,  1614,  1606,  1598,  1590,  1582,  1574,  1566,  1558,  1550,  1542,
//     1533,  1525,  1517,  1508,  1500,  1491,  1483,  1474,  1465,  1456,  1447,
//     1439,  1430,  1421,  1411,  1402,  1393,  1384,  1375,  1365,  1356,  1347,
//     1337,  1328,  1318,  1308,  1299,  1289,  1279,  1269,  1259,  1249,  1239,
//     1229,  1219,  1209,  1199,  1189,  1179,  1168,  1158,  1148,  1137,  1127,
//     1116,  1106,  1095,  1085,  1074,  1063,  1052,  1042,  1031,  1020,  1009,
//     998,   987,   976,   965,   954,   943,   932,   920,   909,   898,   887,
//     875,   864,   852,   841,   830,   818,   807,   795,   783,   772,   760,
//     748,   737,   725,   713,   701,   690,   678,   666,   654,   642,   630,
//     618,   606,   594,   582,   570,   558,   546,   534,   522,   510,   497,
//     485,   473,   461,   449,   436,   424,   412,   399,   387,   375,   362,
//     350,   338,   325,   313,   300,   288,   275,   263,   251,   238,   226,
//     213,   201,   188,   176,   163,   151,   138,   126,   113,   100,   88,
//     75,    63,    50,    38,    25,    13,    0,     -13,   -25,   -38,   -50,
//     -63,   -75,   -88,   -100,  -113,  -126,  -138,  -151,  -163,  -176,  -188,
//     -201,  -213,  -226,  -238,  -251,  -263,  -275,  -288,  -300,  -313,  -325,
//     -338,  -350,  -362,  -375,  -387,  -399,  -412,  -424,  -436,  -449,  -461,
//     -473,  -485,  -497,  -510,  -522,  -534,  -546,  -558,  -570,  -582,  -594,
//     -606,  -618,  -630,  -642,  -654,  -666,  -678,  -690,  -701,  -713,  -725,
//     -737,  -748,  -760,  -772,  -783,  -795,  -807,  -818,  -830,  -841,  -852,
//     -864,  -875,  -887,  -898,  -909,  -920,  -932,  -943,  -954,  -965,  -976,
//     -987,  -998,  -1009, -1020, -1031, -1042, -1052, -1063, -1074, -1085, -1095,
//     -1106, -1116, -1127, -1137, -1148, -1158, -1168, -1179, -1189, -1199, -1209,
//     -1219, -1229, -1239, -1249, -1259, -1269, -1279, -1289, -1299, -1308, -1318,
//     -1328, -1337, -1347, -1356, -1365, -1375, -1384, -1393, -1402, -1411, -1421,
//     -1430, -1439, -1447, -1456, -1465, -1474, -1483, -1491, -1500, -1508, -1517,
//     -1525, -1533, -1542, -1550, -1558, -1566, -1574, -1582, -1590, -1598, -1606,
//     -1614, -1621, -1629, -1637, -1644, -1652, -1659, -1666, -1674, -1681, -1688,
//     -1695, -1702, -1709, -1716, -1723, -1729, -1736, -1743, -1749, -1756, -1762,
//     -1769, -1775, -1781, -1787, -1793, -1799, -1805, -1811, -1817, -1823, -1828,
//     -1834, -1840, -1845, -1850, -1856, -1861, -1866, -1871, -1876, -1881, -1886,
//     -1891, -1896, -1901, -1905, -1910, -1914, -1919, -1923, -1927, -1932, -1936,
//     -1940, -1944, -1948, -1951, -1955, -1959, -1962, -1966, -1969, -1973, -1976,
//     -1979, -1983, -1986, -1989, -1992, -1994, -1997, -2000, -2003, -2005, -2008,
//     -2010, -2012, -2015, -2017, -2019, -2021, -2023, -2025, -2027, -2028, -2030,
//     -2032, -2033, -2035, -2036, -2037, -2038, -2039, -2040, -2041, -2042, -2043,
//     -2044, -2045, -2045, -2046, -2046, -2046, -2047, -2047, -2047, -2047, -2047,
//     -2047, -2047, -2046, -2046, -2046, -2045, -2045, -2044, -2043, -2042, -2041,
//     -2040, -2039, -2038, -2037, -2036, -2035, -2033, -2032, -2030, -2028, -2027,
//     -2025, -2023, -2021, -2019, -2017, -2015, -2012, -2010, -2008, -2005, -2003,
//     -2000, -1997, -1994, -1992, -1989, -1986, -1983, -1979, -1976, -1973, -1969,
//     -1966, -1962, -1959, -1955, -1951, -1948, -1944, -1940, -1936, -1932, -1927,
//     -1923, -1919, -1914, -1910, -1905, -1901, -1896, -1891, -1886, -1881, -1876,
//     -1871, -1866, -1861, -1856, -1850, -1845, -1840, -1834, -1828, -1823, -1817,
//     -1811, -1805, -1799, -1793, -1787, -1781, -1775, -1769, -1762, -1756, -1749,
//     -1743, -1736, -1729, -1723, -1716, -1709, -1702, -1695, -1688, -1681, -1674,
//     -1666, -1659, -1652, -1644, -1637, -1629, -1621, -1614, -1606, -1598, -1590,
//     -1582, -1574, -1566, -1558, -1550, -1542, -1533, -1525, -1517, -1508, -1500,
//     -1491, -1483, -1474, -1465, -1456, -1447, -1439, -1430, -1421, -1411, -1402,
//     -1393, -1384, -1375, -1365, -1356, -1347, -1337, -1328, -1318, -1308, -1299,
//     -1289, -1279, -1269, -1259, -1249, -1239, -1229, -1219, -1209, -1199, -1189,
//     -1179, -1168, -1158, -1148, -1137, -1127, -1116, -1106, -1095, -1085, -1074,
//     -1063, -1052, -1042, -1031, -1020, -1009, -998,  -987,  -976,  -965,  -954,
//     -943,  -932,  -920,  -909,  -898,  -887,  -875,  -864,  -852,  -841,  -830,
//     -818,  -807,  -795,  -783,  -772,  -760,  -748,  -737,  -725,  -713,  -701,
//     -690,  -678,  -666,  -654,  -642,  -630,  -618,  -606,  -594,  -582,  -570,
//     -558,  -546,  -534,  -522,  -510,  -497,  -485,  -473,  -461,  -449,  -436,
//     -424,  -412,  -399,  -387,  -375,  -362,  -350,  -338,  -325,  -313,  -300,
//     -288,  -275,  -263,  -251,  -238,  -226,  -213,  -201,  -188,  -176,  -163,
//     -151,  -138,  -126,  -113,  -100,  -88,   -75,   -63,   -50,   -38,   -25,
//     -13};

// volatile int16_t audioBuffer[AUDIO_TOTAL_SIZE] = {0};

volatile bool refillPing = true;
volatile bool refillPong = true;;
volatile int16_t audioBuffer[AUDIO_TOTAL_SIZE];

#define EVENT_ROUTE_1 1 // We will use Event Route 1 for the hardware trigger

void TimerG0_32kHz_EventArm(void) {
  // 1. Release the Timer from Reset (Do NOT assert it)
  TIMG0->GPRCM.RSTCTL =
      (GPTIMER_RSTCTL_KEY_UNLOCK_W | GPTIMER_RSTCTL_RESETSTKYCLR_CLR);

  TIMG0->GPRCM.PWREN =
      (GPTIMER_PWREN_KEY_UNLOCK_W | GPTIMER_PWREN_ENABLE_ENABLE);
  Clock_Delay(24);

  // 2. Clock Configuration (SYSCLK for TIMG0 in PD0 is 40 MHz)
  TIMG0->CLKSEL = 0x08;      // Select SYSCLK
  TIMG0->CLKDIV = 0x00;      // Divide by 1
  TIMG0->COMMONREGS.CPS = 0; // Prescale = 1 (Value + 1)

  // 3. Set the Period for 32,000 Hz using a 40 MHz clock!
  // 40,000,000 / 32,000 = 1250. LOAD = 1250 - 1 = 1249.
  TIMG0->COUNTERREGS.LOAD = 1249;

  // 4. Configure Event Publishing
  TIMG0->CPU_INT.IMASK = 0;
  TIMG0->GEN_EVENT0.IMASK = GPTIMER_GEN_EVENT0_IMASK_Z_SET;
  TIMG0->FPUB_0 = EVENT_ROUTE_1;

  // 5. Start the Timer in PERIODIC (Repeat) Mode
  TIMG0->COMMONREGS.CCLKCTL = 1;
  TIMG0->COUNTERREGS.CTRCTL =
      (GPTIMER_CTRCTL_EN_ENABLED | GPTIMER_CTRCTL_CM_DOWN |
       GPTIMER_CTRCTL_REPEAT_REPEAT_1); // Bit 4: REPEAT Enable
}

void DAC0_Init(void) {
  // 1. Release the DAC from Reset (Do NOT assert it)
  DAC0->GPRCM.RSTCTL =
      (DAC12_RSTCTL_KEY_UNLOCK_W | DAC12_RSTCTL_RESETSTKYCLR_CLR);

  DAC0->GPRCM.PWREN = (DAC12_PWREN_KEY_UNLOCK_W | DAC12_PWREN_ENABLE_ENABLE);
  Clock_Delay(24);

  // 2. Configure PA15 for analog output
  IOMUX->SECCFG.PINCM[PA15INDEX] = 0x00000080;

  // 3. Configure DAC Control Registers
  // Enable DAC, set to 12-bit resolution, and set Data Format to Two's
  // Complement
  DAC0->CTL0 = (DAC12_CTL0_ENABLE_SET | DAC12_CTL0_RES__12BITS |
                DAC12_CTL0_DFM_TWOS_COMP);

  // 4. Enable the output amplifier and route it to the OUT0 pin (PA15)
  DAC0->CTL1 = (DAC12_CTL1_AMPEN_ENABLE | DAC12_CTL1_OPS_OUT0);
}

void DMA_Init_CircularPingPong() {
  // Note: The MSPM0 DMA block does not have a local GPRCM power register
  // like the timers or DAC. It is managed by SYSCTL.

  // 1. Ensure Channel 0 is disabled before modifying registers
  DMA->DMACHAN[0].DMACTL &= ~DMA_DMACTL_DMAEN_MASK;

  // 2. Set Addresses and Transfer Size
  DMA->DMACHAN[0].DMASA = (uint32_t)audioBuffer;
  DMA->DMACHAN[0].DMADA =
      (uint32_t)&(DAC0->DATA0); // Destination: DAC Data register
  DMA->DMACHAN[0].DMASZ = AUDIO_TOTAL_SIZE;

  // 3. Trigger Configuration (Subscribe to TimerG0 via Event Route 1)
  // Connect Event Route 1 into DMA Subscriber Port 0
  DMA->FSUB_0 = EVENT_ROUTE_1;

  // Tell DMA Channel 0 to trigger whenever Subscriber Port 0 ticks
  DMA->DMATRIG[0].DMATCTL = DMA_GENERIC_SUB0_TRIG;

  // 4. Configure the Channel Control (DMACTL) Register
  DMA->DMACHAN[0].DMACTL =
      DMA_DMACTL_DMAPREIRQ_PREIRQ_HALF | // Automatically flag at exactly 50%
      DMA_DMACTL_DMASRCWDTH_HALF |       // 16-bit source read
      DMA_DMACTL_DMADSTWDTH_HALF |       // 16-bit destination write
      DMA_DMACTL_DMASRCINCR_INCREMENT |  // Increment source array pointer
      DMA_DMACTL_DMADSTINCR_UNCHANGED |  // DAC address never changes
      DMA_DMACTL_DMATM_RPTSNGL |         // Repeated Single Transfer
      DMA_DMACTL_DMAEN_ENABLE; // Enable Channel(Enable Full Interrupt)
  DMA_DMACTL_DMAEN_ENABLE;     // Enable Channel

  // 5. Enable DMA CPU Interrupts
  // Enable the full transfer interrupt (DMACH0) and the early halfway interrupt
  // (PREIRQ)
  DMA->CPU_INT.IMASK =
      (DMA_CPU_INT_IMASK_DMACH0_SET | DMA_CPU_INT_IMASK_PREIRQCH0_SET);

  // Enable DMA Interrupt in Cortex-M0+ NVIC
  NVIC_EnableIRQ(DMA_INT_IRQn);
}

// ISR Name must match the vector table in your TI startup file
void DMA_IRQHandler(void) {
  // Read the Interrupt Index (this automatically clears the flag)
  uint32_t pending_irq = DMA->CPU_INT.IIDX;

  if (pending_irq == DMA_CPU_INT_IIDX_STAT_PREIRQCH0) {
    // Halfway mark reached (Early Interrupt).
    // DMA is now actively reading the Pong half.
    refillPing = true;
  } else if (pending_irq == DMA_CPU_INT_IIDX_STAT_DMACH0) {
    // Transfer complete (Full Interrupt).
    // Pointer wrapped around. DMA is now actively reading the Ping half.
    refillPong = true;
  }
}