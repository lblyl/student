# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# define LEN sizeof(struct Student)
struct Student
{
 char num[20];//ѧ��
 char class[20];
 char name[20];
 int Math;//��ѧ
 int English;//Ӣ��
 int Physic;//����
 int Sum;//�ܷ�
 int rank;//����
 struct Student *next;
};
void ShowMenuT()//���˵���ʾ
{
 char s[10];
 printf("Please enter the password:");
 scanf("%s",s);
 if(strcmp(s,"3120005154")==0)
 {
 printf("\n********************************************************************\n");
 printf("\tWelcome to the Student Scholarship Administration System\n");
 printf("\t1-------------- Input information\n");
 printf("\t2-------------- Show all the information\n");
 printf("\t3-------------- Query\n");
 printf("\t4-------------- Statistics\n");
 printf("\t5-------------- Delete\n");
 printf("\t6-------------- Add\n");
 printf("\t7-------------- Sort\n");
 printf("\t8-------------- Save File\n");
 printf("\t9-------------- Copy File\n");
 printf("\t10------------- Exit\n");
 printf("********************************************************************\n");
 }
 else printf("Password error!Please log out and log back in!\n");
}
void ShowMenuS()//���˵���ʾ
{
 char s[10];
 printf("Please enter the password:");
 scanf("%s",s);
 if(strcmp(s,"123456")==0)
 {
 printf("\n********************************************************************\n");
 printf("\tWelcome to the Student Scholarship Administration System\n");
 printf("\t1-------------- Show all the information\n");
 printf("\t2-------------- Query\n");
 printf("\t3------------- Exit\n");
 printf("********************************************************************\n");
 }
 else printf("Password error!Please log out and log back in!\n");
}
struct Student *input()//����ѧ�����ݴ�������
{
 struct Student *head,*p1,*p2;
 int n=0;//ͳ������ѧ������
 p1=p2=(struct Student *)malloc(LEN);//����һ���µ�Ԫ
 head=NULL;
 printf("----------------------------STUDENT----------------------------*\n");
 printf("|no    |class  |name   |sc1    |sc2    |sc3    |sum    |order  |\n");
 printf("|------|-------|-------|-------|-------|-------|-------|-------|\n");
 scanf("%s",p1->num);
 while(p1->num[0]!='@')//��������жϱ�־
 {
  scanf("%s%s%d%d%d",p1->class,p1->name,&p1->Math,&p1->English,&p1->Physic);
  p1->Sum=0;p1->rank=0;//���ܳɼ����������г�ʼ��
  n++;
  if(n==1)
   head=p1;//������ͷ���г�ʼ��
  else
   p2->next=p1;
  p2=p1;
  p1=(struct Student *)malloc(LEN);//���ٶ�̬�洢��������ʼ��ַ����p1
  scanf("%s",p1->num);
 }
 p2->next=NULL;//����ĩβΪ��
 return head;
}
void Record(struct Student *head)//�������е�����д�뵽�ļ���
{
 FILE *fp;//�����ļ�ָ��fp
 struct Student *p1;
 char s[20];
 p1=head;//��p1ָ������ͷ
 printf("Please enter the file name of the file where the data is stored:");
 scanf("%s",s);//�����ļ���
 if((fp=fopen(s,"w"))==NULL)//������ļ���ʹfpָ����ļ�
 {
  printf("can't open this file\n");
  return;
 }
 while(p1!=NULL)
 {
  fprintf(fp,"%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\n",p1->num,p1->class,p1->name,p1->Math,p1->English,p1->Physic,p1->Sum,p1->rank);
  p1=p1->next;
 }
 if(p1==NULL)//����ɹ������
   printf("Record ok!\n");
 free(p1);
 free(head);//�ͷ�ָ��
 fclose(fp);//�ر��ļ�
}
struct Student *Read_in()//���ļ��ж�ȡ���ݽ���������
{
 FILE *fp;
 struct Student *head,*p2,*p1;
 int n=0;
 char s[20];
 printf("Please enter the filename you want to read in the data:");
 scanf("%s",s);//�����ļ���
 if((fp=fopen(s,"r"))==NULL)
 {
  printf("can't open this file\n");
  return NULL;
 }
 head=NULL;
 p2=p1=(struct Student *)malloc(LEN);
 fscanf(fp,"%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d",p1->num,p1->class,p1->name,&p1->Math,&p1->English,&p1->Physic,&p1->Sum,&p1->rank);
 while(!feof(fp))//�ļ���ȡ�����ı�־
 {
  n++;
  if(n==1)
   head=p1;
  else
   p2->next=p1;
  p2=p1;
  p1=(struct Student *)malloc(LEN);
  fscanf(fp,"%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d",p1->num,p1->class,p1->name,&p1->Math,&p1->English,&p1->Physic,&p1->Sum,&p1->rank);
 }
 //if(feof(fp)!=0) printf("Read in successful");
 p2->next=NULL;
 fclose(fp);//�ر��ļ�
 return head;//���ش���������ͷ
}
void Show_stu_information()//��ʾѧ����Ϣ����
{
 printf("----------------------------STUDENT----------------------------*\n");
 printf("|no    |class  |name   |sc1    |sc2    |sc3    |sum    |order  |\n");
 printf("|------|-------|-------|-------|-------|-------|-------|-------|\n");
 struct Student *p,*head;
 head=Read_in();//����Read_in()����
 p=head;
 while(p!=NULL)
 {
  printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\n",p->num,p->class,p->name,p->Math,p->English,p->Physic,p->Sum,p->rank);
  p=p->next;
 }
}
void ShowMenu3()
{
 printf("\t***********************************************************************\n");
 printf("\t1----------Find a student's personal grade by rank\n");
 printf("\t2----------Check the personal grades of the Top 3 students by class\n");
 printf("\t3----------Search a student's personal grade by grade segment\n");
 printf("\t4----------exit\n");
 printf("\t***********************************************************************\n");
}
void Sort_By_Rank()//����ÿ��ѧ���������ĺ���
{
 struct Student *head,*p1,*p2;
 int i;
 head=Read_in();//��ȡ�ļ��е�ѧ������
 p1=head;
 while(p1!=NULL)
 {
  i=1;
  p2=head;
  while(p2!=NULL)
  {
   if((p1->Sum)<(p2->Sum))
      i++;
   p2=p2->next;
  }
  p1->rank=i;//�ļ�������λ�ò��������е����α��������仯
  p1=p1->next;//��ÿһ�����ݶ����������ݽ��жԱȣ��ó������ݵ�����
 }
 Record(head);//������õ������ٴδ���ļ���
}
void SearchByRank()//����û�����ҵ����ε�ѧ������
{
 struct Student *p1,*head;
 int number;
 head=Read_in();//����Read_in()����
 p1=head;
 if(p1->rank==0)//�ж��Ƿ��������
 {
  printf("No sorting has been performed.Please return to the main menu to perform the sorting operation.\n");
  return;
 }
 printf("Please enter the rank to be queried:");
 scanf("%d",&number);
 printf("----------------------------STUDENT----------------------------*\n");
 printf("|no    |class  |name   |sc1    |sc2    |sc3    |sum    |order  |\n");
 printf("|------|-------|-------|-------|-------|-------|-------|-------|\n");
 while(p1!=NULL)
 {
  if(p1->rank==number)
    printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\n",p1->num,p1->class,p1->name,p1->Math,p1->English,p1->Physic,p1->Sum,p1->rank);
  p1=p1->next;//���������ҵ���������ѧ��
 }
 free(p1);
 free(head);//�ͷ�����
}
void SearchByClass()//��ѯ����༶ǰ�����ĺ���
{
 int i=1;
 char Class[20];
 struct Student *p1,*head,*p2;
 printf("Please enter the class to be queried:for example 20software1\n");
 scanf("%s",Class);//������Ҫ��ѯ�İ༶������
 head=Read_in();//��ȡ�ļ��е�����
 p1=head;
 printf("----------------------------STUDENT----------------------------*\n");
 printf("|no    |class  |name   |sc1    |sc2    |sc3    |sum    |order  |\n");
 printf("|------|-------|-------|-------|-------|-------|-------|-------|\n");
 while(p1!=NULL)
 {
  if(strcmp(Class,p1->class)==0)//�жϻ�ȡ��ѧ�������Ƿ�Ϊ��Ӧ�İ༶
  {
   i=1;
   p2=head;
   while(p2!=NULL)
   {
    if(strcmp(Class,p2->class)==0)//�жϵڶ�����ȡ�������ѧ�������Ƿ�Ϊ��Ӧ�İ༶
     if(p1->Sum<p2->Sum)
       i++;//�����ѧ���ܷ������ڰ༶������
    p2=p2->next;
   }
   if(i<=3)//�жϵ�һ��������ѧ�������Ƿ�Ϊ�༶��ǰ����
    printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\n",p1->num,p1->class,p1->name,p1->Math,p1->English,p1->Physic,p1->Sum,p1->rank);
   else if(i>3)  break;//������ѭ��
  }
  p1=p1->next;//��p1ָ����һ�����
 }
 free(p1);
 free(head);//�ͷ�����
}
void SearchByScore()//���ɼ��β�ѯĳѧ���ĸ��˳ɼ��ĺ���
{
 int i=0,score1,score2;
 struct Student *p1,*head;
 char course[10]={0};
 printf("Please input the score segment you want to query:for example:70-80\n");
 scanf("%d-%d",&score1,&score2);
 if(score1>=score2)//�жϷ����������Ƿ���ȷ
 {
  printf("score2 must be bigger than score1!\n");
  return;
 }
 printf("Please input the course you want to inquire:(Math or English or Physic)\n");
 scanf("%s",course);//����Ҫ��ѯ�Ŀ�Ŀ
 if(!(strcmp(course,"Math")==0||strcmp(course,"English")==0||strcmp(course,"Physic")==0))
 {
  printf("Not found this course\n");//�ж�����Ŀ�Ŀ�Ƿ���ȷ
  return;
 }
 head=Read_in();
 p1=head;
 while(p1!=NULL)
 {
  if(strcmp(course,"Math")==0)//��ѧ��Ŀ
  {
   if(p1->Math>=score1&&p1->Math<=score2)
   {
    printf("-----------STUDENT-------------*\n");
    printf("|no    |class  |name   |Math   |\n");
    printf("|------|-------|-------|-------|\n");
    printf("%s\t%s\t%s\t%d\n",p1->num,p1->class,p1->name,p1->Math);
    i++;
   }
  }else if(strcmp(course,"English")==0)//Ӣ���Ŀ
  {
   if(p1->English>=score1&&p1->English<=score2)
   {
    printf("-----------STUDENT-------------*\n");
    printf("|no    |class  |name   |English|\n");
    printf("|------|-------|-------|-------|\n");
    printf("%s\t%s\t%s\t%d\n",p1->num,p1->class,p1->name,p1->English);
    i++;
   }
  }else if(strcmp(course,"Physic")==0)
  {
   if(p1->Physic>=score1&&p1->Physic<=score2)
   {
    printf("-----------STUDENT-------------*\n");
    printf("|no    |class  |name   |Physic |\n");
    printf("|------|-------|-------|-------|\n");
    printf("%s\t%s\t%s\t%d\n",p1->num,p1->class,p1->name,p1->Physic);
    i++;
   }
  }
  p1=p1->next;
 }
  if(i==0)//�û����������û��ѧ����Ϣ�����
   printf("no the student adopt to adition\n");
}
void Search()
{
 int i;
 do
 {
  ShowMenu3();
  printf("\tplease choose the option:");
  scanf("%d", &i);
  switch(i)
  {
   case 1: SearchByRank(); break;
   case 2: SearchByClass(); break;
   case 3: SearchByScore(); break;
   case 4: break;
   default:printf("input error!\n");
  }
 }while(i!=4);
}
void ShowMenu4()
{
 printf("\t****************************************\n");
 printf("\t1--------------Total\n");
 printf("\t2--------------Grouping statistics\n");
 printf("\t3----------exit\n");
 printf("\t****************************************\n");
}
void StatByStu()//����ÿ��ѧ�����ܳɼ��ĺ���
{
 struct Student *head,*p1;
 head=Read_in();
 p1=head;
 while(p1!=NULL)
 {
  p1->Sum=p1->Math+p1->English+p1->Physic;
  p1=p1->next;//��ÿһ�������ֽܷ��м���
 }
 Record(head);//�Ѽ������ݱ��浽�ļ���
}
void StatByClass()//����ÿ������ܳɼ��ĺ���
{
 char Class[10][10],s[20];
 int ClassSum[10]={0};
 FILE *fp;
 struct Student *head,*p1;
 int i=0,j,flag=1;//i��¼class����,flagΪ�����°༶���ֵı�־
 head=Read_in();
 p1=head;
 while(p1!=NULL)
 {
  flag=1;
  for(j=0;j<i;j++)//��������°༶����
  {
   if(strcmp(Class[j],p1->class)==0)
   {
    flag=0;break;//������ѭ��
   }
  }
  if(flag==1)//������°༶���֣����°༶�����ƴ��浽class��
   strcpy(Class[i++],p1->class);
  p1=p1->next;//ʹp1ָ����һ�����
 }
 p1=head;
 while(p1!=NULL)
 {
  for(j=0;j<i;j++)//����ÿ������ܷ�
  {
   if(strcmp(p1->class,Class[j])==0)
   {
    ClassSum[j]+=p1->Sum;
   }
  }
  p1=p1->next;
 }
 if((fp=fopen("D:\\llb\\student.txt","a"))==NULL)
 {
  printf("can't open this file\n");
  return;
 }
 for(j=0;j<i;j++)
 {
  fprintf(fp,"%s %d\n",Class[j],ClassSum[j]);
  if(j==i-1) printf("Record OK\n");
 }
 fclose(fp);//�ر��ļ�
}
void Statistics()
{
 int i;
 do
 {
  ShowMenu4();
  printf("\tplease choose the option:");
  scanf("%d",&i);
  switch(i)
  {
   case 1: StatByStu(); break;
   case 2: StatByClass(); break;
   case 3: break;
   default: printf("input error!\n");
  }
 }while(i!=3);
}
struct Student *stu_rank(struct Student *head)//��ѧ�����������ĺ���
{
 int i;
 struct Student *p1,*p2;
 p1=head;
 while(p1!=NULL)
 {
  i=1;
  p2=head;
  while(p2!=NULL)
  {
   if(p1->Sum<p2->Sum) i++;
   p2=p2->next;
  }
  p1->rank=i;
  p1=p1->next;
 }
 return head;
}
struct Student *SortByRank(struct Student *head)//����������ʵ�ִ�С��������, �����������ͷָ�롣
{
 struct Student t,*p1,*p2,*p3;
 for(p1=head;p1!=NULL;p1=p1->next)
 {
  p3=p1;
  for(p2=p1->next;p2!=NULL;p2=p2->next)
  {
   if(p3->Sum<p2->Sum) p3=p2;
  }
  if(p3!=p1)//��������е����ݽ��н���
  {
   t.English=p1->English;
   t.Math=p1->Math;
   t.Physic=p1->Physic;
   t.Sum=p1->Sum;
   strcpy(t.class,p1->class);
   strcpy(t.num,p1->num);
   strcpy(t.name,p1->name);
   p1->English=p3->English;
   p1->Math=p3->Math;
   p1->Physic=p3->Physic;
   p1->Sum=p3->Sum;
   strcpy(p1->class,p3->class);
   strcpy(p1->num,p3->num);
   strcpy(p1->name,p3->name);
   p3->English=t.English;
   p3->Math=t.Math;
   p3->Physic=t.Physic;
   p3->Sum=t.Sum;
   strcpy(p3->class,t.class);
   strcpy(p3->num,t.num);
   strcpy(p3->name,t.name);
  }
    }
 head=stu_rank(head);
 Record(head);
 return head;
}
struct Student *SortBynum(struct Student *head)//������ѧ��ʵ�ִ�С��������, �����������ͷָ�롣
{
 struct Student *p1,*p2,*p3;
 struct Student t;
 for(p1=head;p1!=NULL;p1=p1->next)
 {
  p3=p1;
  for(p2=p1->next;p2!=NULL;p2=p2->next)
  {
   if(strcmp(p3->num,p2->num)>0) p3=p2;
  }
  if(p3!=p1)
  {
   t.English=p1->English;
   t.Math=p1->Math;
   t.Physic=p1->Physic;
   strcpy(t.class, p1->class);
   strcpy(t.num, p1->num);
   strcpy(t.name, p1->name);
   p1->English=p3->English;
   p1->Math=p3->Math;
   p1->Physic=p3->Physic;
   strcpy(p1->class,p3->class);
   strcpy(p1->num,p3->num);
   strcpy(p1->name,p3->name);
   p3->English=t.English;
   p3->Math=t.Math;
   p3->Physic=t.Physic;
   strcpy(p3->class,t.class);
   strcpy(p3->num,t.num);
   strcpy(p3->name,t.name);
  }
    }
 p1=head;
 while(p1!=NULL)
 {
  p1->Sum=p1->Math+p1->English+p1->Physic;
  p1=p1->next; //ͳ��ÿ��ѧ�����ܷ�;
 }
 head=stu_rank(head);//����
 return head;
}
void ShowSortBy(int i)//��ʾ�����Ľ��
{
 struct Student *head,*p1;
 //Sort_By_Rank();
 head=Read_in();
 p1=head;
 if(i==1)
 {
  p1=SortByRank(p1);
 }
 else if(i==2)
 {
  p1=SortBynum(p1);
 }
 printf("----------------------------STUDENT----------------------------*\n");
 printf("|no    |class  |name   |sc1    |sc2    |sc3    |sum    |order  |\n");
 printf("|------|-------|-------|-------|-------|-------|-------|-------|\n");
 while(p1!=NULL)
 {
  printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\n",p1->num,p1->class,p1->name,p1->Math,p1->English,p1->Physic,p1->Sum,p1->rank);
  p1=p1->next;
 }
}
void ShowSort()
{
 int i;
 do
 {
  printf("\t****************************************\n");
  printf("\t1----------sort by the rank for all student\n");
  printf("\t2----------sort by the num for all student\n");
  printf("\t3----------Exit!\n");
  printf("\t****************************************\n");
  printf("\tplease choose the option:: ");
  scanf("%d", &i);
  switch(i)
  {
   case 1: ShowSortBy(i); break;
   case 2: ShowSortBy(i); break;
   case 3: break;
   default :printf("input error!\n");
  }
 }while(i!=3);
}
void Delete()
{
 struct Student *head,*p1,*p2;
 char number[10];
 int flag=0;//�ж��û�����ѧ���Ƿ���ȷ�ı�־
 head=Read_in();
 printf("please input the number you want to delete:\n");
 scanf("%s",number);
 p1=head;//ʹp1ָ���һ�����
 p2=NULL;
 while(p1!=NULL)//ȷ��p1���滹�н��
 {
  if(strcmp(p1->num,number)==0)//p1ָ�����Ҫ�ҵĽ��
  {
   if(p2==NULL)//�жϴ�ʱp1�Ƿ�Ϊͷ���
   {
    head=p1->next;//ɾ��ͷ���
    flag=1;
    break;
   }
   else
   {
    if(p1->next==NULL)//�ж�p1�Ƿ�Ϊβ���
    {
     p2->next=NULL;//ɾ��β���
     flag=1;
     break;
    }
    p2->next=p1->next;//ɾ���м�Ľ�㣬����һ�����ĵ�ַ����ǰһ�����
    flag=1;
    break;
   }
  }
  p2=p1;
  p1=p1->next;//p1����һ�����
 }
 if(flag==0) printf("not found this student!\n");
 else Record(head);//ɾ������Ϣ���浽�ļ���
}
void  Add()
{
 struct Student *head1,*head2,*p1,*head=NULL;
 head1=Read_in();
 head2=input();
 p1=head1;
 if(p1!=NULL)
 {
  while(p1->next!=NULL)
     p1=p1->next;//Ѱ������β��
  head=head1;//������ͷ��
  p1->next=head2;//�������ѧ����Ϣ�Ž�����β��
 }
 else head=head2;//�����û�����ݣ������ӵ�ѧ������Ϊ��һ������
 if(head==NULL) printf("Add failure");
 else
 {
  printf("Add success");
  Record(head);//������Ϣ����Ϣ���浽�ļ���
 }
}
void SaveFile()
{
 FILE *fp;
 char filename[30];
 struct  Student *head,*p1;
 printf("Please enter the file name of the file where the data is stored:");
 scanf("%s",filename);
 getchar();
 if((fp=fopen(filename,"w"))==NULL)
 {
  printf("open file error");
  return;
 }
 head=Read_in();
 p1=head;
 while(p1!=NULL)
 {
  fprintf(fp,"%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\n",p1->num,p1->class,p1->name,p1->Math,p1->English,p1->Physic,p1->Sum,p1->rank);
  p1=p1->next;
 }
 if(p1==NULL) printf("Save OK");
 free(head);
 free(p1);
 fclose(fp);
}
void CopyFile()
{
 FILE *fp,*fp1;
 char filename[30];
 char filename1[30];
 struct  Student *p1,stu;
 printf("please input the name of the file you want to copy\n");
 scanf("%s",filename);
 getchar();
 printf("please input the name of the file you want to copy to\n");
 scanf("%s",filename1);
 getchar();
 if((fp=fopen(filename,"r"))==NULL)
 {
  printf("open infile error");
  return;
 }
 if((fp1=fopen(filename1,"w"))==NULL)
 {
  printf("open outfile error");
  return;
 }
 p1=&stu;
 while(!feof(fp))
 {
  fscanf(fp,"%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d",p1->num,p1->class,p1->name,&p1->Math,&p1->English,&p1->Physic,&p1->Sum,&p1->rank);
  if(feof(fp)!=0) {printf("Copy OK");break;}
  fprintf(fp1,"%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\n",p1->num,p1->class,p1->name,p1->Math,p1->English,p1->Physic,p1->Sum,p1->rank);
 }
 fclose(fp);
 fclose(fp1);
}
int main()
{
 int i,j;//�û�ѡ��Ĺ��ܵ����
 printf("\n********************************************************************\n");
 printf("\t1-------------- Teacher login\n");
 printf("\t2-------------- Student login\n");
 printf("********************************************************************\n");
 printf("\tPlease input the options you want to use:");
 scanf("%d",&j);
 switch(j)
 {
  case 1:ShowMenuT();break;
  case 2:ShowMenuS();break;
  case 3:break;
  default: printf("input error!");
 }
 do
 {
  printf("\tPlease input the options you want to use:");
  if(j==2)
  {
   scanf("%d",&i);
   switch(i)
   {
    case 1: Show_stu_information(); break;
    case 2: Search(); break;
    case 3: break;
    default: printf("input error!\n");
   }
  }
  if(j==1)
  {
  scanf("%d",&i);
  switch(i)
  {
   case 1: Record(input()); break;
   case 2: Show_stu_information(); break;
   case 3: Search(); break;
   case 4: Statistics(); break;
   case 5: Delete(); break;
   case 6: Add(); break;
   case 7: ShowSort(); break;
   case 8: SaveFile();break;
   case 9: CopyFile();break;
   case 10: break;
   default: printf("input error!");
  }
  }
 }while(i!=10);
 system("cls");
 return 0;
}
