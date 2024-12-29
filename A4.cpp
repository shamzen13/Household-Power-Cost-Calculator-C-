


#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstring>


using namespace std;

/***********************************************************************
Matr.-Nr:                     3177505
Nachname/Surname:             Zainaldin
Vorname/Given name:           Sham Ahmad
Uni-Email:                    sham.zainaldin@stud.uni-due.de
Studiengang/Course of studis: Computer Engineering ISE Software Engineering
***********************************************************************/

enum Use{
    
    monday , tuesday , wednesday, thursday, friday, saturday, sunday , once,daily,mo_fr,sa_su,weekly
    
};

void input_use(string freq, Use& Use){
    
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
    Use use;
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
      Use use;
      consumer* consumers;
      
      float powerPrice;
      string powerSupplier;
      
      
    
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
            
        default:
            return Use();
        
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
    
    

        void print_consumer (consumer* c , int x, household* h){
        
            
            
        
   
        cout << right << setw(ColoumnWidth - 2) << x << ": " << left << setw(ColoumnWidth) << c->description << "(at address : " << &(c->description) << ")" << endl;
        
        cout << right << setw(ColoumnWidth) << "Power Consumption: " << left <<  c->watt << " W" << endl;
        cout << right << setw(ColoumnWidth) << "Power Consumption standby: " << left << c->watt_standby << " W" << endl;
        cout << right << setw(ColoumnWidth) << "annual hours of use: " << left << annual_hours_of_use(c) << " h" << endl;
        cout << right << setw(ColoumnWidth) << "annual hours of standby: " << left << annual_hours_of_standby(c) << " h" << endl;
        
        float annualcon = annual_kWh(c)/1000;
        cout << right << setw(ColoumnWidth) << "annual consumption: "<< left << annualcon  << " kWh" << endl;
        
        //here
        float anncosts = h->powerPrice * annualcon ;
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
    
    float AnnualPowerCosts (household h){
        
        float Consumption = AnnualConsumption(h);
        
        return Consumption  * h.powerPrice;
        
        
    }
    
    
    /*void function to print out the information based on the number of persons*/
    void print_household(household* h, int HouseNo){
        
        string yesno;
        
        if(h->HotWater == false){
            yesno = "no";
        }else if(h->HotWater == true){
            yesno = "yes";
        };
        
       
        
        float Consumption = AnnualConsumption(*h);
        float Cost = AnnualPowerCosts(*h);
        
        
        consumer* accumalate = h -> consumers;
        float annualtotalccons= 0;
        while (accumalate != nullptr) {
            annualtotalccons += annual_kWh(accumalate)/1000;
            accumalate = accumalate->next;
        }
        
       
        cout << " H O U S E H O L D   N O  " << HouseNo << "  P O W E R   C O N S U M P T I O N" << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << right << setw(ColoumnWidth) << "City: " << h->City << "(at address : " << &(h->City) << ")" << left << setw(ColoumnWidth) << endl;
        cout << right << setw(ColoumnWidth) << "price for one kWh: " << left << h->powerPrice*100 << " ct/kWh" << endl;
        cout << right << setw(ColoumnWidth) << "power supplier: " << left << h->powerSupplier << endl;
        cout << right << setw(ColoumnWidth) << "square metres: " << left << h->SqrMeter << " qm" << endl;
        cout << right << setw(ColoumnWidth) << "persons: " << left << h->Persons << endl;
        cout << right << setw(ColoumnWidth) << "water heated using electricity: " << yesno << endl;
        cout << right << setw(ColoumnWidth) << "list of customers " << endl;
        
        
        cout << "------------------------------------------------------------" << endl;
        
        //print the consumers using while loop to iterate through every member of the structure list
        
        consumer* currentCons = h->consumers;
        int consumerno = 1;
        
        
        while (currentCons != nullptr){
            
            print_consumer(currentCons, consumerno, h);
            consumerno += 1;
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
        
        cout << right << setw(ColoumnWidth) << "total annual power costs: " << left << Cost + annualtotalccons * h->powerPrice << " EUR" << endl;
        
        
        
    }
    



    void input_household(household* h){
        
    
        
        string Q2 = "how many square metres does the household have?";
        input_integer(Q2, h->SqrMeter);
        
        
        cout << "how many persons live in this household? ";
        cin >> h->Persons;
        
        input_electric_water_heating(h->HotWater);
        
        cout << "what is the price for one kWh in EUR? ";
        cin >> h->powerPrice;
        
        cout << "who is the power supplier? ";
        cin >> h->powerSupplier;
        
        
    
        h->consumers = nullptr;
        
}

    
consumer* copy_consumer(consumer* fromh1, consumer* toh2) {
   
    consumer* copyCon = fromh1;
    consumer* head = nullptr;
    
    consumer* end = nullptr;
    
    while (copyCon != nullptr) {
        
        consumer* newCon = new consumer(*copyCon);
        
        
        if (head == nullptr) {
            head = newCon;
            end = newCon;
        } else {
            end->next = newCon;
            end = newCon;
        }
        
        copyCon = copyCon->next;
    }
    
    if (end != nullptr) {
        end->next = toh2;
    }
    
    return head;
}

//--------------------------------------------------------

ostream& operator<<(ostream& os, Use& use){
    
    switch(use){
            
        case once :
            os << "once";
            break;
        
        case daily :
            os << "daily";
            break;
            
        case mo_fr :
            os << "Monday to Friday";
            break;
            
        case sa_su :
            os << "Saturday to Sunday";
            break;
         
        case weekly :
            os << "Weekly";
            break;
        default :
            os << "null";
            break;
    }
    
    return os;
    
    
}

Use convertToString(string& useString){

    if(useString == "daily"){
        return daily;
    }else if(useString == "weekly"){
        return weekly;
    }else if(useString =="once"){
        return once;
    }else if(useString == "mo_fr"){
        return mo_fr;
    }else if(useString == "sa_su"){
        return sa_su;
    }else{
        return daily;
    }

    
}

void WritetoFile(household* currentHouse[], string city ,string fileName, int numhouse , char seperation){

    ofstream file;
    
    file.open(fileName);
    
    if (file.is_open()) {
        cout << fileName << "\" is opened.." << endl;
//HEADER
        file << "A4" << seperation << numhouse << seperation << city << endl;
        
//DIFFERENT HOUSEHOLDS
        
        for(int i  = 0 ; i < numhouse ; i++){
            household* h = currentHouse[i];
            
            if(h != nullptr){
                
        file << "household" << seperation << i << seperation << city << seperation << (h->HotWater ? "true" : "false") << seperation << h->Persons << seperation << h->SqrMeter << seperation << h->powerPrice << seperation << h->powerSupplier << endl;
                
//CONSUMERS
                
            int consumerCount = 1;
            consumer* currentConsumer = h->consumers;
                while(currentConsumer != nullptr){
                    
                    
                    
                    file << "consumer:" << currentConsumer->description << seperation
                    << currentConsumer->hours << seperation << currentConsumer->use << seperation
                    << currentConsumer->watt << seperation << currentConsumer->watt_standby << endl;
                    
                    currentConsumer = currentConsumer->next;
                    consumerCount++;
                    
                } }}
        
            }else {
                cerr << "Unable to open file" << endl; }
            
            file.close();
            cout << "output file \"" << fileName << "\" closed" << endl;
        
        }



void ReadtoFile(string fileName, household* h[], char separator, int n, string &City) {
    
    ifstream file(fileName);
   
    if (!file.is_open()) {
        cerr << "File cannot be opened" << endl;
        return;
    } else {
        cout << "Input file " << fileName << " opened.." << endl;

//task ID
        
        
        string task_ID;
        getline(file, task_ID, separator);
       
        //cout << task_ID << endl;
        
        if (task_ID != "A4") {
            cerr << "Invalid file format" << endl;
            return;
        }
        
//house number & if statement
        int numhouse;
        string houseNo;
        getline(file, houseNo, separator);
        numhouse = stoi(houseNo);
        
       //cout << numhouse << endl;
        
        if (numhouse > n) {
            cout << "file contains up to " << numhouse << ", but here only " << n << " are supported" << endl;
            file.close();
            cout << "input file " << fileName << " closed" << endl;
            
            return;
        }
//city
        string city;
        getline(file, city);
        City = city;

       //cout << city << endl;
       
//price
//        string priceString;
//        getline(file, priceString);
//        price = stof(priceString);

       // cout << price << endl;
        
        string House;
        
        getline(file,House,separator);
        
//READING HOUSEHOLDS&CONSUMERS
        if(House == "household"){
            
        while(!file.eof()){
            
            
                
                 // cout << House  << endl;
                    
                    int houseIndex = 0;
                    string index;
                    getline(file,index,separator);
                    houseIndex = stoi(index);
                    
                   // cout << houseIndex << endl;
                    
                    h[houseIndex] = new household;
                    household* h1 = h[houseIndex];
                    
                    
                    string city2;
                    getline(file, city2, separator);
                    h1->City = city2;
                    city2 = City;
                    
                    //cout << city2 << endl;
                    
                    string hot;
                    getline(file, hot, separator);
                    if (hot == "true") {
                        h1->HotWater = true;
                    } else {
                        h1->HotWater = false;
                    }
                    
                    //cout << hot << endl;
                    
                    
                    string personString;
                    
                    
                    getline(file,personString,separator);
                    h1->Persons = stoi(personString);
                    
                    //cout << personString << endl;
                    
                    string SqrString;
                    
                    getline(file,SqrString,separator);
                    h1->SqrMeter = stoi(SqrString);
                    
                    //cout << h1->SqrMeter << endl;
            
                    string powerString;
                    getline(file,powerString,separator);
                    h1->powerPrice = stof(powerString);
            
                    //cout << powerString << endl;
            
                    string supplier;
                    getline(file, supplier);
                    h1->powerSupplier = supplier;
            
                    //cout << supplier << endl;
                    
                    string consumer_ID;
                     
                    h[houseIndex] = h1;
                    
            while (getline(file, consumer_ID,separator) && (consumer_ID == "consumer")) {
                
                //cout << consumer_ID << endl;
                
                
                consumer* newCon = new consumer;
                
                string desc, hrs, useString, wattString, standbyString;
                
                getline(file, desc, separator);
                newCon->description = desc;
                
                
                //cout << newCon->description << endl;
                
                getline(file, hrs, separator);
                newCon->hours = stof(hrs);
                
                //cout << newCon->hours<< endl;
                
                getline(file, useString, separator);
                newCon->use = convertToString(useString);
                
                // cout << newCon->use << endl;
                
                
                getline(file, wattString, separator);
                newCon->watt = stof(wattString);
                
                //cout << newCon->watt << endl;
                
                getline(file, standbyString);
                newCon->watt_standby = stof(standbyString);
                
                //cout << newCon->watt_standby << endl;
                
                
                
                newCon->next = h1->consumers;
                h1->consumers = newCon;
                
                
                
            }
                    
                    
                }
            
        }
        }
    
    file.close();
    cout << "Input file " << fileName << " is closed" << endl;
}


    
    int main() {
        
        household* UserHousehold = new household;
        
        consumer* NewConsumer = new consumer;
        
        //float PricePerKwH;
        
        
        
        cout << "CALCULATION OF AVERAGE POWER COSTS FOR A HOUSE \n" << endl;
        
        int n;
        cout << "how many households does this house have? " ;
        cin >> n;
        
        household *Householdptr[n];
        
        for(int i = 0 ; i < n ; i++){
            Householdptr[i]=nullptr;
        }
        
        input_city(UserHousehold->City);
        
        
        //cout << "what is the price for one kWh in EUR ? " ;
        //cin >> priceperkwh;
        //PricePerKwH = priceperkwh;
        
        
        
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
            cout << "r read data from file" << endl;
            cout << "w write data to file" << endl;
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
                    
                    
                    //                case 'u' :
                    //
                    //                    cout << "number of household ?";
                    //                    int u;
                    //                    cin >> u;
                    //
                    //                    cout << "which one?";
                    //                    int k;
                    //                    cin >> k;
                    //
                    //                    move_up(Householdptr[u]->consumers, k);
                    //                    break;
                    
                    
                case 'p' :
                    int houseNo;
                    cout << "number of household ?";
                    cin >> houseNo;
                    
                    Householdptr[houseNo]->City = UserHousehold->City;
                    
                    
                    print_household(Householdptr[houseNo],houseNo);
                    
                    break;
                    
                    
                case 'a' :
                    
                    for(int i = 0 ; i<n ; i++){
                        if( Householdptr[i] != nullptr ){
                            Householdptr[i]->City = UserHousehold->City;
                            print_household(Householdptr[i],i);
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
                case 'w' :
                {
                    
                    
                    string writeFileName;
                    
                    cout << "input file name:";
                    cin>> writeFileName;
                    
                    char seperation;
                    cout << "input seperation character:";
                    cin >> seperation;
                    
                    
                    WritetoFile(Householdptr, UserHousehold->City , writeFileName, n, seperation);
                    
                    
                    
                    break;
                    
                }
                    
                case 'r' :
                {
                    string read;
                    cout << "input file name:";
                    cin >> read;
                    
                    char seperation;
                    cout << "input seperation character:";
                    cin >> seperation;
                    
                    
                    ReadtoFile(read, Householdptr, seperation, n, UserHousehold->City);
                    
                    for(int b = 0 ; b < n ; b++){
                        if(Householdptr[b] != nullptr){
                            Householdptr[b]->City = UserHousehold->City;
                        }}
                    
                    break;
                    
                    
                }
                    
                    
                    
                    
                    
                    
                    
                    
                default:
                    cout << "sorry wrong choice" << endl;
                    
            }
            
        }
        
    }
    
    
    
    
    

