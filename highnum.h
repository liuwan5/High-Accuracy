#ifndef highnum_h
#define highnum_h
#include<stdio.h>
#include<string.h>
struct high
{
    int number[11000];
    int l;
};
typedef struct high highnumber;//高精度数据类型，包含其位数与内容
void turn_to_high(highnumber *num,char *str)//将字符串形式的数字转换为高精度类型
{
    int len_of_str=strlen(str);
    int j=0;
    for(int i=len_of_str-1;i>=0;i--){
        num->number[j]=str[i]-'0';
        j++;
    }
    num->l=j;
}
void multiply(highnumber *a,highnumber *b)//高精度乘法，将a与b相乘，结果存于b中
{
    int minl,maxl;
    highnumber *min,*max;
    if(a->l>b->l){
        min=b;max=a;
        minl=b->l;maxl=a->l;
    }
    else{
        min=a;max=b;
        minl=a->l;maxl=b->l;
    }
    int i=0,c=0;
    highnumber tem[minl+2];
    memset(tem,0,sizeof(tem));
    for(i=0;i<minl;i++){
        for(int j=0;j<i;j++){
            tem[i].number[j]=0;
        }
        for(int k=0;k<maxl;k++){
            tem[i].number[k+i]=min->number[i]*max->number[k];
            tem[i].number[k+i]+=c;
            c=tem[i].number[k+i]/10;
            tem[i].number[k+i]%=10;
        }
        tem[i].l=maxl+i;
        if(c!=0){
            tem[i].number[i+maxl]=c;
            tem[i].l++;
        }
        c=0;
    }
    int len=tem[0].l;
    for(i=0;i<minl-1;i++){
        len=add(&tem[i+1],&tem[i]);
    }
    memset(b,0,sizeof(b));
    for(i=0;i<len;i++){
        b->number[i]=tem[minl-1].number[i];
    }
    b->l=len;
}
int add(highnumber *an,highnumber *bn)//高精度加法，将an与bn相加，结果存于an中，返回an的位数
{
    int c=0,maxl=an->l>bn->l?an->l:bn->l;
    for(int i=0;i<maxl;i++){
        an->number[i]+=bn->number[i]+c;
        c=an->number[i]/10;
        an->number[i]%=10;
    }
    if(c!=0){
        an->number[maxl]=c;
        return maxl+1;
    }
    else return maxl;
}
void out_high(highnumber *aim)//高精度数输出函数
{
    for(int i=aim->l-1;i>=0;i--)printf("%d",aim->number[i]);
}
#endif