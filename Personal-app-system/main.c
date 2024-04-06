#include <stdio.h>
#include <string.h>
#include <io.h>
void fu_chu_zhi(Person_information);//ģ�麯������
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

typedef struct App {//����ṹ�壬�����������Ϣ
	char Name[20];
	float Storage;
	char Developer[20];
	char Version[10];
	char Language_CHINA[5];
}App;

typedef struct Person_information {//�û��ṹ��
	char Name[20];
	App Own_App[10];//������һ����СΪʮ������ṹ�����飬���ڴ洢�������Ϣ
}Person_information;

int main() {//ͼ�ν���Ĵ�ӡ
	printf("----------------------------------------\n���ֿ�ִ�еĲ�������Ӧ�ı�����£�\n");
	printf("1, ����û���Ϣ\n2, �޸��û�����\n3, ɾ���û�\n");
	printf("4,��������û�ӵ�����\n5,�޸������û�ӵ���������Ϣ\n6,ɾ�������û������Ϣ\n");
	printf("7,��ÿ���û�ӵ�е�Ӧ�������н�������\n8,����Ӧ�õ������û�\n");
	printf("9,�鿴�����û���Ϣ\n");
	printf("�������������,�˳�����\n----------------------------------------\n");
	Person_information All_person[100];//���ڴ��п�����һ����СΪ100���û��ṹ�����飬�洢�û���Ϣ���������ݵķ��ʺͲ���
	Person_information* All_person_pointer = &All_person;//���û��ṹ������ĵ�ַ��ֵ��All_person_pointerָ�룬���ں�����������
	fu_chu_zhi(All_person_pointer);
	Load(All_person_pointer);//���ļ��е����ݼ��ص�ԭ�ȿ��ٺõ��û��ṹ��������
	while (1) {//�����û������ֵ����ƥ�䣬whileѭ����֤���ڲ�������Ϊ��ֹ������³����һֱ������ȥ
		printf("\n�밴����Ҫִ�еĲ��������Ӧ�ı�ţ�");
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
		default:printf("�������н���");upload(All_person_pointer);return 0;//upload�������û��ṹ�������е����ݴ���ļ��У�����ļ��ر�
		}
	}
}

void fu_chu_zhi(Person_information* p) {//���û��ṹ������Ĳ���λ������ǣ����ļ���ȡ���û��ṹ��������ʱ��δ�����ǵ�������δ�䣬��Ϊ���ա�������ȷ�������ʵ�����ô�С
	for (int i = 0; i < 100; i++) {
		strcpy_s((p+i)->Name,5,"NULL");//���û��ṹ�������ÿһ���û�������Ϊ��NULL��
		for (int j = 0; j < 10; j++)
			strcpy_s((p + i)->Own_App[j].Name ,5,"NULL");//�������û�����������ṹ�������������������Ϊ��NULL��
	}
}

void Load(Person_information* p) {//���ļ��е�����������û��ṹ��������
	FILE* fp;
	if (_access("D:\project\c\Personal app system\Personapp", 0)) {//�ж��ļ��Ƿ����
		fopen_s(&fp, "D:\project\c\Personal app system\Personapp", "w");//�ļ�����������ֻ����ʽ����һ��
		fclose(fp);
		FILE* fp;
		printf("���ļ�δ���ڣ���Ϊ�㴴����һ�������κ����ݵ����ļ���\n�˴������������ִ�в���1-����û�����ֹ���ִ����ʽ��\n");
		return 0;
	}
	fopen_s(&fp, "D:\project\c\Personal app system\Personapp", "r");//��ֻ����ʽ���ļ������ļ���ַ��ֵ��fpָ��
	int i = 0;
	while (1) {//whileѭ�������ļ���ȡ��ĩβʱ���ᱻ����
		if (feof(fp)) break; //��ȡ���ļ�ĩβʱ��feof(fp)��Ż�һ������ֵ������ѭ��
		else {//���ļ��е����ݶ�ȡ���û��ṹ��������
			fscanf_s(fp, "%s", (p + i)->Name,20);
			fscanf_s(fp, "%s", (p + i)->Own_App[0].Name,20);
			fscanf_s(fp, "%f", &(p + i)->Own_App[0].Storage);
			fscanf_s(fp, "%s", (p + i)->Own_App[0].Developer,20);
			fscanf_s(fp, "%s", (p + i)->Own_App[0].Version,10);
			fscanf_s(fp, "%s", (p + i)->Own_App[0].Language_CHINA,5);
			char endyn[5]={0};
			fscanf_s(fp, "%s",endyn, 5);//��ȡÿ��Ӧ�ú��ص����õ�flag������ȷ����ǰӦ�ý������ǵ�ǰ�û�����һ��Ӧ�û�����һ���û�
			for(int j=1;endyn[0] == 'n'; j++) {//��flag����n��ͷʱ����ȷ����ǰ�û��������û��������ϣ���������
				fscanf_s(fp, "%s", (p + i)->Own_App[j].Name, 20);
				fscanf_s(fp, "%f", &(p + i)->Own_App[j].Storage);
				fscanf_s(fp, "%s", (p + i)->Own_App[j].Developer, 20);
				fscanf_s(fp, "%s", (p + i)->Own_App[j].Version, 10);
				fscanf_s(fp, "%s", (p + i)->Own_App[j].Language_CHINA, 5);
				fscanf_s(fp, "%s", endyn, 5);//������ȡ��������flag
			}
			i++;//��ǰ�û������ȡ��󣬽��û��ṹ��������±�����ƶ�һλ������������һ���û�������
		}

	}fclose(fp);//�ر��ļ�
}

void upload(Person_information* p) {//���ṹ�������е��û����뵽�ļ���
	FILE* fp;
	fopen_s(&fp, "D:\project\c\Personal app system\Personapp", "w");//�Զ���ķ�ʽ���ļ�
	for (int i = 0;; i++) {//ѭ������ÿһ���û����������Ϣ
		fprintf(fp,"%s ", p[i].Name);
		for (int j = 0;; j++) {//ѭ�����뵱ǰ�û���ÿһ�������Ϣ
			fprintf(fp,"%s ", p[i].Own_App[j].Name);
			fprintf(fp,"%f ", p[i].Own_App[j].Storage);
			fprintf(fp,"%s ", p[i].Own_App[j].Developer);
			fprintf(fp,"%s ", p[i].Own_App[j].Version);
			fprintf(fp,"%s ", p[i].Own_App[j].Language_CHINA);
			if (!strcmp(p[i].Own_App[j + 1].Name, "NULL"))//����һ�����������Ϊ��NULL��ʱ������������
				break;
			fprintf(fp,"%s ", "no");//����flag���������뵱ǰ�û�����һ�����
		}
		fprintf(fp,"%s ", "yes");//����flag��Ԣ�⵱ǰ�û�����������
		if (!strcmp(p[i + 1].Name, "NULL")) break;//��һ���û���Ϊ��NULL��ʱ���û��������
	}fclose(fp);
}

void Add_person(Person_information* p) {//����û�
	FILE* fp;
	fopen_s(&fp, "D:\project\c\Personal app system\Personapp", "a");//��׷��д��ķ�ʽ���ļ�
	char name[20];
	int num;
	printf("������������û���������");
	scanf_s("%s", name,20);
	for (int i = 0;; i++) {//��������������Ѵ��ڵ��û��������жԱȣ������û��Ƿ����
		if (!strcmp(p[i].Name, name)) {
			printf("���û��Ѵ��ڣ�");
			return 0;
		}
		if (!strcmp(p[i + 1].Name, "NULL"))break;//�û��������궼û�������ģ����˳���ǰѭ��
	}
	fprintf(fp, "%s ", name);//���û�����д���ļ�
	printf("��������û�����ӵ������Ŀ��");
	scanf_s("%d", &num);
	for (int i = 1; i <= num; i++) {//�������Ϣд���ļ�
		printf("��ֱ������%i����������֣������������̣��汾�ţ��Ƿ�֧�����ĵ����\n", i);
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
		if(i==num)fprintf(fp, "%s ", "yes");//��ÿһ��������������ǣ�ȷ��������������Ǳ��������Ǳ���û�
		else fprintf(fp,"%s ","no");
	}
	fclose(fp);
	Load(p);//�����ݴ��Ѹ��µ��ļ��ж�ȡ������ȷ���û��ṹ�������ͬ������
}

void Modify_person(Person_information* p) {//�޸��û�����
	printf("�����������޸��û���������");
	char Name_modified[20];
	scanf_s("%s", Name_modified,20);//�����޸�ǰ���������Թ�����
	for (int i = 0;; i++) {//���û��������б���ƥ��
		if (!strcmp(p[i].Name, Name_modified)) {//ƥ��ɹ�
			char Name_to_be_modified[20];
			printf("�������޸ĺ���û�������");//�����޸ĺ���������Թ��޸�
			scanf_s("%s", Name_to_be_modified,20);
			strcpy_s(p[i].Name,20, Name_to_be_modified);
			printf("�ѽ���Ϊ%s�޸�Ϊ%s", Name_modified, Name_to_be_modified);
			upload(p);//�浽�ļ���
			break;
		}
		if (!strcmp(p[i + 1].Name, "NULL")) { //ƥ��ʧ��
			printf("������˼��û���ҵ����Ŀ���û���");
			break; 
		}
	}
}

void Deleted_person(Person_information* p) {//ɾ���û�
	printf("����������ɾ���û�������:");
	char name_Deleted[20];
	scanf_s("%s", name_Deleted,20);//�����û�����
	for (int i = 0;; i++) {//ѭ������
		if (!strcmp(p[i].Name, name_Deleted)) {//ƥ��ɹ�
			for (int j = i;; j++) {
				strcpy_s(p[j].Name, 20, p[j + 1].Name);//�Ӵ�ɾ�����û���ʼ������ǰ�û���������һ���û���������
				for (int k = 0;k<10; k++) {//�Ӵ�ɾ�����û���ʼ������ǰ�û�����ṹ�������Ӧ�±�λ������һ���û��������
					strcpy_s(p[j].Own_App[k].Name, 20, p[j + 1].Own_App[k].Name);
					p[j].Own_App[k].Storage = p[j + 1].Own_App[k].Storage;
					strcpy_s(p[j].Own_App[k].Developer, 20, p[j + 1].Own_App[k].Developer);
					strcpy_s(p[j].Own_App[k].Version, 10, p[j + 1].Own_App[k].Version);
					strcpy_s(p[j].Own_App[k].Language_CHINA, 5, p[j + 1].Own_App[k].Language_CHINA);
					if (!strcmp(p[j + 1].Own_App[k + 1].Name, "NULL")) {//����һ���û�����һ�������Ϊ��NULL��ʱ
						strcpy_s(p[j].Own_App[k + 1].Name,5, "NULL");//��ǰ�û�����һ�����������Ϊ��NULL������ֹ��ǰ�û��������Ŀ������һ���û�
						break;
					}
				}
				if (!strcmp(p[j + 2].Name, "NULL")) {//���¸��û�����Ϊ��NULL��ʱ
					strcpy_s(p[j + 1].Name, 20, "NULL");//����һ���û���������Ϊ��NULL������Ϊ��һ���û������һ���û������û�пɸ�������
					break;
				}
			}
			return 0;
		}
		else if (!strcmp(p[i + 1].Name, "NULL")) {//�û�����ƥ��ʧ��
			printf("�Բ���û���ҵ����û�\n");
			return 0;
		}
	}
}

void Add_person_app(Person_information* p) {//����û����
	printf("�������������������û���������");
	char Name_add_app[20];
	scanf_s("%s", Name_add_app, 20);//����Ŀ���û�����
	for (int i = 0;; i++) {//ѭ�������û��ṹ�����û�������ƥ��Ŀ���û�����
		if (!strcmp(p[i].Name, Name_add_app)) {//ƥ��ɹ�
			for (int j = 0;; j++)//������ṹ��������±�����ƽ�
				if (!strcmp(p[i].Own_App[j].Name, "NULL")) {//ȷ�����û��ṹ�������ṹ�������±굽��յ�λ�ã��������������Ӳ���
					printf("��ֱ����뽫�����������֣������������̣��汾�ţ��Ƿ�֧�����ĵ����\n", i);
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
			
			if (!strcmp(p[i + 1].Name, "NULL")) {//ƥ��ʧ��
				printf("������˼��û���ҵ����Ŀ���û���\n");
				return 0;
			}
		}
	}

void Modify_person_app(Person_information* p) {//�޸��û������Ϣ
	char Name[20], App[20], Attrrbute[20], Attrubute_zhi[20];//�����û���������������������޸ĺ������ֵ
	printf("��������Ŀ���û�����");
	scanf_s("%s", Name,20);
	for (int i = 0;; i++) {//�ƽ��û��ṹ�����飬��Ŀ���û��������е��û���ƥ��
		if (!strcmp(p[i].Name, Name)) {//�û���ƥ��ɹ�
			printf("�����뽫�޸����Ե��������:");
			scanf_s("%s", App, 20);
			for (int j = 0;; j++) {//�ƽ���ǰ�û�������ṹ�������±꣬��Ŀ��������������е������ƥ��
				if (!strcmp(p[i].Own_App[j].Name, App)) {//ƥ��ɹ�
					while (1) {
						printf("�����뽫�޸ĵ����Ժ��޸ĺ��ֵ��");
						scanf_s("%s", Attrrbute,20);//�����������������������ÿ�����Ե����ֽ��жԱ�
						if (!strcmp(Attrrbute, "Storage")) {//����������������롰Storage����ͬ�����޸ĵ�ǰ�����������С�������ж�ͬ��
							float Attribute_F_zhi;
							scanf_s("%f", &Attribute_F_zhi);
							p[i].Own_App[j].Storage = Attribute_F_zhi;
							upload(p);
							printf("�޸ĳɹ���");
							return 0;
						}
						scanf_s("%s", Attrubute_zhi,20);
						if (!strcmp(Attrrbute, "Name")) { 
							strcpy_s(p[i].Own_App[j].Name, 20, Attrubute_zhi); 
							upload(p);
							printf("�޸ĳɹ���");
							return 0; 
						}
						if (!strcmp(Attrrbute, "Developer")) { 
							strcpy_s(p[i].Own_App[j].Developer, 20, Attrubute_zhi); 
							upload(p);
							printf("�޸ĳɹ���");
							return 0; 
						}
						if (!strcmp(Attrrbute, "Version")) { 
							strcpy_s(p[i].Own_App[j].Version, 10, Attrubute_zhi); 
							upload(p);
							printf("�޸ĳɹ���");
							return 0; 
						}
						if (!strcmp(Attrrbute, "Language_CHINA")) { 
							strcpy_s(p[i].Own_App[j].Language_CHINA, 5, Attrubute_zhi); 
							upload(p);
							printf("�޸ĳɹ���");
							return 0; 
						}//ȫ��ƥ��ʧ��
						printf("ϵͳ�����������������������밴Name,Developer,Version,Language_CHINA�������룬лл");
					}
				}
				if (!strcmp(p[i].Own_App[j + 1].Name, "NULL")) {//�����ƥ��ʧ��
					printf("������˼��û���ҵ����Ŀ�������\n");
					return 0;
				}
			}
			if (!strcmp(p[i + 1].Name, "NULL")) {//�û���ƥ��ʧ��
				printf("������˼��û���ҵ����Ŀ���û���\n");
				return 0;
			}
		}
	}
}

void Deleted_person_app(Person_information * p) {//ɾ���û����
	printf("����������ɾ����Ӧ�õ������û���");
	char App_Name[20];
	scanf_s("%s", App_Name,20);
	for (int i = 0;; i++) {//ѭ���ƽ��û��ṹ��������±꣬�����û�������Ŀ���û���ƥ��
		if (!strcmp(App_Name, p[i].Name)) {//ƥ��ɹ�
			char App_deleted[20];
			printf("����������ɾ����Ӧ��:");
			scanf_s("%s", App_deleted,20);
			for (int j = 0;; j++) {//ѭ���ƽ�����ṹ�������±꣬�������������Ŀ���������ƥ��
				if (!strcmp(App_deleted, p[i].Own_App[j].Name)) {//ƥ��ɹ�
					for (int k = j;; k++) {//ѭ���ƽ�����ṹ�������±꣬��ÿ�����ʵ�и��ǲ���
						if (!strcmp(p[i].Own_App[k + 1].Name,"NULL")) {
							strcpy_s(p[i].Own_App[k].Name, 5, "NULL");//�����һ���������������Ϊ��
							return 0;
						}//�ӵ�ǰ�����ʼ���ú�����������ǰһ���������Ϣ
						strcpy_s(p[i].Own_App[k].Name, 20, p[i].Own_App[k + 1].Name);
						p[i].Own_App[j].Storage = p[i].Own_App[j].Storage;
						strcpy_s(p[i].Own_App[k].Developer, 20, p[i].Own_App[k + 1].Developer);
						strcpy_s(p[i].Own_App[k].Version, 20, p[i].Own_App[k + 1].Version);
						strcpy_s(p[i].Own_App[k].Language_CHINA, 20, p[i].Own_App[k + 1].Language_CHINA);
						if (!strcmp(p[i].Own_App[k + 2].Name, "NULL")) {
							strcpy_s(p[i].Own_App[k+1].Name, 5, "NULL");
							printf("%s�Ѿ���ɾ���ɹ�!", App_deleted);
							return 0;
						}
					}
				}
				else if (!strcmp(p[i].Own_App[j + 1].Name, "NULL")) {//�����ƥ��ʧ��
					printf("������˼��û���ҵ���Ӧ��\n");
					return 0;
				}
			}
		}
		else if (!strcmp(p[i + 1].Name, "NULL")) {//�û���ƥ��ʧ��
			printf("������˼��û���ҵ����û���");
			return 0;
		}
	}
}

void Sorted_person_Num_apps(Person_information* p) {//���û�ӵ�е���������н�����
	
	if(!strcmp(p[0].Name,"NULL")) {//����û��ṹ�������Ƿ�Ϊ��
		printf("�û��б�Ϊ�ա�\n");
		return 0;
	}
	int Person_Owned_nums[100];//�����û�����������飬���û��ṹ����������û�һһ��Ӧ��ͨ���±꽨����ϵ
	for (int i = 0;; i++) {//ѭ������ÿ���û��ṹ�壬���û�������������������������
		if (strcmp(p[i].Name, "NULL")) {//�û����롰NULL������ͬʱ��֤���û�δ����������ִ��һ�²���
			for (int num = 0;;) {//��ÿ���û����������ʼ��Ϊ0
				if (!strcmp(p[i].Own_App[0].Name, "NULL")) {//�û���һ�������Ϊ��NULL��
					Person_Owned_nums[i] = 0;//���ø��û������Ϊ0
					break;
				}
				num++;//������һ
				if (!strcmp(p[i].Own_App[num].Name, "NULL")) {//��i�������������Ϊ��NULL������֤����ǰ�û������������
					Person_Owned_nums[i] = num;//������������Ӧλ������Ϊnum
					break;
				}
			}
		}
		else {
			int Xia_Biao[100];//����һ���±����飬���е�ֵΪ0��1��2��3......��Ŀ�����ڽ�����������������ʱ�����±������ж�Ӧλ�õ�ֵ������ͬ������ȷ������������е�ֵ���û��ṹ�������Ӧ���û������ҵõ�
			for (int k = 0; k < 100; k++) Xia_Biao[k] = k;
			int max = Person_Owned_nums[0], maxxiabiao = 0;//ѡ������
			for (int z = 0; z < i; z++) {
				int max = Person_Owned_nums[z];
				for (int j = z; j < i; j++) {
					if (Person_Owned_nums[j] > max) {
						maxxiabiao = j;
						max = Person_Owned_nums[maxxiabiao];
					}
				}
					int tempt = Person_Owned_nums[z];//������������е�ֵ���н�������
					Person_Owned_nums[z] = Person_Owned_nums[maxxiabiao];
					Person_Owned_nums[maxxiabiao] = tempt;
					tempt = Xia_Biao[z];//���±������е�ֵ������ͬ�Ĳ�����ʹ�������������±������е�ֵ����Ȼ����һһ��Ӧ
					Xia_Biao[z] = Xia_Biao[maxxiabiao];
					Xia_Biao[maxxiabiao] = tempt;
			}
			printf("��ÿ���û�ӵ�е�Ӧ�������н������������£�\n");
			for (int s = 0; s < i; s++) {//�����������������������±�����������Ӧ��ֵ--�û��ṹ�������е��û��±꣬Ҳ����֮�ź���
				printf("%s:%d��Ӧ��\n", p[Xia_Biao[s]].Name, Person_Owned_nums[s]);//���±������е�ֵ��Ӧ���û��ṹ�������е��û�һһ�������
			}
			return 0;
		}
	}
}

void Find_app_owned_person(Person_information* p) {//�ҵ�ӵ��ָ��������û�
	char Name[20];
	int num_own = 0;
	printf("�����������ѯ�������");
	scanf_s("%s", Name,20);
	for (int i=0; i < 100; i++) {//����ѭ�������û�
		for (int j = 0; j < 10; j++) {//����ѭ�������û����������
			if (!strcmp(p[i].Own_App[j].Name, Name)) {//ƥ��ɹ�
				printf("%s\t", p[i].Name);//�����ǰ�û�����
				num_own++;//flag��һ
			}
			if (!strcmp(p[i].Own_App[j + 1].Name, "NULL"))
				break;
		}
		if (!strcmp(p[i + 1].Name, "NULL")) break;//��һ���û�������Ϊ��NULL������˵����������
	}
	if (num_own == 0)printf("δ��ѯ��ӵ�д�Ӧ�õ��û���");//���flag����0����˵��û��ƥ����û�
	else printf("\n���ϱ���ӵ�д�Ӧ�õ��û�");
}

void Look_All(Person_information* p) {//��������û����������������Ϣ
	printf("\nע���Ű��ʽ��\n�û����.�û�����\n  ����� �������� ������ �汾�� �Ƿ�֧������\n  ............\n");//��ʽ��ʾ
	printf("==================================================\n");
	for (int i = 0; i < 100; i++) {//ѭ�����������û�
		printf("%d.%s:\n",i+1, p[i].Name);//����û�����
		for (int j = 0; j < 10; j++) {//ѭ������û�������ṹ������������Ϣ
			printf("  %s", p[i].Own_App[j].Name);
			printf(" %f ", p[i].Own_App[j].Storage);
			printf(" %s ", p[i].Own_App[j].Developer);
			printf(" %s ", p[i].Own_App[j].Version);
			printf(" %s ", p[i].Own_App[j].Language_CHINA);
			if (!strcmp(p[i].Own_App[j + 1].Name, "NULL"))//��һ�������Ϊ�գ�����ṹ�������������
				break;
			printf("\b;\n");//��ʽ����
		}
		printf("\b��%c", '\n');//��ʽ����

		if (!strcmp(p[i + 1].Name, "NULL")) break;//��һ���û�����Ϊ��NULL�����û��ṹ�������������
	}
	printf("==================================================\n");
}