


#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

/***********************************************************************
Matr.-Nr:                     3177505
Nachname/Surname:             Zainaldin
Vorname/Given name:           Sham Ahmad
Uni-Email:                    sham.zainaldin@stud.uni-due.de
Studiengang/Course of studis: Computer Engineering ISE Software Engineering
***********************************************************************/

enum frequencyOfUse{
    
    once,daily,mo_fr,sa_su,weekly
    
};

void input_use(string freq, frequencyOfUse& Use){
    
    cout << freq << endl;
    cout << "daily (d)" << endl << "mo_tu (m)" << endl << "once (o)" << endl
    << "sa_su (s)" << endl << "weekly (w) ?" ;
    
    char input;
    cin >> input ;
    
    if(input == 'd'){
        Use = daily;
    }else if(input == 'm' ){
        Use = mo_fr;
    }else if( input == 'o'){
        Use = once;
    }else if(input == 's'){
        Use = sa_su;
    }else if(input == 'w'){
        Use = weekly;
    };
    
    
}


struct consumer {
  
  string description;
    float watt, watt_standby, hours;
    frequencyOfUse use;
    consumer* next;
    
};


/*Three global constant variables as given*/

int const ConsPerPerson = 200;
int const ConsPerSqrMeter = 9;
int const ConsPerDevice = 200;
int const ConstHeat = 550;




//global variables defined for some calculations
float cost = 0;
float consumption = 0;
float priceperkwh = 0;




  struct household {
  
  string City;
  int Persons;
  int SqrMeter;
  int Devices;
  bool HotWater;
      frequencyOfUse use;
      consumer* consumers;
    
};


void input_double(string Q,float &no){
    
    cout << Q;
    cin >> no;
    

    
}


void add_consumer_to_household (household* h, consumer* c){
    
    c = new consumer;
    c->next = h->consumers;
    h->consumers = c;
    
   
    
    cout << "what is the description of the power consumer? " ;
    cin >> c->description ;
    
    string first = "how many watt will it have? ";
    input_double(first, c->watt);
    
    string second = "how many watt standby it will have? ";
    input_double(second, c->watt_standby);
    
    string freq = "how often will it be used? ";
    input_use(freq, c->use);
    
    cout << "how many hours will it be operating then?" ;
    cin >> c->hours;
    
}



float annual_hours_of_use(consumer* c){
    
    float hrsPerYear;
    
    switch(c->use) {
            
        case daily:
            hrsPerYear = 365 * c->hours;
            return hrsPerYear;
            break;
            
        case weekly:
            hrsPerYear = 52 * c->hours;
            return hrsPerYear;
            break;
        
        case sa_su:
            hrsPerYear = 104 * c->hours;
            return hrsPerYear;
            break;
            
        case mo_fr:
            hrsPerYear = 260 * c->hours;
            return hrsPerYear;
            break;
            
        case once:
            hrsPerYear = c->hours;
            return hrsPerYear;
            break;
        
    }
        
}



float annual_hours_of_standby (consumer* c){
    
    float annualUseHrsStandby = annual_hours_of_use(c);
    return 8760 - annualUseHrsStandby;
    
}




float annual_kWh(consumer* c){
    consumer consumer;
    
    float annualUseHrs = annual_hours_of_use(c);
    float annualStandbyHrs = annual_hours_of_standby(c);
    float totalCons =(annualUseHrs * c->watt + annualStandbyHrs * c->watt_standby);
    
    
    return totalCons;
}


consumer* move_up(consumer* head, int k ){
    
    consumer* currentposition = head;
    consumer* previousposition = nullptr;
    
    int prev = k-1;
    //to go to position, stop before position k
    
    for(int i = 1 ; i < prev ; i++){
        
        previousposition = currentposition;
        currentposition=currentposition->next;
        
    }
    //only one item in list
    if(head->next == nullptr && k==1){
        return head;
    };
    
    if(previousposition!=nullptr){
        previousposition->next = currentposition;
    };
    
    
    if(k==2){
        
        
        previousposition->next = currentposition->next;
        currentposition->next = previousposition;
        head = currentposition;
        
        
    };
    
    if(k>2){
        
        //draft (u can ignore unless my code isnt clear)
        /*
         current is at k-1 (lets say number 2 as the loop stops one position before k), cons is defined at number 3 (the node we want to move)
         we point the current pointer to the node after 3 ( number 4 ), since 2 will be the node pointing to 4 when they switch
         then change the pointer of number 3 to 2 so they switch places, and redefine current as 3 and return it
         */
        
        consumer* cons = currentposition -> next ;
        currentposition->next = currentposition->next->next;
        //currentposition->next = currentposition->next;
        cons->next = currentposition;
        currentposition = cons;
    };
    
    
    
    
    //reorganize
    if(previousposition != nullptr){
        previousposition->next = currentposition;
        currentposition = head;
    };
    
    
    return currentposition;
    
}
    
    
    //Q.10
    const int ColoumnWidth = 35;
    
    
    
    
    
    /* function to calculate the annual consumption*/
    float AnnualConsumption (household h){
        float AnnCons;
        if(h.HotWater) {
            AnnCons = (h.Persons*ConstHeat)+(h.SqrMeter*ConsPerSqrMeter)+(h.Devices*ConsPerDevice);
            return AnnCons;
        }else{
            AnnCons = (h.Persons*ConsPerPerson)+(h.SqrMeter*ConsPerSqrMeter)+(h.Devices*ConsPerDevice);
            return AnnCons;
        }
    }
    
    //Q.11
    void print_consumer (consumer* c , int x){
        
        
        
   
        cout << right << setw(ColoumnWidth - 2) << x << ": " << left << setw(ColoumnWidth) << c->description << "(at address : " << &(c->description) << ")" << endl;
        
        cout << right << setw(ColoumnWidth) << "Power Consumption: " << left <<  c->watt << " W" << endl;
        cout << right << setw(ColoumnWidth) << "Power Consumption standby: " << left << c->watt_standby << " W" << endl;
        cout << right << setw(ColoumnWidth) << "annual hours of use: " << left << annual_hours_of_use(c) << " h" << endl;
        cout << right << setw(ColoumnWidth) << "annual hours of standby: " << left << annual_hours_of_standby(c) << " h" << endl;
        
        float annualcon = annual_kWh(c)/1000;
        cout << right << setw(ColoumnWidth) << "annual consumption: "<< left << annualcon  << " kWh" << endl;
        
        
        float anncosts = priceperkwh * annualcon ;
        cout << right << setw(ColoumnWidth) << "annual costs: " << left << anncosts << " EUR" << endl;
        
        
        
        
    }
    
    
    void input_city (string &city){
        
        cout << "in which city is the household located ? " ;
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
    void print_household(household* h, float PricePerKwH, int HouseNo){
        string yesno;
        
        if(h->HotWater == false){
            yesno = "no";
        }else if(h->HotWater == true){
            yesno = "yes";
        };
        
       
        
        float Consumption = AnnualConsumption(*h);
        float Cost = AnnualPowerCosts(*h, PricePerKwH);
        
        
        consumer* accumalate = h -> consumers;
        float annualtotalccons= 0;
        while (accumalate != nullptr) {
            annualtotalccons += annual_kWh(accumalate)/1000;
            accumalate = accumalate->next;
        }
        
       
        cout << " H O U S E H O L D   N O  " << HouseNo << "  P O W E R   C O N S U M P T I O N" << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << right << setw(ColoumnWidth) << "City: " << h->City << "(at address : " << &(h->City) << ")" << left << setw(ColoumnWidth) << endl;
        cout << right << setw(ColoumnWidth) << "price for one kWh: " << left << PricePerKwH*100 << " ct/kWh" << endl;
        cout << right << setw(ColoumnWidth) << "square metres: " << left << h->SqrMeter << " qm" << endl;
        cout << right << setw(ColoumnWidth) << "persons: " << left << h->Persons << endl;
        cout << right << setw(ColoumnWidth) << "water heated using electricity: " << yesno << endl;
        cout << right << setw(ColoumnWidth) << "list of customers " << endl;
        
        
        cout << "------------------------------------------------------------" << endl;
        
        //print the consumers using while loop to iterate through every member of the structure list
        
        consumer* currentCons = h->consumers;
        int consumerno = 1;
        
        
        
        
        while (currentCons != nullptr){
            
            print_consumer(currentCons, consumerno);
            consumerno++;
            
            
            currentCons = currentCons->next;
        }
        
        
        
        cout << "------------------------------------------------------------" << endl;
        
        cout << right << setw(ColoumnWidth) << "power consumption square meters: " << left <<(h->SqrMeter * ConsPerSqrMeter) << " kWh" << endl;
        
        if(h->HotWater){
            cout << right << setw(ColoumnWidth) << "power consumption on all persons: " << left << (h->Persons * ConstHeat) << " kWh" << endl;
        }else{
            cout << right << setw(ColoumnWidth) << "power consumption on all persons: " << left << (h->Persons * ConsPerPerson) << " kWh" << endl;
        };
        
        
        
        cout << right << setw(ColoumnWidth) << "total annual power consumption: " << left << Consumption + annualtotalccons << " kWh" << endl;
        
        cout << right << setw(ColoumnWidth) << "total annual power costs: " << left << Cost + annualtotalccons * PricePerKwH << " EUR" << endl;
        
        
        
    }
    



    void input_household(household* h){
        
    
        
        string Q2 = "how many square metres does the household have?";
        input_integer(Q2, h->SqrMeter);
        
        
        cout << "how many persons live in this household? ";
        cin >> h->Persons;
        
        input_electric_water_heating(h->HotWater);
    
        h->consumers = nullptr;
        
}

    


    consumer* copy_consumer(consumer* fromh1, consumer* toh2){
        
        //h1 to be copied FROM
        //h2 copied TO
    
        consumer* copyCon = fromh1;
        consumer* newCon= new consumer;
        consumer*head=new consumer;
        head=newCon;
        *newCon=*copyCon;
            while(copyCon != nullptr){
                    
                
                //newCon->next = new consumer;
                newCon->next=new consumer;
                newCon=newCon->next;
                copyCon=copyCon->next;
                newCon->description = copyCon->description;
                newCon->hours = copyCon->hours;
                newCon->use = copyCon->use;
                newCon->watt = copyCon->watt;
                newCon->watt_standby = copyCon->watt_standby;
                
                //newCon = newCon->next;
                //newCon->next = copyCon->next;
                
                
                
                
            }
        newCon->next=toh2;
                
        return head;
            
        };
        
            
            
        
        
        



    int main() {
        
        household* UserHousehold = new household;
       
        consumer* NewConsumer = new consumer;
 
        float PricePerKwH;
       
        
        
        cout << "CALCULATION OF AVERAGE POWER COSTS FOR A HOUSE \n" << endl;
        
        int n;
        cout << "how many households does this house have? " ;
        cin >> n;
        
        household *Householdptr[n];
        
        for(int i = 0 ; i < n ; i++){
            Householdptr[i]=nullptr;
        }
              
        input_city(UserHousehold->City);
        
        
        cout << "what is the price for one kWh in EUR ? " ;
        cin >> priceperkwh;
        PricePerKwH = priceperkwh;
        
        
        
        //for the selection menu
        
        char UserChoice;
        bool program;
        program = true;
        
        while(program){
            
            cout << "q quit" << endl;
            cout << "i input power consumer" << endl;
            cout << "u move up power consumer" << endl;
            cout << "p print household" << endl;
            cout << "a print all households" << endl;
            cout << "n new household" << endl;
            cout << "c copy all consumers (added to already existing ones)" << endl;
            cout << ">>" ;
            
            cin >> UserChoice;
            
            
            switch(UserChoice){
                    
                case 'q' :
                    program = false;
                    cout << "Program ended" << endl;
                    break;
                    
                    
                case 'i' :
                    int x;
                    cout << "number of household ? ";
                    cin >> x ;
                    add_consumer_to_household(Householdptr[x],NewConsumer);
                    break;
                    
                    
                case 'u' :
                    
                    cout << "number of household ?";
                    int u;
                    cin >> u;
                    
                    cout << "which one?";
                    int k;
                    cin >> k;
                    
                    move_up(Householdptr[u]->consumers, k);
                    break;
                    
                    
                case 'p' :
                    int houseNo;
                    cout << "number of household ?";
                    cin >> houseNo;
                    
                    Householdptr[houseNo]->City = UserHousehold->City;
                    
                    
                    print_household(Householdptr[houseNo],PricePerKwH,houseNo);
                    for(int b = 0 ; b < n ; b++){
                        Householdptr[b]->City = UserHousehold->City;
                        
                    }
                    break;
                    
                    
                case 'a' :
                    
                    for(int b = 0 ; b < n ; b++){
                        Householdptr[b]->City = UserHousehold->City;
                    }
                    
                    for(int i = 0 ; i<n ; i++){
                        if( Householdptr[i] != nullptr ){
                            print_household(Householdptr[i],PricePerKwH,i);
                        };
                    };
                    
                    
                    break;
                    
                    
                case 'n' :
                    cout << "number of household? ";
                    int a;
                    cin >> a;
                    if(Householdptr[a] == nullptr){
                        
                        Householdptr[a] = new household;
                        input_household(Householdptr[a]);
                        break;
                        
                    }else {
                        cerr << "This house already exists" << endl;
                        break;
                        
                    };
                    
                    
                case 'c' :
                { int h1,h2;
                    
                    cout << "number of household from which to copy consumers? " ;
                    cin >> h1 ;
                    
                    cout << "number of household to copy to? ";
                    cin >> h2 ;
                    
                   
                Householdptr[h2]->consumers=copy_consumer(Householdptr[h1]->consumers, Householdptr[h2]->consumers);
                    
                    break;
                                }
                    
                default:
                    cout << "sorry wrong choice" << endl;
                    
            }
            
        }
        
    }
    
    
    

