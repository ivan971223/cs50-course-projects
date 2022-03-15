# Food e-commerce website
#### Video Demo: (https://youtu.be/OK8oCfW-pLM)
#### Description: This is a food e-commerce website for the Oliver Restaurant, with using Flask to develop backend and using HTML, CSS and JavaScript for the frontend development.

## Functions
Users can order food from the restaurant online. They can choose food from menu and add to the cart. Then, they can go through the items at the cart and place an order. After order is placed, they can review their order history at the Order page.

## Backend development

>app.py

This file is where the backend server starts. It contains all the functions for registration, login, logout, menu, shopping cart and order history. It stores most of the data at the SQL database `shop.db`.

For function `index()`, it handles the post request from users when adding a food item to cart and gets the food_id and amount from users and store to list and dictionary in session. It also extract data from food SQL table for the display of menu at `index.html`.

For function `cart()`, it queries for the food items with the food_ids stored in session and displays them at the `cart.html`. When user send a request for removal of an item from the cart, the function will remove that particular id and number stored in session.

For function `order()`, it will insert the order data to the SQL database according to his/her user_id when user place their order. Then, it acquire the data from the database and displays the order details at `order.html` according to the order date and time.

For function `register()`, it gets the username and password from user request at the page `register.html` and stored the password hash to the database.

For function `login()`, it gets the input username and password from user request at the page `login.html` and extract the password hash from the database and compare to that input password for login permission using a library function from werkzeug.security.

For function `logout()`, it clears the session and return to `login.html`.

>helper.py

It includes some helper functions including a decorated function `login_required` for checking login session or status, a function `apology()` to display error message and a function `usd()` to convert the money value to usd format.


## Database

>database.py

This file is to open the database `shop.db` and create a table named users for storing username, password hash, a table named food for storing food id, food name and food price and a table named orders for storing order datetime, user id, food id, food name and food amount. Besides, it also read the csv file `shop.csv` and insert the food items to the database.

## Others

>requirement.txt

This text file stores all libraries that the application depends.


## Frontend development


## Templates

 >./templates

 This folders store all of the html files. `layout.html` is the file for the template of other file. It contains the head tag and navigation tag so that other html files can inherit those syntax from this template.

## Static files

>./static

This folder stores the CSS stylesheet files, food images and webstie icon.

## Sessions

>./flask_session

This folder save all the sessions of each user.

