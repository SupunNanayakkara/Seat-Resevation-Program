#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>

using namespace std;

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

vector<flight> flight_vector; //create vector

string flight::getFlight_no()
{
	return flight_no;
}
int flight::getESeatCount()
{
	return e_seat_count;
}

int flight::getBSeatCount()
{
	return b_seat_count;
}

void flight::view_E_seats()
{
	int a=0,b;
	cout<<"Row Number	Available Seats"<<endl;
	while(a<raw_count)
	{
		if(avail_seat[a].seat_class =='E')
		{
			cout<<avail_seat[a].raw_no<<" 		 ";
			b=0;
			while(avail_seat[a].seat_no[b]!='0')
			{
				cout<<avail_seat[a].seat_no[b];
				b++;
			}
			cout<<endl;
		}
		a++;
	}
}

void flight::view_B_seats()
{
	int a=0,b;
	cout<<"Row Number	Available Seats"<<endl;
	while(a<raw_count)
	{
		if(avail_seat[a].seat_class =='B')
		{
			cout<<avail_seat[a].raw_no<<" 		 ";
			b=0;
			while(avail_seat[a].seat_no[b]!='0')
			{
				cout<<avail_seat[a].seat_no[b];
				b++;
			}
			cout<<endl;
		}
		a++;
	}
}

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

//display flight information
void flight::view_flight()
{
	int a=0,b;
	cout<<"Flight Number                              : "<<flight_no<<endl;
	cout<<"Departure Date & Time                      : "<<departure_date_time<<endl;
	cout<<"Deraprture Airport                         : "<<dep_airport<<endl;
	cout<<"Arrival Airport                            : "<<arr_airport<<endl;
	cout<<"Number of Seats Available in Economy Class : "<<e_seat_count<<endl;
	cout<<"Number of Seats Available in Business Class: "<<b_seat_count<<endl;
	cout<<"----------------------------------------------------------------------"<<endl;
	cout<<"|Row Number 	Seat Class 	Available Seats			     |"<<endl;
	
	while(a<raw_count) //traverse all available rows of a flight
	{
		if(avail_seat[a].seat_no[0]!='0') //if at least one seat is available in the row
		{
			cout<<"|";
			cout<<avail_seat[a].raw_no<<"	     	 ";
			cout<<avail_seat[a].seat_class<<"         	 ";
			b=0;
			while(avail_seat[a].seat_no[b]!='0') //traverse all the available seats of a considered row
			{
				cout<<avail_seat[a].seat_no[b];
				b++;
			}
			cout<<"				     |";
			cout<<endl;
		}
		a++;
	}
}

//check availability of the seats according to the user input flight_no, no_of_seats and the seat class
void flight::seatAvailability(int c)
{
	char s_class;
	int no_of_seats;
	cout<<"Enter Class Type(Business-B or Economy-E): ";
	cin>>s_class;
	if(s_class=='E' || s_class=='B')
	{
		cout<<"Enter the number of seats reqired: ";
		cin>>no_of_seats;
		if(s_class=='E')
		{
			if(getESeatCount()>=no_of_seats)
			{
				view_E_seats();
				if(c==4)
				{
					seatBooking(s_class,no_of_seats);
				}
			}
			else
			{
				cout<<"No Sufficient Economy Class Seats in this Flight."<<endl;
				cout<<"Number of Seats Available in Economy Class: "<<getESeatCount()<<endl;
			}
		}
		if(s_class=='B')
		{
			if(getBSeatCount()>=no_of_seats)
			{
				view_B_seats();
				if(c==4)
				{
					seatBooking(s_class,no_of_seats);
				}
			}
			else
			{
				cout<<"No Sufficient Business Class Seats in this Flight."<<endl;
				cout<<"Number of Seats Available in Business Class: "<<getBSeatCount()<<endl;
			}
		}
		
	}
	else
	{
		cout<<"Invalid Input"<<endl;
	}
}

void flight::seatBooking(char s_class,int req_seats)
{
	int a,b,c,row,flag=0,se;
	char seat_no;
	for(int i=0;i<req_seats;i++)
	{
		se=0;
		cout<<"Enter Seat Location (Format: Row_No(1-60) Seat_No(A-F)) :";
		cin>>row>>seat_no;
		a=0;
		while(a<raw_count) //traverse all available rows of a flight to serach the entered row_no
		{
			if(avail_seat[a].raw_no == row && avail_seat[a].seat_class == s_class) //if entered row_no available and entered class is matched
			{
				flag=1;
				b=0;
				while(avail_seat[a].seat_no[b]!='0') //if at least one seat is available in the row
				{
					if(avail_seat[a].seat_no[b]==seat_no) //if entered seat_no is available
					{
						se=1;
						c=b;
						while(avail_seat[a].seat_no[c]!='0') //while traverse all the seats of a row
						{
							avail_seat[a].seat_no[c]=avail_seat[a].seat_no[c+1]; //rearrange the seat_no of the array after seat booking
							c++;
						}	
					}
					b++;	
				}
				if(se==0) //if entered seat_no is not available
				{
					cout<<"Entered Seat is not Available."<<endl;
					i--;
				}	
			}
			a++;	
		}
		if(flag==0) //if entered row_no is not available or entered class is not matched
		{
			cout<<"Entered Seat is not Available."<<endl;
			i--;	
		}	
	}
	cout<<req_seats<<" seat(s) are successfully booked."<<endl<<endl;	
}

int main()
{
	int op,i,c,flag,no_of_seats;
	char s_class;
	string f_no;
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
		
		switch(op)
		{
			case 1:
				cout<<endl;
				cout<<"		 Available Flights Details"<<endl;
				cout<<"		--------------------------"<<endl<<endl;
				for(i=0;i<flight_vector.size();i++)
				{
					flight_vector[i].view_flight();
					cout<<"----------------------------------------------------------------------"<<endl;
					cout<<endl<<endl;
				}
				break;
			case 2:
				cout<<"Enter flight no: ";
				cin>>f_no;
				cout<<endl;
				flag=0;

				for(i=0;i<flight_vector.size();i++)
				{
					if(flight_vector.at(i).getFlight_no()==f_no)
					{
						flag=1;
						flight_vector[i].view_flight();
						cout<<"----------------------------------------------------------------------"<<endl;
					}
				}
				if(flag==0)
				{
					cout<<"Invalid Flight Number."<<endl;
				}
				cout<<endl<<endl;;
				break;
			case 3:
				cout<<"Enter flight no: ";
				cin>>f_no;
				flag=0;
				for(i=0;i<flight_vector.size();i++)
				{
					if(flight_vector.at(i).getFlight_no()==f_no)
					{
						flag=1;
						flight_vector[i].seatAvailability(3);
					}
				}
				if(flag==0)
				{
					cout<<"Invalid Flight Number."<<endl;
				}
				cout<<endl<<endl;
				break;
			case 4:
				cout<<"Enter Flight No: ";
				cin>>f_no;
				cout<<endl;
				flag=0;

				for(i=0;i<flight_vector.size();i++)
				{
					if(flight_vector.at(i).getFlight_no()==f_no)
					{
						flag=1;
						flight_vector[i].seatAvailability(4);
					}
				}
				if(flag==0)
				{
					cout<<"Invalid Flight Number."<<endl;
				}
				cout<<endl<<endl;
				break;
			default:
				cout<<"Invalid Input";
		}	
	}
}
