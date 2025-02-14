const char indexhtml[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>NanoEls H5</title>
  <style>
    body {
      font-family: Roboto, sans-serif;
      margin: 0 auto;
      max-width: 800px;
      padding: 20px;
      background-color: #f4f4f4;
    }
    h1, h2 {
      color: #333;
    }
    input, textarea {
      width: 100%;
    }
    #log {
      height: 200px;
      overflow-y: scroll;
      border: 1px solid #ccc;
      padding: 10px;
      background-color: #fff;
      margin-bottom: 20px;
    }
    #log p {
      padding: 0;
      margin: 0;
    }
    #command-container, #gcode-container {
      display: flex;
      align-items: center;
      margin-bottom: 20px;
    }
    #command {
      flex: 1;
      padding: 10px;
      border: 1px solid #ccc;
      border-radius: 4px;
      margin-right: 10px;
    }
    button {
      padding: 10px 20px;
      border: none;
      border-radius: 4px;
      cursor: pointer;
      color: #fff;
      background-color: #218838;
    }
    button:hover {
      background-color: #105b21;
    }
    #gcode-list {
      margin-top: 20px;
      background-color: #fff;
      padding: 0;
      border: 1px solid #ccc;
      border-radius: 4px;
    }
    #gcode-name, #gcode-content {
      box-sizing: border-box;
      padding: 10px;
      border: 1px solid #ccc;
      border-radius: 4px;
      margin-bottom: 10px;
    }
    #gcode-content {
      height: 200px;
      resize: vertical;
    }
    .remove-icon {
      cursor: pointer;
      color: #dc3545;
      font-size: 16px;
    }
    .remove-icon:hover {
      color: #c82333;
    }
    button.disabled {
      background-color: #ccc;
      cursor: not-allowed;
    }
    button.disabled:hover {
      background-color: #ccc;
    }
    .gcode-row {
      display: flex;
      justify-content: space-between;
      align-items: center;
      padding: 10px;
      cursor: pointer;
    }
    .gcode-row:hover {
      background-color: #f0f0f0;
    }
  </style>
</head>
<body>
  <h1>NanoEls H5</h1>
  <p>This Web UI is served from your NanoEls controller memory. It doesn't need Internet connection. Anyone on your local network has access to it.</p>
  <p>It communicates with NanoEls in 2 ways. For saving, loading and removing stored GCode files it uses HTTP calls that can succeed or fail individually and it doesn't
    affect the realtime communication with the NanoEls controller. For realtime communication it uses WebSocket that is always open and can be used to send commands to the controller and receive responses from it.
  </p>
  <p>Realtime log can also be used for debugging since serial communication with NanoEls can be problematic as that channel is used by the screen.</p>
  <h2>Stored GCode</h2>
  <div id="gcode-list"></div>
  <h2>Add GCode</h2>
  <p>You can generate suitable GCode using <a href="https://kachurovskiy.com/lathecode/" target="_blank">lathecode</a> by uploading STL model of the part
    and specifying other parameters like tool and stock diameter.</p>
  <input type="text" id="gcode-name" placeholder="GCode name" required minlength="2">
  <textarea id="gcode-content" placeholder="GCode content" required minlength="2"></textarea>
  <button id="add-gcode">Save</button>

  <h2>WebSocket realtime communication</h2>
  <div id="log"></div>
  <div id="command-container">
    <input type="text" id="command" placeholder="Enter command" value="?" minlength="1" required>
    <button id="send">Send</button>
  </div>
  <p>Supported websocket commands:</p>
  <ul>
    <li><code>?</code> requests controller status</li>
    <li><code>=20</code> send key code 20 as if it's pressed on the keyboard</li>
    <li><code>!</code> turns the controller off</li>
    <li><code>~</code> turns the controller on</li>
    <li><code>""</code> removes all GCode</li>
  </ul>

  <script>
    const log = document.getElementById('log');
    const commandInput = document.getElementById('command');
    const sendButton = document.getElementById('send');
    const gcodeList = document.getElementById('gcode-list');
    const gcodeNameInput = document.getElementById('gcode-name');
    const gcodeContentInput = document.getElementById('gcode-content');
    const addGcodeButton = document.getElementById('add-gcode');

    const ws = new WebSocket(`ws://${window.location.host.split(':')[0]}:81`);

    ws.onopen = () => {
      logMessage('Connected to server');
    };

    ws.onmessage = (event) => {
      logMessage('Received: ' + event.data);
    };

    ws.onclose = () => {
      logMessage('Disconnected from server');
    };

    function updateButtonStates() {
      sendButton.disabled = commandInput.value.trim().length < 1;
      addGcodeButton.disabled = gcodeNameInput.value.trim().length < 2 || gcodeContentInput.value.trim().length < 2;
      sendButton.classList.toggle('disabled', sendButton.disabled);
      addGcodeButton.classList.toggle('disabled', addGcodeButton.disabled);
    }

    commandInput.addEventListener('input', updateButtonStates);
    gcodeNameInput.addEventListener('input', updateButtonStates);
    gcodeContentInput.addEventListener('input', updateButtonStates);

    document.addEventListener('DOMContentLoaded', updateButtonStates);

    function send() {
      const command = commandInput.value.trim();
      if (command) {
        logMessage('Sent: ' + command);
        ws.send(command);
        commandInput.value = '';
        updateButtonStates();
      }
    }

    commandInput.addEventListener('keydown', (event) => {
      if (event.key === 'Enter') send();
    });

    sendButton.addEventListener('click', () => {
      send();
    });

    addGcodeButton.addEventListener('click', () => {
      const name = gcodeNameInput.value.trim();
      const content = gcodeContentInput.value.trim();
      if (name && content) {
        fetch('/gcode/add', {
          method: 'POST',
          headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
          body: new URLSearchParams({ name, gcode: content })
        })
        .then(response => response.text())
        .then(data => {
          logMessage(data);
          listGcodes();
          gcodeNameInput.value = '';
          gcodeContentInput.value = '';
          updateButtonStates();
        });
      }
    });

    function listGcodes() {
      fetch('/gcode/list')
        .then(response => response.text())
        .then(data => {
          gcodeList.innerHTML = '';
          if (data) {
            data.split('\n').map(g => g.trim()).filter(g => !!g).forEach(gcode => {
              const row = document.createElement('div');
              row.className = 'gcode-row';
              row.dataset.name = gcode;
              row.innerHTML = `
                <span class="gcode-item" data-name="${gcode}">${gcode}</span>
                <span class="remove-icon" data-name="${gcode}">&times;</span>
              `;
              row.addEventListener('click', (event) => {
                loadGcode(event.target.dataset.name);
              });
              row.title = 'Click to load G-code';
              gcodeList.appendChild(row);
            });
            document.querySelectorAll('.remove-icon').forEach(icon => {
              icon.title = 'Click to remove G-code';
              icon.addEventListener('click', (event) => {
                const name = event.target.getAttribute('data-name');
                removeGcode(name);
              });
            });
          } else {
            gcodeList.innerHTML = 'No G-code stored';
          }
        });
    }

    function loadGcode(name) {
      fetch(`/gcode/get?name=${encodeURIComponent(name)}`)
        .then(response => response.text())
        .then(data => {
          gcodeNameInput.value = name;
          gcodeContentInput.value = data;
          updateButtonStates();
        });
    }

    function removeGcode(name) {
      fetch('/gcode/remove', {
        method: 'POST',
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
        body: new URLSearchParams({ name })
      })
      .then(response => response.text())
      .then(data => {
        logMessage(data);
        listGcodes();
      });
    }

    function logMessage(message) {
      const p = document.createElement('p');
      p.textContent = message;
      log.appendChild(p);
      log.scrollTop = log.scrollHeight;
    }

    listGcodes();
  </script>
</body>
</html>
)rawliteral";
