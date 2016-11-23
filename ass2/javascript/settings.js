// function that submits a form with the id of "settings"
function submit_form(){
    var form = document.getElementById("user_state");
    form.submit();
}

function set_updated_bool(bool_value){
    var details_updated_bool = document.getElementById("details_updated");
    details_updated_bool.value = bool_value;
}

// marks a flag that indicates that the user wants to update their details
function update_details(){
    var name = document.getElementById("full_name").value;
    var birthday = document.getElementById("birthday").value;
    var email_addr = document.getElementById("email").value;
    var home = document.getElementById("home").value;
    var program = document.getElementById("program").value;
    var about_me = document.getElementById("about_me").value;
    var courses = document.getElementById("courses").value;

    var name_form = document.getElementById("new_name");
    var birthday_form = document.getElementById("new_birthday");
    var email_form = document.getElementById("new_email");
    var home_form = document.getElementById("new_home");
    var program_form = document.getElementById("new_program");
    var about_me_form = document.getElementById("new_about_me");
    var courses_form = document.getElementById("new_courses");

    name_form.value = name;
    birthday_form.value = birthday;
    email_form.value = email_addr;
    home_form.value = home;
    program_form.value = program;
    about_me_form.value = about_me;
    courses_form.value = courses;

    console.log("About_me_form = " + about_me);
    if (contains_safe_html(about_me) == true){
        console.log("message is safe");
        set_updated_bool("true");
        submit_form();
    }

    else{
        var error_element = document.getElementById("about_me_error");
        error_element.style="color:red;";
    }
}

// determines if a message is safe
function contains_safe_html(message){
    // don't let user use script, img, link or html tags
    var unsafe_tags = /\<script\>|\<img|\<link|\<html/g;
    var is_safe = true;
    // if any unsafe tags are matched then return false
    if (unsafe_tags.exec(message)){
        is_safe = false;
    }

    return is_safe;
}

// marks a bool to suspend an account
function suspend_account(){
    console.log("Suspending account");
    var suspend_form = document.getElementById("suspend");
    suspend_form.value = "true";
    set_updated_bool("true");
    submit_form();
}

// marks a bool to delete the account
function delete_account(){
    console.log("Deleting account");
    var destroy_form = document.getElementById("destroy");
    destroy_form.value = "true";
    set_updated_bool("true");
    submit_form();
}

// changes the password for a user
function change_password(){
    console.log("Changing password");
    var password_form = document.getElementById("new_password");
    var new_password = document.getElementById("password").value;
    var new_password_confirm = document.getElementById("confirm_password").value;

    // error handling
    var error_message_element = document.getElementById("error");
    var error_message = "";

    // console.log("Old_pass = " + new_password + " confirm = " + new_password_confirm);

    // passwords do not match
    if (new_password != new_password_confirm){
        error_message = "Passwords do not match!";
        error_message_element.style = "color: red;";
        error_message_element.innerHTML = error_message;
    }

    //
    else if (new_password == new_password_confirm && new_password.length < 6){
        error_message = "Please enter a password with more than 6 characters!";
        error_message_element.style = "color: red;";
        error_message_element.innerHTML = error_message;
    }

    // new password entered correctly so submit the form
    else{
        password_form.value = new_password;
        set_updated_bool("true");
        submit_form();
    }
}

// this function gets called when the user changes their visibility settings
function select_privacy(){
    var privacy_setting = document.getElementById("privacy_setting").value;
    console.log("User changed their privacy to: " + privacy_setting);
    var privacy_form = document.getElementById("visibility");
    privacy_form.value = privacy_setting;
    set_updated_bool("true");
    submit_form();
}

// submits the form to upload a new profile picture
function upload_profile_pic(){
	var hidden_file_uploaded = document.getElementById("prof_image_uploaded");
	hidden_file_uploaded.value = "true";
    document.getElementById("upload_prof_img").submit();
}

function upload_back_pic(){
	var hidden_file_uploaded = document.getElementById("back_image_uploaded");
	hidden_file_uploaded.value = "true";
    document.getElementById("upload_back_img").submit();
}

// Grabbed from http://jsfiddle.net/LvsYc/
// previews the image before it gets uploaded
function readURL(input, img_id) {
    if (input.files && input.files[0]) {
        var reader = new FileReader();

        reader.onload = function (e) {
            document.getElementById(img_id).setAttribute('src', e.target.result);
        }

        reader.readAsDataURL(input.files[0]);
    }
}

function display_prof_pic(){
    var file_upload_object = document.getElementById("upload_image");
    readURL(file_upload_object, "profile_pic");
    // set_updated_bool("true");
}

function display_back_pic(){
    var file_upload_object = document.getElementById("upload_background");
    readURL(file_upload_object, "background_pic");
    // set_updated_bool("true");
}
