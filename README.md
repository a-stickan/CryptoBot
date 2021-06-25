# CryptoBot


My first major project, uses C++ and Python to execute market buy/sell orders of all currently avaliable cryptocurrencies on Robinhood Crypto. Written primarily in C++, Python script files are called to execute the actual orders.

Libraries in Use:
1. Curl for People (https://github.com/whoshuu/cpr)
2. Curl (https://github.com/curl/curl)
3. Robin Stocks (https://github.com/jmfernandes/robin_stocks)

See the "LICENSE" file for copyright information.


## Instructions for Use:

1. Make sure you have a valid Robinhood account. CryptoBot at the moment only supports Robinhood accounts, so you will not be able to use CryptoBot if you do not have an account.

1. Install and extract the latest stable release .zip folder, being sure to ignore any security/antivirus warnings that pop up. Even though the project is open source and you can check the code yourself to see it isn't malicious, downloading unknown .exe files from the internet will (predictably) set off some alarms in your system. As of now, the current stable release supports Windows, Linux, and Mac OS.

2. Make sure all the files for the program are in the installed folder (name and location of the folder is irrelevant, but the names and locations of the files themselves should not be changed).

2. Make sure you have Python 3 installed on your computer and that by default .py files are opened by the Python application. HAVING THE DEFAULT AS
   AN IDE OR TEXT EDITOR MAY CAUSE SERIOUS ISSUES!
   
3. Run the program by clicking on the "CryptoBotRelease" application.

4. Follow the instructions in the console GUI to initalize CryptoBot's trading capabilities.

5. If you experience errors running "PythonEndLogin.py" (Robinhood doesn't play very well with logins), run the file ON ITS OWN
   and input your username, password, and secret code when prompted. Assuming you have store_session still set to true, the problem
   should be fixed on all future logins until the login token expires. You may have to manually edit the .py file with your credentials to get it working, this step was inconsistent at best from machine to machine in my testing.

6. (Optional but highly recommended) Every time a sell/buy order is processed, a .csv file is put into the installed folder. You can import this file
    into a sheet program like Excel to better manage your portfolio's progress and track your holdings.

## Things to Change (in order of priority):

1. System() calls are very prominent in the C++ end. This is obviously not very scalable (or safe, or efficient), and is the most glaring issue with this repo. I had issues with other implementations (x64 and x84 incompatibilities), and did not have time to resolve the issues behind them.
   Embedding Python calls (https://docs.python.org/3/extending/embedding.html) and going for more OS specific console clear commands would be the easiest way to solve this problem.

2. Login issues with "PythonEndLogin.py". I could not determine why it worked sometimes on some machines with little effort but introduced massive
   issues on others. Documentation at https://robin-stocks.readthedocs.io/en/latest/index.html.

3. Try catch error handling. This could probably be expanded on and improved on the C++ end.

4. Stack and heap usage optimization. Not a major priority, but a lighter build of CryptoBot would be nice.

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

**Main.cpp-** .cpp file mainly in charge of the console UI of the program. Finds the file directory of the folder, resorting to user input if necessary. Calls PythonEndLogin.py to sign new users in. Creates CryptoBot objects using the CryptoBot class. Runs the program using the CryptoPortfolio class to hold the CryptoBot objects and execute threadedUpdate() on all of them. Basic threaded error handling processed here through at_quick_exit().


