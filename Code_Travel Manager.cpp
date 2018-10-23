/*
DSA Project-Travel Manager
3rd Semester
Made By:
	Areeb Tariq (00907)
	Arslan Ahmed (04160)
	Hafiz Usman Mahmood (01317)
		BEE-4C
Submitted To,
	Sir Anees-ur-Rahman
4th January, 2013
*/
#include<iostream>
#include<stdio.h>
#include<string>        //string library
#include<vector>        //vector library
#include<ctime>         //time library to calcultate running time of code
#include <iomanip>			//library to set width and allignment of colums
#define INF INT_MAX     //define infinity value, it will be used to initialize distances of nodes at start of algo
using namespace std;

//forward declaration of City class
class City;            
 
//An object of this class represents a flight from one city to another
class Flight
{
private:
	City *orgCity;        //the originating vertex
	City *dstCity;        //the destination vertex
	unsigned fare;        //fare of the edge
	unsigned distance;    //distance between two cities
	unsigned depTime;     //deprture time of the flight
	unsigned duration;    //duration of the flight

	//Flight Class Constructor with arguments
public: Flight(City *origin, City *destination, unsigned cost,unsigned dist, unsigned dep, unsigned dur)

		{
			orgCity = origin;		//Origin of flight
			dstCity = destination;	//Destination of Flight
			fare = cost;			//Fare of flight
			distance=dist;			//Total arial Distance of flight 
			depTime=dep;			//Departure Time of Flight
			duration=dur;			//Total Duration of Flight including the rest at transits
		}

		//Public Functions of Flight Class to access its Private members
		City* getDstCity()
		{
			return dstCity;
		}

		City* getOrgCity()
		{
			return orgCity;
		}

		unsigned getFareFlight()
		{
			return fare;
		}

		unsigned getDurFlight()
		{
			return duration;
		}
		unsigned getDistance()
		{
			return distance;
		}

		unsigned getDepTime()
		{
			return depTime;
		}
};

//Visit Status of a city
enum Status
{
	NOT_VISITED, VISITED
};

//Different cities of the world are objects of class City
class City
{
private:
	string cityName;				//City name
	unsigned contact;				//Contact number of respective airport for reservation/information
	enum Status visitStatus;		//used in dfs to mark the node visited
	unsigned distance;				//Private variable Distance of City which is updated by Dijkstra
	unsigned fare;					//Private variable Fare of City which is updated by Dijkstra
	unsigned duration;				//Private variable Duration of City which is updated by Dijkstra
	string parentCity;				//Flight arrives from Parent City
	unsigned arrTime;				//Private variable Arrival_Time of City which is updated by Dijkstra 
public:
	vector<Flight> adjFlightList;   //list of outgoing flights from this city

	//Constructor of Class City-Name and Airport Phone# are passed as parameters
	City(string name,unsigned no)
	{
		contact=no;
		cityName = name;
		visitStatus = NOT_VISITED;
	}
	//Destructor of City Class to free up memory of adjacent cities
	~City()
	{
		adjFlightList.clear();
	}

	//Public Functions of class City to access the private variables
	enum Status getStatus()
	{
		return visitStatus;
	}
	unsigned getContact()
	{
		return contact;
	}
	void setVisitStatus(enum Status status)
	{
		visitStatus = status;
	}
	void setFareCity(unsigned far)
	{
		fare=far;
	}
	unsigned getFareCity()
	{
		return fare;
	}
	unsigned getDurCity()
	{
		return duration;
	}
	void setDurCity(unsigned durat)
	{
		duration=durat;
	}
	void setDistance(unsigned dist)
	{
		distance=dist;
	}
	unsigned getDistance()
	{
		return distance;
	}
	string getCityName()
	{
		return cityName;
	}
	void setparentCity( string p)
	{
		parentCity=p;
	}
	string getparentCity()
	{
		return parentCity;
	}
	void setArrTime(unsigned depTime)
	{
		arrTime=depTime;
	}
	unsigned getArrTime()
	{
		return arrTime;
	}

	//add Direct Flights from a city
	void addAdjFlight(City *adjacent, unsigned fare,unsigned dist, unsigned dep_time, unsigned dur)
	{
		//create an edge with 'this' as the originating node and adjacent as the destination node
		Flight newFlight(this, adjacent, fare,dist,dep_time,dur);
		adjFlightList.push_back(newFlight);
	}

	//Returns a vector of Direct Flights from a city
	vector<Flight> getAdjFlights()
	{
		return adjFlightList;
	}
};

//Helper function to reduce no. of Lines Of Code in Dijsktra() method
void helper(string source, string destination, vector<City*>cities, int sortingCriteria)
{
	size_t i;			//used in for loops
	City* tempCity=new City("Temp",123);        //Create temperory City

	//Set its distance, fare, duration,arrival time and parent city to NULL
	tempCity->setDistance(INF);             
	tempCity->setFareCity(INF);				
	tempCity->setDurCity(INF);
	tempCity->setArrTime(INF);
	tempCity->setparentCity("NULL");

	if(source==destination)			//Base Case
		return;						//Recursive functions ends when source passed as parameter equilizes to destination

	for (i=0; i<cities.size();i++)           
	{
		if(cities[i]->getStatus()== NOT_VISITED)        //Check for 1st non-visited city in the graph
			break;
	}
	if(i==cities.size())        //Base Case
		return ;				//When all cities are visited, end the recursive function
	else
	{
		//make the source city as visited
		for (size_t i=0; i<cities.size();i++)            // Iterate through all of the cities
		{
			if( cities[i]->getCityName()==source)        //Check for source city
			{ 
				cities[i]->setVisitStatus(VISITED);        //Change the status of source city to visited

			}

			// Goes into source city adjacency list and update their distance, fare,parent city,arrival time and duration time
			for (size_t j=0; j<cities[i]->getAdjFlights().size(); j++)        //iterate through adjancy list of source city
			{
				//check criteria set by user for sorting by duration or by fare
				if(sortingCriteria==1)			//if criteria is by duration
				{
					if (cities[i]->adjFlightList[j].getDstCity()->getDurCity()  > cities[i]->getDurCity()+ cities[i]->adjFlightList[j].getDurFlight() && cities[i]->adjFlightList[j].getDstCity()->getStatus()==NOT_VISITED)        //if Duration in adjacent city is greater than sum of Duration in source city and flight distance

					{
						cities[i]->adjFlightList[j].getDstCity()->setDistance(cities[i]->getDistance()+cities[i]->adjFlightList[j].getDistance());			//set distance of adjacent city equal to sum of distance of source city and flight
						cities[i]->adjFlightList[j].getDstCity()->setparentCity(cities[i]->getCityName());													//set the source city as parent of the adjacent city
						cities[i]->adjFlightList[j].getDstCity()->setFareCity(cities[i]->getFareCity()+cities[i]->adjFlightList[j].getFareFlight());		//set fare of adjacent city equal to sum of fare of source city and flight
						cities[i]->adjFlightList[j].getDstCity()->setDurCity(cities[i]->getDurCity()+cities[i]->adjFlightList[j].getDurFlight()+45);		//set duration of adjacent city equal to sum of duraion of source city and flight including 45 min break time
						cities[i]->adjFlightList[j].getDstCity()->setArrTime(cities[i]->getArrTime()+cities[i]->adjFlightList[j].getDurFlight()+45);		//set arrival time of adjacent city equal to sum of arrival time of source city and duration of flight including 45 min break time
					}  
				}
				if(sortingCriteria==2)			//if criteria is by fare
				{
					if (cities[i]->adjFlightList[j].getDstCity()->getFareCity()  > cities[i]->getFareCity()+ cities[i]->adjFlightList[j].getFareFlight() && cities[i]->adjFlightList[j].getDstCity()->getStatus()==NOT_VISITED)        //if Fare in adjacent city is greater than sum of Fare in source city and flight distance

					{
						cities[i]->adjFlightList[j].getDstCity()->setDistance(cities[i]->getDistance()+cities[i]->adjFlightList[j].getDistance());			//set distance of adjacent city equal to sum of distance of source city and flight
						cities[i]->adjFlightList[j].getDstCity()->setparentCity(cities[i]->getCityName());													//set the source city as parent of the adjacent city
						cities[i]->adjFlightList[j].getDstCity()->setFareCity(cities[i]->getFareCity()+cities[i]->adjFlightList[j].getFareFlight());		//set fare of adjacent city equal to sum of fare of source city and flight
						cities[i]->adjFlightList[j].getDstCity()->setDurCity(cities[i]->getDurCity()+cities[i]->adjFlightList[j].getDurFlight()+45);		//set duration of adjacent city equal to sum of duraion of source city and flight including 45 min break time
						cities[i]->adjFlightList[j].getDstCity()->setArrTime(cities[i]->getArrTime()+cities[i]->adjFlightList[j].getDurFlight()+45);		//set arrival time of adjacent city equal to sum of arrival time of source city and duration of flight including 45 min break time
					}
				}
			}



			// Select next non-visited city with least Duration or Fare
			for ( size_t j=0; j< cities[i]->getAdjFlights().size();j++)        //iterate through all the adjacent flights from the source
			{

				if(sortingCriteria==2)		//if user wants to sort by Duration
				{
					if(tempCity->getDurCity() > cities[i]->adjFlightList[j].getDstCity()->getDurCity() &&cities[i]->adjFlightList[j].getDstCity()->getStatus()==NOT_VISITED)       
					{
						tempCity=cities[i]->adjFlightList[j].getDstCity();                                        //assign that city as temporary city whose Duration is least and is non-visited yet
					}
				}
				if(sortingCriteria==1)		//if user wants to sort by Fare
				{
					if(tempCity->getFareCity() > cities[i]->adjFlightList[j].getDstCity()->getFareCity() &&cities[i]->adjFlightList[j].getDstCity()->getStatus()==NOT_VISITED)       
					{
						tempCity=cities[i]->adjFlightList[j].getDstCity();                                        //assign that city as temporary city whose Fare is least and is non-visited yet
					}
				}

			}
		}
		helper(tempCity->getCityName(),destination,cities,sortingCriteria);            //recursive call, temp city obtained is sent as a source again in this function
	}

}

//Gives the path of flight from source to destination
void pathfunction(string destination,string source,  vector<City*> cityList, vector<string>& route)
{
	if (destination==source)		//Base Case
	{			
		return ;					//if destination equilizes the source, end the recursive function
	}
	else
	{
		for(size_t i=0; i<cityList.size();i++ )
		{
			if(destination==cityList[i]->getCityName())		//find the destination form cityList
			{
				destination=cityList[i]->getparentCity();		//assigns its parent value to it
				route.push_back(destination);					//Add it to Route vector
				break;
			}
		}
	}
	pathfunction(destination,source,cityList,route);	//Recursive call, with parent of destination passed as destination, and updated route vector
}

//Class having all the cities
class Graph
{
private:
	vector<City*> cityList;         //list of all cities
public:
	vector<City*> getCityList()
	{
		return cityList;
	}

	bool foundCycle;                //true if a cycle is found, false otherwise

	//iterate through all the cities and set them as non-visited cities
	void setNonVisit()
	{
		for(size_t i = 0; i < cityList.size() && !foundCycle ; i++)
		{
			cityList[i]->setVisitStatus(NOT_VISITED);
		}
	}
	void addNewCity(City *newCity)        //add a new city into graph
	{
		cityList.push_back(newCity);
	}

	//find Directflights from a particular city
	void findFlightsOfCity(string cityName)
	{
		unsigned a;			//to store the index of that city
		for(size_t i = 0 ; i < cityList.size() ; i++)
		{
			if(cityList[i]->getCityName() == cityName)		//if city found
			{
				a=i;										//store its index in variable a and break from the loop
				break;
			}
		}

		//iterate through all the adjacent flights from that city and print their names
		for(unsigned x=0; x<cityList[a]->adjFlightList.size();x++)
		{
			cout<<setw(50)<<right<<x+1<<". "<<cityList[a]->adjFlightList[x].getDstCity()->getCityName()<<endl;
		}
	}

	//display all Flight afrom all sources at start of program to the the user
	void disAllFlights()
	{
		cout<<setw(40)<<"Source"<<setw(55)<<"Destination\n\n\n";
		for(size_t i=0;i<cityList.size();i++)
		{
			cout << setfill(' ');
			for(unsigned x=0; x<cityList[i]->adjFlightList.size();x++)
			{
				cout<<setw(30)<<i+1<<". "<<setw(20)<<left<<cityList[i]->getCityName()<<setw(30)<<right<<x+1<<". "<<cityList[i]->adjFlightList[x].getDstCity()->getCityName()<<endl;
			}
			cout<<endl;
		}
	}

	//dijkstra algorithm to find the shortest flight between two cities
	void Dijkstra(string source, string destination)
	{ 
		clock_t c1,c2;				//clock to measure the running time of dijkstra algorithm

		// 1: Sort by Fare, 2: Sort by Duration
		int sortingCriteria;
		cout<<"\nSelect your sorting criteria:\n1: Sort by Flight Duration\n2: Sort by Flight Fare\n";
		cin>>sortingCriteria;

		c1=clock();                //take starting time from PC
		vector<string> route;		//vector of cities	through which the flight passes
		size_t b;					//to store the index of source

		//iterate through complete city list
		for (size_t i=0; i<cityList.size();i++)
		{

			if( cityList[i]->getCityName()==source)    //check for the source city

			{ 
				cityList[i]->setDistance(0);            //set distance of source city to 0
				cityList[i]->setFareCity(0);			//set Fare of source city to 0
				cityList[i]->setDurCity(0);				//set Duration of source city to 0
				cityList[i]->setparentCity("NULL");		//set Parent of source city to NULL
				cityList[i]->setArrTime(depTime());		//set Departure Time of source city randomly
				cityList[i]->setVisitStatus(VISITED);   //set status of source city as visited
				b=i;									//store index of source city in variable b
			}
			else
			{
				cityList[i]->setDistance(INF);				//set distance of all other cities to infinite
				cityList[i]->setFareCity(INF);				//set fare of all other cities to infinite
				cityList[i]->setDurCity(INF);				//set duration time of all other cities to infinite
				cityList[i]->setparentCity("NULL");			//set parent of all other cities to NULL
				cityList[i]->setArrTime(INF);				//set arrival time of all other cities to infinite
				cityList[i]->setVisitStatus(NOT_VISITED);   //mark them as non-visited
			}
		}
		helper(source,destination,cityList,sortingCriteria);            //helper function called

		//Print all the needed data in tabular form
		for ( size_t l=0; l<cityList.size(); l++)
		{
			if (destination == cityList[l]->getCityName())
			{
				if(cityList[l]->getArrTime() > 2400)		//if arrival times is greater than 2400 hrs, subtract 2400 to get user-friendly display
					cityList[l]->setArrTime(cityList[l]->getArrTime()-2400);
				cout<<"\n\n\n"<<setw(20)<<left<<"Origin"<<setw(20)<<left<<"Destination"<<setw(20)<<left<<"\Departure(24-hr)"<<setw(20)<<left<<"Arrival(24-hr)"<<setw(20)<<left<<"Duration(min)"<<setw(20)<<left<<"Distance(km)"<<setw(20)<<left<<"Fare(PAK RUPEE)"<<setw(20)<<left<<"Weather"<<setw(20)<<left<<"Contact#"<<endl;
				cout<<"\n\n"<<setw(20)<<left<<source<<setw(20)<<left<<cityList[l]->getCityName()<<setw(20)<<left<<cityList[b]->getArrTime()<<setw(20)<<left<<cityList[l]->getArrTime()-45<<setw(20)<<left<<cityList[l]->getDurCity()-45<<setw(20)<<left<<cityList[l]->getDistance()<<setw(20)<<left<<cityList[l]->getFareCity()<<setw(20)<<left<<weather()<<setw(20)<<left<<cityList[b]->getContact()<<endl;
				break;
			}
		}

		//Print the route of the flight
		cout<<setw(20)<<right<<"\n\n\n\nThe route of this flight is:\nNote: Flight has a stay of 45 min at each airport\n\n\n\n";
		pathfunction( destination,  source, cityList, route);

		while(route.size()!=0)
		{
			cout<<setw(20)<<route.back()<<" \t-->";		//print the back element of route vector i.e source
			route.pop_back();							//pop it out so that next city is printed untill we reach destination
		}
		cout<<setw(20)<<right<<destination;				//print destination city name

		c2=clock();										//stop taking time from clock
		float diff ((float)c2-(float)c1);
		//print the running time of dijkstra function including the cout statements
		cout<<"\n\n\n\t\t\t\t\t"<<setw(30)<<left<<"Running Time of Dijkstra: "<<diff/(float)1000<<" seconds\n\n\n";


	}

	//generate random weather of 10 kinds for different flights
	string weather()
	{
		srand(time(NULL));
		unsigned a=rand()%10;
		switch(a)
		{
		case 0:
			return "Snow";
		case 1:
			return "Dense Clouds";
		case 2:
			return "Sunny";
		case 3:
			return "Thunderstorms";
		case 4:
			return "Foggy";
		case 5:
			return "Hot";
		case 6:
			return "Partly Cloudy";
		case 7:
			return "Rain";
		case 8:
			return "Windy";
		case 9:
			return "Misty";
		}
	}

	//Generate random departure time for a flight
	int depTime()
	{
		srand(time(NULL));
		unsigned a;
		do
		{
			a=rand()%2400;
		}while(a%15!=0 || a%100>=60);		//departure time must be multiple of 15 and its last two digits(minutes) must be less than 60
		return a;
	}
};

void main()
{
	Graph g;											//create an object of graph class
	int destTry=3,sourceTry=3;							//user has three tries each to enter his/her source and destination city
	int cityCount=0;									//Count of Cities in the world
	int flightCount=0;									//Count of total flights between different cities
	string sourceCity, destCity;						//Variables for Source and Destination Cities, user must input them
	bool sourcePresent=false, destPresent=false;        //Set Source and Destination City presence to false, so that it may re-ask to enter the city if wrongly entered

	cout<<"\t\t\t\t************ WELCOME TO THE FLIGHT MANAGER **************\n\n";
	cout<<"\n\n\t\t*****Please Select Your Source City and Destination City from the following available flights*****\n\n\n";

	//Create cities with their names, and airport phone# as parameters
	City* c1= new City("Christchurch",1259742);       
	City* c2= new City("Wellington", 4136925);       
	City* c3= new City ("Sydney", 1258920);           
	City* c4= new City ("Melbourne", 134657);       
	City* c5= new City ("Canberra", 5987419);       
	City* c6= new City ("Tokyo", 981875);           
	City* c7= new City ("Seoul", 4693215);           
	City* c8= new City ("Shanghai", 741230);       
	City* c9= new City ("Beijing", 4571358);           
	City* c10= new City ("Moscow", 1986572);           
	City* c11= new City ("Karachi", 6798525);
	City* c12= new City ("Riyadh", 6307590);
	City* c13= new City ("Jakarta", 5316412);
	City* c14= new City ("KualaLumpur", 4598035);
	City* c15= new City ("Johannesburg", 3168952);
	City* c16= new City ("Dubai", 3461952);
	City* c17= new City ("Cairo", 9586374);
	City* c18= new City ("Sarajevo", 1326598);
	City* c19= new City ("Rome", 9846154);
	City* c20= new City ("Algiers", 7984511);
	City* c21= new City ("Lisbon", 4698752);
	City* c22= new City ("London", 8951231);
	City* c23= new City ("Berlin", 5487923);
	City* c24= new City ("Paris", 6541398);
	City* c25= new City ("Rio", 8527419);
	City* c26= new City ("Montreal", 9517535);
	City* c27= new City ("Islamabad", 9514697);
	City* c28= new City ("Istanbul", 3469284);
	City* c29= new City ("Casablanca", 1239842);
	City* c30= new City ("Damascus", 8569741);
	City* c31= new City ("Ramallah", 6498713);
	City* c32= new City ("Colombo",1598514);

	//add the cities into graph and increase the city Count
	g.addNewCity(c1); cityCount++;  
	g.addNewCity(c2); cityCount++;       
	g.addNewCity(c3); cityCount++;
	g.addNewCity(c4); cityCount++;       
	g.addNewCity(c5); cityCount++;       
	g.addNewCity(c6); cityCount++;
	g.addNewCity(c7); cityCount++;       
	g.addNewCity(c8); cityCount++;       
	g.addNewCity(c9); cityCount++;   
	g.addNewCity(c10); cityCount++;       
	g.addNewCity(c11); cityCount++;       
	g.addNewCity(c12); cityCount++;
	g.addNewCity(c13); cityCount++;       
	g.addNewCity(c14); cityCount++;       
	g.addNewCity(c15); cityCount++;
	g.addNewCity(c16); cityCount++;       
	g.addNewCity(c17); cityCount++;       
	g.addNewCity(c18); cityCount++;
	g.addNewCity(c19); cityCount++;       
	g.addNewCity(c20); cityCount++;       
	g.addNewCity(c21); cityCount++;
	g.addNewCity(c22); cityCount++;       
	g.addNewCity(c23); cityCount++;       
	g.addNewCity(c24); cityCount++;
	g.addNewCity(c25); cityCount++;       
	g.addNewCity(c26); cityCount++;       
	g.addNewCity(c27); cityCount++;
	g.addNewCity(c28); cityCount++;       
	g.addNewCity(c29); cityCount++;       
	g.addNewCity(c30); cityCount++;
	g.addNewCity(c31); cityCount++;       
	g.addNewCity(c32); cityCount++;

	//add flights from cities with adjacent city, fare, distance and duration time as parameters- and increase the flight count
	c11->addAdjFlight(c27,954,1044.7,815,30); flightCount++;
	c27->addAdjFlight(c11,954,1044.7,1015,30); flightCount++;
	c1->addAdjFlight(c3,954,2138.5,1300,200); flightCount++;
	c3->addAdjFlight(c1,249,2138.5,1600,200); flightCount++;
	c1->addAdjFlight(c2,495,304.6,2100,300); flightCount++;
	c2->addAdjFlight(c1,2489,304.6,100,300); flightCount++;
	c2->addAdjFlight(c3,2156,2225.9,600,200); flightCount++;
	c3->addAdjFlight(c2,123,2225.9,900,200); flightCount++;
	c1->addAdjFlight(c4,1566,2406.49,500,100); flightCount++;
	c5->addAdjFlight(c4,1456,464.39,600,130); flightCount++;
	c3->addAdjFlight(c5,1000,248.99,1100,200); flightCount++;
	c5->addAdjFlight(c3,2516,248.99,1400,200); flightCount++;
	c6->addAdjFlight(c3,251,7826.43,630,120); flightCount++;
	c14->addAdjFlight(c4,279,6367.67,500,200); flightCount++;
	c5->addAdjFlight(c14,2000,6527.3,600,150); flightCount++;
	c4->addAdjFlight(c14,2157,6367.67,1000,100); flightCount++;
	c14->addAdjFlight(c6,2787,5321.67,900,400); flightCount++;
	c4->addAdjFlight(c5,1561,464.39,1500,330); flightCount++;
	c6->addAdjFlight(c14,2541,5321.67,1230,215); flightCount++;
	c13->addAdjFlight(c6,1235,7826.43,1230,200); flightCount++;
	c6->addAdjFlight(c13,1200,7826.43,1130,100); flightCount++;
	c13->addAdjFlight(c14,200,6614.84,800,400); flightCount++;
	c14->addAdjFlight(c13,795,6614.84,1100,130); flightCount++;
	c6->addAdjFlight(c7,799,7826.43,1730,115); flightCount++;
	c7->addAdjFlight(c6,499,7826.43,115,30); flightCount++;
	c6->addAdjFlight(c27,299,5972.8,330,200); flightCount++;
	c27->addAdjFlight(c6,399,5972.8,415,30); flightCount++;
	c6->addAdjFlight(c8,2513,1758.22,200,100); flightCount++;
	c8->addAdjFlight(c6,234,1758.22,300,200); flightCount++;
	c7->addAdjFlight(c8,2564,7881.9,330,200); flightCount++;
	c7->addAdjFlight(c10,435,12794.25,100,600); flightCount++;
	c10->addAdjFlight(c7,436,12794.25,1100,30); flightCount++;
	c8->addAdjFlight(c9,346,1067.31,1500,230); flightCount++;
	c9->addAdjFlight(c8,3456,1067.31,2000,100); flightCount++;
	c9->addAdjFlight(c10,457,9024.51,2200,145); flightCount++;
	c10->addAdjFlight(c9,345,9024.51,400,200); flightCount++;
	c10->addAdjFlight(c27,456,11012.8,1800,200); flightCount++;
	c27->addAdjFlight(c13,4356,11079.6,1800,230); flightCount++;
	c13->addAdjFlight(c11,4566,11019.59,1230,115); flightCount++;
	c11->addAdjFlight(c14,67,4427.76,600,200); flightCount++;
	c14->addAdjFlight(c11,967,4427.76,600,200); flightCount++;
	c11->addAdjFlight(c16,876,1180.33,400,200); flightCount++;
	c16->addAdjFlight(c11,765,1180.33,700,100); flightCount++;
	c11->addAdjFlight(c12,5674,2047.63,630,200); flightCount++;
	c12->addAdjFlight(c11,568,2047.63,750,100); flightCount++;
	c14->addAdjFlight(c12,58,6345.67,300,200); flightCount++;
	c12->addAdjFlight(c15,270,6006.45,600,200); flightCount++;
	c15->addAdjFlight(c12,4563,6006.45,600,200); flightCount++;
	c16->addAdjFlight(c15,436,6427.65,2300,45); flightCount++;
	c17->addAdjFlight(c15,456,6266.09,2030,200); flightCount++;
	c15->addAdjFlight(c20,34,7473.94,1630,300); flightCount++;
	c12->addAdjFlight(c16,6456,867.53,130,25); flightCount++;
	c16->addAdjFlight(c12,3453,867.53,115,30); flightCount++;
	c17->addAdjFlight(c18,345,1906.85,330,200); flightCount++;
	c18->addAdjFlight(c17,5543,1906.85,600,200); flightCount++;
	c18->addAdjFlight(c10,554,9031.85,600,200); flightCount++;
	c10->addAdjFlight(c18,443,9031.85,600,300); flightCount++;
	c16->addAdjFlight(c18,221,3913.58,445,200); flightCount++;
	c16->addAdjFlight(c22,120,5471.08,600,200); flightCount++;
	c22->addAdjFlight(c16,2344,5471.08,600,200); flightCount++;
	c17->addAdjFlight(c16,443,2424.14,600,200); flightCount++;
	c16->addAdjFlight(c17,345,2424.14,600,200); flightCount++;
	c20->addAdjFlight(c15,6786,7473.94,1230,215); flightCount++;
	c17->addAdjFlight(c20,678,2710.67,600,200); flightCount++;
	c20->addAdjFlight(c17,567,2710.67,600,200); flightCount++;
	c20->addAdjFlight(c21,456,1091.88,600,200); flightCount++;
	c21->addAdjFlight(c20,908,1091.88,600,200); flightCount++;
	c17->addAdjFlight(c21,456,3795.71,1200,200); flightCount++;
	c18->addAdjFlight(c22,434,1620.52,1500,130); flightCount++;
	c22->addAdjFlight(c18,235,1620.52,500,30); flightCount++;
	c21->addAdjFlight(c19,52,1861.99,1545,200); flightCount++;
	c19->addAdjFlight(c10,345,8971.88,1720,200); flightCount++;
	c19->addAdjFlight(c24,756,1105.18,1300,100); flightCount++;
	c19->addAdjFlight(c22,567,1433.09,600,200); flightCount++;
	c22->addAdjFlight(c19,3425,1433.09,600,200); flightCount++;
	c24->addAdjFlight(c22,474,342.76,600,200); flightCount++;
	c22->addAdjFlight(c24,456,342.76,500,600); flightCount++;
	c22->addAdjFlight(c21,6457,1585.77,1530,120); flightCount++;
	c21->addAdjFlight(c22,63,1585.77,600,130); flightCount++;
	c22->addAdjFlight(c23,4352,932.08,700,200); flightCount++;
	c23->addAdjFlight(c22,4153,932.08,830,100); flightCount++;
	c24->addAdjFlight(c19,7845,1105.18,1630,120); flightCount++;
	c21->addAdjFlight(c24,88,1454.07,1830,120); flightCount++;
	c24->addAdjFlight(c23,44,878.08,1510,130); flightCount++;
	c23->addAdjFlight(c24,58,878.08,1515,100); flightCount++;
	c23->addAdjFlight(c21,3,2313.75,1600,200); flightCount++;
	c21->addAdjFlight(c23,204,2313.75,600,200); flightCount++;
	c26->addAdjFlight(c21,445,5224.18,600,200); flightCount++;
	c21->addAdjFlight(c26,456,5224.18,600,200); flightCount++;
	c26->addAdjFlight(c23,78,5997.36,600,200); flightCount++;
	c23->addAdjFlight(c26,125,5997.36,1630,200); flightCount++;
	c22->addAdjFlight(c26,213,5219.5,600,300); flightCount++;
	c26->addAdjFlight(c25,453,8202.91,300,200); flightCount++;
	c25->addAdjFlight(c26,98,8202.91,600,200); flightCount++;
	c25->addAdjFlight(c23,1235,10010.54,600,200); flightCount++;
	c23->addAdjFlight(c25,45,10010.54,600,200); flightCount++;
	c25->addAdjFlight(c21,34,7715.35,600,200); flightCount++;
	c21->addAdjFlight(c25,38,7715.35,1030,500); flightCount++;
	c28->addAdjFlight(c16,39,2992.92,1430,200); flightCount++;
	c16->addAdjFlight(c28,453,2992.92,600,200); flightCount++;
	c28->addAdjFlight(c21,38,3237.45,1730,100); flightCount++;
	c21->addAdjFlight(c28,123,3237.45,1845,110); flightCount++;
	c28->addAdjFlight(c22,458,2500.56,1510,200); flightCount++;
	c22->addAdjFlight(c28,45,2500.56,600,200); flightCount++;
	c28->addAdjFlight(c18,300,922.4,1600,300); flightCount++;
	c29->addAdjFlight(c21,3000,591.91,2100,20); flightCount++;
	c21->addAdjFlight(c29,135,591.91,200,400); flightCount++;
	c29->addAdjFlight(c20,453,1029.59,1500,50); flightCount++;
	c20->addAdjFlight(c29,1238,1029.59,2200,400); flightCount++;
	c29->addAdjFlight(c17,123,3668.86,2230,200); flightCount++;
	c22->addAdjFlight(c30,38,3538.66,1525,100); flightCount++;
	c17->addAdjFlight(c30,453,612.45,600,200); flightCount++;
	c30->addAdjFlight(c17,158,612.45,600,200); flightCount++;
	c31->addAdjFlight(c16,159,2052.42,1600,145); flightCount++;
	c31->addAdjFlight(c17,247,428.08,1200,300); flightCount++;
	c17->addAdjFlight(c31,1947,428.08,100,150); flightCount++;
	c32->addAdjFlight(c11,2012,11019.59,1745,100); flightCount++;
	c11->addAdjFlight(c32,1348,11019.59,1900,300); flightCount++;
	c13->addAdjFlight(c32,4538,3301.7,1200,230); flightCount++;
	cout<<endl;

	//display all flights in tabular form with source and destination columns
	g.disAllFlights();
	cout<<"\n\t\t\t\t\t\tTotal cities: "<<cityCount;

	//display total count of cities and flights 
	cout<<"\n\t\t\t\t\t\tTotal Flights: "<<flightCount<<endl;
	cout<<"\n\n\t\t\t\t\t\tEnter source city: ";
	do{
		getline(cin,sourceCity);                            //source city input by user

		//If Source City entered is present, change bool variable to true
		for(size_t i=0;i<g.getCityList().size();i++)
		{
			if(g.getCityList()[i]->getCityName()==sourceCity)
			{
				sourcePresent=true;
				break;
			}
		}

		if(sourcePresent)                //If source city present
		{
			cout<<"\n\t\t\t\tDirect Flights from "<<sourceCity<<" are available to following cities:\n\n";
			g.findFlightsOfCity(sourceCity);                //Display Direct Flights from source city

			cout<<"\n\n\n\t\t\t\t\t\tEnter your destination city: ";
			do{
				getline(cin, destCity);                            //Destination city input by user

				//Check if destination city is present, change bool variable to true
				for(size_t i=0;i<g.getCityList().size();i++)
				{
					if(g.getCityList()[i]->getCityName()==destCity)
					{
						destPresent=true;
						break;
					}
				}

				if(destPresent)                                //If destination city is also found,
				{
					g.Dijkstra(sourceCity,destCity);            //Call dijkstra method to get the shortest path between source and destination city
					break;
				}
				//if destination city entered is not present, give 3 chances to the user to enter correct destination city
				else
				{
					cout<<"\nNo Flight operations to "<<destCity<<" from "<<sourceCity<<endl;
					cout<<"\nRe-Enter your Destination\n\tYou have "<<destTry<<" tries remaining:"<<endl;
					destTry--;
				}
			}while(destTry>=0);
			break;
		}
		//if source city entered is not present, give 3 chances to the user to enter correct source city
		else
		{
			cout<<"\nSorry, We don't Operate Flights from "<<sourceCity<<endl;            //If source city not present, display this message
			cout<<"\nRe-Enter your Departure City\n\tYou have "<<sourceTry<<" tries remaining:"<<endl;
			sourceTry--;
		}
	}while(sourceTry>=0);
	system("pause");			//end the program :) :) :)
}