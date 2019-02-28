#include<stdio.h>
#include<iostream>
#include<graphics.h>
#include<windows.h>
#include<string.h>

using namespace std;
int a[15],b[15],n,x,m;
int color[]={0,14,15,6,5,4};

COORD xy = {0, 0};


void gotoxy (int x, int y)
{
        xy.X = x; xy.Y = y; // X and Y coordinates
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

int abs (int n)
{
    return ( (n>0) ? n : ( n * (-1)));
}

void DDA(int X0, int Y0, int X1, int Y1,int c)
{
    int dx = X1 - X0;
    int dy = Y1 - Y0;


    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float Xinc = dx / (float) steps;
    float Yinc = dy / (float) steps;
    float X = X0;
    float Y = Y0;
    for (int i = 0; i <= steps; i++)
    {
        putpixel (X,Y,color[c]);
        X += Xinc;
        Y += Yinc;
        delay(100);
    }
}

void draw(int x,int m,int y,int start,int last,int n,int choice)//draw(x,n,i+1,start,b[count1-2],m,0);
{
    int b,d,e,f,h,j;
    double a,c,g,i;
    a=(900.0/n)*x;
    c=(600/m);
    d=(int)(c);
    b=(int)(a);

    if(y==1)
    {
        //string s=to_string(start);
        g=(900.0/n)*start;
        h=(int)(g);
        setcolor(color[choice]);
        //outtextxy(50+h,50,);
        circle(50+h,50,5);
        line(50+h,50,(50+a),(50+(c*y)));
        circle(50+a,50+(c*y),5);
    }
    else
    {
        char s = (char)x;
        i=(900.0/n)*last;
        j=(int)(i);
        setcolor(color[choice]);
        //outtextxy(50+j,50,s);
        line((50+j),(50+(c*(y-1))),(50+a),(50+(c*y)));
        circle(50+a,50+(c*y),5);
    }
}

int absolute(int a,int b)
{
    int c;
    c=a-b;
    if(c<0)
        return -c;
    else
        return c;
}

void copy(int *a,int*b)
{

    for(int i=0;i<n;i++)
    b[i]=a[i];
}

int fcfs(int *a,int start)
{
    int i,count1=1,count=0;
    for(i=0;i<n;i++)
    {
        x-=a[i];
        if(x<0)
            x=-x;
        count+=x;
        x=a[i];
        b[count1++]=x;
        printf("%d\t",x);
        draw(x,n,i+1,start,b[count1-2],m,0);
    }
    //display(count1);
    return count;
}

int sstf(int *c,int start)
{
    int i,pos,j,min,count1=1,count=0;
    copy(c,a);
    for(i=0;i<n;i++)
    {
        min=absolute(a[i],x);
        pos=i;
        for(j=i;j<n;j++)
		    if(min>absolute(x,a[j]))
            {
                pos=j;
			    min=absolute(x,a[j]);
            }
        count+=absolute(x,a[pos]);
        x=a[pos];
        a[pos]=a[i];
        a[i]=x;
        b[count1++]=x;
        printf("%d\t",x);
        draw(x,n,i+1,start,b[count1-2],m,1);
    }
    return count;
}
void asc(int *a)
{
     int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<n-i-1;j++)
            if(a[j]>a[j+1])
            {
                x=a[j];
                a[j]=a[j+1];
                a[j+1]=x;
            }
}
void desc(int pos,int *a)
{
    int i,j;
    for(i=0;i<pos;i++)
        for(j=0;j<pos-i-1;j++)
            if(a[j]<a[j+1])
            {
                x=a[j];
                a[j]=a[j+1];
                a[j+1]=x;
            }
}
int scan(int *c,int start)
{
    int i,j,pos=0,count=0,count1=1;
    copy(c,a);
    asc(a);
    for(i=0;i<n;i++)
        if(a[i]<start)
            pos++;
    desc(pos,a);
        x=start;
        printf("%d\t",x);
        for(i=0;i<pos;i++)
        {
            count+=absolute(a[i],x);
            x=a[i];
            b[count1++]=x;
            printf("%d\t",x);
            draw(x,n+1,i+1,start,b[count1-2],m,2);
        }
        count+=absolute(x,0);
        x=0;
        b[count1++]=0;
        printf("%d\t",x);
        draw(x,n+1,pos+1,start,b[count1-2],m,2);
        for(i=pos;i<n;i++)
        {
            count+=absolute(a[i],x);
            x=a[i];
            b[count1++]=x;
            printf("%d\t",x);
            draw(x,n+1,i+2,start,b[count1-2],m,2);
        }
		   // display(count1);
        return count;
}
int cscan(int *c,int start)
{
	    int i,j,pos=0,count=0,count1=1,z=1;
	    copy(c,a);
	    asc(a);
	    for(i=0;i<n;i++)
			if(a[i]<start)
                pos++;
	    x=start;
	    for(i=pos;i<n;i++)
        {
            count+=absolute(x,a[i]);
			x=a[i];
			b[count1++]=x;
			printf("%d\t",x);
            draw(x,n+1,z++,start,b[count1-2],m,3);
        }
	    count+=absolute(m-1,x);
	    x=0;
	    b[count1++]=0;
	    printf("%d\t%d\t",m-1,0);
        draw(x,n+1,z++,start,b[count1-2],m,3);
	    for(i=0;i<pos;i++)
        {
            count+=absolute(x,a[i]);
			x=a[i];
			b[count1++]=x;
			printf("%d\t",x);
            draw(x,n+1,z++,start,b[count1-2],m,3);
        }
	   // display(count1);
	    return count;
}
int look(int *c,int start)
{
	    int i,j,pos=0,count=0,count1=1,z=1;
	    copy(c,a);
	    asc(a);
	    for(i=0;i<n;i++)
		    if(a[i]<start)
                pos++;
	    desc(pos,a);
	    x=start;
	    for(i=0;i<pos;i++)
        {
            count+=absolute(a[i],x);
		    x=a[i];
		    b[count1++]=x;
		    printf("%d\t",x);
            draw(x,n,z++,start,b[count1-2],m,4);
        }
	    for(i=pos;i<n;i++)
        {
            count+=absolute(a[i],x);
		    x=a[i];
		    b[count1++]=x;
		    printf("%d\t",x);
            draw(x,n,z++,start,b[count1-2],m,4);
        }
	    //display(count1);
	    return count;
}
int clook(int *c,int start)
{
	    int i,j,pos=0,count=0,count1=1,z=1;
	    copy(c,a);
	    asc(a);
	    for(i=0;i<n;i++)
		    if(a[i]<start)
        pos++;
	    x=start;
	    for(i=pos;i<n;i++)
        {
            count+=absolute(x,a[i]);
		    x=a[i];
		    b[count1++]=x;
		    printf("%d\t",x);
            draw(x,n,z++,start,b[count1-2],m,5);
        }
	    for(i=0;i<pos;i++)
        {
            count+=absolute(x,a[i]);
		    x=a[i];
		    b[count1++]=x;
		    printf("%d\t",x);
            draw(x,n,z++,start,b[count1-2],m,5);
        }
	    //display(count1);
	    return count;
}
float angle=270;
struct arccoordstype aa, bb;
void c1(int a1)
{
    setbkcolor(CYAN);
    setcolor(CYAN);
    arc(getmaxx()/2,getmaxy()/2,angle-a1,angle-a1,35);
    getarccoords(&aa);
    setcolor(BLACK);
    setfillstyle(SOLID_FILL,BLACK);
    fillellipse(aa.xstart,aa.ystart,4,4);
}

int main()
{
    int gd = DETECT, gm, x, y,page=0;
    POINT cp;
    float angle1 = 90;
    struct arccoordstype a2, b2;
    int cx,cy;
    initgraph(&gd, &gm, "C:\\TC\\BGI");
    DWORD shr=GetSystemMetrics(SM_CYSCREEN);
    DWORD swr=GetSystemMetrics(SM_CXSCREEN);
    int sh=0.9*(shr);
    int sw=(swr);
    int th,tw;
    initwindow(sw,sh,"DISK-SCHEDULING",-3,-3,false,true);

    //#####################Starting##############################
       delay(800);
   while(angle1<=450)
   {
      setcolor(BLACK);
      arc(getmaxx()/2,getmaxy()/2,angle1,angle1+1,50);
      setcolor(RED);
      getarccoords(&a2);
      circle(a2.xstart,a2.ystart,25);
      setcolor(BLACK);
      arc(getmaxx()/2,getmaxy()/2,angle1,angle1+1,100);
      setcolor(BLUE);
      getarccoords(&a2);
      circle(a2.xstart,a2.ystart,25);
      setcolor(BLACK);
      arc(getmaxx()/2,getmaxy()/2,angle1,angle1+1,150);
      getarccoords(&a2);
      setcolor(CYAN);
      circle(a2.xstart,a2.ystart,25);
      setcolor(BLACK);
      arc(getmaxx()/2,getmaxy()/2,angle1,angle1+1,200);
      setcolor(GREEN);
      getarccoords(&a2);
      circle(a2.xstart,a2.ystart,25);
      setcolor(BLACK);
      arc(getmaxx()/2,getmaxy()/2,angle1,angle1+1,250);
      setcolor(LIGHTCYAN);
      getarccoords(&a2);
      circle(a2.xstart,a2.ystart,50);
      angle1 = angle1+2;
      delay(1);
   }
   delay(500);
   setcolor(LIGHTCYAN);
   outtextxy(30,20,"Siddhant Tulsyan");
   outtextxy(30,40,"16104051");
   delay(500);

   outtextxy(sw-120,20,"Avishka Agarwal");
   outtextxy(sw-120,40,"16104060");
   delay(500);

   settextstyle(BOLD_FONT,HORIZ_DIR,3);
   outtextxy(181,sh/2-12,"PRESS");
   delay(400);
   outtextxy(sw/2-7,sh/2-12,"A");
   delay(400);
   outtextxy(sw-250,sh/2-12,"KEY!!");

   getch();
   setbkcolor(CYAN);
   setcolor(CYAN);
   settextstyle(10,HORIZ_DIR,1);
   delay(400);

     while(angle!=1230)
     {
         setactivepage(page);
         setvisualpage(1-page);
         cleardevice();

         setcolor(BLACK);
         outtextxy((getmaxx()/2)-45,(getmaxy()/2)+70,"Loading...");

         if(angle>=0 && angle<=990)
         c1(0);

         if(angle>=300 && angle<=990)
            c1(30);

         if(angle>=330 && angle<=990)
            c1(60);

         if(angle>=360 && angle<=990)
            c1(90);

         if(angle>=390 && angle<=990)
            c1(120);

         if(angle>=420 && angle<=990)
            c1(150);

         if(angle>=450 && angle<=990)
            c1(180);

         if(angle>=480 && angle<=990)
            c1(210);

        if(angle>990 && angle<=1020)
        {
            c1(30);
            c1(60);
            c1(90);
            c1(120);
            c1(150);
            c1(180);
            c1(210);
        }
        if(angle>1020 && angle<=1050)
        {
            c1(60);
            c1(90);
            c1(120);
            c1(150);
            c1(180);
            c1(210);
        }
        if(angle>1050 && angle<=1080)
        {
            c1(90);
            c1(120);
            c1(150);
            c1(180);
            c1(210);
        }
        if(angle>1080 && angle<=1110)
        {
            c1(120);
            c1(150);
            c1(180);
            c1(210);
        }
        if(angle>1110 && angle<=1140)
        {
            c1(150);
            c1(180);
            c1(210);
        }
        if(angle>1140 && angle<=1170)
        {
            c1(180);
            c1(210);
        }
        if(angle>1170 && angle<=1200)
        {
            c1(210);
        }
        if(angle>1200)
        {

        }
         angle=angle+2;
         delay(1);
         page=1-page;
     }
     setactivepage(page);
     cleardevice();
     outtextxy((getmaxx()/2)-45,(getmaxy()/2)+70,"Lets Go!!");
     getch();
     cleardevice();

    int choice,start,i,count,count1,c[15],d[6][2],j;
    count=0;
    count1=0;
    j=0;
    system("COLOR E9");
    gotoxy(50,0);
    printf("----------------------------------\n\n");
    gotoxy(50,1);
    printf("|********DISK SCHEDULING*********|");
    gotoxy(50,2);
    printf("----------------------------------\n\n");
    printf("\nEnter the number of cylinders :\t");
    scanf("%d",&m);
    printf("\nEnter the number of requests :\t");
    scanf("%d",&n);
    printf("\nEnter current position :\t");
    scanf("%d",&start);
    printf("\nEnter the request queue :\n");
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
        c[i]=a[i];
        if(a[i]>=m)
        {
            printf("\ninvalid input: re-enter\t");
            scanf("%d",&a[i]);
            c[i]=a[i];
        }
    }
    line(50,50,50,650);
    line(50,50,950,50);
    line(950,50,950,650);
    line(50,650,950,650);
    do
    {
        system("cls");
        gotoxy(50,0);
        printf("---------------------------\n\n");
        gotoxy(50,1);
        printf("DISK SCHEDULING ALGORITHMS");
        gotoxy(50,2);
        printf("---------------------------\n\n");
        printf("1. FCFS\n2. SSTF\n3. SCAN\n4. C-SCAN\n5. LOOK\n6. C-LOOK\n\n");
        printf("\nEnter choice :\t");
        scanf("%d",&choice);
		count=0;
        count1=1;
        x=start;
        b[0]=x;
        printf("REQUESTED QUEUE IS:");
        for(i=0;i<n;i++)
            printf("\t%d",c[i]);
        switch(choice)
        {
            case 1:
                    printf("\n\n***************FCFS****************\n\n");
                    printf("Scheduling services the request in the order that follows:\n%d\t",start);
                    count=fcfs(c,start);
                    printf("\n\nTotal Head Movement :%d Cylinders",count);
                    break;
            case 2:
                    printf("\n\n***************SSTF***************\n\n");
                    printf("Scheduling services the request in the order that follows:\n%d\t",start);
                    count=sstf(c,start);
                    printf("\nTotal Head Movement: %d Cylinders",count);
                    break;
            case 3:
                    printf("\n\n***************SCAN***********\n\n");
                    printf("Scheduling services the request in the order that follows:\n");
                    count=scan(c,start);
                    printf("\nTotal Head Movement: %d Cylinders",count);
                    break;
            case 4:
                    printf("\n\n***************C-SCAN************\n\n");
                    printf("Scheduling Services the request in the order that follows:\n%d\t",start);
                    count=cscan(c,start);
                    count+=m;
                    printf("\nTotal Head movement: %d Cylinders",count);
                    break;
            case 5:
                    printf("\n\n*****************LOOK**********\n\n");
                    printf("\nScheduling services the request in the order as follows :\n%d\t",start);
                    count=look(c,start);
                    printf("\nToal Head Movement: %d Cylinders",count);
                    break;
            case 6:
                    printf("\n\n***************C-LOOK***********\n\n");
                    printf("Scheduling Services the request in the order that follows:\n%d\t",start);
                    count=clook(c,start);
                    printf("\nTotal Head movement: %d Cylinders",count);
                    break;
        }
        d[j][0]=choice;

        d[j][1]=count;
        j++;
        printf("\n\nDo you want to continue(1 to continue) :\t");
        scanf("%d",&choice);
    }
    while(choice==1);
    system("cls");
    int mi=0;
    string s="";
	for(i=0;i<j;i++)
	{
        switch(d[i][0])
        {
            case 1:
                    printf("\n FCFS");
                    printf("\t%d",d[i][1]);
                    if(d[i][1]<mi||mi==0)
                    {
                        mi=d[i][1];
                        s="FCFS";
                    }
                    break;
            case 2:
                    printf("\n SSTF");
                    printf("\t%d",d[i][1]);
                    if(d[i][1]<mi||mi==0)
                    {
                        mi=d[i][1];
                        s="SSTF";
                    }
                    break;
            case 3:
                    printf("\n SCAN");
                    printf("\t%d",d[i][1]);
                    if(d[i][1]<mi||mi==0)
                    {
                        mi=d[i][1];
                        s="SCAN";
                    }
                    break;
            case 4:
                    printf("\n C-SCAN");
                    printf("\t%d",d[i][1]);
                    if(d[i][1]<mi||mi==0)
                    {
                        mi=d[i][1];
                        s="C-SCAN";
                    }
                    break;
            case 5:
                    printf("\n LOOK");
                    printf("\t%d",d[i][1]);
                    if(d[i][1]<mi||mi==0)
                    {
                        mi=d[i][1];
                        s="LOOK";
                    }
                    break;
            case 6:
                    printf("\n C-LOOK");
                    printf("\t%d",d[i][1]);
                    if(d[i][1]<mi||mi==0)
                    {
                        mi=d[i][1];
                        s="C-LOOK";
                    }
                    break;
        }
    }
    //cout<<"\n\nMost effective algorithm with least no. of head movements was "<< s <<" with "<< min <<" movements.";
}
