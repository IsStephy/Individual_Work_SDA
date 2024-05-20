from flask import Flask, render_template, request, redirect, url_for
import subprocess, os  # Import os module

# Define the base directory
BASE_DIR = os.path.dirname(os.path.abspath(__file__))

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/signup', methods=['GET', 'POST'])
def signup():
    if request.method == 'POST':
        name = request.form['Name']
        surname = request.form["Surname"]
        email = request.form['email'] 
        password = request.form['password']
        users_file_path = os.path.join(BASE_DIR, 'users.txt')  
        with open(users_file_path, 'a') as f:
            f.write(f'{name}:{surname}:{email}:{password}\n')
        return redirect(url_for('register')) 
    return render_template('signup.html')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        name = request.form['Name']
        surname = request.form['Surname']
        password = request.form['password']
        if validate_credentials(name, surname, password):
            return redirect(url_for('user_page', name=name, surname=surname))
        else:
            return "Invalid name/surname or password, please try again."
    return render_template('login.html')

@app.route('/user_page/<name>/<surname>')
def user_page(name, surname):
    result = subprocess.run(['./main'], capture_output=True, text=True, input=f'{name}\n{surname}\n')
    output = result.stdout
    return render_template('user_page.html', output=output)

@app.route('/register', methods=['GET', 'POST'])
def register():
    posts = ["Conducator", "Sef", "Superior", "Inalt","Mediu","Necalificat"] 
    if request.method == 'POST':
        name = request.form['name']
        surname = request.form['surname']
        date_of_birth = request.form['date_of_birth']
        post = request.form['post']
        stare = request.form['stare']
        before = request.form['before']
        after = request.form['after']
        payments = {year: request.form.get(f'payment_{year}', '0') for year in range(1999, 2023)}

        # Save the data to info.txt
        info_file_path = os.path.join(BASE_DIR, 'info.txt')  # Path to info.txt
        with open(info_file_path, 'a') as f:
            f.write(f"Name: {name}\nSurname: {surname}\nDate_of_Birth: {date_of_birth}\nCode: {"00001"}\n")
            f.write(f"Post: {post}\nStare: {stare}\nBefore: {before}\nAfter: {after}\nPayments:\n")
            for year, payment in payments.items():
                f.write(f"Year {year}: {payment}\n")
        return redirect(url_for('login'))
    return render_template('register.html', posts=posts)

def validate_credentials(name, surname, password):
    users_file_path = os.path.join(BASE_DIR, 'users.txt')  # Path to users.txt
    with open(users_file_path, 'r') as f:
        users = f.readlines()
    for user in users:
        stored_name, stored_surname, stored_email, stored_password = user.strip().split(':')
        if stored_name == name and stored_surname == surname and stored_password == password:
            return True
    return False

if __name__ == '__main__':
    app.run(debug=True, port=5001) 