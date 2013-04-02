count = 0;
total = 0;
file = null;

$ = jQuery


function setLines(data) {
  file = data.split("\n");
  console.log(file);
  total = file.length - 1;
}

function totalCount() {
  return total;
}

function loadFile() {

  $.ajax({
    url: "input.txt",
    async: false,
    type: "GET",
    dataType: "text"
  }).done(setLines);
}

function nextLine() {
  line = file[count];
  count++;
  return line;
}

function currentCount() {
  return count;
}
