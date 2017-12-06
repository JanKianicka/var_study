/**
 * OK, lecture about Java script and programming in Visual Studio is done.
 * https://www.youtube.com/watch?v=zPHerhks2Vg
 * Java scrit in half an hour without JQuery
 */

function add(num1, num2) {
    return num1 + num2;
}

function get_titel() {
    return document.title;
}
/* */
var newItemCounter = 1;
var ourHeadline = document.getElementById("our_headline");
ourHeadline.innerHTML = "Test change";
var listItems = document.getElementById("our_list").getElementsByTagName("li");
var ourList = document.getElementById("our_list");
var ourButton = document.getElementById("our_button");

ourList.addEventListener("click", activateItem);


/*for (i = 0; i < listItems.length; i++) {
    listItems[i].innerHTML = "Modified";
    listItems[i].addEventListener("click", activateItem);
}*/

function activateItem(e) {
    if (e.target.nodeName == "LI") {
        ourHeadline.innerHTML = e.target.innerHTML;
        for (i = 0; i < e.target.parentNode.children.length; i++) {
            e.target.parentNode.children[i].classList.remove("mystyle");
        }
        e.target.classList.add("mystyle");
    }
}
/* function activateItem() {
    ("Click activated!");
    ourHeadline.innerHTML = this.innerHTML;
}
*/


ourButton.addEventListener("click", createNewItem);

function createNewItem() {
    ourList.innerHTML += "<li>Something new" + newItemCounter + "</li>";
    newItemCounter++;
}


/*
 * Continuation of the lesson learning object oriented programming in javascript
 * https://www.youtube.com/watch?v=rlLuL3jYLvA
 */

function person(name, favColor) {
    console.log("Hello, my name is " + name + " and my favorite color is " + favColor + ".");
}

person("John Doe", "blue");
person("Jane Smith", "green");

/*
 * We make object for John
 */

var Jon_obj = {
    name: "John_from_object",
    favoriteColor: "blue_from_object",
    greet: function () {
        console.log("Hello " + Jon_obj.name + "!");
    }
}

person(Jon_obj.name, Jon_obj.favoriteColor);
Jon_obj.greet();

/*
 * Using classes - class is created by 'function'
 */

function Person(fullName, favColor) {
    this.name = fullName;
    this.favoriteColor = favColor;
    this.greet = function() {
        console.log("Hello, my name is" + this.name + " and my favorite color is " + this.favoriteColor + ".");
    }
}

var John_from_class = new Person("John_from_class", "blue_from_class");
John_from_class.greet();

