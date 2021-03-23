# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# define LEN sizeof(struct Student)
struct Student
{
 char num[20];//学号
 char class[20];
 char name[20];
 int Math;//数学
 int English;//英语
 int Physic;//物理
 int Sum;//总分
 int rank;//排名
 struct Student *next;
};
void ShowMenuT()//主菜单显示
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
void ShowMenuS()//主菜单显示
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
struct Student *input()//输入学生数据创建链表
{
 struct Student *head,*p1,*p2;
 int n=0;//统计输入学生个数
 p1=p2=(struct Student *)malloc(LEN);//开辟一个新单元
 head=NULL;
 printf("----------------------------STUDENT----------------------------*\n");
 printf("|no    |class  |name   |sc1    |sc2    |sc3    |sum    |order  |\n");
 printf("|------|-------|-------|-------|-------|-------|-------|-------|\n");
 scanf("%s",p1->num);
 while(p1->num[0]!='@')//输入结束判断标志
 {
  scanf("%s%s%d%d%d",p1->class,p1->name,&p1->Math,&p1->English,&p1->Physic);
  p1->Sum=0;p1->rank=0;//对总成绩和排名进行初始化
  n++;
  if(n==1)
   head=p1;//对链表头进行初始化
  else
   p2->next=p1;
  p2=p1;
  p1=(struct Student *)malloc(LEN);//开辟动态存储区，把起始地址赋给p1
  scanf("%s",p1->num);
 }
 p2->next=NULL;//链表末尾为空
 return head;
}
void Record(struct Student *head)//把链表中的数据写入到文件中
{
 FILE *fp;//定义文件指针fp
 struct Student *p1;
 char s[20];
 p1=head;//让p1指向链表头
 printf("Please enter the file name of the file where the data is stored:");
 scanf("%s",s);//输入文件名
 if((fp=fopen(s,"w"))==NULL)//打开输出文件并使fp指向此文件
 {
  printf("can't open this file\n");
  return;
 }
 while(p1!=NULL)
 {
  fprintf(fp,"%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\n",p1->num,p1->class,p1->name,p1->Math,p1->English,p1->Physic,p1->Sum,p1->rank);
  p1=p1->next;
 }
 if(p1==NULL)//保存成功的输出
   printf("Record ok!\n");
 free(p1);
 free(head);//释放指针
 fclose(fp);//关闭文件
}
struct Student *Read_in()//从文件中读取数据进行链表创建
{
 FILE *fp;
 struct Student *head,*p2,*p1;
 int n=0;
 char s[20];
 printf("Please enter the filename you want to read in the data:");
 scanf("%s",s);//输入文件名
 if((fp=fopen(s,"r"))==NULL)
 {
  printf("can't open this file\n");
  return NULL;
 }
 head=NULL;
 p2=p1=(struct Student *)malloc(LEN);
 fscanf(fp,"%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d",p1->num,p1->class,p1->name,&p1->Math,&p1->English,&p1->Physic,&p1->Sum,&p1->rank);
 while(!feof(fp))//文件读取结束的标志
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
 fclose(fp);//关闭文件
 return head;//返回创建的链表头
}
void Show_stu_information()//显示学生信息函数
{
 printf("----------------------------STUDENT----------------------------*\n");
 printf("|no    |class  |name   |sc1    |sc2    |sc3    |sum    |order  |\n");
 printf("|------|-------|-------|-------|-------|-------|-------|-------|\n");
 struct Student *p,*head;
 head=Read_in();//调用Read_in()函数
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
void Sort_By_Rank()//计算每个学生的排名的函数
{
 struct Student *head,*p1,*p2;
 int i;
 head=Read_in();//读取文件中的学生数据
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
  p1->rank=i;//文件中链表位置不动，其中的名次变量发生变化
  p1=p1->next;//把每一个数据都与所有数据进行对比，得出此数据的排名
 }
 Record(head);//把排序好的链表再次存回文件中
}
void SearchByRank()//输出用户想查找的名次的学生数据
{
 struct Student *p1,*head;
 int number;
 head=Read_in();//调用Read_in()函数
 p1=head;
 if(p1->rank==0)//判断是否进行排名
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
  p1=p1->next;//遍历链表，找到此排名的学生
 }
 free(p1);
 free(head);//释放链表
}
void SearchByClass()//查询输出班级前三名的函数
{
 int i=1;
 char Class[20];
 struct Student *p1,*head,*p2;
 printf("Please enter the class to be queried:for example 20software1\n");
 scanf("%s",Class);//输入想要查询的班级的名称
 head=Read_in();//读取文件中的数据
 p1=head;
 printf("----------------------------STUDENT----------------------------*\n");
 printf("|no    |class  |name   |sc1    |sc2    |sc3    |sum    |order  |\n");
 printf("|------|-------|-------|-------|-------|-------|-------|-------|\n");
 while(p1!=NULL)
 {
  if(strcmp(Class,p1->class)==0)//判断获取的学生数据是否为对应的班级
  {
   i=1;
   p2=head;
   while(p2!=NULL)
   {
    if(strcmp(Class,p2->class)==0)//判断第二个获取的链表的学生数据是否为对应的班级
     if(p1->Sum<p2->Sum)
       i++;//计算此学生总分在所在班级的排名
    p2=p2->next;
   }
   if(i<=3)//判断第一个链表中学生数据是否为班级的前三名
    printf("%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\n",p1->num,p1->class,p1->name,p1->Math,p1->English,p1->Physic,p1->Sum,p1->rank);
   else if(i>3)  break;//跳出内循环
  }
  p1=p1->next;//让p1指向下一个结点
 }
 free(p1);
 free(head);//释放链表
}
void SearchByScore()//按成绩段查询某学生的个人成绩的函数
{
 int i=0,score1,score2;
 struct Student *p1,*head;
 char course[10]={0};
 printf("Please input the score segment you want to query:for example:70-80\n");
 scanf("%d-%d",&score1,&score2);
 if(score1>=score2)//判断分数段输入是否正确
 {
  printf("score2 must be bigger than score1!\n");
  return;
 }
 printf("Please input the course you want to inquire:(Math or English or Physic)\n");
 scanf("%s",course);//输入要查询的科目
 if(!(strcmp(course,"Math")==0||strcmp(course,"English")==0||strcmp(course,"Physic")==0))
 {
  printf("Not found this course\n");//判断输入的科目是否正确
  return;
 }
 head=Read_in();
 p1=head;
 while(p1!=NULL)
 {
  if(strcmp(course,"Math")==0)//数学科目
  {
   if(p1->Math>=score1&&p1->Math<=score2)
   {
    printf("-----------STUDENT-------------*\n");
    printf("|no    |class  |name   |Math   |\n");
    printf("|------|-------|-------|-------|\n");
    printf("%s\t%s\t%s\t%d\n",p1->num,p1->class,p1->name,p1->Math);
    i++;
   }
  }else if(strcmp(course,"English")==0)//英语科目
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
  if(i==0)//用户输入分数段没有学生信息的输出
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
void StatByStu()//计算每个学生的总成绩的函数
{
 struct Student *head,*p1;
 head=Read_in();
 p1=head;
 while(p1!=NULL)
 {
  p1->Sum=p1->Math+p1->English+p1->Physic;
  p1=p1->next;//对每一个结点的总分进行计算
 }
 Record(head);//把计算数据保存到文件中
}
void StatByClass()//计算每个班的总成绩的函数
{
 char Class[10][10],s[20];
 int ClassSum[10]={0};
 FILE *fp;
 struct Student *head,*p1;
 int i=0,j,flag=1;//i记录class总数,flag为有无新班级出现的标志
 head=Read_in();
 p1=head;
 while(p1!=NULL)
 {
  flag=1;
  for(j=0;j<i;j++)//检查有无新班级出现
  {
   if(strcmp(Class[j],p1->class)==0)
   {
    flag=0;break;//跳出此循环
   }
  }
  if(flag==1)//如果有新班级出现，把新班级的名称储存到class中
   strcpy(Class[i++],p1->class);
  p1=p1->next;//使p1指向下一个结点
 }
 p1=head;
 while(p1!=NULL)
 {
  for(j=0;j<i;j++)//计算每个班的总分
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
 fclose(fp);//关闭文件
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
struct Student *stu_rank(struct Student *head)//对学生进行排名的函数
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
struct Student *SortByRank(struct Student *head)//对链表按名次实现从小到大排序, 并返回链表的头指针。
{
 struct Student t,*p1,*p2,*p3;
 for(p1=head;p1!=NULL;p1=p1->next)
 {
  p3=p1;
  for(p2=p1->next;p2!=NULL;p2=p2->next)
  {
   if(p3->Sum<p2->Sum) p3=p2;
  }
  if(p3!=p1)//对两结点中的数据进行交换
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
struct Student *SortBynum(struct Student *head)//对链表按学号实现从小到大排序, 并返回链表的头指针。
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
  p1=p1->next; //统计每个学生的总分;
 }
 head=stu_rank(head);//排名
 return head;
}
void ShowSortBy(int i)//显示排序后的结果
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
 int flag=0;//判断用户输入学号是否正确的标志
 head=Read_in();
 printf("please input the number you want to delete:\n");
 scanf("%s",number);
 p1=head;//使p1指向第一个结点
 p2=NULL;
 while(p1!=NULL)//确保p1后面还有结点
 {
  if(strcmp(p1->num,number)==0)//p1指向的是要找的结点
  {
   if(p2==NULL)//判断此时p1是否为头结点
   {
    head=p1->next;//删除头结点
    flag=1;
    break;
   }
   else
   {
    if(p1->next==NULL)//判断p1是否为尾结点
    {
     p2->next=NULL;//删除尾结点
     flag=1;
     break;
    }
    p2->next=p1->next;//删除中间的结点，把下一个结点的地址赋给前一个结点
    flag=1;
    break;
   }
  }
  p2=p1;
  p1=p1->next;//p1后移一个结点
 }
 if(flag==0) printf("not found this student!\n");
 else Record(head);//删除后信息保存到文件中
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
     p1=p1->next;//寻找链表尾部
  head=head1;//新链表头部
  p1->next=head2;//把输入的学生信息放进链表尾部
 }
 else head=head2;//如果还没有数据，则增加的学生数据为第一个数据
 if(head==NULL) printf("Add failure");
 else
 {
  printf("Add success");
  Record(head);//增加信息后信息保存到文件中
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
 int i,j;//用户选择的功能的序号
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
