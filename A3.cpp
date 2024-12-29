
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

/***********************************************************************
Matr.-Nr:                     3177505
Nachname/Surname:             Zainaldin
Vorname/Given name:           Sham Ahmad
Uni-Email:                    sham.zainaldin@stud.uni-due.de
Studiengang/Course of studis: Computer Engineering ISE Software Engineering
***********************************************************************/


int const yearDays = 10; //change to 365
int const quarterhour = 24*4;

float priceperkwh = 0.0003;


enum Use{
    
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
    sunday,
    once,
    daily,
    mo_fr,
    sa_su,
    
    
};

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
            os << "Saturday";
            break;
            
        case monday :
            os << "Monday";
            break;
            
        case tuesday :
            os << "Tuesday";
            break;
            
        case wednesday :
            os << "Wednesday";
            break;
            
        case thursday :
            os << "Thursday";
            break;
            
        case friday :
            os << "Friday";
            break;
            
        case saturday :
            os << "Saturday";
            break;
            
        case sunday :
            os << "Sunday";
            break;
            
        default :
            os << "null";
            break;
    }
    
    return os;
    
    
}


    Use operator++(Use& use){
    
     
        switch(use){
            case monday :
                return tuesday;
            case tuesday :
                return  wednesday;
                
            case wednesday :
                return thursday;
                
            case thursday :
                return friday;
                
            case friday :
                return saturday;
                
            case saturday:
                return sunday;
                
            case sunday:
                return monday;
                
                
            case once:
            case daily:
            case mo_fr:
            case sa_su:
                
            default: return use;
                
     
                
        }
        
        
        
        
}





void input_use(string freq, Use& Use){
    
        cout << freq << endl;

        cout << "Monday (0)" << endl
             << "Tuesday (1)" << endl
             << "Wednesday (2)" << endl
             << "Thursday (3)"<< endl
             << "Friday (4)" << endl
             << "Saturday (5)" << endl
             << "Sunday (6)" << endl
             << "daily (d)" << endl
             << "mo_fr (m)" << endl
             << "once (o)" << endl
             << "sa_su (s)?" << endl;

        char input;
        cin >> input;

        if (input == 'd')
        {
            Use = daily;
        }
        else if (input == 'm')
        {
            Use = mo_fr;
        }
        else if (input == 'o')
        {
            Use = once;
        }
        else if (input == 's')
        {
            Use = sa_su;
        }
        else if (input == '0')
        {
            Use = monday;
        }
        else if (input == '1')
        {
            Use = tuesday;
        }
        else if (input == '2')
        {
            Use = wednesday;
        }
        else if (input == '3')
        {
            Use = thursday;
        }
        else if (input == '4')
        {
            Use = friday;
        }
        else if (input == '5')
        {
            Use = saturday;
        }
        else if (input == '6')
        {
            Use = sunday;
        };
    }
    
    
    
struct year {

    int Year;
    Use firstDay;
    string unit;
    float RowColoumn[yearDays][quarterhour];
    
    
};


inline year zeros(year& y){
    
    for( int i = 0 ; i < yearDays ; i++ ){
        for(int n = 0 ; n < quarterhour ; n++){
            
            y.RowColoumn[i][n] = 0.0;
            
        };
    };
    return y;
}


 
inline int time(int h, int m){

    return h * 60 + m;

    
}



ostream& operator<<(ostream& os, year& y) {
os << "year: " << y.Year  << " (unit : " << y.unit << ")" << endl;

Use day = y.firstDay;

for (int i = 0; i < yearDays; ++i) {
    os << "day " << i << ": " << day << endl;
    
    
    for (int hour = 0; hour < 3; ++hour) {
        
        os << setw(2) << hour << ":00" << " ";
        
        for (int j = 0; j < 4; ++j) {
            os << setw(8) << fixed << setprecision(2) << y.RowColoumn[i][hour*4+j] << " ";
        }
        
    
        
        os << endl;
    }
    os << endl;
    
    day = ++day;
}

return os;
}


year operator+(year& y1,year& y2){

    if((y1.unit == y2.unit) && (y1.Year == y2.Year) && (y1.firstDay == y2.firstDay)) {
    
        year add ;
    
        for(int i = 0; i < yearDays ; i++){
            for(int n = 0 ; n < quarterhour ; n++ ){
            
                add.RowColoumn[i][n] = y1.RowColoumn[i][n] + y2.RowColoumn[i][n];
                
        }
            
    }
        add.unit = y1.unit;
        add.Year = y1.Year;
        add.firstDay = y1.firstDay;
        
        return add;
        
}else{
    cerr << "values dont match" << endl;
    return year() ;
}


}


void add_consumption(year &y, int day, int min1, int min2, float wattage)
{

int quarterStart = min1 / 15;
int quarterEnd = min2 / 15;

int startWithinQuarter = min1 % 15;
int endWithinQuarter = min2 % 15;

y.RowColoumn[day][quarterStart] += (wattage / 60.0) * (15 - startWithinQuarter);

for (int i = quarterStart + 1; i < quarterEnd; ++i)
{
    y.RowColoumn[day][i] += (wattage / 60.0) * 15;
}

y.RowColoumn[day][quarterEnd] += (wattage / 60.0) * endWithinQuarter;
}
    
   
   
   


void add_consumption(year& y, Use use, int min1, int min2, float wattage){

int days = yearDays;
Use current_day = y.firstDay;

switch(use){
        
    case daily:
        
        for(int i = 0 ; i < days ; ++i){
            
            add_consumption(y, i, min1, min2, wattage);
            current_day = ++current_day;
        }
        break;
        
    case mo_fr :
    
        for (int i = 0; i < days; ++i)
        {
            
            if (current_day != saturday && current_day != sunday)
            {
                add_consumption(y, i, min1, min2, wattage);
            }
            current_day = ++current_day;
        }
        break;
        
        
        case sa_su :
        
            for (int i = 0 ; i < days ; ++i){
                if (current_day == saturday || current_day == sunday)
                {
                    add_consumption(y, i, min1, min2, wattage);
                }
                current_day = ++current_day;
            }
        
            break;
        

        default :
        
        for (int i = 0; i < days; ++i)
        {
           
            if (current_day == use)
            {
                add_consumption(y, i, min1, min2, wattage);
            }
            current_day = ++current_day;
        }
        break;
    }
            
            
    }
    
    
    
    

inline float sum(year& y){

    float sum = 0.0;
    
    
    for(int i = 0 ; i<yearDays ; i++){
        for(int n = 0 ; n<quarterhour ; n++){
            
            sum += y.RowColoumn[i][n];
            
            
        }
    }
    
    return sum;
    
}



inline year& ones(year& y){
    
    
    
    for(int i = 0 ; i < yearDays ; i++){
        for(int k  = 0 ; k < quarterhour ; k++){
            
            y.RowColoumn[i][k] = 1.0;
        }
        
    }
    return y;
    
    
}

year operator-(year& y1, year& y2){
    
    if((y1.unit == y2.unit) && (y1.Year == y2.Year) && (y1.firstDay == y2.firstDay)) {
        
        year difference;
        
        for(int i  = 0 ; i < yearDays ; i++){
            for(int k  = 0 ; k < quarterhour ; k++){
                
                difference.RowColoumn[i][k] = y1.RowColoumn[i][k] - y2.RowColoumn[i][k];
                
            }
            
        }
        
        difference.unit = y1.unit;
        difference.Year = y1.Year;
        difference.firstDay = y1.firstDay;
        
        
        return difference;
        
    }else{
        cerr<< "year data does not match !" << endl;
        return year();
    }
    
}


year operator*(float x, year& y){
    
    year multiply;
    
    for(int i = 0 ; i < yearDays ; i++){
        for(int k  = 0; k < quarterhour ; k++ ){
            
            multiply.RowColoumn[i][k] = x * y.RowColoumn[i][k];
            
        }
        
        
    }
    
    multiply.unit = y.unit;
    multiply.Year = y.Year;
    multiply.firstDay = y.firstDay;
    
    
    return multiply;
    
    
}


void set_unit(year& y, string unit){
    
    y.unit = unit;
    
}





int main() {
    
    
    
    
    year actual;
    year total;
    
    actual.firstDay = monday;
    actual.Year = 2024;
    actual.unit = "Watt";
    zeros(actual);
    
    total.firstDay = monday;
    total.Year = 2024;
    total.unit = "Watt";
    zeros(total);
    
    
    


    char UserChoice;
    bool program;
    program = true;
    
    cout << "YEARLY CONSUMPTION QUARTER HOUR" << endl;
    
    while(program){
        
        
        
        cout << "q quit" << endl;
        cout << "a add actual to total (using operator +)" << endl;
        cout << "m subtract actual from total (using operator -)" << endl;
        cout << "s scalar multiplication" << endl;
        cout << "c change unit" << endl;
        cout << "v sum up values" << endl;
//        cout << "c annual consumption and cost (price for one kWh: 30.00 ct/kWh; calling function sum)" << endl;
        cout << "o output actual (using operator <<)" << endl;
        cout << "t output total (using operator <<)" << endl;
        cout << "u add consumption according to frequency of use (call functions add_consumption)" << endl;
        cout << "y set actual to ones (call function ones)" << endl;
        cout << "z set actual to zeros (call function zeros)" << endl;
        cout << ">>" ;
        cin >> UserChoice;
        
        
        switch(UserChoice){
                
            case 'q':
                program = false;
                cout << "program ended" << endl;
                break;
                
            case 'a' :
                
                total = actual+total;
                break;
                
                
            case 'v' :
                    {   float annualActualCons = sum(actual) / 8;
                        float annualTotalCons = sum(total) / 8;
            
//                        float actualCost = annualActualCons;
//                        float totalCost = annualTotalCons * priceperkwh;
//
                        cout << "sum actual = " << fixed << setprecision(2) <<annualActualCons << " " << actual.unit << endl;
                        cout << "sum total = " << fixed << setprecision(2) << annualTotalCons << " " << total.unit << endl;
                
                                break;
                            }
                
            case 'o':
                
                cout << actual << endl;
                
                break;
                
                
            case 't' :
                
                cout << total << endl;
                
                break;
                
            case 'u' :
            {
                int min1, min2;
                float wattage;
                int specific_day;
                char blank = '\0';
                
                int hour1;
                int hour2;
                
                Use use;
                string freq = "how often will it be used ? ";
                
                input_use(freq, use);
                
                if (use == once)
                {
                    cout << "on which day?";
                    cin >> specific_day;
                    
                    cout << "from hour:minute ? ";
                    cin >> hour1 >> blank >> min1;
                    
                    cout << "to hour:minute ? ";
                    cin >> hour2 >> blank >> min2;
                    
                    cout << "how many watt will it have? ";
                    cin >> wattage;
                    
                    min1 = time(hour1, min1);
                    min2 = time(hour2, min2);
                    
                    add_consumption(actual, specific_day, min1, min2, wattage);
                    break;
                }
                else
                {
                    
                    
                    cout << "from hour:minute ? ";
                    cin >> hour1 >> blank >> min1;
                    
                    cout << "to hour:minute ? ";
                    cin >> hour2 >> blank >> min2;
                    
                    cout << "how many watt will it have? ";
                    cin >> wattage;
                    
                    min1 = time(hour1, min1);
                    min2 = time(hour2, min2);
                    
                    
                    
                    add_consumption(actual, use, min1, min2, wattage);
                    
                    break;
                    
                }
                break;
                
            }
            case 'z' :
                
                actual = zeros(actual);
                
                break;
                
                
                
            case 'm' :
                
                total = total - actual;
                
                break;
                
            case 's' :
            {
                cout << "a for actual" << endl << "t for total" << endl;
                
                char choice;
                float scalar;
                
                cin >> choice;
                
                cout << "value of scalar ? " ;
                cin >> scalar;
                
                if(choice == 'a'){
                    
                    actual = scalar*actual;
                    
                }else if(choice == 't'){
                    
                    total = scalar * total;
                    
                }else{
                    cerr << "invalid choice" << endl;
                }
                
        }
                break;
                
            case 'c' :
            {
                cout << "a for actual" << endl << "t for total" << endl;
                
                char in;
                cin >> in;
                
                string unit;
                cout << "what is the new unit ? " ;
                cin >> unit;
                
                if(in == 'a'){
                    
                    actual.unit = unit;
                    
                }else if(in == 't'){
                    
                    total.unit = unit;
                    
                }else{
                    cerr << "Invalid entries" << endl;
                }
                
            }
                
                break;
                
            case 'y' :
                
                actual = ones(actual);
                
                break;
                
            default:
                cerr << "sorry wrong choice" << endl;
                break;
                
        }
        
        
        
        
    }
    

        }
        
