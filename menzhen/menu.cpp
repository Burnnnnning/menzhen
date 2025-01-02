#include "function.h"

void DisplayMenu()
{
	while (true)
	{
		int choiceTable, choiceOp;
		cout << "=====门诊数据库管理系统=====" << endl;
		cout << "选择要操作的数据表" << endl;
		cout << "0.退出系统" << endl;
		cout << "1.医生信息-Doctor表" << endl;
		cout << "2.患者信息-Patient表" << endl;
		cout << "3.诊疗项目信息-Treatment_Item表" << endl;
		cout << "4.看病信息-Patient_Doctor表" << endl;
		cout << "5.治疗信息-Patient_Treatment_Item表" << endl;
		cout << "请输入你的选择：";
		cin >> choiceTable;
		if (choiceTable == 0)	break;
		//system("cls");
		cout << "选择要进行的操作" << endl;
		cout << "0.返回" << endl;
		cout << "1.添加信息" << endl;
		cout << "2.删除信息" << endl;
		cout << "3.查询信息" << endl;
		cout << "4.修改信息" << endl;
		cout << "请输入你的选择：";
		cin >> choiceOp;
		//system("cls");

		switch (choiceOp) {
		case 1:	InsertOp(choiceTable); break;
		case 2: DeleteOp(choiceTable); break;
		case 3: QueryOp(choiceTable);  break;
		case 4: ModifyOp(choiceTable); break;
		default: break;
		}
	}
}