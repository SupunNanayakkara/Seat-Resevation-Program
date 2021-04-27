#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>

using namespace std;

vector<flight> flight_vector; //create vector

//seat structure with row_no, seat_class and seats
struct seat
{
	int raw_no;
	char seat_class;
	char seat_no[6]={'0','0','0','0','0','0'};	
};

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
		int i,j,flag,count,row,esc=0,bsc=0;
		string data,row1,row2,srow;
		char seats[12];
		while(data_file.eof()==0)
		{
			flight obj;
			flag = 0;
			getline(data_file,data);
			obj.flight_no = data;
			getline(data_file,data);
			obj.departure_date_time = data;
			getline(data_file,data);
			obj.dep_airport = data;
			getline(data_file,data);
			obj.arr_airport = data;
			i=0;
			esc=0;bsc=0;
			while(flag!=1)
			{
				data_file.getline(seats,12); //get row details to char array
				if(seats[0]=='\0') //if 1st element of a seats array(line of the file) is null, then it is empty line
				{
					flag = 1;	
				}
				else
				{
					count = 0;
					j=0;
					while(count!=3)
					{
						if(count==0)
						{
							row1 = seats[0]; 
							row2 = seats[1];
							j++;
							if(seats[j]!=' ')
							{
								srow = row1 + row2;
								j=j+2;
							}
							else
							{
								srow = row1;
								j=j+1;
							}
							stringstream(srow)>>row; //convert string row_no to integer row_no
							obj.avail_seat[i].raw_no = row; //row_no
							count = 1; //identify row_no 	
						}
						else if(count==1)
						{
							obj.avail_seat[i].seat_class = seats[j]; //seat_class
							j=j+2;
							count = 2; //identify seats class
						}
						else
						{
							int k=0;
							while(seats[j]!='\0')
							{
								obj.avail_seat[i].seat_no[k] = seats[j]; //seats
								j++;
								k++;
							}
							if(obj.avail_seat[i].seat_class=='E')
							{
								esc = esc + k; //total no of economy class seats in a flight
								obj.e_seat_count = esc;
							}
							else
							{
								bsc = bsc + k; //total no of business class seats in a flight
								obj.b_seat_count = bsc;								
							}
							
							count = 3; //complete traversing (identify the availablle seats of the row) 
							i++;
						}						
					}
				}
				obj.raw_count = i;					
			}
			flight_vector.push_back(obj); //enter the object to the vector	
		}
	}
	data_file.close();  
}

int main()
{
	int op;
	
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
