/*=======================================================
 系统名称：两轮车主控板
 文件名称：PARAMETER.H
 描    述：参数定义头文件
 编    写：GQY上海公司研发中心
 目标芯片：TMS320LF2407A,TMS320LF2406A
 编写时间：2009-06-05
 最近修改时间：2013-10-24
 目前版本：3.0  
=========================================================*/
 #ifndef __parameter_h__
 #define __parameter_h__
/*=======================================================
 包含系统的其它头文件
=========================================================*/
#include "system.h"
 
 #define  VERB                30   
 #define  CANTXDPERIOD        14//11//30//11    // 30ms
 #define  BALANCEPERIOD       20//100//20//25//50//100//80//60//97// 63     // 100Hz(10ms) -> 63
                                       // 50Hz(20ms)  -> 125
							           // 40Hz(25ms)  -> 158
                                       // 25Hz(40ms)  -> 250
 #define  TRACECOUNTCOST       5
 #define  BATINITSOCVAL        6758    // 6200*1.09

 #define  CARTYPE              0x40   // La
 //#define  CARTYPE              0x41 // Sc

 #define  POWOFFBALTILTAGLVAL  756   //LA
 //#define  POWOFFBALTILTAGLVAL  448   //SC Open
 //#define  POWOFFBALTILTAGLVAL  252   //SC Close

  #define  BALLOCKSPDVAL       3072
/*=======================================================
 平衡控制参数
=========================================================*/
 #define  DEFAULTCOEFFTA       0       //32//24//64// 80  
 #define  DEFAULTCOEFFTAI      0//8    //4 //6 //1 // 1
 #define  DEFAULTCOEFFTAD      0//0   //0 //0 //0 // 2

 #define  DEFAULTCOEFFTR       45//60//80//80//40//46//6//2//50//80//60      //60//60//70//80//100  
 #define  DEFAULTCOEFFTRI      10//12//16//16//8//12//4//1//6//16//8       //8 //4 //2 //1 //1
 #define  DEFAULTCOEFFTRD      20//20//0//0       //0 //8 //16//16

 #define  DEFAULTCOEFFTV       2//32// 2//3//1//2//0//4//20      //20//25//50//20//10//30
 #define  DEFAULTCOEFFTVI      2//5//2//3//6//3//3//0//16//4       //2 //2 //4 //4 //1 //8
 #define  DEFAULTCOEFFTVD      2//20//40//2//3//4//2       //2 //5 //10

 #define  DEFAULTCOEFFTY       28//32//32//32//16//24//16//12//24//20//0//32//16//16      //16//16//20//16//8 //16 
 #define  DEFAULTCOEFFTYI      2//2//2//1//2//4//12//2//10//0//4//2//4       //4 //2 //4 //8 //2 //2
 #define  DEFAULTCOEFFTYD      55//69//69//46//92//130//20//80//100//10//0//15       //0 //0

 #define  DEFAULTCOEFFTT       4//8//0//2//16//8//0//36//32      //32
 #define  DEFAULTCOEFFTTI      2//0//2//0//25//0//4       //4
 //#define  DEFAULTCOEFFTTD      27//20//0//0//0//3//1//0       //16
 //#define  DEFAULTCOEFFTTD      16//SC Open
 #define  DEFAULTCOEFFTTD      9//SC Close
 #define  DEFAULTTURNMID     2048//450

 #define  DEFAULTTILTADJ12     450//495//1024//1029//0x0105  //0x1405 // 0x5003 // 0x5003
 #define  DEFAULTTILTADJ34     0//276//264//0x0101  //0x0302 // 0x0302 // 0x0101
 #define  DEFAULTTILTADJ56     0//316//264//0x0102//0x0100  //0x0201 // 0x0203 // 0x0201

 //#define  DEFAULTKP_IQ         410//3328//4996//0x0D00
 //#define  DEFAULTKI_IQ         0//512//1024//0x0200
// #define  DEFAULTSPEEDSTARTVAL 0//21 * 274

// #define  DEFAULTACCLITVAL     100//50//290
// #define  DEFAULTANGLEBASELITVAL 1000//896
 #define  DEFAULTHIGHSPDLITVAL   7680//6656//
 #define  DEFAULTLOWSPDLITVAL   3076
// #define  DEFAULTBATSOC        5400   // 电池出厂时电量,单位:mAH  Q0

 #define  LOGSTARTPOST         42//40     // 保存记录起始位置

 #endif
