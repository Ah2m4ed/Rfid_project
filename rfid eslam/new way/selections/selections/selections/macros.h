#ifndef _macros_H
#define  _macros_H

#define SET_BIT(reg,Index)		 reg|=(1<<Index)
#define CLR_BIT(Reg,Index)		 Reg&=(~(1<<Index))
#define GET_BIT(reg,index)		((reg>>index)&0x01)

#endif