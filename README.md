# CryptoBot


My first major project, uses C++ and Python to execute market buy/sell orders of all currently avaliable cryptocurrencies on Robinhood Crypto. Written primarily in C++, Python script files are called to execute the actual orders.

Libraries in Use:
1. Curl for People (https://github.com/whoshuu/cpr)
2. Curl (https://github.com/curl/curl)
3. Robin Stocks (https://github.com/jmfernandes/robin_stocks)

See the "LICENSE" file for copyright information.


## Instructions for Use:

1. Make sure you have a valid Robinhood account. CryptoBot at the moment only supports Robinhood accounts, so you will not be able to use CryptoBot if you do not have an account.

1. Install the latest stable release. As of now only Windows machines can run CryptoBot, but future releases for Linux and MacOS may happen in the future.

2. Make sure you have Python installed on your computer and that by default .py files are opened by the Python application. HAVING THE DEFAULT AS
   AN IDE OR TEXT EDITOR MAY CAUSE SERIOUS ISSUES!

3. Place the downloaded CryptoBot folder and all its files in your C drive (C:/). THE PROGRAM WILL LIKELY NOT OPERATE WITHOUT THIS STEP!

4. Run the program by clicking on the "CryptoBotRelease" application.

5. Follow the instructions in the console GUI to initalize CryptoBot's trading capabilities.

6. If you experience errors running "PythonEndLogin.py" (Robinhood doesn't play very well with logins), run the file ON ITS OWN
   and input your username, password, and secret code when prompted. Assuming you have store_session still set to true, the problem
   should be fixed on all future logins. You may have to manually edit the .py file with your credentials to get it working, this step was inconsistent at best from machine to machine in my testing.

7. (Optional but highly recommended) Every time a sell/buy order is processed, a .csv file is put into CryptoBot. You can import this file
    into a sheet program like Excel to better manage your portfolio's progress and track your holdings.

## Things to Change (in order of priority):

1. System() calls are very prominent in the C++ end. This is obviously not very scalable (or safe, or efficient), and is what limits the program 
   to Windows at the moment. I had issues with other implementations (x64 and x84 incompatibilities), and did not have time to resolve the issues behind them.
   Embedding Python calls (https://docs.python.org/3/extending/embedding.html) and removing the system("CLS") calls in main
   should make CryptoBot much more friendly on other operating systems like Linux.
   
2. More user control over the specific buy/sell points and the actual buy/sell amount that occurs would greatly improve the code. Expanding the .txt file system would be the easiest way to solve this issue, but a fairly sophisticated embedded Python application would work even better in exchange for being far harder and more time consuming to implement.

3. Login issues with "PythonEndLogin.py". I could not determine why it worked sometimes on some machines with little effort but introduced massive
   issues on others. Documentation at https://robin-stocks.readthedocs.io/en/latest/index.html.

4. Try catch error handling. This could probably be expanded on and improved on the C++ end.

5. Stack and heap usage optimization. Not a major priority, but a lighter build of CryptoBot would be nice.

## Basic Code Documentation:

### Python End:

**PythonEndBuy.py-** manages the execution of buy orders, exports a .csv file when completed.
		 Called as a script through the C++ end, no logic involved.

**PythonEndSell.py-** manages the execution of sell orders, exports a .csv file when completed.
		  Called as a script through the C++ end, no logic involved.

**PythonEndLogin.py-** manages the login process, stores the login session for convinence afterwards. Theoretically should only show up once to prompt the user to enter their username and password, user logins are permanently saved after the fact. Called as a script through the C++ end, no logic involved.



### C++ End:

**CryptoBot.cpp-** .cpp file for the CryptoBot class. Contains most of the logic behind getting prices
		and determining when to sell. Creates .txt files at times to pass information
		on to the Python end.

**CryptoBot.h-** header file for the CryptoBot.cpp file.

**Portfolio.cpp-** .cpp file for the CryptoPortfolio class. Creates a vector of CryptoBot objects that can then be
 		multithreaded through the threadedUpdate() function. More threads can be edited in if you desire, I put a hard
		cap at 4 threads to prevent potential performance issues.

**Portfolio.h-** header file for the Portfolio.cpp file.

**Main.cpp-** .cpp file mainly in charge of the console UI of the program. Calls PythonEndLogin.py to sign new users in. Creates CryptoBot objects using the CryptoBot class. Runs the program using the CryptoPortfolio class to hold the CryptoBot objects and execute threadedUpdate() on all of them. Basic threaded error handling processed here through at_quick_exit().


