Contributors:
Aidan Stickan (a-stickan) -  C++ end, .txt file system
Winston Slater - Python end, .csv exportation


See "LICENSE.txt" for copyright information.
________________________________________________________________________________________________________________________________________________________________________

Instructions for Use:
1. Make sure you have Python installed on your computer and that by default .py files are opened by the Python application. HAVING THE DEFAULT AS
   AN IDE OR TEXT EDITOR WILL CAUSE SERIOUS ISSUES!

2. Place the downloaded CryptoBot folder and all its files in your C drive (C:\). THE PROGRAM WILL LIKELY NOT OPERATE WITHOUT THIS STEP!

3. Run the program by clicking on the "CryptoBotRelease" application.

4. Follow the instructions in the console GUI to initalize CryptoBot's trading capabilities.

5. If you experience errors running "PythonEndLogin.py" (Robinhood doesn't play very well with logins), run the file ON ITS OWN
   and input your username, password, and secret code when prompted. Assuming you have store_session still set to true, the problem
   should be fixed on all future logins. You may have to manually edit the .py file to get it working, this step was inconsistent at best
   in our testing.

6. (Optional but highly recommended) Every time a sell/buy order is processed, a .csv file is put into CryptoBot. You can import this file
    into a sheet program like Excel to better manage your portfolio's progress and track your holdings.
________________________________________________________________________________________________________________________________________________________________________

Things to Change (in order of priority):

1. System() calls are very prominent in the C++ end. This is obviously not very scalable (or safe, or efficient), and is what limits the program 
   to Windows at the moment. We had issues with other implementations, and did not have time to resolve the issues behind them.
   Embedding Python calls (https://docs.python.org/3/extending/embedding.html) and removing the system("CLS") calls in main
   should make CryptoBot much more friendly on other operating systems like Linux.

2. Login issues with "PythonEndLogin.py". We could not determine why it worked sometimes on some machines with little effort but introduced massive
   issues on others. Documentation at https://robin-stocks.readthedocs.io/en/latest/index.html.

3. Try catch error handling. This could probably be expanded on and improved on the C++ end.

4. Stack and heap usage optimization. Not a major priority, but a lighter build of CryptoBot would be nice.
________________________________________________________________________________________________________________________________________________________________________

Python End:

PythonEndBuy.py- manages the execution of buy orders, exports a .csv file when completed.
		 Called as a script through the C++ end, no logic involved.

PythonEndSell.py- manages the execution of sell orders, exports a .csv file when completed.
		  Called as a script through the C++ end, no logic involved.

PythonEndLogin.py- manages the login process, stores the login session for convinence afterwards.
		   Called as a script through the C++ end, no logic involved.

__________________________________________________________________________________________________________________________________________________________________________

C++ End:

CryptoBot.cpp- .cpp file for the CryptoBot class. Contains most of the logic behind getting prices
		and determining when to sell. Creates .txt files at times to pass information
		on to the Python end.

CryptoBot.h- header file for the CryptoBot.cpp file.

Portfolio.cpp- .cpp file for the CryptoPortfolio class. Creates a vector of CryptoBot objects that can then be
 		multithreaded through the threadedUpdate() function. More threads can be edited in, I put a hard
		cap at 4 threads to prevent performance issues.

Portfolio.h- header file for the Portfolio.cpp file.

Main.cpp- .cpp file mainly in charge of the console UI of the program. Calls PythonEndLogin.py to sign new users in.
	  Basic threaded error handling processed here through at_quick_exit().

___________________________________________________________________________________________________________________________________________________________________________

