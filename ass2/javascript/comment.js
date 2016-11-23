// This javascript file contains function that respond when a user comments or replies to a post
var previous_reply_id = "";

// opens the reply box so the user can reply
function open_reply_box(reply_button){
	var reply_id = reply_button.id;
	if (reply_id != previous_reply_id){
		var reply_path = reply_button.name;
		var new_reply_box = document.createElement("div");
		console.log("Showing reply box");
		new_reply_box.setAttribute("class", "commentList");
		new_reply_box.innerHTML = "<input id=\"reply_box\" class=\"form-control col-md-8 add_comment\" type=\"text\" placeholder=\"Enter your reply\" />" +
                                  "<button class=\"reply_button btn btn-primary btn-xs\" name=\"" + reply_path + "\" onclick=\"add_reply(this)\">Add</button>";

		var commentBox = document.getElementById(reply_id);
		commentBox.parentNode.insertBefore(new_reply_box, commentBox.nextSibling);
		previous_reply_id = reply_id;
	}
}

// submits the send_comment form to the server
function add_comment(comment_button){
	console.log("Sending comment to cgi...");
	var comment_path = comment_button.name;
	var post_id = comment_button.id;
	var comment_box = document.getElementById("post_" + post_id);
	var comment = comment_box.value;
	var hidden_comment = document.getElementById("comment_to_send");
	var hidden_comment_path = document.getElementById("path_to_comment_reply");
	hidden_comment.value = comment;
	hidden_comment_path.value = comment_path;
	console.log("Comment: " + comment);
	console.log("Path: " + comment_path);
	var hidden_comment_form = document.getElementById("user_state");
	console.log(hidden_comment_form);
	hidden_comment_form.submit();
}

// submits the send_reply form to the server
function add_reply(reply_button){
	console.log("Sending reply to cgi...");
	var reply_path = reply_button.name;
	var reply_box = document.getElementById("reply_box");
	var reply = reply_box.value;
	var hidden_reply = document.getElementById("reply_to_send");
	var hidden_reply_path = document.getElementById("path_to_comment_reply");
	hidden_reply.value = reply;
	hidden_reply_path.value = reply_path;
	console.log("Reply: " + reply);
	console.log("Reply path: " + reply_path);
	var hidden_reply_form = document.getElementById("user_state");
	hidden_reply_form.submit();
}

// submits a user's post to the server
function add_post(){
	var hidden_post = document.getElementById("post_to_send");
	var big_post = document.getElementById("big_post_box");
	var post = big_post.value;
	hidden_post.value = post;
	var state_form = document.getElementById("user_state");
	state_form.submit();
}

function delete_post(button_clicked){
	var path_to_delete = button_clicked.name;
	var delete_form = document.getElementById("delete_path");
	delete_form.value = path_to_delete;
	var state_form = document.getElementById("user_state");
	state_form.submit();
}
