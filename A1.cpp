#include <iostream>
#include <string>
using namespace std;

/***********************************************************************
Matr.-Nr:                     3177505
Nachname/Surname:             Zainaldin
Vorname/Given name:           Sham Ahmad
Uni-Email:                    sham.zainaldin@stud.uni-due.de
Studiengang/Course of studis: Computer Engineering ISE Software Engineering
***********************************************************************/





/*Three global constant variables as given*/
int const ConsPerPerson = 200;
int const ConsPerSqrMeter = 9;
int const ConsPerDevice = 200;
int const ConstHeat = 550;


/*Defining the structure which will be used as a parameter in the functions later in the code*/
  struct household {
  
  string City;
  int Persons;
  int SqrMeter;
  int Devices;
  bool HotWater;
      
  
};

/* function to calculate the annual consumption*/
float AnnualConsumption (household h){
    
    return
    (h.Persons*ConstHeat)+(h.SqrMeter*ConsPerSqrMeter)+(h.Devices*ConsPerDevice);
}


void input_city (string &city){
    
    cout << "in which city is the household located ?" ;
    cin >> city;
    
}

void input_integer (string Q, int &entry){
    
    cout << Q ;
    cin >> entry;
    
}


void input_electric_water_heating(bool &water){
    
    char yn;
    
  
    cout << "is hot water heated using electricity? (y(es) or n(o)) : " ;
    cin >> yn;
    
    if(yn == 'y'){
        water = true;
    }else if(yn == 'n'){
        water = false;
    }
    
}



/* function to calculate the power costs*/

float AnnualPowerCosts (household h, float PricePerKwH){
    
    float Consumption = AnnualConsumption(h);
    
    return Consumption  * PricePerKwH;

    
}

/*void function to print out the information based on the number of persons*/
void print_household(household h, float PricePerKwH){
    string yesno;
    
    if(h.HotWater == false){
         yesno = "no";
    }else if(h.HotWater == true){
         yesno = "yes";
    };
    
    cout << "\n AVERAGE POWER COSTS \n ===================" << endl;
    cout << "household in: " << h.City << endl;
    cout << "square meter:" << h.SqrMeter << endl;
    cout << "persons:" << h.Persons << endl;
    cout << "(major) electrical devices:" << h.Devices << endl;
    cout << "water heated using electricity: " << yesno << endl;
    cout << "price for one KwH:" << PricePerKwH << "EUR" << endl;
    cout << "annual power consumption:" << AnnualConsumption(h) << "kWh"<< endl;
    cout << "annual power costs:" << AnnualPowerCosts(h, PricePerKwH) << "EUR \n" << endl ;
    

}



/*main function which contains the user input questions and loops to display costs depending on the number of persons which the loop iterates*/
int main() {

    household UserHousehold;
    float PricePerKwH;
    
    cout << "CALCULATION OF AVERAGE POWER COSTS FOR A HOUSEHOLD \n" << endl;
    
  
    
    input_city(UserHousehold.City);
    
   
    string Q2 = "how many square metres does the household have?";
    input_integer(Q2, UserHousehold.SqrMeter);
    
    
    string Q3 = "how many (major) electrical devices does the household have ? ";
    input_integer(Q3, UserHousehold.Devices);
    
    
    input_electric_water_heating(UserHousehold.HotWater);
    
    
    
    for (int n = 1 ; n<=5 ; n++ ){
        
        for( PricePerKwH = 0.3 ; PricePerKwH < 0.45 ; PricePerKwH += 0.05 ){
            
       
            
            UserHousehold.Persons = n;
            
            print_household(UserHousehold, PricePerKwH);
        };
        
    };
    
    return 0;
    
   
}
