#include "CryptoBot.h"
#include "Portfolio.h"
#include <limits>
#include <filesystem>
#undef max

void clearConsole() //change system() dependency eventually, bugtest this on Linux later
{
#ifdef _unix_
	std::system("clear");
#else
	std::system("CLS");
#endif
}

void errorMessage()
{
	std::cout << "Exiting via quick_exit\n";
	quick_exit(EXIT_SUCCESS);
}

CryptoBot initializeCrypto(std::string path)
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

	double percent_ceiling = -1;
	double percent_ceiling_backup = -1;
	while (true)
	{
		std::cout << "\nPlease enter the percentage ceiling you want to sell at.\nFor example, entering 1.18 would execute a market sell when the price is 18% HIGHER than the initial value at runtime.\nTHE VALUE MUST BE GREATER THAN 1!\nEnter \"-999\" if you do not want to sell at any value above your initial price.\n";
		std::cin >> percent_ceiling;
		
		if (percent_ceiling <= 1 || !std::cin)
		{
			if (percent_ceiling == -999)
			{
				break;
			}
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			percent_ceiling = -1;
		}
		std::cout << "Please reenter this number, making sure that it is indeed a percentage ceiling you feel comfortable selling at.\n";
		std::cin >> percent_ceiling_backup;
		if (percent_ceiling <= 1 || !std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			percent_ceiling_backup = -1;
		}
		if (percent_ceiling == percent_ceiling_backup && percent_ceiling != -1)
		{
			break;
		}
		std::cout << "\nYou have made a typo. Please try again.\n";
	}

	double percent_floor = -1;
	double percent_floor_backup = -1;
	while (true)
	{
		std::cout << "\nPlease enter the percentage floor you want to sell at.\nFor example, entering .75 would execute a market sell when the price is 25% LOWER than the initial value at runtime.\nTHE VALUE MUST BE LESS THAN 1 AND GREATER THAN 0!\nEnter \"-999\" if you do not want to sell at any value below your initial price.\n";
		std::cin >> percent_floor;
		
		if (percent_floor >= 1 || percent_floor <= 0 || !std::cin)
		{
			if (percent_floor == -999)
			{
				break;
			}
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			percent_floor = -1;
		}
		std::cout << "Please reenter this number, making sure that it is indeed a percentage floor you feel comfortable selling at.\n";
		std::cin >> percent_floor_backup;
		if (percent_floor_backup >= 1 || !std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			percent_floor_backup = -1;
		}
		if (percent_floor == percent_floor_backup && percent_floor != -1)
		{
			break;
		}
		std::cout << "\nYou have made a typo. Please try again.\n";
	}

	double percent_buy = -1;
	double percent_buy_backup = -1;
	while (true)
	{
		std::cout << "\nPlease enter the percentage of your total allocated buying power you would like CryptoBot to spend\non " + coin_input + " when the buy logic triggers.\nFor example, entering .75 will spend 75% of your buying power on the tracked coin.\nTHE VALUE MUST BE LESS THAN OR EQUAL TO 1 AND GREATER THAN 0!\nEnter \"-999\" if you do not want to buy the coin.\n";
		std::cin >> percent_buy;

		if (percent_buy <= 0 || percent_buy > 1 || !std::cin)
		{
			if (percent_buy == -999)
			{
				break;
			}
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			percent_buy = -1;
		}
		std::cout << "Please reenter this number, making sure that it is indeed a sell percentage you feel comfortable with.\n";
		std::cin >> percent_buy_backup;
		if (percent_buy_backup < 0 || percent_buy_backup >= 1 || !std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			percent_buy_backup = -1;
		}
		if (percent_buy == percent_buy_backup && percent_buy != -1)
		{
			break;
		}
		std::cout << "\nYou have made a typo. Please try again.\n";
	}

	double percent_sell = -1;
	double percent_sell_backup = -1;
	while (true)
	{
		std::cout << "\nPlease enter the percentage of your amount tradable of " + coin_input + " you would\nlike CryptoBot to sell when the sell logic triggers.\nFor example, entering .50 will sell 50% of the coin's amount tradable.\nTHE VALUE MUST BE LESS THAN OR EQUAL TO 1 AND GREATER THAN 0!\nEnter \"-999\" if you do not want to sell the coin.\n";
		std::cin >> percent_sell;

		if (percent_sell <= 0 || percent_sell > 1 || !std::cin)
		{
			if (percent_sell == -999)
			{
				break;
			}
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			percent_sell = -1;
		}
		std::cout << "Please reenter this number, making sure that it is indeed a sell percentage you feel comfortable with.\n";
		std::cin >> percent_sell_backup;
		if (percent_sell_backup < 0 || percent_sell_backup >= 1 || !std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			percent_sell_backup = -1;
		}
		if (percent_sell == percent_sell_backup && percent_sell != -1)
		{
			break;
		}
		std::cout << "\nYou have made a typo. Please try again.\n";
	}

	clearConsole(); 
	CryptoBot bot = CryptoBot(coin_input, amount_tradable, buying_power, percent_ceiling, percent_floor, percent_buy, percent_sell, path);
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
			std::cout << "\n\n\n";
			break;
		}
		std::cout << "You have made a typo. Remember that \"I AGREE\" is case sensitive\n";
	}

	std::string location = std::filesystem::current_path().string();
	location = location.substr(0 , location.size() - 3);
	for (int x = 0; x < location.size(); x++)
	{
		if (location[x] == '\\')
		{
			location[x] = '/';
		}
	}
	std::string user_path;
	std::string path_input;
	while (true)
	{
		std::cout << "Location of the installed CryptoBot folder is: \n" << location << "\n\n";
		std::cout << "Please write \"correct\" if it is correct, otherwise write \"incorrect\" and substitute your own path.\nSUBSTITUTE AT YOUR OWN RISK, MAJOR ERRORS COULD STEM FROM AN INCORRECT PATH!\n";
		std::cout << "If you do not yet have a CryptoBot folder, review the installation instructions in the README.md file on GitHub.\n";
		std::cin >> path_input;
		if (path_input == "correct")
		{
			user_path = location;
			if (std::filesystem::exists(user_path))
			{
				std::cout << "\n\n";
				break;
			}
		}
		if (path_input == "incorrect")
		{
			std::cout << "Enter the path of the CryptoBot folder manually (formatting identical to that of the location seen above).\nREGARDLESS OF OS, USE / FOR PATH DELIMITERS!\n";
			std::cin >> user_path;
			if (std::filesystem::exists(user_path))
			{
				std::cout << "\n\n";
				break;
			}
		}
		std::cout << "\nYou have either made a typo or the path to the file does not exist. Please try again.\n\n";
	}
	
	std::string string_path = user_path + "PythonScripts/PythonEndLogin.py";
	char* char_path = const_cast<char*>(string_path.c_str());
	std::system(char_path);
	free(char_path);

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

	clearConsole();

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
			portfolio.newBot(initializeCrypto(user_path));
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

	clearConsole(); 
	portfolio.threadedUpdate();
	at_quick_exit(errorMessage);
}
