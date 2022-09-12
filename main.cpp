#include <iostream>
#include "DHT11.h"
#include<wiringPi.h>
#include <fstream>
#include <ctime>
#include <cstring>
#include<unistd.h>
using namespace std;


vector<int> getdata(); 
int conv(vector<int>);
bool mycheck(vector<int>);


int main()
{
    //Setup Rpi4 and open a .csv file
    wiringPiSetupGpio();
    DHT11 mine(22);
    ofstream myfile;
    myfile.open ("example.csv"); //MODIFY .csv file name
    cout<< "Setup ran ok" <<endl;

    //forever loop-> Reads every 10 seconds
    while(1){
        int flag= 0;
        time_t now = time(0);
        tm *ltm = localtime(&now);
        if (ltm->tm_sec%10 ==0 && !flag){//MODIFY this line to change how oftern to get data
            
            TRYAGAIN:
                mine.getData();
                
                char* dt = ctime(&now);
                if (dt[strlen(dt)-1] == '\n') {dt[strlen(dt)-1] = '\0';} // Fix time char array to remove the new line and replace with null pointer

                if (mine.check() ){
                    //print and store info
                    cout << dt<< ","<<mine.getHumidity() << " " << mine.getTemperature()<< endl;
                    myfile << dt<< ","<< mine.getHumidity() << " " << mine.getTemperature()<< endl;
                }else{                    
                    usleep(2000000); //MODIFY...currently set to 2 seconds. DHT11 has a 1 Hz sampling rate. Do not go less than 1 second.
                    goto TRYAGAIN;
                }
        }else if (ltm->tm_sec%10 !=0&& flag){
            flag= 0;
        }





    }

    return 0;
}
