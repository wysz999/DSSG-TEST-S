#ifndef _ENUM_H_
#define _ENUM_H_

enum TheadState
{
	//空闲
	FREE = 0,
	//使用中
	BUSY,
	//等待销毁
	DEL,
};


#endif // !_ENUM_H_