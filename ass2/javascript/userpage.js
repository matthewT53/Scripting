// this function sets the value of the user_selected hiddden input when a mate is clicked
function mate_clicked(mate){
    var zID = mate.value;
    console.log("Mate's value: " + zID);
    var inputUserSelected = document.getElementById("user_selected");
    inputUserSelected.value = zID;

    // submit the page to get the user's mate's page
    document.getElementById("user_state").submit();
}

// adds a user as a mate
function add_mate(){
    var hidden_action = document.getElementById("action");
    hidden_action.value = "add";
    var user_state_form = document.getElementById("user_state");
    user_state_form.submit();
}

// removes a mate from the mate list
function remove_mate(){
    var hidden_action = document.getElementById("action");
    hidden_action.value = "remove";
    var user_state_form = document.getElementById("user_state");
    user_state_form.submit();
}

// changes the currnet page the uer is viewing depending on page selection
function change_page(navbar_button){
    var next_page = navbar_button.value;
    console.log("Next page: " + next_page);
    var current_page_form = document.getElementById("current_page");
    current_page_form.value = next_page;
    document.getElementById("user_state").submit();
}

// code to control pagination
var current_page_num = 1; // keeps track of the current page
function previous_page(){
    var page_num = current_page_num - 1;
    // prevent the user from going out of bounds
    if (page_num >= 1){
        var page_element = document.getElementById("page_" + current_page_num);
        page_element.style="display: none;";
        page_element = document.getElementById("page_" + page_num);
        page_element.style = "";
        current_page_num--;
    }
}

function next_page(){
    var page_num = current_page_num + 1;
    var max = document.getElementById("max_page").value;
    // prevent the user from going out of bounds
    if (page_num <= max){
        var page_element = document.getElementById("page_" + current_page_num);
        page_element.style="display: none;";
        page_element = document.getElementById("page_" + page_num);
        page_element.style = "";
        current_page_num++;
    }
}
