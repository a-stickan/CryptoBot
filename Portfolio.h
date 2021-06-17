#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "CryptoBot.h"


class CryptoPortfolio
{
	std::vector<CryptoBot> portfolio;

public:

	void newBot(CryptoBot bot);

	void threadedUpdate();

	~CryptoPortfolio();
};

#endif
