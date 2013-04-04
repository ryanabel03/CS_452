/*
* This group of functions is responsible for reading a file in and
* parsing it line by line.
*
*/

//Globals
count = 0;
total = 0;
file = null;

$ = jQuery


/*
* Split a file up into an array of lines
*/
function setLines(data) {
  file = data.split("\n");
  console.log(file);
  total = file.length - 1;
}


/*
* Get the total number of lines
*/
function totalCount() {
  return total;
}


/*
* Load a file using ajax
*/
function loadFile() {

  $.ajax({
    url: "input.txt",
    async: false,
    type: "GET",
    dataType: "text"
  }).done(setLines);
}


/*
* Get the next line in the file
*/
function nextLine() {
  line = file[count];
  count++;
  return line;
}

/*
* Get the current line number
*/
function currentCount() {
  return count;
}
