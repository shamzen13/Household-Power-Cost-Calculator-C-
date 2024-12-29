


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





//--------------------CLASS CONSUMER------------------------


class consumer {

     private:
  
    string description;
    float watt, watt_standby, hours;
    Use use;
    consumer* next;
    
    static unsigned int instance;
    
    public :
    
    // get
    
    string getDesc(){
        return description;
    }
    
    float getWatt(){
        return watt;
    }
    
    float getWattStand(){
        return watt_standby;
    }
    
    float getHrs(){
        return hours;
    }
    
    Use getUse(){
        return use;
    }
    
    consumer* getNext(){
        return next;
    }
    
    
    // set
    
    void setDesc(string desc){
        description = desc;
    }
    
    void setWatt(float w){
        watt = w;
    }
    
    void setWattStandby(float ws){
        watt_standby = ws;
    }
    
    void setHrs(float h){
        hours = h;
    }
    
    void setUse(Use u){
        use = u;
    }
    
    void setNext(consumer* c){
        next = c;
    }
    
    
    
    //standard constructor for initializing
    consumer() :
    next(nullptr) {
        
        instance++;
        
    }
    
    //getter for the instance
    static unsigned int get_instance(){
        return instance;
    }
    
    //deconstructor
    ~consumer(){
        
        cout << "The consumer with description : " <<  description << " at address " << this << " deleted" << endl;
        
        
        instance--;
        
    }
    
   
    
    //functions
    
    
    float annual_hours_of_use(){
        
        float hrsPerYear;
        
        switch(use) {
                
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

    
    
    
    float annual_hours_of_standby (){
        
        float annualUseHrsStandby = annual_hours_of_use();
        return 8760 - annualUseHrsStandby;
        
    }

    
    float annual_kWh(){
        
        float annualUseHrs = annual_hours_of_use();
        float annualStandbyHrs = annual_hours_of_standby();
        float totalCons =(annualUseHrs * watt + annualStandbyHrs * watt_standby);
        
        
        return totalCons;
    }

    void print_consumer (int x,float powerprice){
        
        
        
   
        cout << right << setw(ColoumnWidth - 2) << x << ": " << left << setw(ColoumnWidth) << description << endl;
        cout << right << setw(ColoumnWidth) << "(this : " << this << ")" << endl;
        cout << right << setw(ColoumnWidth) << "Power Consumption: " << left <<  watt << " W" << endl;
        cout << right << setw(ColoumnWidth) << "Power Consumption standby: " << left << watt_standby << " W" << endl;
        cout << right << setw(ColoumnWidth) << "annual hours of use: " << left << annual_hours_of_use() << " h" << endl;
        cout << right << setw(ColoumnWidth) << "annual hours of standby: " << left << annual_hours_of_standby() << " h" << endl;
        
        float annualcon = annual_kWh()/1000;
        cout << right << setw(ColoumnWidth) << "annual consumption: "<< left << annualcon  << " kWh" << endl;
        
        
        float anncosts = powerprice * annualcon ;
        cout << right << setw(ColoumnWidth) << "annual costs: " << left << anncosts << " EUR" << endl;
        
        
        
    }
    
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
   
    
    
};


//initialize instance:

unsigned int consumer::instance = 0;


//--------------------CLASS HOUSEHOLD------------------------


class Household {
    
        private :
    
    unsigned int Persons;
    int SqrMeter;
    int Devices;
    bool HotWater;
    Use use;
    consumer* consumers;
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

    int getDevices(){
        return Devices;
    }
    
    bool getHotWater(){
        return HotWater;
    }
    
    Use getUse(){
        return use;
    }
    
    consumer* getConsumer(){
        return consumers;
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
    
    void setDevices(int device){
        Devices = device;
    }
    
    void setHotWater(bool hot){
        HotWater = hot;
    }
    
    void setUse(Use u){
        use = u;
    }
    
    void setConsumer(consumer* c){
        consumers = c;
    }
    
    void setPowerPrice(float price){
        powerPrice = price;
    }
    
    void setPowerSupplier(string supplier){
        powerSupplier = supplier;
    }

    //standard constructor initializing consumer into a null pointer
    Household() :
    consumers(nullptr) {}
    
    //deconstructor & deleting household
    ~Household(){
        
        
    
        consumer* currentConsumer = consumers;
        while (currentConsumer != nullptr) {
            consumer* temp = currentConsumer;
            currentConsumer = currentConsumer->getNext();
            temp->~consumer();
        }
        
        cout << "the household at address " << this << " is deleted" << endl;
        
    }
    
    
    
    //functions
    
    consumer* copy_consumer(consumer* fromh1, consumer* toh2) {
     
      consumer* copyCon = fromh1;
      consumer* head = nullptr;
      
      consumer* end = nullptr;
      
    
        
        
      while (copyCon != nullptr) {
          
          consumer* newCon = new consumer();
          *(newCon) = *copyCon;
          
          if (head == nullptr) {
              head = newCon;
              end = newCon;
          } else {
              end->setNext(newCon);
              end = newCon;
          }
          
          
          copyCon = copyCon->getNext();
          
//          unsigned int No_con = consumer::get_instance();
//          No_con++;
          //here
          //consumer::incrementinstance();
          
      }
        
      
      if (end != nullptr) {
          end->setNext(toh2);
      }
      
        
        
      return head;
    }
    
    
    
    consumer* move_up(consumer* head, int k ){
        
        consumer* currentposition = head;
        consumer* previousposition = nullptr;
        
        int prev = k-1;
        //to go to position, stop before position k
        
        for(int i = 1 ; i < prev ; i++){
            
            previousposition = currentposition;
            currentposition=currentposition->getNext();
            
        }
        //only one item in list
        if(head->getNext() == nullptr && k==1){
            return head;
        };
        
        if(previousposition!=nullptr){
            previousposition->setNext(currentposition);
        };
        
        
        if(k==2){
            
            
            previousposition->setNext( currentposition->getNext());
            currentposition->setNext(previousposition);
            head = currentposition;
            
            
        };
        
        if(k>2 && currentposition->getNext()!=nullptr && currentposition != nullptr){
            
            //draft (u can ignore unless my code isnt clear)
            /*
             current is at k-1 (lets say number 2 as the loop stops one position before k), cons is defined at number 3 (the node we want to move)
             we point the current pointer to the node after 3 ( number 4 ), since 2 will be the node pointing to 4 when they switch
             then change the pointer of number 3 to 2 so they switch places, and redefine current as 3 and return it
             */
            
            consumer* cons = currentposition->getNext();
            currentposition->setNext(currentposition->getNext()->getNext());
            cons->setNext(currentposition);
            currentposition = cons;
        };
        
        
        
        
        //reorganize
        if(previousposition != nullptr){
            previousposition->setNext(currentposition);
            currentposition = head;
        };
        
        
        return currentposition;
        
    }
    
    
    void input_double(string Q,float &no){
      
      
      cout << Q;
      cin >> no;
      

      
    }

    
    void add_consumer_to_household (consumer* c){
      
//        if (c == nullptr) {
//             cerr << "Invalid consumer" << endl;
//             return;
//         }

         c = new consumer;
      c->setNext(this->consumers);
      this->consumers = c;
      
     
        
//
//        if (this->consumers == nullptr) {
//              this->consumers = c;
//          } else {
//              consumer* current = this->consumers;
//              while (current->getNext() != nullptr) {
//                  current = current->getNext();
//              }
//              current->setNext(c);
//          }
        
        string desc;
      cout << "what is the description of the power consumer? " ;
        cin.ignore();
        getline(cin, desc);
        c->setDesc(desc);
        
        
        float watt;
      string first = "how many watt will it have? ";
        input_double(first, watt);
        c->setWatt(watt);
        
        float standby;
      string second = "how many watt standby it will have? ";
      input_double(second, standby);
        c->setWattStandby(standby);
        
        Use usage;
      string freq = "how often will it be used? ";
      c->input_use(freq,usage);
        c->setUse(usage);
        
        
        float hours;
      cout << "how many hours will it be operating then?" ;
        cin >> hours;
        c->setHrs(hours);
      
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
        
    
        consumers = nullptr;
        
  }
    
    
    float AnnualConsumption (){
        float AnnCons;
        if(HotWater) {
            AnnCons = (Persons*ConstHeat)+(SqrMeter*ConsPerSqrMeter)+(Devices*ConsPerDevice);
            return AnnCons;
        }else{
            AnnCons = (Persons*ConsPerPerson)+(SqrMeter*ConsPerSqrMeter)+(Devices*ConsPerDevice);
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
        
        
        consumer* accumalate = consumers;
        float annualtotalccons = 0;
        while (accumalate != nullptr) {
            annualtotalccons += accumalate->annual_kWh()/1000;
            accumalate = accumalate->getNext();
        }
        
       
        cout << " H O U S E H O L D   N O  " << HouseNo << "  P O W E R   C O N S U M P T I O N" << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << right << setw(ColoumnWidth) << "(this: " << left << this << ")" << endl;
        cout << right << setw(ColoumnWidth) << "price for one kWh: " << left << powerPrice*100 << " ct/kWh" << endl;
        cout << right << setw(ColoumnWidth) << "power supplier: " << left << powerSupplier << endl;
        cout << right << setw(ColoumnWidth) << "square metres: " << left << SqrMeter << " qm" << endl;
        cout << right << setw(ColoumnWidth) << "persons: " << left << Persons << endl;
        cout << right << setw(ColoumnWidth) << "water heated using electricity: " << yesno << endl;
        cout << right << setw(ColoumnWidth) << "list of customers " << endl;
        
        
        cout << "------------------------------------------------------------" << endl;
        
        //print the consumers using while loop to iterate through every member of the structure list
        
        consumer* currentCons = consumers;
        int consumerno = 1;
        
        
        while (currentCons != nullptr){
            
            currentCons->print_consumer(consumerno,powerPrice);
            consumerno += 1;
            currentCons = currentCons->getNext();
            
        }
        
        
        
        cout << "------------------------------------------------------------" << endl;
        
        cout << right << setw(ColoumnWidth) << "power consumption square meters: " << left <<(SqrMeter * ConsPerSqrMeter) << " kWh" << endl;
        
        if(HotWater){
            cout << right << setw(ColoumnWidth) << "power consumption on all persons: " << left  << (Persons * ConstHeat) << " kWh" << endl;
        }else{
            cout << right << setw(ColoumnWidth) << "power consumption on all persons: " << left << (Persons * ConsPerPerson) << " kWh" << endl;
        };
        
        
        
        cout << right << setw(ColoumnWidth) << "total annual power consumption: " << left << Consumption + annualtotalccons << " kWh" << endl;
        
        cout << right << setw(ColoumnWidth) << "total annual power costs: " << left <<Cost + annualtotalccons * powerPrice << " EUR" << endl;

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
        
      cout << "House at address : " << this << " deleted" << endl;
        
//       address.~Address();

        
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
        
        unsigned int No_consumers = consumer::get_instance() - 1;
        
        
    
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
          file << "A5" << seperation << number_of_households << seperation << address.getStreet() << seperation << address.getNo()  << seperation << address.getZip() << seperation << address.getCity() << endl;

          
    //DIFFERENT HOUSEHOLDS
          
          for(int i  = 0 ; i < number_of_households ; i++){
              Household* h = household[i];
              
              if(h != nullptr){
                  
                  
                  
          file << "household" << seperation << i << seperation << (h->getHotWater() ? "true" : "false") << seperation << h->getPersons() << seperation << h->getSqrMeter() << seperation << h->getPowerPrice() << seperation << h->getPowerSupplier() << endl;
                  
    //CONSUMERS
                  
              int consumerCount = 1;
              consumer* currentConsumer = h->getConsumer();
                  while(currentConsumer != nullptr){
                      
                      
                      
                      file << "consumer" << seperation << currentConsumer->getDesc() << seperation
                      << currentConsumer->getHrs() << seperation << UseToString(currentConsumer->getUse()) << seperation
                      << currentConsumer->getWatt() << seperation << currentConsumer->getWattStand() << endl;
                      
                      currentConsumer = currentConsumer->getNext();
                      consumerCount++;
                      
                  } }}
          
              }else {
                  cerr << "Unable to open file" << endl; }
              
              file.close();
              cout << "output file \"" << fileName << "\" closed" << endl;
          
          }
    
    
    
    void ReadtoFile(House* newHouse, string fileName, char separator) {
      
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
          
          
          if (task_ID != "A5") {
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
          
          
          
         //cout << numhouse << endl;
          
//          if (numhouse > number_of_households) {
//              cout << "file contains up to " << numhouse << ", but here only " << number_of_households << " are supported" << endl;
//              file.close();
//              cout << "input file " << fileName << " closed" << endl;
//
//              return;
//          }
          
          
          //address line
          
          
          getline(file,street,separator);
          
          
          
          //cout << street << endl;
          
          
          getline(file, address_houseno, separator);
          
          
          //cout << address_houseno << endl;
          
          
          getline(file,zip,separator);
          
          
          //cout << zip << endl;
          
          
          getline(file, city);

          
//          cout << city << endl;
          
         
          
//          £House* newHouse  = new House(numhouse,add);
          
          newHouse->address.inputAddress(street, address_houseno, zip, city);
          
          
          
    //city
//          string city;
//          getline(file, city);
//          City = city;

         //cout << city << endl;
         
    //price
    //        string priceString;
    //        getline(file, priceString);
    //        price = stof(priceString);

        
          
          string House;
          
          getline(file,House,separator);
          
    //READING HOUSEHOLDS&CONSUMERS
          if(House == "household"){
              
              while(!file.eof()){
                  
                  
                  
//                   cout << House  << endl;
                  
                  int houseIndex = 0;
                  string index;
                  getline(file,index,separator);
                  houseIndex = stoi(index);
                  
//                   cout << houseIndex << endl;
                  
                  household[houseIndex] = new Household;
                  Household* h1 = household[houseIndex];
                  
                  // no more city
                  
                  //                      string city2;
                  //                      getline(file, city2, separator);
                  //                    add.setCity(city2);
                  //                      city2 = City;
                  
                  //cout << city2 << endl;
                  
                  string hot;
                  getline(file, hot, separator);
                  if (hot == "true") {
                      h1->setHotWater(true);
                  } else {
                      h1->setHotWater(false) ;
                  }
                  
                 // cout << hot << endl;
                  
                  
                  
                  
                  string personString;
                  
                  getline(file,personString,separator);
                  
                  int personInt = stoi(personString);
                  h1->setPersons(personInt);
                  
                 // cout << personString << endl;
                  
                  
                  
                  string SqrString;
                  
                  getline(file,SqrString,separator);
                  
                  
                  int SqrInt = stoi(SqrString);
                  h1->setSqrMeter(SqrInt);
                  
                 // cout << SqrInt << endl;
                  
                  
                  
                  string powerString;
                  getline(file,powerString,separator);
                  float PowerFloat = stof(powerString);
                  h1->setPowerPrice(PowerFloat);
                  
                  
                  
                  string supplier;
                  getline(file, supplier);
                  h1->setPowerSupplier(supplier);
                  
                  //cout << supplier << endl;
                  
                  string consumer_ID;
                  
                  household[houseIndex] = h1;
                  
                  while (getline(file, consumer_ID,separator) && (consumer_ID == "consumer")) {
                      
                      //cout << consumer_ID << endl;
                      
                      
                      consumer* newCon = new consumer;
                      
                      string desc, hrs, useString, wattString, standbyString;
                      
                      getline(file, desc, separator);
                      newCon->setDesc(desc);
                      
                      
                      //cout << newCon->description << endl;
                      
                      getline(file, hrs, separator);
                      newCon->setHrs(stof(hrs));
                      
                      //cout << newCon->hours<< endl;
                      
                      getline(file, useString, separator);
                      newCon->setUse(convertToUse(useString));
                      
                      // cout << newCon->use << endl;
                      
                      
                      getline(file, wattString, separator);
                      newCon->setWatt(stof(wattString));
                      
                      //cout << newCon->watt << endl;
                      
                      getline(file, standbyString);
                      newCon->setWattStandby(stof(standbyString));
                      
                      //cout << newCon->watt_standby << endl;
                      
                      
                      
                      newCon->setNext(h1->getConsumer()) ;
                      h1->setConsumer(newCon);
                      
                      
                      
            }
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
      
      
      
      consumer* NewConsumer = new consumer;
      
      House* house = nullptr;
      
      //float PricePerKwH;
      
      
      
      cout << "CALCULATION OF AVERAGE POWER COSTS FOR A HOUSE - CLASS VERSION \n" << endl;
          
      
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
//                      house = nullptr;
                  
                  
                  break;
              }
                  
              case 'i' :
              {
                  int x;
                  cout << "number of household ? ";
                  cin >> x ;
                  
                  Household* h2 = house->get_household(x);
                  
                  h2->add_consumer_to_household(NewConsumer);
                  
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
                  
                  h->setConsumer(h->move_up(h->getConsumer(), k));
                  
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
                  
                  consumer* copied = FromHouse->copy_consumer(FromHouse->getConsumer(), ToHouse->getConsumer());
                  
                  ToHouse->setConsumer(copied);
                
                  
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
                  
                  
                  house->ReadtoFile(house, read, seperation);
                  
                  
                  break;
                  
              };
                  
              default:
                  cout << "sorry wrong choice, please try again" << endl;
                  
          }
          
      }
      
  }
  
  
  
  

