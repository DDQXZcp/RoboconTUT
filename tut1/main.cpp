#include "mbed.h"
//Board
DigitalOut led(LED1);
DigitalOut TubeA(PA_2);
DigitalOut TubeB(PA_7);
DigitalOut TubeC(PA_6);
DigitalOut TubeD(PA_5);
DigitalOut TubeE(PA_4);
DigitalOut TubeF(PA_3);
DigitalOut TubeG(PA_1);
DigitalOut Tubedp(PA_0);
DigitalOut TubeS1(PA_9);
DigitalOut TubeS2(PA_10);
DigitalOut TubeS3(PA_12);
DigitalOut DC_Motor(PF_0);

Ticker display;
//Ticker thermo;

//Serial pc(USBTX, USBRX,115200); // tx, rx
//Serial MLX90614(PB_6, PB_7,9600); // tx, rx

void tube_select(int tube_num){//Select from 1-3
    switch(tube_num){
        case 1:
            TubeS1=0;TubeS2=1;TubeS3=1;Tubedp=0;
            break;
        case 2:
            TubeS1=1;TubeS2=0;TubeS3=1;Tubedp=1;
            break;
        case 3:
            TubeS1=1;TubeS2=1;TubeS3=0;Tubedp=0;
            break;
        default:
            TubeS1=1;TubeS2=1;TubeS3=1;
            break;
        }
    }
void num_select(int display_num){//Select from 1-3
    switch(display_num){
        case 0:
            TubeA=1;//Top
            TubeB=1;//Right top
            TubeC=1;//Right bottom
            TubeD=1;//Bottom
            TubeE=1;//Left bottom
            TubeF=1;//Left top
            TubeG=0;//Middle
            Tubedp=0;
            break;
        case 1:
            TubeA=0;TubeB=1;TubeC=1;TubeD=0;TubeE=0;TubeF=0;TubeG=0;
            break;
        case 2:
            TubeA=1;TubeB=1;TubeC=0;TubeD=1;TubeE=1;TubeF=0;TubeG=1;
            break;
        case 3:
            TubeA=1;TubeB=1;TubeC=1;TubeD=1;TubeE=0;TubeF=0;TubeG=1;
            break;
        case 4:
            TubeA=0;TubeB=1;TubeC=1;TubeD=0;TubeE=0;TubeF=1;TubeG=1;
            break;
        case 5:
            TubeA=1;TubeB=0;TubeC=1;TubeD=1;TubeE=0;TubeF=1;TubeG=1;
            break;
        case 6:
            TubeA=1;TubeB=0;TubeC=1;TubeD=1;TubeE=1;TubeF=1;TubeG=1;
            break;
        case 7:
            TubeA=1;TubeB=1;TubeC=1;TubeD=0;TubeE=0;TubeF=0;TubeG=0;
            break;
        case 8:
            TubeA=1;TubeB=1;TubeC=1;TubeD=1;TubeE=1;TubeF=1;TubeG=1;
            break;
        case 9:
            TubeA=1;TubeB=1;TubeC=1;TubeD=1;TubeE=0;TubeF=1;TubeG=1;
            break;
        default:
            TubeA=1;TubeB=0;TubeC=0;TubeD=1;TubeE=1;TubeF=1;TubeG=1;
            break;
        }
    }
static int current_tube;
static int display_value;//Three number int
void decode(int value,int* tube_value_1,int* tube_value_2,int* tube_value_3){
    int b = value % 10; //个位
    int temp1 = value / 10;
    int c = temp1 % 10;//十位
    int temp2 = temp1 / 10;
    int d = temp2 % 10;//百位
    *tube_value_3 = b;
    *tube_value_2 = c;
    *tube_value_1 = d;
    }
void scan(){
    int tube_value_1;
    int tube_value_2;
    int tube_value_3;
    decode(display_value,&tube_value_1,&tube_value_2,&tube_value_3);
    tube_select(current_tube);
    switch(current_tube){
        case 1:
            num_select(tube_value_1);
            break;
        case 2:
            num_select(tube_value_2);
            break;
        case 3:
            num_select(tube_value_3);
            break;
        default:
            break;
        }
    current_tube++;
    if(current_tube>3)current_tube=1;
    }
    /*
int buffer_index=0;
char rx_buffer[10];    
void request_thermo(){
    MLX90614.putc(0xA5);
    MLX90614.putc(0x45);  
    MLX90614.putc(0xEA);           
    }
void Rx_interrupt() {
    led=1;
    char receive = MLX90614.getc();
    rx_buffer[buffer_index] = receive;
    //pc.printf("I got '%d'\n", rx_buffer[0]);
    if(buffer_index==0 && rx_buffer[0]!=0x5A){return;}
    buffer_index++;
    if(buffer_index==9){
            buffer_index=0;
            //pc.printf("I got '%c'\n", 0x55);
        }    
    led=0;
    return;
}*/
int main()
{
    display_value = 666;
    display.attach(&scan, 0.002);//No flash observed
    //request_thermo();
    //thermo.attach(&request_thermo, 0.2);
    //MLX90614.attach(&Rx_interrupt, Serial::RxIrq);
    while(1) {
    }
}
