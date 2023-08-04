#include <AsyncTCP.h>

#include "ESPAsyncWebServer.h"

#include <WiFi.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <U8g2lib.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/Picopixel.h>
#include <Fonts/FreeSerif9pt7b.h>
#include <Fonts/TomThumb.h>
#include <Fonts/Org_01.h>
#define VPack_1 36
#define VPack_2 39
#define VPack_3 34
#define THSense 13
#define OUT_Toggle 33
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


//WIT Logo bitmap
const unsigned char wit_logo [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xc0, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xc0, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xc0, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xc0, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xc0, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xc0, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xc0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xc0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xc0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xc0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xc0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xc0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xc0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1e, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x3e, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x3e, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x7e, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0xfe, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x01, 0xfe, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x03, 0xfe, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x07, 0xfe, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x07, 0xfe, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x0f, 0xfe, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xfe, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x3f, 0xfe, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x3f, 0xfe, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xfe, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf9, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<!-- CSS Contents -->
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { 
      font-size: 3.0rem; 
      background-color: #4287f5;
      color: white;
      text-shadow: #474747 3px 5px 2px;
    }
    body {
      background-color: #232933;
      color: white;
    }
    @media screen and (prefers-color-scheme: light) {
      body {
        background-color: white;
        color: black;
      }
    }
    p { 
      font-size: 3.0rem; 
    }
    pBody {
      font-size: 1.2rem;
      color: black;
    }
    .units { 
      font-size: 1.2rem; 
    }
    .dht-labels {
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 5px;
    }
    .collapsible {
      background-color: #4287f5;
      color: white;
      cursor: pointer;
      padding: 18px;
      min-width: 100%; <!-- this might cause issues on mobile -->
      border: none;
      text-align: left;
      outline: none;
      font-size: 15px;
    }
    .active, .collapsible:hover {
      background-color: #555;
    }
    .collapsible:after {
      content: '\002B';
      color: white;
      font-weight: bold;
      float: right;
      margin-left: 5px;
    }
    .active:after {
      content: "\2212";
    }
    .content {
      padding: 0 18px;
      max-height: 0;
      overflow: hidden;
      transition: max-height 0.5s ease-out;
      background-color: #f1f1f1;
    }
  </style>

</head>
<!-- HTML Contents -->
<body>
  <h2>RVBP<br>Dashboard</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="dht-labels">Temperature:</span> 
    <span id="temperature">%TEMPERATURE%</span>
    <sup class="units">&deg;F</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i> 
    <span class="dht-labels">Humidity:</span>
    <span id="humidity">%HUMIDITY%</span>
    <sup class="units">&percnt;</sup>
  </p>
  <p>
    <span class="dht-labels">Pack 1:</span>
    <span id="v1voltage">%V1VOLTAGE%</span>
    <sup class="units">V</sup>
  </p>
  <p>
    <span class="dht-labels">Pack 2:</span>
    <span id="v2voltage">%V2VOLTAGE%</span>
    <sup class="units">V</sup>
  </p>
  <p>
    <span class="dht-labels">Pack 3:</span>
    <span id="v3voltage">%V3VOLTAGE%</span>
    <sup class="units">V</sup>
  </p>
  <p>
    <span class="dht-labels">Total Voltage:</span>
    <span id="totalvoltage">%TOTALVOLTAGE%</span>
    <sup class="units">V</sup>
  </p>
  <p>
    <span class="dht-labels">Charge Percentage:</span>
    <span id="chargepercent">%CHARGEPERCENT%</span>
    <sup class="units">&percnt;</sup>
  </p>
  <span>
  <button class="collapsible">About</button>
  <div class="content">
    <pBody>
    The RVBP (Recycled Vape Battery Pack) project focuses on recycling lithium-ion batteries from disposable vaping devices to create a smart IoT USB battery pack.
     By refurbishing these batteries, we aim to reduce electronic waste and promote sustainability. The battery pack combines 15 recycled lithium-ion batteries,
      connecting 5 cells in series and arranging 3 packs of 5 cells in parallel (5S3P configuration), delivering enhanced capacity and voltage stability.
       Users can monitor real-time battery performance, including voltages, charge capacity, temperature, and humidity, through an intuitive web dashboard.
        RVBP strives to provide an eco-friendly and efficient power solution, contributing to a cleaner and greener environment.
    </pBody>
  </div>
  </span>
  <br>
  <span>
  <button class="collapsible">Quick Facts</button>
  <div class="content">
    <pBody>
    <b>Widespread Usage:</b> Lithium-ion batteries are the most commonly used rechargeable batteries in various applications, including smartphones, laptops, electric vehicles, and portable electronics. Their lightweight and high energy density make them a preferred choice for modern technology.<br>
    <b>Resource Intensive:</b> The production of lithium-ion batteries involves mining and processing scarce and valuable resources such as lithium, cobalt, and nickel. These mining activities can lead to environmental degradation and ecological disruption in the regions where these resources are extracted.<br>
    <b>Electronic Waste:</b> As the demand for lithium-ion batteries grows, so does the problem of electronic waste. Improper disposal or recycling of used batteries can lead to hazardous chemicals, including lithium and cobalt, leaching into the soil and water, causing environmental contamination.<br>
    <b>Energy-Intensive Recycling:</b> While recycling lithium-ion batteries is crucial for sustainability, the recycling process itself requires significant energy input. Energy-intensive methods used to recycle these batteries can potentially offset some of the environmental benefits.<br>
    <b>Transportation Challenges:</b> The transportation of lithium-ion batteries from manufacturers to end-users can contribute to carbon emissions, especially when dealing with large-scale electric vehicle batteries or bulk shipments.<br>
    <b>Fire Risk:</b> In rare cases, lithium-ion batteries can experience thermal runaway, leading to fires or explosions. Improper handling and disposal of damaged or defective batteries can exacerbate the risks of accidents.<br>
    <b>Sustainable Solutions:</b> To mitigate the environmental impact of lithium-ion batteries, efforts are being made to develop sustainable battery chemistries, recycling methods, and environmentally friendly materials sourcing.
        Research is ongoing to find alternatives to critical resources like cobalt, which will reduce the environmental burden of battery production.<br>
    <b>Extended Lifespan:</b> Extending the lifespan of lithium-ion batteries through proper care and maintenance can reduce the frequency of disposal and the associated environmental consequences.<br><br>
    In conclusion, while lithium-ion batteries have revolutionized modern technology and enabled numerous advancements, their widespread usage and improper disposal can have significant environmental implications.
        Emphasizing responsible manufacturing, recycling, and exploring greener alternatives are essential steps towards minimizing the impact of lithium-ion batteries on the environment.<br>
    </pBody>
  </div>
  </span>
  <br>

 <span>
  <button class="collapsible">GitHub Repo</button>
  <div class="content">
    <pBody>
      For more information about the project including design files, sources, and more, please visit our GitHub repository!
      <b>https://github.com/bogonissATWIT/RVBP</b><br>
      Our aim is to make the RVBP project <u>open source</u>, empowering others to leverage our work
      and maximize its positive impact on sustainability and battery recycling initiatives.<br>
    </pBody>
  </div>
  </span>
  <span>
  <button class="collapsible">Future Plans</button>
  <div class="content">
    <pBody>
      In the future, we envision expanding the RVBP (Recycled Vape Battery Pack) project with ambitious plans for hardware development and integration of additional peripherals.
      Our roadmap includes incorporating more sensors such as temperature/humidity sensors and flame sensors to enhance the monitoring capabilities and safety features of the battery pack.
       We also aim to integrate RVBP with popular smart home platforms like HomeAssistant and ESPHome, enabling seamless compatibility with a wide range of smart devices and automation systems. 
      Moreover, to make RVBP even more user-friendly and versatile, we plan to integrate with popular virtual assistants such as Alexa, Siri, and Google Home, allowing users to control and monitor the battery pack through voice commands.
       By embracing open-source principles, we are committed to fostering collaboration and innovation, ensuring that the RVBP project has a far-reaching and meaningful impact on sustainable energy solutions and eco-conscious practices.<br>
    </pBody>
  </div>
  </span>
  <button class="collapsible">User Manual</button>
    <div class="content">
      <pBody>
        To download the <b>user manual</b>, please visit the following url:<br>
        https://github.com/bogonissATWIT/RVBP/blob/main/Vape%20Recycling%20Battery%20Pack%20MANUAL%20(1).docx
      </pBody>
   </div>
  </span>
  <button class="collapsible">Credits</button>
  <div class="content">
    <pBody>
      Sam Bogonis, Matt Taylor, Aaron Lundgren<br>
      Advisor: Professor Saurav Basnet<br>
      Wentworth Institute of Technology 2023
    </pBody>
  </div>
  </span>
</body>
<!-- JavaScript Functions for Real-Time UI Data -->
<script>
  setInterval(function ( ) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("temperature").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/temperature", true);
    xhttp.send();
  }, 10000 ) ;
  setInterval(function ( ) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("humidity").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/humidity", true);
    xhttp.send();
  }, 10000 ) ;
  setInterval(function ( ) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("v1voltage").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/v1voltage", true);
    xhttp.send();
  }, 10000 ) ;
  setInterval(function ( ) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("v2voltage").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/v2voltage", true);
    xhttp.send();
  }, 10000 ) ;
  setInterval(function ( ) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("v3voltage").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/v3voltage", true);
    xhttp.send();
  }, 10000 ) ;
  setInterval(function ( ) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("totalvoltage").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/totalvoltage", true);
    xhttp.send();
  }, 10000 ) ;
  setInterval(function ( ) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("chargepercent").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/chargepercent", true);
    xhttp.send();
  }, 10000 ) ;
  var coll = document.getElementsByClassName("collapsible");
  var i;
  for (i = 0; i < coll.length; i++) {
    coll[i].addEventListener("click", function() {
      this.classList.toggle("active");
      var content = this.nextElementSibling;
      if (content.style.maxHeight){
        content.style.maxHeight = null;
      } else {
        content.style.maxHeight = content.scrollHeight + "px";
      } 
    });
  }
</script>
</html>)rawliteral";

// SSID & Password
const char* ssid = "RVBP-Connect";  // Enter your SSID here
const char* password = "123456789";  //Enter your Password here

// IP Address details
IPAddress local_ip(192, 168, 4, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

AsyncWebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)

//Display and DHT22 Setup
DHT DHT(THSense, DHT22); //Initalizes humid/temp sensor on pin 4 with make DHT22 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

String readDHTTemperature(){
  float t = DHT.readTemperature(true);
  if (isnan(t)) {
    return "--";
  }
  else{
    Serial.println(t);
    return String(t);
  }
}

String readDHTHumidity(){
  float h = DHT.readHumidity();
  if (isnan(h)) {
    return "--";
  }
  else{
    Serial.println(h);
    return String(h);
  }
}

String processor(const String& var) {
  const int V1 = 36;
  const int V2 = 39;
  const int V3 = 34;

  float Pack1 = (analogRead(V1) / 4095.0) * 21.00;
  float Pack2 = (analogRead(V2) / 4095.0) * 21.00;
  float Pack3 = (analogRead(V3) / 4095.0) * 21.00;

  Serial.println(var);
  
  if(var == "TEMPERATURE"){
    return readDHTTemperature();
  }
  else if(var == "HUMIDITY"){
    return readDHTHumidity();
  }
  else if(var == "V1VOLTAGE"){
    return (String)Pack1;
  }
  else if(var == "V2VOLTAGE"){
    return (String)Pack2;
  }
  else if(var == "V3VOLTAGE"){
    return (String)Pack3;
  }
  else if(var == "CHARGEPERCENT"){
    return (String)((((Pack1 + Pack2 + Pack3) / (21.00 * 3))) * 100.00);
  }
  else if(var == "TOTALVOLTAGE"){
    return (String)(Pack1 + Pack2 + Pack3);
  }
  return String();
}

void displayWITSplash() {
    display.clearDisplay();
      display.drawBitmap(0,0, wit_logo, 128, 64, WHITE);
    display.display();
}

void displayNameSplash() {
    display.clearDisplay();
      display.setTextColor(WHITE);
      display.setTextSize(1);
      display.setFont(&Org_01);
      display.setCursor(0, 10);
      display.setTextWrap(0);
      display.setCursor(32, 10);
      display.println("Recycled Vape");
      display.setTextWrap(0);
      display.setCursor(18, 17);
      display.println("Battery Pack V2.10");
      display.drawLine(17, 20, 110, 20, 1);
      display.setCursor(30, 35);
      display.setTextWrap(0);
      display.setCursor(36, 35);
      display.println("Sam Bogonis");
      display.setTextWrap(0);
      display.setCursor(36, 42);
      display.println("Matt Taylor");
      display.setTextWrap(0);
      display.setCursor(28, 49);
      display.println("Aaron Lundgren");
      display.drawRect(24, 28, 80, 25, 1);
   display.display();
}

void displayTH() {
    display.clearDisplay();
      display.setCursor(5, 10);
      display.setFont(&Org_01);
      display.setTextSize(2);
      display.print("IP:");
      display.setCursor(40, 10);
      display.print("192.168.4.1");
      display.setCursor(10, 32);
      display.print("T:");
      display.setCursor(50, 32);
      display.print(readDHTTemperature() + "F");
      display.setCursor(10, 55);
      display.print("H:");
      display.setCursor(50, 55);
      display.print(readDHTHumidity() + "%");
      display.drawLine(0, 16, 128, 16, 1);
      display.drawLine(0, 40, 128, 40, 1);
    display.display();
}

void displayPackVoltage (String V1,String V2,String V3) { //(String)(analogRead(VX))
    display.clearDisplay();
      display.setCursor(5, 15);
      display.setTextSize(2);
      display.print("P1:");
      display.setCursor(50, 15);
      display.print(V1 + "V");
      display.setCursor(5, 37);
      display.print("P2:");
      display.setCursor(50, 37);
      display.print(V2 + "V");
      display.setCursor(5, 58);
      display.print("P3:");
      display.setCursor(50, 58);
      display.print(V3 + "V");
      display.drawLine(0, 22, 128, 22, 1);
      display.drawLine(0, 44, 128, 44, 1);
    display.display();
}

void setup() {
  //Pinmode setup
  pinMode(VPack_1, INPUT);
  pinMode(VPack_2, INPUT);
  pinMode(VPack_3, INPUT);
  pinMode(THSense, INPUT);
  pinMode(OUT_Toggle, OUTPUT);
  digitalWrite(OUT_Toggle, HIGH);

  DHT.begin();
  Wire.begin(21,22);

  Serial.begin(115200);

  // Create SoftAP
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);

  Serial.print("Connect to My access point: ");
  Serial.println(ssid);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTTemperature().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTHumidity().c_str());
  });
 
  server.begin();
  Serial.println("HTTP server started");
  delay(100);

  //OLED Display setup
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
      Serial.println(F("SSD1306 allocation failed"));
      for(;;);
    }

  //Splash Screens
  delay(2000);
  displayNameSplash();
  delay(2000);
  displayWITSplash();
  delay(2000);

}

void loop() {
  delay(2000);
  displayTH();
  delay(2000);
  displayPackVoltage((String)((analogRead(VPack_1)/4095) * 21.0) , (String)((analogRead(VPack_1)/4095) * 21.0), (String)((analogRead(VPack_1)/4095) * 21.0));
}
