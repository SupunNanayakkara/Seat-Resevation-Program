#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>

using namespace std;


//flight class
class flight
{
	private:
		string flight_no;
		string departure_date_time;
		string dep_airport;
		string arr_airport;
		int e_seat_count;
		int b_seat_count;
		int raw_count;
		seat avail_seat[60];
	public:
		flight() //constructor
		{
			e_seat_count=0;
			b_seat_count=0;
		};
		
		string getFlight_no(); //return flight no
		int getESeatCount(); //return count of a Economy Class Seats in a flight
		int getBSeatCount(); //return count of a Business Class Seats in a flight
		
		void set_flight_info(); //set text file data to the vector
		void view_flight(); //display flight information
		void seatAvailability(int c); //check availability of the seats according to the user input flight_no, no_of_seats and the seat class
		void seatBooking(char s_class,int req_seats); //seats booking according to the user input flight_no, no_of_seats and the seat class
		void view_E_seats(); //view Economy seats with the row_no in a user input flight
		void view_B_seats(); //view Business seats with the row_no in a user input flight
		void insertData(); //modified data written to the flights.dat file
		
		~flight(){};//destructor;
};

//set text file data to the vector
void flight::set_flight_info()
{
	fstream data_file; //for flights.txt file
	data_file.open("flights.txt",ios::in); //open file to read   
	if(!data_file) 
		cout<<"File Not Existing."; 
	else
	{
		cout<<"File Exist";
	}
	data_file.close();  
}

int main()
{
	int op;
	flight obj;
	
	obj.set_flight_info();
	
	cout<<"\t---------------Welcome to Virgin Airlines-----------------"<<endl<<endl<<endl;
	
	while(op!=5)
	{
		cout<<" * Virgin Airlines-Seat Management System *"<<endl<<endl;
		cout<<"\t		Option Menu"<<endl;
		cout<<"\t----------------------------------------"<<endl;
		cout<<"\t| 1. Display Available Flights         |"<<endl;
		cout<<"\t| 2. View Flight                       |"<<endl;
		cout<<"\t| 3. Seat Availablity                  |"<<endl;
		cout<<"\t| 4. Seat Booking                      |"<<endl;
		cout<<"\t| 5. Exit                              |"<<endl;
		cout<<"\t----------------------------------------"<<endl;
		
		cout<<"Enter Your Option: ";
		cin>>op;
		
		
	}
}
