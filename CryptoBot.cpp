#pragma warning(disable:4996)
#include "CryptoBot.h"

CryptoBot::CryptoBot(std::string name, double tradable, double buying)
{
	crypto_name = name;
	amount_tradable = tradable;
	buying_power = buying;
	double temp = getPrice(name);
	initial_price = temp;
	current_price = temp;
	min_price = temp;
	cycle_counter = 0;
	velocity = 0; //change in price from cycle to cycle
};

double CryptoBot::getPrice(std::string name)
{
	std::string url = "https://api.coingecko.com/api/v3/simple/price?ids=" + name + "&vs_currencies=usd";
	cpr::Response response = cpr::Get(cpr::Url{ url });
	std::string num_string = response.text;
	try
	{
		if (num_string.empty()) //url will be empty if no connection, would cause serious errors if not caught here
		{
			throw url;
		}
	}
	catch (std::string address)
	{
		std::cout << "Network Error!\n";
		std::cout << "You were unable to connect to the CoinGecko API at the URL:\n" << address << "\n";
		std::cout << "Check your internet connection by pinging the URL above in your console.\n";
		std::quick_exit(0);
	}
	std::string dollarprice;
	std::string centprice;
	int counter = 0;
	bool decimalflag = true;
	std::string nums = "0123456789";

	//converts a string into a double
	for (int x = 0; x < num_string.size(); x++)
	{
		if (nums.find(num_string[x]) != std::string::npos)
		{
			if (decimalflag)
			{
				dollarprice += num_string[x];
			}
			else
			{
				centprice += num_string[x];
				counter++;
			}

		}
		else if (num_string[x] == '.')
		{
			decimalflag = false;
		}
	}
	if (!centprice.empty())
	{
		double truevalue = (double)std::stoi(dollarprice) + (double)std::stoi(centprice) / (pow(10, counter));
		return truevalue;
	}
	else
	{
		double truevalue = (double)std::stoi(dollarprice);
		return truevalue;
	}
};

void CryptoBot::updatePrice()
{
	double old_price = current_price;
	std::chrono::seconds timespan(20); //chrono allows for more accurate time measurements
	std::this_thread::sleep_for(timespan);
	current_price = getPrice(crypto_name);
	if (current_price < min_price)
	{
		min_price = current_price;
	}
	cycle_counter++;
	if (cycle_counter > 750) //internal clock for the function, prevents rapid buys/selloffs
	{
		cycle_counter = 0; //resets roughly every ~4.17 hours automatically
	}
	velocity = current_price - old_price;

	std::ios_base::sync_with_stdio(false); //speeding up cout
	std::cin.tie(nullptr);

	std::cout << "Name: " << crypto_name << "\n";
	std::cout << "Current: " << current_price << "\n";
	std::cout << "Initial: " << initial_price << "\n";
	std::cout << "Min: " << min_price << "\n";
	std::cout << "Amount Held: " << amount_tradable << "\n";
	std::cout << "Velocity: " << velocity << "\n";
	std::cout << "Counter: " << cycle_counter << "\n\n";

	transaction_limits(); //updatePrice() and transaction_limits() call each other, creating an infinite loop
};

void CryptoBot::fileCreation(std::string type)
{
	std::string ticker;
	if (crypto_name == "bitcoin") { ticker = "BTC"; }
	else if (crypto_name == "ethereum") { ticker = "ETH"; }
	else if (crypto_name == "bitcoin-cash") { ticker = "BCH"; }
	else if (crypto_name == "ethereum-classic") { ticker = "ETC"; }
	else if (crypto_name == "litecoin") { ticker = "LTC"; }
	else { ticker = "DOGE"; }
	if (type == "buy")
	{
		//logic for the astronomically rare situation where multiple threads sell/buy at once
		std::ifstream infile("buy.txt");
		while (infile.good())
		{
			std::cout << "File already exists\n";
			std::chrono::seconds timespan(5);
			std::this_thread::sleep_for(timespan);
		}
		std::ofstream file("buy.txt");
		file << ticker << "\n" << amount_tradable << "\n" << buying_power;
		file.close();
	}
	else
	{
		//logic for the astronomically rare situation where multiple threads sell/buy at once
		std::ifstream infile("sell.txt");
		while (infile.good())
		{
			std::cout << "File already exists\n";
			std::chrono::seconds timespan(5);
			std::this_thread::sleep_for(timespan);
		}
		std::ofstream file("sell.txt");
		file << ticker << "\n" << amount_tradable;
		file.close();
	}
};

void CryptoBot::transaction_limits()
{
	if (cycle_counter % 30 == 0 && amount_tradable > 0 && initial_price * 1.05 <= current_price && velocity < 0)
	{
		std::cout << "Selling limit, calling Python file\n";
		fileCreation("sell");
		//feel free to embed Python here for greater portability (we had x84 x64 differences that we didn't want to resolve)
		system("C:/CryptoBot/PythonEndSell.py");
		amount_tradable -= amount_tradable * 0.15;
	}
	else if (cycle_counter % 30 == 0 && amount_tradable > 0 && initial_price * .85 >= current_price && velocity < 0)
	{
		std::cout << "Selling limit, calling Python file\n";
		fileCreation("sell");
		//feel free to embed Python here for greater portability (we had x84 x64 differences that we didn't want to resolve)
		system("C:/CryptoBot/PythonEndSell.py");
		amount_tradable -= amount_tradable * 0.15;
	}
	else if (cycle_counter > 550 && min_price >= current_price)
	{
		std::cout << "Buying limit, calling Python file\n";
		fileCreation("buy");
		//feel free to embed Python here for greater portability (we had x84 x64 differences that we didn't want to resolve)
		system("C:/CryptoBot/PythonEndBuy.py");
		double holder;
		std::ifstream file("buy.txt");
		file >> holder;
		file.close();
		std::remove("buy.txt");
		buying_power -= holder;
		amount_tradable += holder / current_price;
		cycle_counter = 0;
	}
	updatePrice();
};

CryptoBot::~CryptoBot() {};