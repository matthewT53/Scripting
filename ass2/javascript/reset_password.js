function reset_password(){
    var new_pass_input = document.getElementById("new_pass");
    var confirm_pass_input = document.getElementById("confirm_pass");
    var new_pass_form = document.getElementById("new_pass_form");
    var confirm_pass_form = document.getElementById("confirm_pass_form");
    var error_label = document.getElementById("error");

    // get the passwords that the user has entered
    var new_password = new_pass_input.value;
    var confirm_password = confirm_pass_input.value;
    var error_message = "";

    // check if both passwords match
    if (new_password != confirm_password){
        error_message = "Passwords do not match";
        error_label.style = "color: red;";
        error_label.innerHTML = error_message;
    }

    // check if the new password is long enough
    else if (new_password.length < 6){
        error_message = "Enter a password more than 6 characters";
        error_label.style = "color: red;";
        error_label.innerHTML = error_message;
    }

    // password looks good enough so jsut submit it
    else{
        var form = document.getElementById("reset_form");
        form.submit();
    }
}
