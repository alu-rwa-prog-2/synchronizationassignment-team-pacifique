#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h> 
  

// Grobal variables 

int NumberOfPizza;

int traySize=10;

pthread_mutex_t lock;


// Supplying function
void *mySupplyingThread(void *vargp) 
{ 
        pthread_mutex_lock(&lock); 
        
        if(NumberOfPizza<traySize)
        {
        
                NumberOfPizza= NumberOfPizza+1;
                printf("After Supplying 1 pizza we have %d pizza\n",NumberOfPizza);
                
                        if(NumberOfPizza==traySize)
                {
                    printf("Pizzas are full of tray\nChef don't cook the other pizzas\n\n");
                    printf("Clients you may eat  please!\n\n");
                }
                
                if(NumberOfPizza==1)
                {
                    printf("Now pizzas are available\nClient, please you may take pizzas\n\n");
                }
                        
                       sleep(2);
        }
        pthread_mutex_unlock(&lock); 
        return NULL; 
} 


 
   void *myConsumingThread(void *vargp) 
{ 
            pthread_mutex_lock(&lock); 
            
            if(NumberOfPizza>0)
            {
                    NumberOfPizza= NumberOfPizza-1;
                    printf("After  eating one pizza, we have%dpizza\n",NumberOfPizza);
                    
                     if(NumberOfPizza==0)
                    {
                        printf("Pizzas are not available\nChef can you please cook the other pizzas\n\n");
                    }
                            sleep(2);
                            
            }
            pthread_mutex_unlock(&lock); 
            return NULL; 
} 
   
   
   // Main function
int main() 
{ 
    
    // Creating Thread Id
    pthread_t supplyThread_id,  consumeThrea_id; 
    
    while(1)
    {
        
        // Calling of Thread Supplying function when pizza is less than 10
        while(NumberOfPizza<traySize)
        {
            pthread_create(&supplyThread_id, NULL, mySupplyingThread,NULL); 
            
             
        }
        
        // Calling of Thread Consuming function when pizza is available
       
        while(NumberOfPizza>1)
        {
            pthread_create(&consumeThrea_id,NULL,myConsumingThread,NULL);
           
        }
        
    }
    
    
    pthread_join(supplyThread_id,NULL);
    pthread_join(consumeThrea_id,NULL);
    
    exit(0); 
}
