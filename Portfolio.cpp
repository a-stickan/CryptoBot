#include "Portfolio.h"

void CryptoPortfolio::newBot(CryptoBot bot)
{
	portfolio.push_back(bot);
};

void CryptoPortfolio::threadedUpdate()
{
	int size = portfolio.size();

	if (size == 1)
	{
		std::thread t1(&CryptoBot::updatePrice, &portfolio.at(0));
		t1.join();
	}

	if (size == 2)
	{
		std::thread t1(&CryptoBot::updatePrice, &portfolio.at(0));
		std::thread t2(&CryptoBot::updatePrice, &portfolio.at(1));
		t1.join();
		t2.join();
	}

	if (size == 3)
	{
		std::thread t1(&CryptoBot::updatePrice, &portfolio.at(0));
		std::thread t2(&CryptoBot::updatePrice, &portfolio.at(1));
		std::thread t3(&CryptoBot::updatePrice, &portfolio.at(2));
		t1.join();
		t2.join();
		t3.join();
	}

	if (size == 4)
	{
		std::thread t1(&CryptoBot::updatePrice, &portfolio.at(0));
		std::thread t2(&CryptoBot::updatePrice, &portfolio.at(1));
		std::thread t3(&CryptoBot::updatePrice, &portfolio.at(2));
		std::thread t4(&CryptoBot::updatePrice, &portfolio.at(3));
		t1.join();
		t2.join();
		t3.join();
		t4.join();
	}
};

CryptoPortfolio::~CryptoPortfolio() {};