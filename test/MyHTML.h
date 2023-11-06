#ifndef MYHTML_H
#define MYHTML_H

const char body[] PROGMEM = R"===(
<!DOCTYPE html>
<html>
  <body>
    <input type="range" id="myRange" min="0" max="100" oninput="updateValue(this.value)"> Value: <span id="demo"></span>
    <button id="forwardBtn" onclick="setDirection('forward')">Forward</button>
    <button id="backwardBtn" onclick="setDirection('backward')">Backward</button>
    <script>
      window.onload = function() {
        getDataAndDisplay();
      }

      function updateValue(value) {
        document.getElementById("demo").innerHTML = value;
        sendData(value);
      }

      function setDirection(direction) {
        sendDataDirection(direction);
      }

      function sendData(value) {
        var xhr = new XMLHttpRequest();
        xhr.open("GET", "/set_speed?speed=" + value, true);
        xhr.send();
      }

      function sendDataDirection(direction) {
        var xhr = new XMLHttpRequest();
        xhr.open("GET", "/set_direction?dir=" + direction, true);
        xhr.send();
      }

      function getDataAndDisplay() {
        var xhr = new XMLHttpRequest();
        xhr.open("GET", "/get_value", true);
        xhr.onreadystatechange = function() {
          if (xhr.readyState == 4 && xhr.status == 200) {
            var value = xhr.responseText;
            document.getElementById("demo").innerHTML = value;
            document.getElementById("myRange").value = value;
          }
        };
        xhr.send();
      }
    </script>
  </body>
</html>
)===";

#endif // MYHTML_H
