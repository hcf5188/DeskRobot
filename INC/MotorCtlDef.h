//***********************************************
//***  FileName: MotorCtlDef.h   *****************
//***********************************************
#define PWM_CYCLE     8000//6400    //
#define ADC_CurZero   2048              //ADC Sample Value of the Zero Current
#define ADC_HaMean     1786  //2048   //  //ADC Sample Mean Value of Hall signal 
#define VoltRef       0x3D0
#define Kcurrent      0x1800            //Q12 10A = 0x1000 
#define Kspeed        0x1D17    //0x245C   //        //Q10
#define sqrt3inv      0x93C             //Q12 1/sqrt(3)
#define sqrt3inv2     0x1BB6            //Q12 sqrt(3)
#define SpCtlCyc      1                 // Speed Loop Time
#define VDMAX  		 0x0F800000		
#define VDMIN			-0x0F800000			
#define VQMAX  		 0x0F800000			
#define VQMIN			-0x0F800000		
#define LMTRI      0x28000000
#define Min_pwm    80
#define DeadTime   180
