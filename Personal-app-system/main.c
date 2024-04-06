#include <stdio.h>
#include <string.h>
#include <io.h>
void fu_chu_zhi(Person_information);//模块函数声明
void Load(Person_information);
void upload(Person_information);
void Add_person(Person_information);
void Modify_person(Person_information);
void Deleted_person(Person_information);
void Add_person_app(Person_information);
void Modify_person_app(Person_information);
void Deleted_person_app(Person_information);
void Sorted_person_Num_apps(Person_information);
void Find_app_owned_person(Person_information);
void Look_All(Person_information);

typedef struct App {//软件结构体，包含软件的信息
	char Name[20];
	float Storage;
	char Developer[20];
	char Version[10];
	char Language_CHINA[5];
}App;

typedef struct Person_information {//用户结构体
	char Name[20];
	App Own_App[10];//包含了一个大小为十的软件结构体数组，用于存储软件的信息
}Person_information;

int main() {//图形界面的打印
	printf("----------------------------------------\n各种可执行的操作及对应的编号如下：\n");
	printf("1, 添加用户信息\n2, 修改用户姓名\n3, 删除用户\n");
	printf("4,添加已有用户拥有软件\n5,修改已有用户拥有软件的信息\n6,删除已有用户软件信息\n");
	printf("7,按每个用户拥有的应用数进行降序排序\n8,查找应用的所属用户\n");
	printf("9,查看所有用户信息\n");
	printf("输入其余任意键,退出程序\n----------------------------------------\n");
	Person_information All_person[100];//在内存中开辟了一个大小为100的用户结构体数组，存储用户信息，便于数据的访问和操作
	Person_information* All_person_pointer = &All_person;//将用户结构体数组的地址赋值给All_person_pointer指针，便于后续函数传参
	fu_chu_zhi(All_person_pointer);
	Load(All_person_pointer);//将文件中的数据加载到原先开辟好的用户结构体数组中
	while (1) {//按照用户输入的值进行匹配，while循环保证了在不进行人为终止的情况下程序会一直运行下去
		printf("\n请按你想要执行的操作输入对应的编号：");
		int a;
		scanf_s("%d", &a);
		switch (a) {
		case 1:Add_person(All_person_pointer); break;
		case 2:Modify_person(All_person_pointer); break;
		case 3:Deleted_person(All_person_pointer); break;
		case 4:Add_person_app(All_person_pointer); break;
		case 5:Modify_person_app(All_person_pointer); break;
		case 6:Deleted_person_app(All_person_pointer); break;
		case 7:Sorted_person_Num_apps(All_person_pointer); break;
		case 8:Find_app_owned_person(All_person_pointer); break;
		case 9:Look_All(All_person_pointer); break;
		default:printf("程序运行结束");upload(All_person_pointer);return 0;//upload函数将用户结构体数组中的数据存回文件中，随后文件关闭
		}
	}
}

void fu_chu_zhi(Person_information* p) {//对用户结构体数组的部分位置做标记，将文件读取至用户结构体数组中时，未被覆盖的区域标记未变，意为“空”，可以确定数组的实际利用大小
	for (int i = 0; i < 100; i++) {
		strcpy_s((p+i)->Name,5,"NULL");//将用户结构体数组的每一个用户名设置为“NULL”
		for (int j = 0; j < 10; j++)
			strcpy_s((p + i)->Own_App[j].Name ,5,"NULL");//将所有用户包含的软件结构体数组的所有软件名标记为“NULL”
	}
}

void Load(Person_information* p) {//将文件中的数据输出到用户结构体数组中
	FILE* fp;
	if (_access("D:\project\c\Personal app system\Personapp", 0)) {//判断文件是否存在
		fopen_s(&fp, "D:\project\c\Personal app system\Personapp", "w");//文件不存在则以只读方式创建一个
		fclose(fp);
		FILE* fp;
		printf("该文件未存在，以为你创建了一个不含任何数据的新文件！\n此次运行软件，请执行操作1-添加用户，防止出现错误格式！\n");
		return 0;
	}
	fopen_s(&fp, "D:\project\c\Personal app system\Personapp", "r");//以只读方式打开文件，将文件地址赋值给fp指针
	int i = 0;
	while (1) {//while循环，当文件读取到末尾时，会被打破
		if (feof(fp)) break; //读取到文件末尾时，feof(fp)会放回一个非零值，打破循环
		else {//将文件中的数据读取到用户结构体数组中
			fscanf_s(fp, "%s", (p + i)->Name,20);
			fscanf_s(fp, "%s", (p + i)->Own_App[0].Name,20);
			fscanf_s(fp, "%f", &(p + i)->Own_App[0].Storage);
			fscanf_s(fp, "%s", (p + i)->Own_App[0].Developer,20);
			fscanf_s(fp, "%s", (p + i)->Own_App[0].Version,10);
			fscanf_s(fp, "%s", (p + i)->Own_App[0].Language_CHINA,5);
			char endyn[5]={0};
			fscanf_s(fp, "%s",endyn, 5);//读取每个应用后特地设置的flag，用于确定当前应用接下来是当前用户的下一个应用还是下一个用户
			for(int j=1;endyn[0] == 'n'; j++) {//当flag是以n开头时，可确定当前用户的软件还没有输入完毕；继续输入
				fscanf_s(fp, "%s", (p + i)->Own_App[j].Name, 20);
				fscanf_s(fp, "%f", &(p + i)->Own_App[j].Storage);
				fscanf_s(fp, "%s", (p + i)->Own_App[j].Developer, 20);
				fscanf_s(fp, "%s", (p + i)->Own_App[j].Version, 10);
				fscanf_s(fp, "%s", (p + i)->Own_App[j].Language_CHINA, 5);
				fscanf_s(fp, "%s", endyn, 5);//继续读取该软件后的flag
			}
			i++;//当前用户软件读取完后，将用户结构体数组的下标向后移动一位，继续输入下一个用户的数据
		}

	}fclose(fp);//关闭文件
}

void upload(Person_information* p) {//将结构体数组中的用户输入到文件中
	FILE* fp;
	fopen_s(&fp, "D:\project\c\Personal app system\Personapp", "w");//以读入的方式打开文件
	for (int i = 0;; i++) {//循环输入每一个用户名和软件信息
		fprintf(fp,"%s ", p[i].Name);
		for (int j = 0;; j++) {//循环输入当前用户的每一个软件信息
			fprintf(fp,"%s ", p[i].Own_App[j].Name);
			fprintf(fp,"%f ", p[i].Own_App[j].Storage);
			fprintf(fp,"%s ", p[i].Own_App[j].Developer);
			fprintf(fp,"%s ", p[i].Own_App[j].Version);
			fprintf(fp,"%s ", p[i].Own_App[j].Language_CHINA);
			if (!strcmp(p[i].Own_App[j + 1].Name, "NULL"))//当下一个软件的名称为“NULL”时，软件输入完毕
				break;
			fprintf(fp,"%s ", "no");//输入flag，接着输入当前用户的下一个软件
		}
		fprintf(fp,"%s ", "yes");//输入flag，寓意当前用户软件输入完毕
		if (!strcmp(p[i + 1].Name, "NULL")) break;//下一个用户名为“NULL”时，用户输入完毕
	}fclose(fp);
}

void Add_person(Person_information* p) {//添加用户
	FILE* fp;
	fopen_s(&fp, "D:\project\c\Personal app system\Personapp", "a");//以追加写入的方式打开文件
	char name[20];
	int num;
	printf("请输入需添加用户的姓名：");
	scanf_s("%s", name,20);
	for (int i = 0;; i++) {//将输入的姓名与已存在的用户姓名进行对比，检测该用户是否存在
		if (!strcmp(p[i].Name, name)) {
			printf("该用户已存在！");
			return 0;
		}
		if (!strcmp(p[i + 1].Name, "NULL"))break;//用户都遍历完都没有重名的，则退出当前循环
	}
	fprintf(fp, "%s ", name);//将用户姓名写入文件
	printf("请输入该用户需添加的软件数目：");
	scanf_s("%d", &num);
	for (int i = 1; i <= num; i++) {//将软件信息写入文件
		printf("请分别输入第%i个软件的名字，容量，开发商，版本号，是否支持中文等情况\n", i);
		char Name[20];
		float Storage;
		char Developer[20];
		char Version[10];
		char Language_CHINA[5];
		scanf_s("%s", Name,20);
		scanf_s("%f", &Storage);
		scanf_s("%s", Developer,20);
		scanf_s("%s", Version,10);
		scanf_s("%s", Language_CHINA,5);
		fprintf(fp, "%s ", Name);
		fprintf(fp, "%f ", Storage);
		fprintf(fp, "%s ", Developer);
		fprintf(fp, "%s ", Version);
		fprintf(fp, "%s ", Language_CHINA);
		if(i==num)fprintf(fp, "%s ", "yes");//在每一个软件后做特殊标记，确定该软件接下来是别的软件还是别的用户
		else fprintf(fp,"%s ","no");
	}
	fclose(fp);
	Load(p);//将数据从已更新的文件中读取出来，确保用户结构体数组的同步更新
}

void Modify_person(Person_information* p) {//修改用户姓名
	printf("请输入你想修改用户的姓名：");
	char Name_modified[20];
	scanf_s("%s", Name_modified,20);//输入修改前的姓名，以供查找
	for (int i = 0;; i++) {//对用户姓名进行遍历匹配
		if (!strcmp(p[i].Name, Name_modified)) {//匹配成功
			char Name_to_be_modified[20];
			printf("请输入修改后的用户姓名：");//输入修改后的姓名，以供修改
			scanf_s("%s", Name_to_be_modified,20);
			strcpy_s(p[i].Name,20, Name_to_be_modified);
			printf("已将名为%s修改为%s", Name_modified, Name_to_be_modified);
			upload(p);//存到文件中
			break;
		}
		if (!strcmp(p[i + 1].Name, "NULL")) { //匹配失败
			printf("不好意思，没有找到你的目标用户！");
			break; 
		}
	}
}

void Deleted_person(Person_information* p) {//删除用户
	printf("请输入你想删除用户的姓名:");
	char name_Deleted[20];
	scanf_s("%s", name_Deleted,20);//输入用户姓名
	for (int i = 0;; i++) {//循环遍历
		if (!strcmp(p[i].Name, name_Deleted)) {//匹配成功
			for (int j = i;; j++) {
				strcpy_s(p[j].Name, 20, p[j + 1].Name);//从待删除的用户开始，将当前用户姓名用下一个用户姓名覆盖
				for (int k = 0;k<10; k++) {//从待删除的用户开始，将当前用户软件结构体数组对应下标位置用下一个用户软件覆盖
					strcpy_s(p[j].Own_App[k].Name, 20, p[j + 1].Own_App[k].Name);
					p[j].Own_App[k].Storage = p[j + 1].Own_App[k].Storage;
					strcpy_s(p[j].Own_App[k].Developer, 20, p[j + 1].Own_App[k].Developer);
					strcpy_s(p[j].Own_App[k].Version, 10, p[j + 1].Own_App[k].Version);
					strcpy_s(p[j].Own_App[k].Language_CHINA, 5, p[j + 1].Own_App[k].Language_CHINA);
					if (!strcmp(p[j + 1].Own_App[k + 1].Name, "NULL")) {//当下一个用户的下一个软件名为“NULL”时
						strcpy_s(p[j].Own_App[k + 1].Name,5, "NULL");//当前用户的下一个软件名设置为“NULL”，防止当前用户的软件数目多余下一个用户
						break;
					}
				}
				if (!strcmp(p[j + 2].Name, "NULL")) {//下下个用户姓名为“NULL”时
					strcpy_s(p[j + 1].Name, 20, "NULL");//将下一个用户姓名设置为“NULL”，因为下一个用户是最后一个用户，其后没有可覆盖他的
					break;
				}
			}
			return 0;
		}
		else if (!strcmp(p[i + 1].Name, "NULL")) {//用户姓名匹配失败
			printf("对不起，没有找到该用户\n");
			return 0;
		}
	}
}

void Add_person_app(Person_information* p) {//添加用户软件
	printf("请输入你想添加软件的用户的姓名：");
	char Name_add_app[20];
	scanf_s("%s", Name_add_app, 20);//输入目标用户姓名
	for (int i = 0;; i++) {//循环遍历用户结构体中用户姓名，匹配目标用户姓名
		if (!strcmp(p[i].Name, Name_add_app)) {//匹配成功
			for (int j = 0;; j++)//将软件结构体数组的下标向后推进
				if (!strcmp(p[i].Own_App[j].Name, "NULL")) {//确保该用户结构体的软件结构体数组下标到达空的位置，进行新软件的添加操作
					printf("请分别输入将添加软件的名字，容量，开发商，版本号，是否支持中文等情况\n", i);
					char Name[20];
					float Storage;
					char Developer[20];
					char Version[10];
					char Language_CHINA[5];
					scanf_s("%s", Name, 20);
					scanf_s("%f", &Storage);
					scanf_s("%s", Developer, 20);
					scanf_s("%s", Version, 10);
					scanf_s("%s", Language_CHINA, 5);
					strcpy_s(p[i].Own_App[j].Name, 20, Name);
					p[i].Own_App[j].Storage = Storage;
					strcpy_s(p[i].Own_App[j].Developer, 20, Developer);
					strcpy_s(p[i].Own_App[j].Version, 10, Version);
					strcpy_s(p[i].Own_App[j].Language_CHINA, 5, Language_CHINA);
					upload(p);
					upload(p);
					return 0;
				}
		}
			
			if (!strcmp(p[i + 1].Name, "NULL")) {//匹配失败
				printf("不好意思，没有找到你的目标用户！\n");
				return 0;
			}
		}
	}

void Modify_person_app(Person_information* p) {//修改用户软件信息
	char Name[20], App[20], Attrrbute[20], Attrubute_zhi[20];//代表用户名，软件名，属性名，修改后的属性值
	printf("请输入你目标用户名：");
	scanf_s("%s", Name,20);
	for (int i = 0;; i++) {//推进用户结构体数组，将目标用户名数组中的用户名匹配
		if (!strcmp(p[i].Name, Name)) {//用户名匹配成功
			printf("请输入将修改属性的软件名称:");
			scanf_s("%s", App, 20);
			for (int j = 0;; j++) {//推进当前用户的软件结构体数组下标，将目标软件名和数组中的软件吗匹配
				if (!strcmp(p[i].Own_App[j].Name, App)) {//匹配成功
					while (1) {
						printf("请输入将修改的属性和修改后的值：");
						scanf_s("%s", Attrrbute,20);//输入属性名，将其与软件的每个属性的名字进行对比
						if (!strcmp(Attrrbute, "Storage")) {//若输入的属性名与与“Storage”相同，则修改当前软件的容量大小，下列判断同意
							float Attribute_F_zhi;
							scanf_s("%f", &Attribute_F_zhi);
							p[i].Own_App[j].Storage = Attribute_F_zhi;
							upload(p);
							printf("修改成功！");
							return 0;
						}
						scanf_s("%s", Attrubute_zhi,20);
						if (!strcmp(Attrrbute, "Name")) { 
							strcpy_s(p[i].Own_App[j].Name, 20, Attrubute_zhi); 
							upload(p);
							printf("修改成功！");
							return 0; 
						}
						if (!strcmp(Attrrbute, "Developer")) { 
							strcpy_s(p[i].Own_App[j].Developer, 20, Attrubute_zhi); 
							upload(p);
							printf("修改成功！");
							return 0; 
						}
						if (!strcmp(Attrrbute, "Version")) { 
							strcpy_s(p[i].Own_App[j].Version, 10, Attrubute_zhi); 
							upload(p);
							printf("修改成功！");
							return 0; 
						}
						if (!strcmp(Attrrbute, "Language_CHINA")) { 
							strcpy_s(p[i].Own_App[j].Language_CHINA, 5, Attrubute_zhi); 
							upload(p);
							printf("修改成功！");
							return 0; 
						}//全都匹配失败
						printf("系统检测你所输入的属性名有误，请按Name,Developer,Version,Language_CHINA进行输入，谢谢");
					}
				}
				if (!strcmp(p[i].Own_App[j + 1].Name, "NULL")) {//软件名匹配失败
					printf("不好意思，没有找到你的目标软件！\n");
					return 0;
				}
			}
			if (!strcmp(p[i + 1].Name, "NULL")) {//用户名匹配失败
				printf("不好意思，没有找到你的目标用户！\n");
				return 0;
			}
		}
	}
}

void Deleted_person_app(Person_information * p) {//删除用户软件
	printf("请输入你想删除的应用的所属用户：");
	char App_Name[20];
	scanf_s("%s", App_Name,20);
	for (int i = 0;; i++) {//循环推进用户结构体数组次下标，遍历用户名，与目标用户名匹配
		if (!strcmp(App_Name, p[i].Name)) {//匹配成功
			char App_deleted[20];
			printf("请输入你想删除的应用:");
			scanf_s("%s", App_deleted,20);
			for (int j = 0;; j++) {//循环推进软件结构体数组下标，遍历软件名，与目标软件名相匹配
				if (!strcmp(App_deleted, p[i].Own_App[j].Name)) {//匹配成功
					for (int k = j;; k++) {//循环推进软件结构体数组下标，对每个软件实行覆盖操作
						if (!strcmp(p[i].Own_App[k + 1].Name,"NULL")) {
							strcpy_s(p[i].Own_App[k].Name, 5, "NULL");//将最后一个软件的名字设置为空
							return 0;
						}//从当前软件开始，用后面的软件覆盖前一个软件的信息
						strcpy_s(p[i].Own_App[k].Name, 20, p[i].Own_App[k + 1].Name);
						p[i].Own_App[j].Storage = p[i].Own_App[j].Storage;
						strcpy_s(p[i].Own_App[k].Developer, 20, p[i].Own_App[k + 1].Developer);
						strcpy_s(p[i].Own_App[k].Version, 20, p[i].Own_App[k + 1].Version);
						strcpy_s(p[i].Own_App[k].Language_CHINA, 20, p[i].Own_App[k + 1].Language_CHINA);
						if (!strcmp(p[i].Own_App[k + 2].Name, "NULL")) {
							strcpy_s(p[i].Own_App[k+1].Name, 5, "NULL");
							printf("%s已经被删除成功!", App_deleted);
							return 0;
						}
					}
				}
				else if (!strcmp(p[i].Own_App[j + 1].Name, "NULL")) {//软件名匹配失败
					printf("不好意思，没有找到该应用\n");
					return 0;
				}
			}
		}
		else if (!strcmp(p[i + 1].Name, "NULL")) {//用户名匹配失败
			printf("不好意思，没有找到该用户！");
			return 0;
		}
	}
}

void Sorted_person_Num_apps(Person_information* p) {//按用户拥有的软件量进行降排序
	
	if(!strcmp(p[0].Name,"NULL")) {//检查用户结构体数组是否为空
		printf("用户列表为空。\n");
		return 0;
	}
	int Person_Owned_nums[100];//储存用户软件量的数组，与用户结构体数组里的用户一一对应，通过下标建立关系
	for (int i = 0;; i++) {//循环遍历每个用户结构体，将用户所有软件量存入软件量数组中
		if (strcmp(p[i].Name, "NULL")) {//用户名与“NULL”不相同时，证明用户未遍历结束，执行一下操作
			for (int num = 0;;) {//将每个用户的软件量初始化为0
				if (!strcmp(p[i].Own_App[0].Name, "NULL")) {//用户第一个软件名为“NULL”
					Person_Owned_nums[i] = 0;//设置该用户软件量为0
					break;
				}
				num++;//数量加一
				if (!strcmp(p[i].Own_App[num].Name, "NULL")) {//第i个软件的名字若为“NULL”，则证明当前用户软件遍历结束
					Person_Owned_nums[i] = num;//将软件量数组对应位置设置为num
					break;
				}
			}
		}
		else {
			int Xia_Biao[100];//创建一个下标数组，其中的值为0，1，2，3......，目标是在将软件量数组进行排序时，将下标数组中对应位置的值进行相同的排序，确保软件量数组中的值在用户结构体数组对应的用户可以找得到
			for (int k = 0; k < 100; k++) Xia_Biao[k] = k;
			int max = Person_Owned_nums[0], maxxiabiao = 0;//选择排序法
			for (int z = 0; z < i; z++) {
				int max = Person_Owned_nums[z];
				for (int j = z; j < i; j++) {
					if (Person_Owned_nums[j] > max) {
						maxxiabiao = j;
						max = Person_Owned_nums[maxxiabiao];
					}
				}
					int tempt = Person_Owned_nums[z];//将软件量数组中的值进行降序排序
					Person_Owned_nums[z] = Person_Owned_nums[maxxiabiao];
					Person_Owned_nums[maxxiabiao] = tempt;
					tempt = Xia_Biao[z];//将下标数组中的值进行相同的操作，使得软件量数组和下标数组中的值的仍然保持一一对应
					Xia_Biao[z] = Xia_Biao[maxxiabiao];
					Xia_Biao[maxxiabiao] = tempt;
			}
			printf("按每个用户拥有的应用数进行降序排序结果如下：\n");
			for (int s = 0; s < i; s++) {//将软件量数组进行排序，其在下标数组中所对应的值--用户结构体数组中的用户下标，也会随之排好序
				printf("%s:%d个应用\n", p[Xia_Biao[s]].Name, Person_Owned_nums[s]);//将下标数组中的值对应的用户结构体数组中的用户一一输出即可
			}
			return 0;
		}
	}
}

void Find_app_owned_person(Person_information* p) {//找到拥有指定软件的用户
	char Name[20];
	int num_own = 0;
	printf("请输入你想查询的软件：");
	scanf_s("%s", Name,20);
	for (int i=0; i < 100; i++) {//遍历循环所有用户
		for (int j = 0; j < 10; j++) {//遍历循环单个用户的所有软件
			if (!strcmp(p[i].Own_App[j].Name, Name)) {//匹配成功
				printf("%s\t", p[i].Name);//输出当前用户姓名
				num_own++;//flag加一
			}
			if (!strcmp(p[i].Own_App[j + 1].Name, "NULL"))
				break;
		}
		if (!strcmp(p[i + 1].Name, "NULL")) break;//下一个用户的姓名为“NULL”，则说明遍历结束
	}
	if (num_own == 0)printf("未查询到拥有此应用的用户！");//如果flag等于0；则说明没有匹配的用户
	else printf("\n以上便是拥有此应用的用户");
}

void Look_All(Person_information* p) {//输出所有用户及其所有软件的信息
	printf("\n注：排版格式：\n用户序号.用户名：\n  软件名 储存容量 开发商 版本号 是否支持中文\n  ............\n");//格式提示
	printf("==================================================\n");
	for (int i = 0; i < 100; i++) {//循环遍历所有用户
		printf("%d.%s:\n",i+1, p[i].Name);//输出用户姓名
		for (int j = 0; j < 10; j++) {//循环输出用户的软件结构体数组的软件信息
			printf("  %s", p[i].Own_App[j].Name);
			printf(" %f ", p[i].Own_App[j].Storage);
			printf(" %s ", p[i].Own_App[j].Developer);
			printf(" %s ", p[i].Own_App[j].Version);
			printf(" %s ", p[i].Own_App[j].Language_CHINA);
			if (!strcmp(p[i].Own_App[j + 1].Name, "NULL"))//下一个软件名为空，软件结构体数组遍历结束
				break;
			printf("\b;\n");//格式控制
		}
		printf("\b。%c", '\n');//格式控制

		if (!strcmp(p[i + 1].Name, "NULL")) break;//下一个用户姓名为“NULL”，用户结构体数组遍历结束
	}
	printf("==================================================\n");
}