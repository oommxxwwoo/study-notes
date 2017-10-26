#define ADC_BA    0xB800A000  /*!< ADC Control */
#define REG_ADC_CTL       (ADC_BA+0x000) /*!< ADC Contrl */
#define REG_ADC_CONF      (ADC_BA+0x004) /*!< ADC Configure */
#define REG_ADC_IER       (ADC_BA+0x008) /*!< ADC Interrupt Enable Register */
#define REG_ADC_ISR       (ADC_BA+0x00C) /*!< ADC Interrupt Status Register */
#define REG_ADC_WKISR     (ADC_BA+0x010) /*!< ADC Wake Up Interrupt Status Register */
#define REG_ADC_XYDATA    (ADC_BA+0x020) /*!< ADC Touch XY Pressure Data */
#define REG_ADC_ZDATA     (ADC_BA+0x024) /*!< ADC Touch Z Pressure Data */
#define REG_ADC_DATA      (ADC_BA+0x028) /*!< ADC Normal Conversion Data */
#define REG_ADC_VBADATA   (ADC_BA+0x02C) /*!< ADC Battery Detection Data */
#define REG_ADC_KPDATA    (ADC_BA+0x030) /*!< ADC Key Pad Data */
#define REG_ADC_SELFDATA  (ADC_BA+0x034) /*!< ADC Self-Test Data */
#define REG_ADC_XYSORT0   (ADC_BA+0x1F4) /*!< ADC Touch XY Position Mean Value Sort 0 */
#define REG_ADC_XYSORT1   (ADC_BA+0x1F8) /*!< ADC Touch XY Position Mean Value Sort 1 */
#define REG_ADC_XYSORT2   (ADC_BA+0x1FC) /*!< ADC Touch XY Position Mean Value Sort 2 */
#define REG_ADC_XYSORT3   (ADC_BA+0x200) /*!< ADC Touch XY Position Mean Value Sort 3 */
#define REG_ADC_ZSORT0    (ADC_BA+0x204) /*!< ADC Touch Z Pressure Mean Value Sort 0 */
#define REG_ADC_ZSORT1    (ADC_BA+0x208) /*!< ADC Touch Z Pressure Mean Value Sort 1 */
#define REG_ADC_ZSORT2    (ADC_BA+0x20C) /*!< ADC Touch Z Pressure Mean Value Sort 2 */
#define REG_ADC_ZSORT3    (ADC_BA+0x210) /*!< ADC Touch Z Pressure Mean Value Sort 3 */
#define REG_ADC_MTMULCK   (ADC_BA+0x220) /*!< ADC Manual Test Mode Unlock */
#define REG_ADC_MTCONF    (ADC_BA+0x224) /*!< ADC Manual Test Mode Configure */
#define REG_ADC_MTCON     (ADC_BA+0x228) /*!< ADC Manual Test Mode Control */
#define REG_ADC_ADCAII    (ADC_BA+0x22C) /*!< ADC Analog Interface Information */
#define REG_ADC_ADCAIIRLT (ADC_BA+0x230) /*!< ADC Analog Interface Information Result */


/*---------------------------------------------------------------------------------------------------------*/
/* ADC_CTL constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define ADC_CTL_ADEN            0x00000001  /*!< ADC Power Control */
#define ADC_CTL_VBGEN       0x00000002  /*!< ADC Internal Bandgap Power Control */
#define ADC_CTL_PWKPEN      0x00000004  /*!< ADC Keypad Power Enable Control */
#define ADC_CTL_MST             0x00000100  /*!< Menu Start Conversion */
#define ADC_CTL_PEDEEN      0x00000200  /*!< Pen Down Event Enable */
#define ADC_CTL_WKPEN       0x00000400  /*!< Keypad Press Wake Up Enable */
#define ADC_CTL_WKTEN       0x00000800  /*!< Touch Wake Up Enable */
#define ADC_CTL_WMSWCH      0x00010000  /*!< Wire Mode Switch For 5-Wire/4-Wire Configuration */

/*---------------------------------------------------------------------------------------------------------*/
/* ADC_CONF constant definitions                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
#define ADC_CONF_TEN                0x00000001  /*!< Touch Enable */
#define ADC_CONF_ZEN                0x00000002  /*!< Press Enable */
#define ADC_CONF_NACEN          0x00000004  /*!< Normal AD Conversion Enable */
#define ADC_CONF_VBATEN         0x00000100  /*!< Voltage Battery Enable */
#define ADC_CONF_KPCEN          0x00000200  /*!< Keypad Press Conversion Enable */
#define ADC_CONF_SELFTEN        0x00000400  /*!< Selft Test Enable */
#define ADC_CONF_DISTMAVEN  (1<<20)     /*!< Display T Mean Average Enable */
#define ADC_CONF_DISZMAVEN  (1<<21)     /*!< Display Z Mean Average Enable */
#define ADC_CONF_HSPEED         (1<<22)     /*!< High Speed Enable */

#define ADC_CONF_CHSEL_Pos  3            /*!< Channel Selection Position */
#define ADC_CONF_CHSEL_Msk  (7<<3)       /*!< Channel Selection Mask */
#define ADC_CONF_CHSEL_VBT  (0<<3)       /*!< ADC input channel select VBT */
#define ADC_CONF_CHSEL_VHS  (1<<3)       /*!< ADC input channel select VHS */
#define ADC_CONF_CHSEL_A2       (2<<3)       /*!< ADC input channel select A2 */
#define ADC_CONF_CHSEL_A3       (3<<3)       /*!< ADC input channel select A3 */
#define ADC_CONF_CHSEL_YM       (4<<3)       /*!< ADC input channel select YM */
#define ADC_CONF_CHSEL_YP       (5<<3)       /*!< ADC input channel select YP */
#define ADC_CONF_CHSEL_XM       (6<<3)       /*!< ADC input channel select XM */
#define ADC_CONF_CHSEL_XP       (7<<3)       /*!< ADC input channel select XP */

/*---------------------------------------------------------------------------------------------------------*/
/* ADC_IER constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define ADC_IER_MIEN                0x00000001  /*!< Menu Interrupt Enable */
#define ADC_IER_KPEIEN          0x00000002  /*!< Keypad Press Event Interrupt Enable */
#define ADC_IER_PEDEIEN         0x00000004  /*!< Pen Down Even Interrupt Enable */
#define ADC_IER_WKTIEN          0x00000008  /*!< Wake Up Touch Interrupt Enable */
#define ADC_IER_WKPIEN          0x00000010  /*!< Wake Up Keypad Press Interrupt Enable */
#define ADC_IER_KPUEIEN         0x00000020  /*!< Keypad Press Up Event Interrupt Enable */
#define ADC_IER_PEUEIEN         0x00000040  /*!< Pen Up Event Interrupt Enable */

/*---------------------------------------------------------------------------------------------------------*/
/* ADC_ISR constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define ADC_ISR_MF              0x00000001  /*!< Menu Complete Flag */
#define ADC_ISR_KPEF            0x00000002  /*!< Keypad Press Event Flag */
#define ADC_ISR_PEDEF           0x00000004  /*!< Pen Down Event Flag */
#define ADC_ISR_KPUEF           0x00000008  /*!< Keypad Press Up Event Flag */
#define ADC_ISR_PEUEF           0x00000010  /*!< Pen Up Event Flag */
#define ADC_ISR_TF              0x00000100  /*!< Touch Conversion Finish */
#define ADC_ISR_ZF              0x00000200  /*!< Press Conversion Finish */
#define ADC_ISR_NACF            0x00000400  /*!< Normal AD Conversion Finish */
#define ADC_ISR_VBF             0x00000800  /*!< Voltage Battery Conversion Finish */
#define ADC_ISR_KPCF            0x00001000  /*!< Keypad Press Conversion Finish */
#define ADC_ISR_SELFTF      0x00002000  /*!< Self-Test Conversion Finish */
#define ADC_ISR_INTKP           0x00010000  /*!< Interrupt Signal For Keypad Detection */
#define ADC_ISR_INTTC           0x00020000  /*!< Interrupt Signal For Touch Screen Touching Detection */


#define REG_CLK_PCLKEN1	0xB000021C
#define REG_SYS_APBIPRST1	0xB0000068
#define REG_CLK_DIVCTL7		0xB000023C


//以上是可能用到的宏

//以下为uboot中的宏函数
/*
__raw_writel(val, reg_addr)写寄存器
__raw_readl(reg_addr)读寄存器
*/

/*
说明:

1、以下函数为ADC的测试函数,参考: 《 NUC970编程指南.pdf 3.5.3章节》编写。
2、硬件nuc972df62y芯片第55管脚,即ADC0接到外部3.3v。芯片第65管脚,即Vref接到GND。
3、程序的步骤如下：配置ADC时钟,开启ADC,配置ADC通道,开启转换,【延时读取数据(之前未使用IER,ISR寄存器,直接延时读取的)】,现在改成与《NUC970编程指南》里面完全相同的步骤。
4、现象:程序每次都正常运行,可是读出的电压都很低。

运行截图:
select channel = 0 ,eg  0:VBT(A0), 1:VHS(A1), 2:A2, 3:A3, 4:YM(A4), 5:YP(A5), 6:XM(A6),7:XP(A7)
Waiting for Normal mode Interrupt
DATA=0x00000213,voltage=0.427v
U-Boot>


*/


void board_adc(char num)
{

	unsigned int data,n;
	unsigned int d1,d2,val=0;

	/* Enable ADC engine clock */
    __raw_writel(1<<24, REG_CLK_PCLKEN1);

      /* ADC Engine Clock is set to 1 MB/S */
    __raw_writel( __raw_readl(REG_CLK_DIVCTL7) & ~((0x3<<19)|(0x7<<16)), REG_CLK_DIVCTL7);
    __raw_writel( (0x0<<19)|(11<<16), REG_CLK_DIVCTL7);

      /* Enable ADC Power */
    __raw_writel( ADC_CTL_ADEN, REG_ADC_CTL);

	
    printf("select channel = %d ,eg  0:VBT(A0), 1:VHS(A1), 2:A2, 3:A3, 4:YM(A4), 5:YP(A5), 6:XM(A6),7:XP(A7)\n", num);

	switch(num)
	{
		case  0 : val=0; break;
		case  1 : val=1; break;
		case  2 : val=2; break;
		case  3 : val=3; break;
		case  4 : val=4; break;
		case  5 : val=5; break;
		case  6 : val=6; break;
		case  7 : val=7; break;
		default :
			printf("used val = 0\n");
			val = 0;
			break;
	}
	
    __raw_writel(__raw_readl(REG_ADC_CONF)  | (ADC_CONF_NACEN | val<<3 | (3<<6) | (1<<22)), REG_ADC_CONF); 
	

	__raw_writel(ADC_ISR_MF | ADC_ISR_NACF, REG_ADC_ISR); 
	
	/* narmal_test interrupt mode */
	
	__raw_writel(__raw_readl(REG_ADC_IER)  |(ADC_IER_MIEN), REG_ADC_IER); 
		
	
	do{

		__raw_writel(__raw_readl(REG_ADC_CTL)  | ADC_CTL_MST, REG_ADC_CTL); 
		
		printf("Waiting for Normal mode Interrupt\n");
		//udelay(10000);//10ms
		
		while(!(__raw_readl(REG_ADC_ISR) & ADC_ISR_MF));
		
		__raw_writel(ADC_ISR_MF, REG_ADC_ISR); 

		if(__raw_readl(REG_ADC_ISR) & ADC_ISR_NACF)
		{
			data=__raw_readl(rREG_DATA);
			n=(33*data*100)>>12;
			d1=n/1000;
			d2=n%1000;
			printf("DATA=0x%08x,voltage=%d.%dv\n",data,d1,d2);
		}
		else
			printf("interrupt error\n");
	}while(0);
}
