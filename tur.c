#include<stdio.h>
#define EAST 1
#define SOUTH 2
#define WEST 3
#define NORTH 4

int getCommand1(int commands[],int size);
void getCommand(int commands[]); 
void printArray(int a[][50],int rows,int cols);
void draw(int commands[],int size,int picture[][50],int rows,int cols);

main()
{
   //int commands[100]={2,5,12,3,5,12,3,5,12,3,5,12,1,6,9};//ŽæŽ¢ÃüÁî 
   int commands[100]={2,5,12,3,5,12,3,5,6,4,5,12,4,5,6,3,5,12,3,5,12,1,6,9, 11, 14,2,1}; 
   int picture[50][50]={0}; //ŽæŽ¢ÍŒÆ¬ 
   
   draw(commands,100,picture,50,50);
   return 0;
}

int getCommand1(int commands[],int size)
{
   int command;
   int i=0;
   
   printf("input the commands\n");  
   scanf("%d",&command);
   while(command!=9 && i<=size-1){
     commands[i]=command;
      if (command==5){
         i++;             
         if (i<=size-1){
            printf("input steps(,%d)"); 
            fflush(stdin);           
            scanf(",%d",&command);       
            commands[i]=command;    
         }
         else
            return -1;       
      }
      i++;
      scanf("%d",&command);
   }
   
   if (i<=size-1){
      commands[i]=9;
      return 1;
   }
   else
      return -1; //±íÊŸÃüÁîÊý×éÔœœç 
}

//Œò»¯µÄÃüÁîÊäÈëº¯Êý£¬²»¿ŒÂÇÃüÁî¹ý¶àµŒÖÂÊý×éÔœœçÎÊÌâ 
void getCommand(int commands[])
{
   int i=0;
   
   printf("input the commands\n");  
   scanf("%d",&commands[i]);
   while(commands[i]!=9 ){
      if (commands[i]==5){                  
         printf("input steps(,%d)"); 
         i++; 
         scanf(",%d",&commands[i]);        
      }
      i++;
      scanf("%d",&commands[i]);
   }
}

void draw(int commands[],int size,int picture[][50],int rows,int cols)
{
   int i,j;//Ñ­»·¿ØÖÆ±äÁ¿ 
   int row=49,col=0;//º£¹ê³õÊŒÎ»ÖÃÔÚ×ø±êÔ­µã 
   int dir=NORTH;//º£¹ê³õÊŒ·œÏòÊÇÏò±±
   int write=0; //ÓÃÓÚŒÇÂŒ±ÊÊÇ·ñ³¬ÉÏ¡£0£º³¯ÉÏ£»1£º³¯ÏÂ¡£³õÊŒ³¯ÉÏ 
    
   for (i=0;i<=size-1 && commands[i]!=9;i++)
      switch (commands[i]){
         case 1:write=0;break;
         case 2:write=1;break;
         case 3://ÓÒ×ª£¬žÄ±äº£¹ê³¯Ïò
            switch (dir){
               case EAST:   dir=SOUTH; break;
               case SOUTH:  dir=WEST;  break;
               case WEST:   dir=NORTH; break;
               case NORTH:  dir=EAST;  break;
               default: printf(" error dir\n");break;
            }
            break;
         case 4://×ó×ª£¬žÄ±äº£¹ê³¯Ïò 
            switch (dir){
               case EAST:   dir=NORTH; break;
               case SOUTH:  dir=EAST;  break;
               case WEST:   dir=SOUTH; break;
               case NORTH:  dir=WEST;  break;
               default: printf("error dir\n");break;
            }
            break;
        case 5://»­ÍŒ 
            i++;  //ÓÃÓÚ¶ÁÈ¡Ç°œøµÄ²œÊý       
            if (write==1){ //Èç¹û±Ê³¯ÏÂ£¬Ôò»­ÍŒ
              switch (dir){
                    case EAST:  
                         for(j=1;j<=commands[i];j++){
                            col++;
                            picture[row][col]=1;
                         }    
                         break;
                    case SOUTH: 
                         for(j=1;j<=commands[i];j++){
                            row++;
                            picture[row][col]=1;
                         }  
                         break; 
                    case WEST:  
                         for(j=1;j<=commands[i];j++){
                            col--;
                            picture[row][col]=1;
                         }    
                         break;
                    case NORTH: 
                         for(j=1;j<=commands[i];j++){
                            row--;
                            picture[row][col]=1;
                         }  
                         break;   
                    default:printf("invalid direction in first part of case 5\n");
                 }   
            }                 
            else{//Èç¹û±Ê³¯ÉÏ,ÔòÖ»ÊÇŒòµ¥ÐÞžÄº£¹êµÄ×ø±ê 
               switch (dir){
                  case EAST: col+=commands[i]; break; 
                  case SOUTH:row+=commands[i]; break;   
                  case WEST: col-=commands[i]; break; 
                  case NORTH:row-=commands[i]; break; 
                  default:printf("invalid direction in second part of case 5\n");
               } 
            } 
            break;
         case 6:printArray(picture,50,50);break;    
      }//case
      
}

void printArray(int a[][50],int rows,int cols)
{
   int row,col;
   printf("the array is:\n");      
   for(row=0;row<=rows-1;row++){
      for(col=0;col<=cols-1;col++)
         if(a[row][col]!=0)
            printf("*");
         else
            printf(" ");
      printf("\n");
   }     
}



