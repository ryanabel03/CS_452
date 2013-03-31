function parseHeader(line) {
  //Do nothing for now
}

function parseLine(line) {
  chunks = line.split(" ");
  h = {};
  h["process"] = chunks[0];
  h["action"] = chunks[1];
  h["resource"] = chunks[2];

  return h;
}
