
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
    
    monday , tuesday , wednesday, thursday, friday, saturday, sunday , once, daily, mo_fr, sa_su, weekly
    
};

void input_use(string freq, Use& Use){
    
    cout << freq << endl;
    cout << "daily (d)" << endl << "mo_fr (m)" << endl << "once (o)" << endl
    << "sa_su (s)" << endl << "weekly (w) ?" ;
    
    char input;
    cin >> input ;
    
    switch (input){
            
        case 'd' :
            Use = daily;
            break;
            
        case 'm' :
            Use = mo_fr;
            break;
            
        case 'o' :
            Use = once;
            break;
            
        case 's' :
            Use = sa_su;
            break;
            
        case 'w' :
            Use = weekly;
            break;
            
        default:
            cout << "Invalid choice" << endl;
            Use = once;
            break;
            
            
            
            
            
    }
                
            }


string UseToString(Use use) {
    switch (use) {
        case once:
            return "once";
        case daily:
            return "daily";
        case mo_fr:
            return "Monday to Friday";
        case sa_su:
            return "Saturday and Sunday";
        case weekly:
            return "Weekly";
        default:
            return "null";
    }
}


const int ColoumnWidth = 35;

/* four global constant variables as given*/

int const ConsPerPerson = 200;
int const ConsPerSqrMeter = 9;
int const ConsPerDevice = 200;
int const ConstHeat = 550;



//global variables defined for some calculations
float cost = 0;
float consumption = 0;

// ----------------- ABSTRACT CLASS DEVICE --------------



class Device {
    
        private:
    string description;
    
    Device* next;
    
public:
    
    // getters
    
    string getDesc();

    Device* get_next();
    
    
    
    
    // setters
    void setDesc(string desc);

    void set_next(Device* d);
    
    // overloaded constructor
    
    
    Device(Device* device = nullptr);



    //virtual deconstructor - incomplete
    virtual ~Device()=0;
    
    // virtual input
    
    virtual void input()=0;
    
    // get a copy
    virtual Device* get_a_copy() = 0;
        
        
    
    
    //virtual public pure function declarations
     
    virtual void print(int x, float y) = 0;
    
    
    virtual float annual_kWh() = 0;
    
    virtual string get_a_string_for_file(char c) = 0;
    
    
    
};

Device::Device(Device* device) :
   next(device) {}


Device:: ~Device(){
    cout << "Device " << this->description << " at address "<< this <<" deleted" << endl ;
}

void Device::input(){
    
    cout << "what is the description of the power consumer ? " ;
    cin.ignore();
    getline(cin,description);
}


// getters

string Device::getDesc(){
    return description;
}

Device* Device::get_next(){
    return next;
}

void Device::setDesc(string desc){
    description=desc;
};

void Device::set_next(Device* d){
    next = d;
};




//--------------------CLASS CONSUMER------------------------


class Consumer : public Device {

     private:
  
    
    float watt;
    
    Use use;
    
    static unsigned int total_number;

    
    public :
    
    // get
    
        
    float getWatt();
    
 
    Use getUse();
    
    
    
    // set
    
    void setWatt(float w);
    
    void setUse(Use u);
    
    //overloaded constructor - here
    Consumer(Device* device = nullptr);
    
    
    //virtual public input
    
    virtual void input() override;
    
    
  
    //getter for the instance
    static unsigned int get_total_number(){
        return total_number;
    }
    
    //destructor
    virtual ~Consumer()=0;
    

    
   
};


Consumer::Consumer(Device* device)  : Device(device)
{
 
    total_number++;
}

Consumer:: ~Consumer(){
     
     cout << "The consumer with description : " <<  Device::getDesc() << " at address " << this << "deleted" << endl;
     
     
     total_number--;
     
 }


void Consumer::input()  {
    
    Device::input();
    cout << "How many watt will it have ? " ;
    cin >> watt;
    
  
    string freq = "How often will it be used ? ";
    input_use(freq,use);
    
    
};


float Consumer::getWatt(){
return watt;
}



Use Consumer::getUse(){
return use;
}




// set


void Consumer::setWatt(float w){
watt = w;
}

void Consumer::setUse(Use u){
use = u;
}

//initializing total number
unsigned int Consumer::total_number = 0 ;



//--------------------CLASS Immobile------------------------

class Immobile : public Consumer {
    
    private :
   
    float watt_standby, hours;
    
    
    public :
    
    //overloaded constructor
    
    Immobile(Device* d = nullptr):
    Consumer(d)
    {
        
        
    }
    
    //destructor
    
    ~Immobile(){
        cout << "Immobile " << Consumer::getDesc() << " at address " << this << " deleted " << endl;
    }
    
    //setters&getters
    
    float getWattStand(){
        return watt_standby;
    }
    
    float getHrs(){
        return hours;
    }
    
    void setWattStand(float standby){
        watt_standby = standby;
    }
    
    void setHrs(float hr){
        hours = hr;
    }
    
    
    
    //functions
    
    
    
    float annual_hours_of_standby (){
        
        float annualUseHrsStandby = annual_hours_of_use();
        return 8760 - annualUseHrsStandby;
        
    }
    
    
    float annual_hours_of_use(){
        
        float hrsPerYear;
        
        switch(Consumer::getUse()) {
                
            case daily:
                hrsPerYear = 365 * hours;
                return hrsPerYear;
                break;
                
            case weekly:
                hrsPerYear = 52 * hours;
                return hrsPerYear;
                break;
            
            case sa_su:
                hrsPerYear = 104 * hours;
                return hrsPerYear;
                break;
                
            case mo_fr:
                hrsPerYear = 260 * hours;
                return hrsPerYear;
                break;
                
            case once:
                hrsPerYear = hours;
                return hrsPerYear;
                break;
                
            default:
                hrsPerYear = 0;
                break;
        }
        return hrsPerYear;
    }

    float annual_kWh() override{
        
        float annualUseHrs = annual_hours_of_use();
        float annualStandbyHrs = annual_hours_of_standby();
        float totalCons =(annualUseHrs * Consumer::getWatt() + annualStandbyHrs * watt_standby);
        
        
        return totalCons/1000;
    }

    void print (int x,float powerprice) override {
        
        
        
   
        cout << right << setw(ColoumnWidth - 2) << x << ": " << left << setw(ColoumnWidth) << Consumer::getDesc() << endl;
        cout << right << setw(ColoumnWidth) << "(this : " << this << ")" << endl;
        cout << right << setw(ColoumnWidth) << "Power Consumption: " << left <<  Consumer::getWatt() << " W" << endl;
        cout << right << setw(ColoumnWidth) << "Power Consumption standby: " << left << watt_standby << " W" << endl;
        cout << right << setw(ColoumnWidth) << "annual hours of use: " << left << annual_hours_of_use() << " h" << endl;
        cout << right << setw(ColoumnWidth) << "annual hours of standby: " << left << annual_hours_of_standby() << " h" << endl;
        
        float annualcon = annual_kWh();
        cout << right << setw(ColoumnWidth) << "annual consumption: "<< left << annualcon  << " kWh" << endl;
        
        
        float anncosts = powerprice * annualcon ;
        cout << right << setw(ColoumnWidth) << "annual costs: " << left << anncosts << " EUR" << endl;
        
        
        
    }
    
    void input() override{
        Device::input();
        cout << "How many watts? " ;
        float Watt;
        cin >> Watt;
        Consumer::setWatt(Watt);
                          
        cout << "How many watt standby? " ;
        cin >> watt_standby;
        
        Use usee;
        input_use("How often will it be used ?", usee);
        Consumer::setUse(usee);
        
        
        
        cout << "Enter number of hours: " ;
        cin >> hours;
        
        
    }
                
                
                
        
        //get a copy function - here
    
    virtual  Device* get_a_copy() override {
        
        Device* copy = new Immobile;
        
        *copy = *this;
        
        return new Immobile(*this);
        
    }
            
        //get_string_for_file function
    
    virtual string get_a_string_for_file(char c) override {
        
        string immo = "Immobile";
    string complete = immo + c + Device::getDesc() + c + to_string(hours) + c + UseToString(Consumer::getUse()) + c + to_string(watt_standby);
        
        return complete;
        
        
        
    }
    
        
};
   
    
    
//--------------------CLASS Mobile------------------------

class Mobile : public Consumer{
    
private:
    
    float km;
    
public:
    
    //overloaded constructor
    
    Mobile(Device* d = nullptr):
    Consumer(d)
    {}
    
    //destructor
    
    ~Mobile()
    {
        cout << "Mobile " << Consumer::getDesc() << " at address " << this << " deleted " << endl;
        
    }
    
    
    
    //setter&getter
    
    void set_km(float KM){
        km = KM;
    }
    
    float get_km(){
        return km;
    }
    
    void input() override {
        Device::input();
        
        
        cout << "how many watt will it have ? ";
        float watt;
        cin >> watt;
        Consumer::setWatt(watt);
        
        Use use;
        input_use("how often will it be used ? ", use);
        Consumer::setUse(use);
        
        cout << "how many km will be driven? ";
        cin>>km;
    }
    
  
    float annual_kWh() override{
        
        float hrsMultiplied_freq;
        
        switch(Consumer::getUse()){
                
            case daily:
                hrsMultiplied_freq = 365 * km;
            
                break;
                
            case weekly:
                hrsMultiplied_freq = 52 * km;
                ;
                break;
            
            case sa_su:
                hrsMultiplied_freq = 104 * km ;
                
                break;
                
            case mo_fr:
                hrsMultiplied_freq = 260 * km;
                
                break;
                
            case once:
                hrsMultiplied_freq = km;
                
                break;
                
            default:
                hrsMultiplied_freq = 0;
                break;
            
                
        }
        
        float ConsumptionPer100 = Consumer::getWatt() / 100.0;
        float AnnualPowerConsumption = hrsMultiplied_freq * ConsumptionPer100;
        
            
        return AnnualPowerConsumption/1000;
    }

     
    void print(int no_devices, float PricePerHour) override{
        
        cout << right << setw(ColoumnWidth) << no_devices << ":" << left << setw(ColoumnWidth) << Consumer::getDesc() << endl;
        cout << right << setw(ColoumnWidth) << "(this : " << this << ")" << endl;
        cout << right << setw(ColoumnWidth) << "power consumption 100km : " << fixed << setprecision(2) << Consumer::getWatt() / 1000 << " kWh" << endl;
        cout << right << setw(ColoumnWidth) << "km driven : "  << fixed << setprecision(2) << km << " km " << UseToString(Consumer::getUse()) << endl;
        
        float annKwH = annual_kWh();
        cout << right << setw(ColoumnWidth) << "annual consumption : "  << annKwH << " kWh" << fixed << setprecision(2)  << endl; //here
        
        
        float annCosts = annual_kWh() * PricePerHour;
        cout << right << setw(ColoumnWidth) << "annual costs : "  << annCosts << " EUR" <<fixed << setprecision(2) << endl;

    
        
    }
    
    //get a copy function - here

virtual  Device* get_a_copy() override {
    
    
    Device* copy = new Mobile;
    
    *copy = *this;
    
    return new Mobile(*this);
    
}
        
    //get_string_for_file function

virtual string get_a_string_for_file(char c) override {
    
    string mob = "Mobile" ;
    
    
    string complete = mob + c + Consumer::getDesc() + c + to_string(km) + c + UseToString(Consumer::getUse()) + c + to_string(Consumer::getWatt()) ;
    return complete;
    
}
    
    
    
};

//--------------------CLASS PRODUCER------------------------

class Producer : public Device{
  
    public :

    //overloaded constructor
    Producer(Device* d = nullptr);
  
    //destructor
    virtual ~Producer()=0;
        
    //input
    void input();
    
};

Producer::Producer(Device* d):
Device(d)
{}


void Producer::input(){
    Device::input();
}

Producer:: ~Producer(){
    
    cout << "Producer " << Device::getDesc() << " at address " << this << " deleted" << endl;
    
    
}
    

//--------------------CLASS SOLAR------------------------

class Solar : public Producer{
    
    private :
    
    float watt_peak;
    int year;
    
    
    public :
    //overloaded constructor
    
    Solar(Device* d = nullptr):
    Producer(d)
    {}

    //destructor - here
    
    virtual ~Solar(){
        cout << "Solar " << Device::getDesc() << " at address " << this << " deleted" << endl;
    }
    
    //setters&getters
    
    void set_watt_peak(float peak){
        watt_peak = peak;
    }
    
    void set_year(int y){
        year = y;
    }
  
    float get_watt_peak(){
        return watt_peak;
    }
    
    int get_year(){
        return year;
    }
    
    
    //input
    void input()override{
        Producer::input();
        cout << "how many watt peak have been installed? ";
        cin >> watt_peak;
        cout << "in which year were the solar modules installed? " ;
        cin >> year;
    }
    
    //annual kwh
    float annual_kWh() override{
        
        float kiloHrs;
        
        
//        for(int currentYear = 2024 ; currentYear < year  ; currentYear++){
//            
//            kiloHrs *= 1 - 0.005;
//            
//        }
       
        float reduction = 0.005;
        float total_reduction = (2024-year) * reduction;
        
        float reduction_value =  watt_peak * total_reduction;
        
        kiloHrs = (-watt_peak) + reduction_value;
        
        return kiloHrs;
            
         
    }
        

    
    
     //print
        void print(int no_devices, float priceperkwh) override{
            
            cout << right << setw(ColoumnWidth) << no_devices << ":" << left << setw(ColoumnWidth) << Producer::getDesc() << endl;
            cout << right << setw(ColoumnWidth) << "(this : " << this << ")" << endl;
            cout << right << setw(ColoumnWidth) << "solar cells installed power : "  << fixed << setprecision(2) <<  watt_peak << " watt peak" << endl;
            cout << right << setw(ColoumnWidth) << "age of solar cells : " << fixed << setprecision(2) << 2024-year << " years" << endl;
            cout << right << setw(ColoumnWidth) << "annual production : "  << fixed << setprecision(2) << annual_kWh()  << " kWh "<< endl;
            cout << right << setw(ColoumnWidth) << "annual savings : " << fixed << setprecision(2) << (annual_kWh()*priceperkwh) << " EUR " << endl;

            
        }
        
        //get a copy function - here

    virtual  Device* get_a_copy()override{
     
        Device* copy = new Solar;
        
        *copy = *this;
        return new Solar(*this);
        
    }
            
        //get_string_for_file function

    virtual string get_a_string_for_file(char c) override{
        
        string sol = "Solar";
        string complete = sol + c + Producer::getDesc() + c + to_string(year) + c + to_string(watt_peak) ;
        return complete;
    };
        
    
};






//--------------------CLASS HOUSEHOLD------------------------


class Household {
    
        private :
    
    unsigned int Persons;
    int SqrMeter;
    bool HotWater;
    Use use;
    Device* device;
    float powerPrice;
    string powerSupplier;
    

        public:
    
    //getters
    int getPersons(){
        return Persons;
    }
    
    int getSqrMeter(){
        return SqrMeter;
    }

    Device* getDevices(){
        return device;
    }
    
    bool getHotWater(){
        return HotWater;
    }
    
    Use getUse(){
        return use;
    }
    
   
    
    float getPowerPrice(){
        return powerPrice;
    }
    
    string getPowerSupplier(){
        return powerSupplier;
    }
    
    
    //setters
    
    void setPersons(unsigned int person){
        Persons = person;
    }
    
    void setSqrMeter(int sqr){
        SqrMeter = sqr;
    }
    
    
    void setHotWater(bool hot){
        HotWater = hot;
    }
    
    void setUse(Use u){
        use = u;
    }
    
    void setDevices(Device* d){
        device = d;
    }
    
    void setPowerPrice(float price){
        powerPrice = price;
    }
    
    void setPowerSupplier(string supplier){
        powerSupplier = supplier;
    }

    //standard constructor initializing consumer into a null pointer
    Household() :
    device(nullptr) {}
    
    //deconstructor & deleting household
    ~Household(){
        
        cout << "the household at address " << this << " is deleted" << endl;
    
        Device* currentConsumer = device;
        while (currentConsumer != nullptr) {
            Device* temp = currentConsumer;
            currentConsumer = currentConsumer->get_next();
            temp->~Device();
        }
        
    }
    
    
    
    //functions
    
    Device* copy_devices(Household* fromh1,Household* toh2) {
        
        Device* currentDevice = fromh1->getDevices();
        
        
        while(currentDevice != nullptr){
            
            Device* copy = currentDevice->get_a_copy();
            
            toh2->add_device_to_household(copy);
            
           currentDevice = currentDevice->get_next();
            
        }
         
       
        return toh2->getDevices();
    }
    
    
    
    Device* move_up(Device* head, int k ){
        
        Device* currentposition = head;
        Device* previousposition = nullptr;
        
        int prev = k-1;
        //to go to position, stop before position k
        
        for(int i = 1 ; i < prev ; i++){
            
            previousposition = currentposition;
            currentposition=currentposition->get_next();
            
        }
        //only one item in list
        if(head->get_next() == nullptr && k==1){
            return head;
        };
        
        if(previousposition!=nullptr){
            previousposition->set_next(currentposition);
        };
        
        
        if(k==2){
            
            
            previousposition->set_next( currentposition->get_next());
            currentposition->set_next(previousposition);
            head = currentposition;
            
            
        };
        
        if(k>2 && currentposition->get_next()!=nullptr && currentposition != nullptr){
            
            //draft (u can ignore unless my code isnt clear)
            /*
             current is at k-1 (lets say number 2 as the loop stops one position before k), cons is defined at number 3 (the node we want to move)
             we point the current pointer to the node after 3 ( number 4 ), since 2 will be the node pointing to 4 when they switch
             then change the pointer of number 3 to 2 so they switch places, and redefine current as 3 and return it
             */
            
            Device* cons = currentposition->get_next();
            currentposition->set_next(currentposition->get_next()->get_next());
            cons->set_next(currentposition);
            currentposition = cons;
        };
        
        
        
        
        //reorganize
        if(previousposition != nullptr){
            previousposition->set_next(currentposition);
            currentposition = head;
        };
        
        
        return currentposition;
        
    }
    
    
    void input_double(string Q,float &no){
      
      
      cout << Q;
      cin >> no;
      

      
    }

    //here
    void add_device_to_household (Device* c){
      
//        c->set_next(device);
//        device  = c;
        
        if (Immobile* immobileDevice = dynamic_cast<Immobile*>(c)) {
               Immobile* newImmobile = new Immobile(*immobileDevice);
               newImmobile->set_next(device);
               device = newImmobile;
           } else if (Solar* solarDevice = dynamic_cast<Solar*>(c)) {
               Solar* newSolar = new Solar(*solarDevice);
               newSolar->set_next(device);
               device = newSolar;
           } else if (Mobile* mobileDevice = dynamic_cast<Mobile*>(c)) {
               Mobile* newMobile = new Mobile(*mobileDevice);
               newMobile->set_next(device);
               device = newMobile;
           }
    
      
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
    
    
    
    void input_household(){
        
    
        int sqr;
        string Q2 = "how many square metres does the household have?";
        input_integer(Q2, sqr);
        SqrMeter = sqr;
        
        int person;
        cout << "how many persons live in this household? ";
        cin >> person;
        Persons = person;
        
        bool hot;
        input_electric_water_heating(hot);
        HotWater = hot;
        
        float power;
        cout << "what is the price for one kWh in EUR? ";
        cin >> power;
        powerPrice = power ;
        
        string supplier;
        cout << "who is the power supplier? ";
        cin.ignore();
        getline(cin,supplier);
        powerSupplier = supplier;
        
    
        device = nullptr;
        
  }
    
    
    float AnnualConsumption (){
        float AnnCons;
        if(HotWater) {
            AnnCons = (Persons*ConstHeat)+(SqrMeter*ConsPerSqrMeter);
            return AnnCons;
        }else{
            AnnCons = (Persons*ConsPerPerson)+(SqrMeter*ConsPerSqrMeter);
            return AnnCons;
        }
    }
    
    

    
    /* function to calculate the power costs */
    
    float AnnualPowerCosts (float power){
        
        float consumption = this->AnnualConsumption();
        
        return consumption * power;
        
    }
    

    void print_household(int HouseNo){
        
        string yesno;
        
        if(HotWater == false){
            yesno = "no";
        }else if(HotWater == true){
            yesno = "yes";
        };
        
       
        
        float Consumption = AnnualConsumption();
        float Cost = AnnualPowerCosts(powerPrice);
        
        
        Device* accumalate = device;
        float annualtotalccons = 0;
        while (accumalate != nullptr) {
            annualtotalccons += accumalate->annual_kWh();
            accumalate = accumalate->get_next();
        }
        
       
        cout << " H O U S E H O L D   N O  " << HouseNo << "  P O W E R   C O N S U M P T I O N" << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << right << setw(ColoumnWidth) << "(this: " << left << this << ")" << endl;
        cout << right << setw(ColoumnWidth) << "price for one kWh: " << left << powerPrice*100 << " ct/kWh" << endl;
        cout << right << setw(ColoumnWidth) << "power supplier: " << left << powerSupplier << endl;
        cout << right << setw(ColoumnWidth) << "square metres: " << left << SqrMeter << " qm" << endl;
        cout << right << setw(ColoumnWidth) << "persons: " << left << Persons << endl;
        cout << right << setw(ColoumnWidth) << "water heated using electricity: " << yesno << endl;
        cout << right << setw(ColoumnWidth) << "list of devices " << endl;
        
        
        cout << "------------------------------------------------------------" << endl;
        
        //print the consumers using while loop to iterate through every member of the list
        
        Device* currentCons = device;
        int consumerno = 1;
        
        
        while (currentCons != nullptr){
            
            currentCons->print(consumerno,powerPrice);
            consumerno += 1;
            currentCons = currentCons->get_next();
            
        }
        
        
        
        cout << "------------------------------------------------------------" << endl;
        
        cout << right << setw(ColoumnWidth) << "power consumption square meters: " << left <<(SqrMeter * ConsPerSqrMeter) << " kWh" << endl;
        
        if(HotWater){
            cout << right << setw(ColoumnWidth) << "power consumption on all persons: " << left << (Persons * ConstHeat) << " kWh" << endl;
        }else{
            cout << right << setw(ColoumnWidth) << "power consumption on all persons: " << left << (Persons * ConsPerPerson) << " kWh" << endl;
        };
        
      
        
        cout << right << setw(ColoumnWidth) << "total annual power consumption: " << left << Consumption + annualtotalccons << " kWh" << endl;
        
        cout << right << setw(ColoumnWidth) << "total annual power costs: " << left << Cost + annualtotalccons * powerPrice << " EUR" << endl;

//        cout << Cost << endl;
//        cout << annualtotalccons << endl;
//        cout << powerPrice << endl;
//       cout << Consumption << endl;
        
        cout << "------------------------------------------------------------" << endl;
        cout << "------------------------------------------------------------" << endl;
        
    }
    




    
    
};


  //---------------------CLASS ADDRESS------------------------------
  
class Address {

    private:
    
    string street,no,zip,city;
    
    public :
    
    //overloading constructor for initializing
    
    Address(string street, string no, string zip, string city):
    
    street(""),no(""),zip(""),city("")
    
    {}

    
    //getters
    
    string getStreet(){
        return street;
    }
    
    string getNo(){
        return no;
    }
    
    string getZip(){
        return zip;
    }
    
    string getCity(){
        return city;
    }
    
    
    //methods for inputting and to_string
    
    void inputAddress(string str, string No, string zipcode, string cityy ){
        
        street = str;
        no = No;
        zip = zipcode;
        city = cityy;
        
         
    }
    
    
    string to_string(){
        
        string AddressString = street +" " + no + ",  " + zip + " " + city;
        return AddressString;
        
    }
    
    //deconstructor
    
    ~Address(){
        
        cout << "Address : " << to_string() << " at address " << this  << " deleted" << endl;
      
        
        
    }
    
    
    
};

Use convertToUse(string& useString){

  if(useString == "daily"){
      return daily;
  }else if(useString == "weekly"){
      return weekly;
  }else if(useString =="once"){
      return once;
  }else if(useString == "Monday to Friday"){
      return mo_fr;
  }else if(useString == "Saturday and Sunday"){
      return sa_su;
  }else{
      return daily;
  }

  
}

//--------------CLASS HOUSE-------------------------------

class House{
    
private:
    
    int number_of_households;
    Household **household;
    Address address;
    
    
    
public:
    
    //constructor to initialize array
    House(int n, Address add): number_of_households(n), address(add){
        
        household = new Household*[number_of_households];
        for(int i = 0 ; i < number_of_households ; ++i){
            household[i] = nullptr ;
            
        }}
        
        
    //getting households
        Household* get_household(int n){
            return household[n];
            
        }
    
        Household* operator[](int n){
        return household[n];
    }
        
    
    void set_household(Household* h, int n){
        household[n] = h;
    }
    

    
    
    //deconstructor
    
    ~House(){
        
//        cout << "House at address : " << this << " deleted" << endl;
        
//        address.~Address();

        
        for(int i = 0; i < number_of_households ; i++){
            
            Household* h = get_household(i);
            if(h != nullptr){
        
        
                h->~Household();
            
            }
            
            
        }
        
        delete[] household;
        
        
        
    }
    
    
    //functions
    
    
    void print_all(){
        
        unsigned int No_consumers = Consumer::get_total_number();
        
        cout << "===========================================================" << endl;
        
        cout << right <<setw(ColoumnWidth) << "H O U S E" << left << setw(ColoumnWidth) << endl;
        
        cout << "===========================================================" << endl;
        
        
        cout << right << setw(ColoumnWidth) << "(this : " << this << ")" << left << setw(ColoumnWidth) << endl;
        cout << right <<  setw(ColoumnWidth) << "address: " << address.getStreet() << " " << address.getNo() << "," << address.getZip() << " " << address.getCity() << left << setw(ColoumnWidth) << endl;
        cout << right << setw(ColoumnWidth) << "number of households: " << number_of_households << left << setw(ColoumnWidth) << endl;
       
        cout << right << setw(ColoumnWidth) << "total number of all consumers: " << No_consumers << left << setw(ColoumnWidth) << endl;
        
        
        cout << "===========================================================" << endl;
        
        for (int i  = 0 ; i < number_of_households ; i++){
            
            Household* h = get_household(i);
            
            if (h != nullptr){
                h->print_household(i);
            }
            
        }
        
        
    }
    
    void write_to_file(string fileName, char seperation){

      ofstream file;
      
      file.open(fileName);
      
      if (file.is_open()) {
          cout << fileName << "\" is opened.." << endl;
    //HEADER
          
          
          
            
          
          
          file << "A6" << seperation << number_of_households << seperation << address.getStreet() << seperation << address.getNo()  << seperation << address.getZip() << seperation << address.getCity() << endl;

          
    //DIFFERENT HOUSEHOLDS
          
          for(int i  = 0 ; i < number_of_households ; i++){
              Household* h = household[i];
              
              if(h != nullptr){
                  
                  
                  
          file << "Household" << seperation << i << seperation << (h->getHotWater() ? "true" : "false") << seperation << h->getPersons() << seperation << h->getSqrMeter() << seperation << h->getPowerPrice() << seperation << h->getPowerSupplier() << endl;
                  
    //CONSUMERS
                  
              int consumerCount = 1;
              Device* currentDevice = h->getDevices();
                  while(currentDevice != nullptr){

                      file << currentDevice->get_a_string_for_file(seperation) << endl;
                      
                   currentDevice = currentDevice->get_next();
                      consumerCount++;
                      
                  } }}
          
              }else {
                  cerr << "Unable to open file" << endl; }
              
              file.close();
              cout << "output file \"" << fileName << "\" closed" << endl;
          
          }
    
    
    
  static void ReadtoFile(House* newHouse, string fileName, char separator) {
      
      ifstream file(fileName);
     
      if (!file.is_open()) {
          cerr << "File cannot be opened" << endl;
          return;
      } else {
          cout << "Input file " << fileName << " opened.." << endl;

    //task ID
         
          
          string task_ID;
          getline(file, task_ID, separator);
         
          
          
          
          if (task_ID != "A6") {
              cerr << "Invalid file format" << endl;
              return;
          }
          
    
    //house number & if statement
          int numhouse;
          string houseNo;
          getline(file, houseNo, separator);
          numhouse = stoi(houseNo);
          newHouse->number_of_households = numhouse;
          
          
          string street, address_houseno,zip,city;
          Address add = Address(street,address_houseno,zip,city);
          
          

          //address line
          
          
          getline(file,street,separator);
          
          
          
          
          
          
          getline(file, address_houseno, separator);
          
          
      
          
          
          getline(file,zip,separator);
          
          
      
          
          
          getline(file, city);

          
      
          
         
          
//          House* newHouse  = new House(numhouse,add);
          
          newHouse->address.inputAddress(street, address_houseno, zip, city);
          
          string House;
          
          getline(file,House,separator);
          
    //READING HOUSEHOLDS&CONSUMERS
          if(House == "Household"){
              
              while(!file.eof()){
                  
                  
                 
                  
                  int houseIndex = 0;
                  string index;
                  getline(file,index,separator);
                  houseIndex = stoi(index);
                  
              
                  
                  Household* h1 = new Household;
                
                  
                  string hot;
                  getline(file, hot, separator);
                  if (hot == "true") {
                      h1->setHotWater(true);
                  } else {
                      h1->setHotWater(false) ;
                  }
                  
            
                  
                  string personString;
                  
                  getline(file,personString,separator);
                  
                  int personInt = stoi(personString);
                  h1->setPersons(personInt);
                  
                  
                  
                  
                  string SqrString;
                  
                  getline(file,SqrString,separator);
                  
                  
                  int SqrInt = stoi(SqrString);
                  h1->setSqrMeter(SqrInt);
                  
                 
                  
                  
                  
                  string powerString;
                  getline(file,powerString,separator);
                  float PowerFloat = stof(powerString);
                  h1->setPowerPrice(PowerFloat);
                  
                  
                  
                  string supplier;
                  getline(file, supplier);
                  h1->setPowerSupplier(supplier);
                  
                 
                  
                  string device_ID;
                  
                  
                  
                  
                  while(getline(file,device_ID,separator) && ((device_ID == "Solar") || (device_ID == "Mobile" ||device_ID == "Immobile" ))){
                      
                      if(device_ID == "Solar"){
                          
                          
                          Solar* newSol = new Solar;
                          
                          string description,yearString,peakString;
                          
                          getline(file,description,separator);
                          newSol->setDesc(description);
                          
                 
                          
                          getline(file,yearString,separator);
                          int yearFloat = stoi(yearString);
                          newSol->set_year(yearFloat);
                          
                                
                          getline(file,peakString);
                          float peakFloat = stof(peakString);
                          newSol->set_watt_peak(peakFloat);
                          
                          
                          newSol->set_next(h1->getDevices()) ;
                          h1->setDevices(newSol);
                          
                          
                      }else if(device_ID == "Mobile"){
                          
                          
                          Mobile* newMob = new Mobile;
                          string descrip, useString, wattString, Km;
                          
                          getline(file,descrip,separator);
                          newMob->setDesc(descrip);
                          
                          
                          
                          getline(file,Km,separator);
                          float km = stof(Km);
                          newMob->set_km(km);
                          
                         
                          
                          getline(file, useString, separator);
                          newMob->setUse(convertToUse(useString));
                          
                          
                          
                          getline(file,wattString);
                          float wattFloat = stof(wattString);
                          newMob->setWatt(wattFloat);
                          
                          
                          
                          newMob->set_next(h1->getDevices()) ;
                          h1->setDevices(newMob);
                          
                          
                      } else if((device_ID == "Immobile")){
                          
                          
                          //cout << consumer_ID << endl;
                          
                          
                          Immobile* newCon = new Immobile;
                          
                          string desc, hrs, useString, wattString, standbyString;
                          
                          getline(file, desc, separator);
                          newCon->setDesc(desc);
                          
                          
                          //cout << newCon->description << endl;
                          
                          getline(file, hrs, separator);
                          newCon->setHrs(stof(hrs));
                          
                          getline(file,useString,separator);
                          newCon->setUse(convertToUse(useString));
                          
                          
                          getline(file,wattString,separator);
                          float wattF = stof(wattString);
                          newCon->setWatt(wattF);
                          
                          getline(file, standbyString);
                          newCon->setWattStand(stof(standbyString));
                          
                          //cout << newCon->watt_standby << endl;
                          
                          
                          
                          newCon->set_next(h1->getDevices()) ;
                          h1->setDevices(newCon);
                          
                          
                          
                          
                      }
                  }
                  newHouse->set_household(h1, houseIndex);
           }
          }
        }
      
      file.close();
      cout << "Input file " << fileName << " is closed" << endl;
    }

    
        
};
    

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
          os << "Saturday and Sunday";
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


  int main() {
      
      
      
      //Device* NewConsumer = new device;
      
      House* house = nullptr;
      
      //float PricePerKwH;
      
      
      
      cout << "CALCULATION OF AVERAGE POWER COSTS FOR A HOUSE - CLASS VERSION WITH INHERITANCE \n" << endl;
          
      
      //cout << "what is the price for one kWh in EUR ? " ;
      //cin >> priceperkwh;
      //PricePerKwH = priceperkwh;
      
      
      
      //for the selection menu
      
      char UserChoice;
      bool program;
      program = true;
      
      while(program){
          
          cout << "q quit" << endl;
          cout << "d delete house" << endl;
          cout << "h house initialisation" << endl;
          cout << "i input immobile consumer" << endl;
          cout << "s input solar producer" << endl;
          cout << "u move up device" << endl;
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
                  
                  
            
                  
                  
                  
              case 'h' :
              {
                  
                  int n;
                  cout << "how many households does this house have? " ;
                  cin >> n;
                  
                  
                  Household *Householdptr[n];
                  
                  
                  for(int i = 0 ; i < n ; i++){
                      Householdptr[i]=nullptr;
                  }
                
                  
                  string streetname, num, zipcode, cit;
                  
                  
                  Address add = Address(streetname, num, zipcode, cit);
                  cout << "what is the street name? ";
                  cin.ignore();
                  getline(cin,streetname);
                  
                  
                  cout << "what is house number? ";
                  cin >> num;
                  
                  cout << "what is zip code? ";
                  cin >> zipcode;
                  
                  cout << "what is the city name? ";
                  cin.ignore();
                  getline(cin,cit);
                  
                  add.inputAddress(streetname, num, zipcode, cit);
                  

                  
                  house = new House(n,add);
                  
                  break;
              };
                  
              case 'd' :
              {
                  
//                  if(house != nullptr){
//
//                      for(int i = 0 ; i < 100 ; i++){
//                          Household* h = house->get_household(i);
//                          if(h != nullptr){
//                              delete h;
//
//                          }
                      
                      
                  //house->~House();
    delete house;
                      house = nullptr;
                  
                  
                  break;
              }
                  
              case 'i' :
              {
                  int x;
                  cout << "number of household ? ";
                  cin >> x ;
                  
                  Household* h2 = house->get_household(x);
                  if(h2!=nullptr){
                      Immobile* newImmo = new Immobile;
                      newImmo->input();
                      h2->add_device_to_household(newImmo);
                  }
                  
                  
                  break;
              };
                  
              case 'u' :
              {
                  cout << "number of household ?";
                  int u;
                  cin >> u;
                  
                  cout << "which one?";
                  int k;
                  cin >> k;
                  
                  
                  
                  Household* h = house->get_household(u);
                  
                  h->setDevices(h->move_up(h->getDevices(),k));
                  
                  break;
            
                  
                  
              };
                  
//              case 'p' :
//                  int houseNo;
//                  cout << "number of household ?";
//                  cin >> houseNo;
//
//
//
//
//
//                  Householdptr[houseNo]->City = UserHousehold->City;
//
//
//                  print_household(Householdptr[houseNo],houseNo);
//
//
//
//                  break;
                  
                  
              case 'a' :
                  
                  if(house == nullptr){
                      cout << "house is a nullptr, please first choose h to initialise a new house" << endl;
                      
                  }else{
                      house->print_all();
                  }
                      
                      break;
                  
                  
              case 'n' :
              {
                  cout << "number of household? ";
                  int a;
                  cin >> a;
                  
                  Household* h  = new Household;
                  
                  if(house->get_household(a) == nullptr){
                      
                      house->set_household(h,a);
                      h->input_household();
                    
                  }else{
                      cerr << "This household already exists" << endl;
                  }
                  
                  break;
                  
                  };
                  
                  
              case 'c' :
              {
                  
                  int h1,h2;
                  
                  cout << "number of household from which to copy consumers? " ;
                  cin >> h1 ;
                  
                  cout << "number of household to copy to? ";
                  cin >> h2 ;
                  
                                    
                  Household* FromHouse = house->get_household(h1);
                  Household* ToHouse = house->get_household(h2);
                  
                  if(ToHouse == nullptr){
                      
                      cerr << "this house does not exist, please enter a valid one" << endl;
                      break;
                  }
                  
                 // consumer* copied = FromHouse->copy_consumer(FromHouse->getConsumer(), ToHouse->getConsumer());
                  
                  
                  
                  ToHouse->copy_devices(FromHouse, ToHouse);
                
                  
                  float updateCost = ToHouse->AnnualPowerCosts(ToHouse->getPowerPrice());
                  ToHouse->AnnualPowerCosts(updateCost);
                  
                  
                  
                  break;
              };
                  
              case 'w' :
              {
                  
                  
                  string writeFileName;
                  
                  cout << "input file name:";
                  cin>> writeFileName;
                  
                  char seperation;
                  cout << "input seperation character:";
                  cin >> seperation;
                  
                  
                  
                  house->write_to_file(writeFileName, seperation);
                  
                  
                  
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
                  
                  
                  //house->ReadtoFile(house, read, seperation);
                  
                  House* newHouse = new House(0,Address("", "", "", ""));
                  House::ReadtoFile(newHouse, read, seperation);
                  
                  if(house != nullptr)
                      delete house;
                      
                      house = newHouse;
                  
                  break;
                  
              };
              case 's' :{
                 
                  cout << "number of household? " ;
                  int index;
                  cin >> index;
                  
                  Household* h = house->get_household(index);
                  
                  
                  
                  if(h != nullptr){
                      Solar* newSolar = new Solar;
                      
                      newSolar->input();
                      
                      h->add_device_to_household(newSolar);
                      
                      
                  }else{
                      cout << "house doesnt exist" << endl;
                  }
                  
                  break;
                  
              }
                  
              case'm':
              {
                  cout << "number of household? ";
                  int index;
                  cin>>index;
                  
                  Household* h = house->get_household(index);
                  if(h != nullptr){
                      
                      Mobile* newMobile = new Mobile;
                      
                      newMobile->input();
                      
                      h->add_device_to_household(newMobile);
                      
                      
                  }else{
                      cout << "house doesnt exist" << endl;
                  }
                  break;
                  
              }
                  
                  
                  
              default:
                  cout << "sorry wrong choice, please try again" << endl;
                  
          }
          
      }
      
  }
  
  
  
  


