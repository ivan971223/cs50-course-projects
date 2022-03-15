# Food e-commerce website
#### Video Demo: (https://youtu.be/OK8oCfW-pLM)
#### Description: This is a food e-commerce website for the Oliver Restaurant, with using Flask to develop backend and using HTML, CSS and JavaScript for the frontend development.

## Functions
Users can order food from the restaurant online. They can choose food from menu and add to the cart. Then, they can go through the items at the cart and place an order. After order is placed, they can review their order history at the Order page.

>app.py

This file is where the backend server starts. It contains all the functions for registration, login, logout, menu, shopping cart and order history.

```
@app.route("/", methods=["GET", "POST"])
@login_required
def index():

    if "cart_item" not in session:
        session["cart_item"] = []
    if "cart" not in session:
        session["cart"] = {}

    if request.method == "POST":
        id = request.form.get("id")
        number = int(request.form.get("number"))
        if id and number > 0:
            session["cart_item"].append(id)
            session["cart"][f'{id}'] = number
            foods = db.execute("SELECT id, name, price FROM food")
            return render_template("index.html", foods=foods, is_added=True)

    foods = db.execute("SELECT id, name, price FROM food")
    return render_template("index.html", foods=foods, is_added=False)
```
>index()
