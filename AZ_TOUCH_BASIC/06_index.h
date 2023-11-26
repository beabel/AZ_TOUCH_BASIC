//html for web pages
const char MAIN_page[] PROGMEM = R"=====(
<html>
<head>
<meta http-equiv='content-type' content='text/html; charset=UTF-8'>
<meta name='viewport' content='width=320' />
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
<link rel="stylesheet" href="//code.jquery.com/ui/1.12.1/themes/base/jquery-ui.min.css">
<script src="https://code.jquery.com/ui/1.12.1/jquery-ui.min.js"></script>
<link rel="stylesheet" href="//use.fontawesome.com/releases/v5.0.7/css/all.css">
<script>
$(document).ready(function() {
  $("#tabs").tabs();
  getSSID();
  $("#btn_save").click(saveSSID);
  $("#btn_reset").click(restartHost);        
});

function getSSID() {
    $.ajax({
        type:"GET",
        url:"/cmd/getaccess",
        data:{},
        success: function(data){
            const parts = data.split("\n");
            $("#ssid_input").val(parts[0]);
            $("#pkey_input").val(parts[1]);
            $("#ntp_input").val(parts[2]);
        }
    });
}

function saveSSID() {
  $.ajax({
      type:"GET",
      url:"/cmd/setaccess",
      data:{"ssid":$("#ssid_input").val(),"pkey":$("#pkey_input").val(),"ntp":$("#ntp_input").val()},
      success: function(data){
          alert(data);
      }
  });
}

function restartHost() {
    $.ajax({
        type:"POST",
        url:"/cmd/restart",
        data:{},
    });
}
</script>
<style>
body {
    width:300px;
    background-color: silver;
}
label { 
  display: inline-block;
  margin-top: 5px;
  width: 100%;
  float: left;  
}
button {
    margin: 3px;
    height: 2.0em;    
}
input {
  width:100%;
}
</style>
</head>
<body>
<h1>Web AZ-Touch</h1>

<div id="tabs">
    <ul>
        <li><a href="#wlan"><i class="fa fa-wifi"></i></a></li>
    </ul>      
    <div id="wlan">
      <label>SSID:
        <input id="ssid_input" />
      </label>
      <br />
      <label>PKEY:
        <input id="pkey_input" type="password"/>
      </label>
      <br />
      <label>NTP:
        <input id="ntp_input" />
      </label>
      <br />
      <div align="center">
        <button id="btn_save" type="button">speichern</button>
        <button id="btn_reset" type="button">Neustart</button>
      </div>
    </div>
</div>
</body>
</html>
)=====";

//*****************************************************************************************************************
const char CONFIG_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta http-equiv='content-type' content='text/html; charset=UTF-8'>
<meta name='viewport' content='width=320' />
<style>
body {
  width:300px;
  font-family:arial;
}
button {
  width:110px;
  background-color:silver;
  border-radius:10px;
}
.theme {
  background-color:cadetblue;
  padding:10px;
  border-radius: 10px;
  border: 2px solid silver;
}
.confpane {
  width:280px;
  height:75px;
}
.txtinput {
  position:absolute;
  left:90px;
  width:200px;
}
.label {
  color:white;
  font-family:arial;
}
</style>
</head>
<body>
<h1 style="text-align:center;">Web AZ-Touch</h1>
<form>
    <div class="confpane theme">
        <div>
            <span class="label">SSID:</span>
            <input name="conf_ssid" class="txtinput"/>
        </div>
        <div style="padding-top:10px;">
            <span class="label">PKEY:</span>
            <input name="conf_pkey" class="txtinput" type="password"/>
        </div>
        <div style="padding-top:10px;text-align:center">
            <button type="submit" name="reset">senden + Neustart</button>
        </div>
    </div>
</form>
</body>
</html>
)=====";
