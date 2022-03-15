# Food e-commerce website
#### Video Demo: (https://youtu.be/OK8oCfW-pLM)
#### Description: This is a food e-commerce website for the Oliver Restaurant, with using Flask to develop backend and using HTML, CSS and JavaScript for the frontend development.

## Functions
Users can order food from the restaurant online. They can choose food from menu and add to the cart. Then, they can go through the items at the cart and place an order. After order is placed, they can review their order history at the Order page.

>app.py

This file is where the backend server starts. It contains all the functions for registration, login, logout, menu, shopping cart and order history. For function `index()`, it handles the post request from users when adding a food item to cart and gets the food_id and amount from users and store to list and dictionary in session. It also extract data from food SQL table for the display of menu. For function `cart`, it handles post request from users 

