#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//printf_student_list(student* sptr,int n){ //학생정보 출력 기능.
    //student * eptr = sptr +n; //while문에서 끝내기 위해.
    //2.while(sptr<eptr)
    //1.for(int i=0; i<n; i++){
        //printf(%d: age = %d , name:%s\n",i+1, sptr->age, sptr->name);
        //sptr ++;
    //}
//}
typedef struct student{
    char name [20];
    int age;
    char address[20];
}Student;

void age_cheak(Student stu){
    if(stu.age<20){
        printf("미성년자입니다.\n");
    }else{
        printf("성인입니다.\n");
    }
}

int main(){
    Student s1= {"홍길동",20,"조선"};
    printf("%s ,%d ,%s\n",s1.name,s1.age,s1.address);
    age_cheak(s1);
    //Student s[30] ={{age,"name1"........}};
    //동적 메모리 할당.
    //int NoofStd;
    //Student *stdptr; //배열의 첫주소값을 가르킬 포인터.
    //printf("How many Student?: ")
    //scanf("%d",&NoofStd);
    //Student * stdptr = malloc(sizeof(student)*NoofStd);
    //말록함수로 선언하여 학생 수만큼 메모리할당. 
    //stdptr->age = 21;
    //strncpy(stdptr->name. "name1",20);
    //(stdptr+1)->age=22;
    //strncpy(stdptr->name. "name2",30);
    ///...... 이렇게 마음대로 늘여갈 수 있음.
    //printf_student_list(stdptr,3);
}