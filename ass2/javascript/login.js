function login(){
    var username_object = document.getElementById("uLogin");
    var password_object = document.getElementById("uPassword");

    // get the values from both the objects
    var username_value = username_object.value;
    var password_value = password_object.value;
    var password_hashed = Sha256.hash(password_value);

    // get the hidden field objects
    var hidden_username = document.getElementById("uid");
    var hidden_password = document.getElementById("pwd");

    // set these values in the hidden fields
    hidden_username.value = username_value;
    hidden_password.value = password_hashed; // will hash this later

    // user hasn't supplied info for a field
    if (username_value == "" || password_value == ""){
        var error_message_element = document.getElementById("error");
        var message = "";
        if (username_value == ""){
            message = "Please provide your username";
        }

        else if (password_value == ""){
            message = "Please provide your password";
        }
        error_message_element.style = "color: red;";
        error_message_element.innerHTML = message;
    }

    else{
        // submit this form
        document.getElementById("login_form").submit();
    }
}

function logout(){
    var logged_in_hidden = document.getElementById("logged_in");
    logged_in_hidden.value = 0;
    var user_state_form = document.getElementById("user_state");
    user_state_form.submit();
}

// click "sign up" on login screen
function click_create_acc(){
    console.log("Creating a new account");
    var form_action = document.getElementById("welcome_page_action");
    form_action.value = "sign_up";
    var form = document.getElementById("login_form");
    form.submit();
}

function forgot_password(){
    console.log("user forgot their password");
    var form_action = document.getElementById("welcome_page_action");
    form_action.value = "forgot";
    var form = document.getElementById("login_form");
    form.submit();
}

function submit_reset_password(){
    console.log("Submitting form with email to server");
    var email_address_hidden = document.getElementById("email_address");
    var email_address_box = document.getElementById("email_address_box");
    var email_addr = email_address_box.value;
    email_address_hidden.value = email_addr;
	console.log("Email address:" + email_addr);
    var form = document.getElementById("login_form");
    form.submit();
}

// click "Sign Up" on sign up screen
function signup(){
    // get elements from the form we will submit
    var form_zid = document.getElementById("zid_form");
    var form_email = document.getElementById("email_form");
    var form_password = document.getElementById("password_form");
    var form_confirm = document.getElementById("confirm_form");
    var form_name = document.getElementById("name_form");
    var form_birthday = document.getElementById("birthday_form");
    var form_home = document.getElementById("home_form");

    // get the information the user entered
    var zid = document.getElementById("zid").value;
    var email = document.getElementById("email").value;
    var password = document.getElementById("password").value;
    var confirm = document.getElementById("confirm").value;
    var birthday = document.getElementById("birthday").value;
    var name = document.getElementById("name").value;
    var home = document.getElementById("home").value;

    var hashed_password = Sha256.hash(password);
    var hashed_confirm = Sha256.hash(confirm);

    form_zid.value = zid;
    form_email.value = email;
    form_password.value = hashed_password;
    form_confirm.value = hashed_confirm;
    form_name.value = name;
    form_birthday.value = birthday;
    form_home.value = home;

    // find any errors the user has made filling in the form
    var message = "";
    if (password != confirm){
        message = "Passwords do not match";
    }

    if (zid == "" || email == "" || password == "" || confirm == "" || name == "" || birthday == "" || home == ""){
        message = "One or more fields are missing";
    }

    if (message != ""){
        var error_message_element = document.getElementById("error");
        error_message_element.style = "color: red;";
        error_message_element.innerHTML = message;
    }

    else{
        // get the form and submit
        var form = document.getElementById("signup_form");
        // don't let user submit if there are errors
        form.submit();
    }
}
