#include "CryptoBot.h"
#include "Portfolio.h"
#include <limits>
#undef max

void errorMessage()
{
	std::cout << "Exiting via quick_exit\n";
	quick_exit(EXIT_SUCCESS);
}

inline CryptoBot initializeCrypto()
{
	std::string coin_input;
	std::string backup_input;
	bool flag = true;
	std::vector<std::string> supported_currencies = { "bitcoin", "bitcoin-cash", "dogecoin", "ethereum", "ethereum-classic", "litecoin" };
	while (flag)
	{
		std::cout << "\nCryptocurrencies avaliable on Robinhood: bitcoin, bitcoin-cash, dogecoin, ethereum, ethereum-classic, and litecoin\nPlease enter a coin you would like to trade:\n";
		std::cin >> coin_input;
		std::cout << "Please reenter the coin's name, making sure that you spell it correctly.\n";
		std::cin >> backup_input;
		if (coin_input == backup_input)
		{
			for (int i = 0; i < supported_currencies.size(); i++)
			{
				if (supported_currencies.at(i) == coin_input) { flag = false; }
			}
		}
		else
		{
			std::cout << "\nYou have made a typo. Please try again.\n";
		}
	};

	double amount_tradable = -1;
	double amount_tradable_backup = -1;
	while (true)
	{
		std::cout << "\nPlease enter the amount of " + coin_input + " you would like to trade (decimals included).\nDO NOT ENTER A NUMBER LARGER THAN THE AMOUNT YOU POSSESS ON YOUR ACCOUNT!\n";
		std::cin >> amount_tradable;
		if (amount_tradable < 0 || !std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			amount_tradable = -1;
		}
		std::cout << "Please reenter this number, making sure that it is a value you possess in your account and are willing to trade.\n";
		std::cin >> amount_tradable_backup;
		if (amount_tradable_backup < 0 || !std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			amount_tradable_backup = -1;
		}
		if (amount_tradable_backup == amount_tradable && amount_tradable != -1)
		{
			break; //I know breaks are often hated, but they allow for more elegant and compact code when in comes to printing out the typo logic
		}
		std::cout << "\nYou have made a typo. Please try again.\n";
	}

	double buying_power = -1;
	double buying_power_backup = -1;
	while (true)
	{
		std::cout << "\nPlease enter the amount of buying power you would like to leverage for " + coin_input + " in USD.\nDO NOT ENTER A NUMBER LARGER THAN THE AMOUNT OF CAPITAL CURRENTLY HELD!\n";
		std::cin >> buying_power;
		if (buying_power < 0 || !std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			buying_power = -1;
		}
		std::cout << "Please reenter this number, making sure that it is an amount of capital you currently\npossess in your account and are willing to spend on " + coin_input + ".\n";
		std::cin >> buying_power_backup;
		if (buying_power_backup < 0 || !std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			buying_power_backup = -1;
		}
		if (buying_power == buying_power_backup && buying_power != -1)
		{
			break;
		}
		std::cout << "\nYou have made a typo. Please try again.\n";
	}

	system("CLS"); //end implementation likely GUI based, took shortcuts with system("CLS") for readability
	CryptoBot bot = CryptoBot(coin_input, amount_tradable, buying_power);
	return bot;
}

int main()
{
	std::ios_base::sync_with_stdio(false); //speeding up cout
	std::cin.tie(nullptr);

	std::cout << "   _____            _               ____        _   \n";
	std::cout << "  / ____|          | |             |  _\\       | |  \n";
	std::cout << " | |     _ __ _   _| |_ _ __   ___ | |_)|  ___ | |_ \n";
	std::cout << " | |    | '__| | | | __| '_ \\ / _ \\|  _ < / _ \\| __|\n";
	std::cout << " | |____| |  | |_| | |_| |_) | (_) | |_) | (_) | |_ \n";
	std::cout << "  \\_____|_|  \\__,|  \\__|.__/  \\___/|____/ \\___/ \\__|\n";
	std::cout << "              |___/    |_|                          \n\n\n";

	std::cout << "C++ end, Python end, and file system by Aidan Stickan (a-stickan)\n\n\n";

	std::cout << "_______________________________________________________________________________________________________________\n";
	std::cout << "Disclaimers:                                                                                                   |\n";
	std::cout << "\t1. Investing in cryptocurrencies carries a significant risk. Please research before buying.            |\n";
	std::cout << "\t2. The publishers of this program are not accountable for ANY FINANCIAL LOSSES as a result of your own |\n";
	std::cout << "\t   actions, errors in the program itself, or errors in your Robinhood Account.                         |\n";
	std::cout << "\t3. By using this program, you may incur financial losses and profits are not guaranteed.               |\n";
	std::cout << "_______________________________________________________________________________________________________________|\n\n\n";

	std::cout << "Please type \"I AGREE\" if you have read and understand the terms above. Close and do not attempt to run CryptoBot if you do not agree to the terms provided in the disclaimers section\n";
	std::string user_input;


	while (true)
	{
		std::cout << "Type here: \n";
		std::getline(std::cin, user_input);
		if (user_input == "I AGREE")
		{
			break;
		}
		std::cout << "You have made a typo. Remember that \"I AGREE\" is case sensitive\n";
	}

	system("CLS"); //end implementation likely GUI based, took shortcuts with system("CLS") for readability
	//feel free to embed Python here for greater portability (we had x84 x64 differences that we didn't want to resolve)
	system("C:/CryptoBot/PythonEndLogin.py");
	system("CLS");

	std::ifstream buyfile("buy.txt");
	if (buyfile.good()) //logic to make sure that buy.txt doesn't already exist
	{
		std::remove("buy.txt");
	}

	std::ifstream sellfile("sell.txt");
	if (sellfile.good()) //logic to make sure that sell.txt doesn't already exist
	{
		std::remove("sell.txt");
	}


	std::string coin_check;
	int counter = 0;
	CryptoPortfolio portfolio;
	while (true)
	{
		std::cout << "You are keeping track of " << counter << " coins out of the limit of 4\n";
		if (counter == 4)
		{
			std::cout << "You have reached the maximum amount of coins that can be tracked. Running program.\n";
			break;
		}
		std::cout << "Please type \"add\" if you would like to add a coin to CryptoBot. Type anything else to begin running the program.\n";
		std::cin >> coin_check;
		if (coin_check == "add")
		{
			portfolio.newBot(initializeCrypto());
			counter++;
		}
		else
		{
			if (counter > 0)
			{
				break;
			}
			else
			{
				std::cout << "\nYou must keep track of at least one cryptocurrency.\n";
			}
		}
	}

	system("CLS"); //end implementation likely GUI based, took shortcuts with system("CLS") for readability
	portfolio.threadedUpdate();
	at_quick_exit(errorMessage);
}
