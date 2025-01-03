#include "function.h"

// 定义全局变量
SQLRETURN ret = NULL;	//返回信息
SQLHENV henv = NULL;	//环境句柄
SQLHDBC hdbc = NULL;	//连接句柄
SQLHSTMT hstmt = NULL;	//语句句柄

// 释放资源
void FreeHandle()
{
	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
	SQLFreeHandle(SQL_HANDLE_ENV, henv);
}

// 将 string 转为 wstring 
wstring StringToWString(const std::string& str) 
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(str);
}

// 测试返回值 ret
void Debug(SQLRETURN ret)
{
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
		cout << "SQL_SUCCESS" << endl;
	}
	else if (ret == SQL_ERROR) {
		cout << "SQL_ERROR" << endl;
	}
	else if (ret == SQL_INVALID_HANDLE) {
		cout << "SQL_INVALID_HANDLE" << endl;
	}
	else if (ret == SQL_NEED_DATA) {
		cout << "SQL_NEED_DATA" << endl;
	}
	else if (ret == SQL_NO_DATA_FOUND) {
		cout << "SQL_NO_DATA_FOUND" << endl;
	}
	else {
		cout << "NO_INFO" << endl;
	}
}

// 数据库连接函数
void Connect()
{
	// 申请环境
	ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
		cout << "申请环境失败！" << endl;
		return;
	}

	// 设置环境
	ret = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
		cout << "设置环境失败！" << endl;
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
		return;
	}

	// 申请数据库连接
	ret = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
		cout << "申请数据库连接失败！" << endl;
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
		return;
	}

	// 连接数据库
	wstring wserver = StringToWString("SQL");
	wstring wuser = StringToWString("sa");
	wstring wpassword = StringToWString("123456");

	ret = SQLConnectW(hdbc, (SQLWCHAR*)wserver.c_str(), SQL_NTS, (SQLWCHAR*)wuser.c_str(),
		SQL_NTS, (SQLWCHAR*)wpassword.c_str(), SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
		cout << "数据库连接成功!" << endl;
	}
	else {
		cout << "数据库连接失败！" << endl;
		SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
		return;
	}
}

void InsertOp(int choiceTable)
{
	ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt); // 申请句柄  
	string str1 = "use menzhen"; // 选择数据库menzhen
	wstring wstr1 = StringToWString(str1);
	ret = SQLExecDirectW(hstmt, (SQLWCHAR*)wstr1.c_str(), SQL_NTS);

	switch (choiceTable) {
	case 1: // 医生信息-Doctor表
	{
		// 测试用例
		// 医生编号， 医生姓名， 医生性别， 医生年龄， 医生科室， 联系电话， 出诊时间
		// insert into Doctor values('D001','张三','男',30,'内科','2019-01-01','2020-01-01')
		cout << "请依次输入医生编号、医生姓名、医生性别、医生年龄、医生科室、出诊时间" << endl;
		cout << "（各项之间用空格分隔）" << endl;
		string Doctor_Number, Name, Gender, Age, Department, Contact_Phone, Outpatient_Time;
		cin >> Doctor_Number >> Name >> Gender >> Age >> Department >> Contact_Phone >> Outpatient_Time;

		string sql = "insert into Doctor values ('" + Doctor_Number + "', '" + Name + "', '" + Gender + "', '" + Age + "', '" + Department + "', '" + Contact_Phone + "', '" + Outpatient_Time + "')";
		wstring wsql = StringToWString(sql);

		ret = SQLExecDirectW(hstmt, (SQLWCHAR*)wsql.c_str(), SQL_NTS);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
			cout << "医生信息插入成功！" << endl;
		}
		else {
			cout << "医生信息插入失败！" << endl;
		}
		break;
	}
	case 2: // 患者信息-Patient表
	{
		cout << "请依次输入：患者编号、身份证号、患者姓名、患者年龄、患者症状、患者联系电话、患者医保" << endl;
		cout << "（各项之间用空格分隔）" << endl;
		string Patient_Number, ID_Card_Nubmer, Name, Age, Gender, Symptom, Contact_Info, Medical_Insurance;
		cin >> Patient_Number >> ID_Card_Nubmer >> Name >> Age >> Gender >> Symptom >> Contact_Info >> Medical_Insurance;
		
		string sql = "insert into Patient values('" + Patient_Number + "','" + ID_Card_Nubmer + "','" + Name + "','" + Age + "','" + Gender + "','" + Symptom + "','" + Contact_Info + "','" + Medical_Insurance + "')";
		wstring wsql = StringToWString(sql);

		ret = SQLExecDirectW(hstmt, (SQLWCHAR*)wsql.c_str(), SQL_NTS);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
			cout << "患者信息插入成功！" << endl;
		}
		else {
			cout << "患者信息插入失败！" << endl;
		}
		break;
	}
	case 3: // 诊疗项目信息-Treatment_Item表
	{
		cout << "请依次输入：项目编号、项目名称、项目价格" << endl;
		cout << "（各项之间用空格分隔）" << endl;
		string Item_Number, Item_Name, Item_Price;
		cin >> Item_Number >> Item_Name >> Item_Price;

		string sql = "insert into Treatment_Item values('" + Item_Number + "','" + Item_Name + "','" + Item_Price + "')";
		wstring wsql = StringToWString(sql);

		ret = SQLExecDirectW(hstmt, (SQLWCHAR*)wsql.c_str(), SQL_NTS);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
			cout << "诊疗项目信息插入成功！" << endl;
		}
		else {
			cout << "诊疗项目信息插入失败！" << endl;
		}
		break;
	}
	case 4: // 看病信息-Patient_Doctor表
	{
		// cout << "看病信息为关系表，无法直接插入！" << endl;
		cout << "请依次输入：患者编号(必须存在)、医生编号(必须存在)、看病时间" << endl;
		cout << "（各项之间用空格分隔）" << endl;
		string Patient_Number, Doctor_Number, Medical_Time;
		cin >> Patient_Number >> Doctor_Number >> Medical_Time;

		string sql = "insert into Patient_Doctor values('" + Patient_Number + "','" + Doctor_Number + "','" + Medical_Time + "')";
		wstring wsql = StringToWString(sql);

		ret = SQLExecDirectW(hstmt, (SQLWCHAR*)wsql.c_str(), SQL_NTS);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
			cout << "看病信息插入成功！" << endl;
		}
		else {
			cout << "看病信息插入失败！" << endl;
		}
		break;
	}
	case 5: // 治疗信息-Patient_Treatment_Item表
	{
		// cout << "治疗信息为关系表，无法直接插入！" << endl
		cout << "请依次输入：患者编号(必须存在)、项目编号(必须存在)、治疗时间" << endl;
		cout << "（各项之间用空格分隔）" << endl;
		string Patient_Number, Item_Number, Treatment_Time;
		cin >> Patient_Number >> Item_Number >> Treatment_Time;

		string sql = "insert into Patient_Treatment_Item values('" + Patient_Number + "','" + Item_Number + "','" + Treatment_Time + "')";
		wstring wsql = StringToWString(sql);

		ret = SQLExecDirectW(hstmt, (SQLWCHAR*)wsql.c_str(), SQL_NTS);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
			cout << "治疗信息插入成功！" << endl;
		}
		else {
			cout << "治疗信息插入失败！" << endl;
		}
		break;
	}
	default:
		cout << "无效的表选择！" << endl;
		break;
	}

	FreeHandle(); // 释放资源  
}

void QueryOp(int choiceTable)
{
	ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt); // 申请句柄 
	string str1 = "use menzhen"; // 选择数据库menzhen
	wstring wstr1 = StringToWString(str1);
	ret = SQLExecDirectW(hstmt, (SQLWCHAR*)wstr1.c_str(), SQL_NTS);

	switch (choiceTable) {
	case 1:	// 查询医生信息-Doctor表
	{
		string sql = "select * from Doctor";
		wstring wsql = StringToWString(sql);
		ret = SQLExecDirectW(hstmt, (SQLWCHAR*)wsql.c_str(), SQL_NTS);

		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		{
			cout << "查询医生信息结果如下：" << endl;
			SQLCHAR str1[255], str2[255], str3[255], str4[255], str5[255], str6[255], str7[255];//用来存放从数据库获取的列信息，你有几列就定义几个变量
			SQLLEN len_str1, len_str2, len_str3, len_str4, len_str5, len_str6, len_str7;//字符串对应长度，你有几列就定义几个变量
			cout << "医生编号" << " " << "医生姓名" << " " << "医生性别" << " " << "医生年龄" << " " << "医生科室" << " " << "联系电话" << " " << "出诊时间" << endl;
			while (SQLFetch(hstmt) != SQL_NO_DATA)
			{
				SQLGetData(hstmt, 1, SQL_C_CHAR, str1, 255, &len_str1);//从数据库获取数据，你的列有多少，就写多少，从1开始
				SQLGetData(hstmt, 2, SQL_C_CHAR, str2, 255, &len_str2);
				SQLGetData(hstmt, 3, SQL_C_CHAR, str3, 255, &len_str3);
				SQLGetData(hstmt, 4, SQL_C_CHAR, str4, 255, &len_str4);
				SQLGetData(hstmt, 5, SQL_C_CHAR, str5, 255, &len_str5);
				SQLGetData(hstmt, 6, SQL_C_CHAR, str6, 255, &len_str6);
				SQLGetData(hstmt, 7, SQL_C_CHAR, str7, 255, &len_str7);
				cout << string((char*)str1, len_str1) << "  " << string((char*)str2, len_str2)
					<< "  " << string((char*)str3, len_str3) << "  " << string((char*)str4, len_str4)
					<< "  " << string((char*)str5, len_str5) << "  " << string((char*)str6, len_str6)
					<< "  " << string((char*)str7, len_str7) << endl;
			}
		}
		break;
	}
	case 2:
	{
		// 查询患者信息-Patient表
		string sql = "select * from Patient";
		wstring wsql = StringToWString(sql);
		ret = SQLExecDirectW(hstmt, (SQLWCHAR*)wsql.c_str(), SQL_NTS);

		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		{
			cout << "查询患者信息结果如下：" << endl;
			SQLCHAR str1[255], str2[255], str3[255], str4[255], str5[255], str6[255], str7[255], str8[255];//用来存放从数据库获取的列信息，你有几列就定义几个变量
			SQLLEN len_str1, len_str2, len_str3, len_str4, len_str5, len_str6, len_str7, len_str8;//字符串对应长度，你有几列就定义几个变量
			// 患者编号，身份证号，患者姓名，患者年龄，患者性别，患者症状，患者联系电话，患者医保
			cout << "患者编号" << " " << "身份证号" << " " << "患者姓名" << " " << "患者年龄" << " " << "患者性别" << " " << "患者症状" << " " << "患者联系电话" << " " << "患者医保" << endl;
			while (SQLFetch(hstmt) != SQL_NO_DATA)
			{
				SQLGetData(hstmt, 1, SQL_C_CHAR, str1, 255, &len_str1);//从数据库获取数据，你的列有多少，就写多少，从1开始
				SQLGetData(hstmt, 2, SQL_C_CHAR, str2, 255, &len_str2);
				SQLGetData(hstmt, 3, SQL_C_CHAR, str3, 255, &len_str3);
				SQLGetData(hstmt, 4, SQL_C_CHAR, str4, 255, &len_str4);
				SQLGetData(hstmt, 5, SQL_C_CHAR, str5, 255, &len_str5);
				SQLGetData(hstmt, 6, SQL_C_CHAR, str6, 255, &len_str6);
				SQLGetData(hstmt, 7, SQL_C_CHAR, str7, 255, &len_str7);
				SQLGetData(hstmt, 8, SQL_C_CHAR, str8, 255, &len_str8);
				cout << string((char*)str1, len_str1) << "  " << string((char*)str2, len_str2)
					<< "  " << string((char*)str3, len_str3) << "  " << string((char*)str4, len_str4)
					<< "  " << string((char*)str5, len_str5) << "  " << string((char*)str6, len_str6)
					<< "  " << string((char*)str7, len_str7) << "  " << string((char*)str8, len_str8) << endl;
			}	
		}
		break;
	}
	case 3:
	{
		// 查询诊疗项目-Treatment_Item表
		string sql = "select * from Treatment_Item";
		wstring wsql = StringToWString(sql);
		ret = SQLExecDirectW(hstmt, (SQLWCHAR*)wsql.c_str(), SQL_NTS);

		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		{
			cout << "查询诊疗项目信息结果如下：" << endl;
			SQLCHAR str1[255], str2[255], str3[255];//用来存放从数据库获取的列信息，你有几列就定义几个变量
			SQLLEN len_str1, len_str2, len_str3;//字符串对应长度，你有几列就定义几个变量
			cout << "项目编号" << " " << "项目名称" << " " << "项目价格" << endl;
			while (SQLFetch(hstmt) != SQL_NO_DATA)
			{
				SQLGetData(hstmt, 1, SQL_C_CHAR, str1, 255, &len_str1);//从数据库获取数据，你的列有多少，就写多少，从1开始
				SQLGetData(hstmt, 2, SQL_C_CHAR, str2, 255, &len_str2);
				SQLGetData(hstmt, 3, SQL_C_CHAR, str3, 255, &len_str3);
				cout << string((char*)str1, len_str1) << "   " << string((char*)str2, len_str2)
					<< "   " << string((char*)str3, len_str3) << endl;
			}
		}
		break;
	}
	case 4:
	{
		// 查询看病信息-Patient_Doctor表
		string sql = "select * from Patient_Doctor";
		wstring wsql = StringToWString(sql);
		ret = SQLExecDirectW(hstmt, (SQLWCHAR*)wsql.c_str(), SQL_NTS);

		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		{
			cout << "查询看病信息结果如下：" << endl;
			SQLCHAR str1[255], str2[255], str3[255];
			SQLLEN len_str1, len_str2, len_str3;
			cout << "患者编号" << " " << "医生编号" << " " << "看病时间" << endl;
			while (SQLFetch(hstmt) != SQL_NO_DATA)
			{
				SQLGetData(hstmt, 1, SQL_C_CHAR, str1, 255, &len_str1);
				SQLGetData(hstmt, 2, SQL_C_CHAR, str2, 255, &len_str2);
				SQLGetData(hstmt, 3, SQL_C_CHAR, str3, 255, &len_str3);
				cout << string((char*)str1, len_str1) << "  " << string((char*)str2, len_str2) << "  " << string((char*)str3, len_str3) << endl;
			}
		}
		break;
	}
	case 5:
	{
		// 查询治疗信息-Patient_Treatment_Item表
		string sql = "select * from Patient_Treatment_Item";
		wstring wsql = StringToWString(sql);
		ret = SQLExecDirectW(hstmt, (SQLWCHAR*)wsql.c_str(), SQL_NTS);

		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		{
			cout << "查询治疗信息结果如下：" << endl;
			SQLCHAR str1[255], str2[255], str3[255];
			SQLLEN len_str1, len_str2, len_str3;
			cout << "患者编号" << " " << "项目编号" << " " << "治疗时间" << endl;
			while (SQLFetch(hstmt) != SQL_NO_DATA)
			{
				SQLGetData(hstmt, 1, SQL_C_CHAR, str1, 255, &len_str1);
				SQLGetData(hstmt, 2, SQL_C_CHAR, str2, 255, &len_str2);
				SQLGetData(hstmt, 3, SQL_C_CHAR, str3, 255, &len_str3);
				cout << string((char*)str1, len_str1) << "  " << string((char*)str2, len_str2) << "  " << string((char*)str3, len_str3) << endl;
			}
		}
		break;
	}
	default:
		cout << "无效的表选择！" << endl;
		break;
	}

	FreeHandle(); // 释放资源
}

void DeleteOp(int choiceTable)
{
	// 查询操作，用来显示表内容
	QueryOp(choiceTable);

	ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt); // 申请句柄 
	string str1 = "use menzhen";
	wstring wstr1 = StringToWString(str1);
	ret = SQLExecDirectW(hstmt, (SQLWCHAR*)wstr1.c_str(), SQL_NTS);

	switch (choiceTable) {
	case 1:
	{
		// 删除医生信息-Doctor表
		string sql = "delete from Doctor where Doctor_Number=";
		string Sno;
		cout << "请输入要删除的医生编号" << endl;
		cin >> Sno;
		sql = sql + "'" + Sno + "'";
		wstring wsql = StringToWString(sql);

		ret = SQLExecDirectW(hstmt, (SQLWCHAR*)wsql.c_str(), SQL_NTS);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
			cout << "医生信息删除成功！" << endl;
		}
		else {
			cout << "医生信息删除失败！" << endl;
		}
		break;
	}
	case 2:
	{
		// 删除患者信息-Patient表
		string sql = "delete from Patient where Patient_Number=";
		string Sno;
		cout << "请输入要删除的患者编号" << endl;
		cin >> Sno;
		sql = sql + "'" + Sno + "'";
		wstring wsql = StringToWString(sql);

		ret = SQLExecDirectW(hstmt, (SQLWCHAR*)wsql.c_str(), SQL_NTS);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
			cout << "患者信息删除成功！" << endl;
		}
		else {
			cout << "患者信息删除失败！" << endl;
		}
		break;
	}
	case 3:
	{
		// 删除诊疗项目信息-Treatment_Item表
		string sql = "delete from Treatment_Item where Item_Number=";
		string Sno;
		cout << "请输入要删除的诊疗项目编号" << endl;
		cin >> Sno;
		sql = sql + "'" + Sno + "'";
		wstring wsql = StringToWString(sql);

		ret = SQLExecDirectW(hstmt, (SQLWCHAR*)wsql.c_str(), SQL_NTS);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
			cout << "诊疗项目信息删除成功！" << endl;
		}
		else {
			cout << "诊疗项目信息删除失败！" << endl;
		}
		break;
	}
	case 4:
	{
		// 删除看病信息-Patient_Doctor
		string sql = "delete from Patient_Doctor where ";
		string Sno, Cno;
		cout << "请输入要删除的患者编号和医生编号" << endl;
		cin >> Sno >> Cno;
		sql = sql + "Patient_Number='" + Sno + "' and " + "Doctor_Number='" + Cno + "'";
		wstring wsql = StringToWString(sql);

		ret = SQLExecDirectW(hstmt, (SQLWCHAR*)wsql.c_str(), SQL_NTS);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
			cout << "看病信息删除成功！" << endl;
		}
		else {
			cout << "看病信息删除失败！" << endl;
		}
		break;
	}
	case 5:
	{
		// 删除治疗信息-Patient_Treatment_Item
		string sql = "delete from Patient_Treatment_Item where ";
		string Sno, Cno;
		cout << "请输入要删除的患者编号和项目编号" << endl;
		cin >> Sno >> Cno;
		sql = sql + "Patient_Number='" + Sno + "' and " + "Item_Number='" + Cno + "'";
		wstring wsql = StringToWString(sql);

		ret = SQLExecDirectW(hstmt, (SQLWCHAR*)wsql.c_str(), SQL_NTS);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
			cout << "治疗信息删除成功！" << endl;
		}
		else {
			cout << "治疗信息删除失败！" << endl;
		}
		break;
	}
	default:
		cout << "无效的表选择！" << endl;
		break;
	}

	FreeHandle(); // 释放资源  
}

void ModifyOp(int choiceTable)
{
	QueryOp(choiceTable);

	ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt); // 申请句柄 
	string str1 = "use student"; // 选择数据库student
	wstring wstr1 = StringToWString(str1);
	ret = SQLExecDirectW(hstmt, (SQLWCHAR*)wstr1.c_str(), SQL_NTS);

	//  修改SQL语句
	//  UPDATE table_name
	//	SET column1 = value1, column2 = value2, ...
	//	WHERE condition;
	switch (choiceTable) {
	case 1:
	{
		//string sql = "select * from Student";
		//wstring wsql = StringToWString(sql);
		//ret = SQLExecDirectW(hstmt, (SQLWCHAR*)wsql.c_str(), SQL_NTS);

		string condition, Sno, Sname, Sage, Sdept;
		cout << "请输入要修改的学生学号" << endl;
		cin >> condition;
		cout << "请输入修改后的内容，依次输入学号、姓名、年龄、所在系" << endl;
		cin >> Sno >> Sname >> Sage >> Sdept;
		string sql2 = "update Student set [sno-学号]='" + Sno + "',[sname-姓名]='" + Sname + "',[sage-年龄]=" + Sage + ",[sdept-所在系]='" + Sdept + "' where [sno-学号]='" + condition + "'";
		wstring wsql2 = StringToWString(sql2);

		ret = SQLExecDirectW(hstmt, (SQLWCHAR*)wsql2.c_str(), SQL_NTS);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
			cout << "修改成功！" << endl;
		}
		else {
			cout << "修改失败！" << endl;
		}
		break;
	}
	case 2:
	{
		string condition, Cno, Cname, Cbefore;
		cout << "请输入要修改的课程号" << endl;
		cin >> condition;
		cout << "请输入修改后的内容，依次输入课程号，课程名，先行课" << endl;
		cin >> Cno >> Cname >> Cbefore;
		string sql2 = "update Course set [cno-课程号]='" + Cno + "',[cname-课程名]='" + Cname + "',[cbefore-先行课]='" + Cbefore + "' where [cno-课程号]='" + condition + "'";
		wstring wsql2 = StringToWString(sql2);

		ret = SQLExecDirectW(hstmt, (SQLWCHAR*)wsql2.c_str(), SQL_NTS);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
			cout << "修改成功！" << endl;
		}
		else {
			cout << "修改失败！" << endl;
		}
		break;
	}
	case 3:
	{
		string conditionSno, conditionCno, Sno, Cno, grade;
		cout << "请输入要修改的学生学号和课程号" << endl;
		cin >> conditionSno >> conditionCno;
		cout << "请输入修改后的内容，依次输入学号，课程号，成绩" << endl;
		cin >> Sno >> Cno >> grade;
		string sql2 = "update SC set [sno-学号]='" + Sno + "',[cno-课程号]='" + Cno + "',[grade-成绩]='" + grade + "' where [sno-学号]='" + conditionSno + "' and [cno-课程号]='" + conditionCno + "'";
		wstring wsql2 = StringToWString(sql2);

		ret = SQLExecDirectW(hstmt, (SQLWCHAR*)wsql2.c_str(), SQL_NTS);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
			cout << "修改成功！" << endl;
		}
		else {
			cout << "修改失败！" << endl;
		}
		break;
	}
	default:
		cout << "无效的表选择！" << endl;
		break;
	}

	FreeHandle(); // 释放资源
}