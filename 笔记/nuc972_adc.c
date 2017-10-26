void board_version_adc(char num)
{

	unsigned int data,n;
	unsigned int d1,d2,val=0;

	/* Enable ADC engine clock */
	writel(readl(REG_CLK_PCLKEN1) | (1<<24), REG_CLK_PCLKEN1);  

	/* ADC Engine Clock is set to 1 MB/S */
	//writel( readl(REG_CLK_DIVCTL7) & ~((0x3<<19)|(0x7<<16)), REG_CLK_DIVCTL7);
	//writel( (0x0<<19)|(11<<16), REG_CLK_DIVCTL7);

	/* Enable ADC Power */
	writel( ADC_CTL_ADEN, REG_ADC_CTL);

	
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
	
	writel((readl(REG_ADC_CONF)  & ~ADC_CONF_CHSEL_Msk)  | (ADC_CONF_NACEN | val<<3 ), REG_ADC_CONF); 
      //writel((readl(REG_ADC_CONF)  & ~ADC_CONF_CHSEL_Msk)  | (ADC_CONF_NACEN | val<<3 | (1<<22)), REG_ADC_CONF); 
 
	writel(ADC_ISR_MF | ADC_ISR_NACF  , REG_ADC_ISR); //ADC_ISR_VBF//clear bit

	/* narmal_test interrupt mode */

	//writel(readl(REG_ADC_IER)  |(ADC_IER_MIEN), REG_ADC_IER); 
		
	
	do{

              printf("adc isr : 0x%08x \n",readl(REG_ADC_ISR));
		//writel(readl(REG_ADC_CTL)  | ADC_CTL_MST, REG_ADC_CTL); 
		writel( ADC_CTL_ADEN | ADC_CTL_MST, REG_ADC_CTL); 
		printf("Waiting for Normal mode Interrupt\n");
		//udelay(100);//10ms

		printf("adc ctl : 0x%08x \n",readl(REG_ADC_CTL));
		printf("adc conf : 0x%08x \n",readl(REG_ADC_CONF));
		
		udelay(10000);//10ms

		printf("adc isr : 0x%08x \n",readl(REG_ADC_ISR));
		
		//while(!(readl(REG_ADC_ISR) & ADC_ISR_MF));
		
		//writel(ADC_ISR_MF, REG_ADC_ISR); 

		//if(readl(REG_ADC_ISR) & ADC_ISR_NACF)
			
		//while(!(rREG_ISR & ADC_ISR_MF));
		//rREG_ISR = ADC_ISR_MF; //Clear MF flag
		//if(rREG_ISR & ADC_ISR_NACF)
		{
			data=readl(REG_ADC_DATA);
			n=(33*data*100)>>12;
			d1=n/1000;
			d2=n%1000;
			printf("DATA=0x%08x,voltage=%d.%dv\n",data,d1,d2);
		}
		//else
			//printf("interrupt error\n");
	}while(0);
}
