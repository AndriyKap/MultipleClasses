#include<iostream>
#include<string>
#include<ctime>
#include<fstream>

using namespace std;

class Car
{
private:
	string mark;
	string name;
	double volume;
public:
	virtual string GetType() = 0;
	string GetMark()
	{
		return mark;
	}
	double GetVolume()
	{
		return volume;
	}
	bool operator<(Car& car)
	{
		if (this->GetVolume() < car.GetVolume())
		{
			return true;
		}
		if (this->GetVolume() == car.GetVolume())
		{
			return this->GetMark() < car.GetMark();
		}
	}

	virtual void input(fstream& f)
	{
		f >> mark >> name >> volume;
	}

	virtual void print(fstream& f)
	{
		f << mark << " " << name << " " << volume << " ";
	}
};

class Diesel : virtual public Car
{
private:
	int volume_of_tank;
public:
	virtual string GetType()
	{
		return "Diesel";
	}

	int GetVolumeOfTank()
	{
		return volume_of_tank;
	}

	friend fstream& operator >> (fstream& f, Diesel& car)
	{
		car.input(f);
	}

	friend fstream& operator << (fstream& f, Diesel& car)
	{
		car.print(f);
	}

	virtual void input(fstream& f)
	{
		Car::input(f);
		f >> volume_of_tank;
	}

	virtual void print(fstream& f)
	{
		Car::print(f);
		f << volume_of_tank << endl;
	}
};

class Electrocar : virtual public Car
{
private:
	double max_time_of_run;
	double time_of_charge;
public:	
	virtual string GetType()
	{
		return "Electrocar";
	}

	double GetTimeOfRun()
	{
		return max_time_of_run;
	}

	double GetTimeOfCharge()
	{
		return time_of_charge;
	}

	friend fstream& operator >> (fstream& f, Electrocar& car)
	{
		car.input(f);
	}

	friend fstream& operator << (fstream& f, Electrocar& car)
	{
		car.print(f);
	}

	virtual void input(fstream& f)
	{
		Car::input(f);
		f >> max_time_of_run >> time_of_charge;
	}

	virtual void print(fstream& f)
	{
		Car::print(f);
		f << max_time_of_run << " " << time_of_charge << endl;
	}
};

class Hybrid : public Diesel, public Electrocar
{
private:
	int run_of_diesel;
	int run_of_electro;
public:
	virtual string GetType()
	{
		return "Hybrid";
	}

	int GetRunOfDiesel()
	{
		return run_of_diesel;
	}

	int GetRunOfElectro()
	{
		return run_of_electro;
	}

	friend fstream& operator >> (fstream& f, Hybrid& car)
	{
		car.input(f);
	}

	friend fstream& operator << (fstream& f, Hybrid& car)
	{
		car.print(f);
	}

	virtual void input(fstream& f)
	{
		Diesel::input(f);
		Electrocar::input(f);
		f >> run_of_diesel >> run_of_electro;
	}

	virtual void print(fstream& f)
	{
		Diesel::print(f);
		Electrocar::print(f);
		f << " " << run_of_diesel << " " << run_of_electro;
	}
};

int main() 
{
	fstream f;
	fstream f2;
	f.open("Cars.txt");
	f2.open("Cars2.txt");
	int n = 3;
	Car** cars = new Car* [n];
	int temp;
	int i = 0;
	while (i != n)
	{
		f >> temp;
		switch (temp)
		{
			case 1: 
				cars[i] = new Diesel;
				break;
			case 2: 
				cars[i] = new Electrocar;
				break;
			case 3:
				cars[i] = new Hybrid;
				break;
		}
		cars[i]->input(f);
		i++;
	}
	f.close();

	for (int j = 0; j < n; j++)
	{
		cars[j]->print(f2);
	}

	for (int j = 0; j < n; j++)
	{
		if (dynamic_cast<Hybrid*>(cars[j]) != 0)
		{
			Hybrid* hybrid = dynamic_cast<Hybrid*>(cars[j]);
			cout << hybrid->GetRunOfDiesel() << endl;
			cout << hybrid->GetRunOfElectro() << endl;
		}
	}

	f2.close();



	return 0;
}