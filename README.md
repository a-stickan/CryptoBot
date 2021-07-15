# CryptoBot


Work in progress! Uses C++ and Python to execute market buy/sell orders of all avaliable cryptocurrencies on Robinhood Crypto based on current market conditions.

Libraries in Use:
1. Curl for People (https://github.com/whoshuu/cpr)
2. Robin Stocks (https://github.com/jmfernandes/robin_stocks)

See the "LICENSE" file for copyright information.


## Instructions for Use:

1. Make sure you have a valid Robinhood account. CryptoBot only supports Robinhood accounts, so you will not be able to use CryptoBot if you do not have an account.

2. Install and extract the latest stable release .zip folder, being sure to ignore any security/antivirus warnings that pop up. As of now, the latest release only supports Windows out of the box (use the CMakeLists.txt file and the raw source code for cross-platform).

3. Make sure all the files for the program are in the installed folder (name and location of the folder is irrelevant, but the contained files and folders should not be changed in any way).

4. Make sure you have Python 3 installed on your computer and that by default .py files are opened by the Python application. HAVING THE DEFAULT AS
   AN IDE OR TEXT EDITOR MAY CAUSE SERIOUS ISSUES!
   
5. Run the program by clicking on the "CryptoBotRelease" application if you are on Windows. You will have to build the executable yourself if you are on Linux/Mac.

6. Follow the instructions in the console GUI to initialize CryptoBot's trading capabilities.

7. If you experience errors running "PythonEndLogin.py" (Robinhood doesn't play very well with logins), run the file ON ITS OWN
   and input your username, password, and secret code when prompted. The problem should be fixed on all future logins until the login token expires.

8. (Optional but highly recommended) Every time a sell/buy order is processed, a .csv file is put into the installed folder. You can import this file
    into a sheet program like Excel to better manage your portfolio's progress and track your holdings.

## Things to Change (in order of priority):

1. Better implement the cross-platform compatibility. The CMake end is done and the code itself is cross-platform, but no ready-made executable for Linux/Mac exists at the moment.

2. System() calls are very prominent in the C++ end and are the most glaring technical issue with this repo. I had issues with other implementations (x64 and x84 incompatibilities), and did not have time to resolve the issues behind them.
   Embedding Python calls (https://docs.python.org/3/extending/embedding.html) and going for more OS specific console clear commands would be the easiest way to solve this problem.

3. Stack and heap usage optimization. I'm unsure whether or not the indirect recursion in CryptoBot.cpp will ever realistically cause a stack overflow error, but it is something that can certainly be improved.

4. Error handling. Could be made far more robust on the C++ end.

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


