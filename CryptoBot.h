#ifndef CRYPTOBOT_H
#define CRYPTOBOT_H

#include <iostream>
#include <string>
#include <vector>
#include <cpr/api.h>
#include <cpr/multipart.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <math.h>
#include <fstream>

class CryptoBot
{
	std::string crypto_name;
	std::string directory;
	double amount_tradable;
	double buying_power;
	double initial_price;
	double current_price;
	double min_price;
	double velocity;
	double percent_ceiling;
	double percent_floor;
	double percent_buy;
	double percent_sell;
	int cycle_counter = 0;

public:

	CryptoBot(std::string name, double tradable, double buying, double ceiling, double floor, double buy, double sell, std::string directory);

	double getPrice(std::string name);

	void fileCreation(std::string type);

	void updatePrice();

	void transaction_limits();

	~CryptoBot();

};

#endif
