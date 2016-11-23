// function that gets called when the user clicks the search button
function get_search_results(){
    var search_bar = document.getElementById("search_bar");
    var data_to_search = search_bar.value;
    console.log("You searched for: " + data_to_search);
    var hidden_field_search = document.getElementById("search_for");
    hidden_field_search.value = data_to_search;

    // submit the form to the server to get the results
    document.getElementById("user_state").submit();
}

function click_results_mate(mateClicked){
    var zid = mateClicked.id;
    console.log("ZID is: " + zid);
    var fetchUserObject = document.getElementById("user_selected");
    fetchUserObject.value = zid;
    document.getElementById("user_state").submit();
}
