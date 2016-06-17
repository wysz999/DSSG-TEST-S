#ifndef _XMLDATAMANAGER_H_
#define _XMLDATAMANAGER_H_
/**********************

XML数据管理类

**********************/
//#include "common\common.h"

class XMLDataManager
{
public:
	XMLDataManager();
	~XMLDataManager();

private:
	bool LoadServerConfig();
	bool ReLoadServerConfig();
};



#endif // !_XMLDATAMANAGER_H_