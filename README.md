  <h1>Ardpix Library</h1>

  <p>The Ardupix library is designed to facilitate communication with Ardupilot-compatible systems using Arduino.</p>

  <h2>Table of Contents</h2>

  <ul>
    <li><a href="#installation">Installation</a></li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#examples">Examples</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
  </ul>

  <h2 id="installation">Installation</h2>

  <p>To use the Ardupix library in your Arduino project, follow these steps:</p>

  <ol>
    <li>Download the latest release from the <a href="https://github.com/SoorajR-ai/ArduPix">GitHub repository</a>.</li>
    <li>Extract the downloaded ZIP file.</li>
    <li>Copy the <code>ardupix</code> folder to your Arduino libraries directory.</li>
  </ol>

  <h2 id="usage">Usage</h2>

  <h3>Instantiating Ardupix</h3>

  <p>To use Ardupix in your Arduino sketch, you first need to include the library:</p>

  <pre><code>#include "ardupix.h"</code></pre>

  <p>Then, create an instance of the <code>ardupix</code> class, passing a <code>Stream</code> object (e.g., <code>Serial</code> for communication) to the constructor:</p>

  <pre><code>ardupix rover(&Serial);</code></pre>

  <h3>Running ardupix</h3>

  <p>In your <code>setup()</code> function, initialize the communication channel (e.g., <code>Serial</code>) and in your <code>loop()</code> function, call the <code>run()</code> method to handle incoming MAVLink messages and send heartbeats:</p>

  <pre><code>void setup() {
  Serial.begin(115200);
}

void loop() {
  rover.run();
}</code></pre>

  <h2 id="examples">Examples</h2>

  <h3>Heartbeat Example</h3>

  <pre><code>#include "ardupix.h"

ardupix rover(&Serial);

void setup() {
  Serial.begin(115200);
}

void loop() {
  rover.run();
}</code></pre>

  <p>This example initializes ardupix with the <code>Serial</code> communication channel and continuously runs the <code>ardupix::run()</code> method.</p>

  <h2 id="contributing">Contributing</h2>

  <p>If you want to contribute to ardupix, feel free to open issues or submit pull requests. Make sure to follow the <a href="CONTRIBUTING.md">contribution guidelines</a>.</p>

  <h2 id="license">License</h2>

  <p>This project is licensed under the <a href="LICENSE">MIT License</a>.</p>

</body>

